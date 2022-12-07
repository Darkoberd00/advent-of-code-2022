//
// Created by Phil on 06.12.2022.
//
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <tuple>
#include <algorithm>

using std::tuple;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::to_string;
using std::vector;
using std::stringstream;
using std::unique_ptr;
using std::min;

int day = 7;

struct File{
    string name;
    long size;
};

struct Directory{
    string name;
    vector<unique_ptr<Directory>> dirs;
    vector<unique_ptr<File>> files;
    Directory * parent;
    long size;
};

void output(Directory * main_dir, int level);
vector<string> split (const string& s, const char& delimiter);
long update_sizes(Directory * main_dir);
tuple<long, long> count_dirs_lte_threshold(Directory * main_dir, long threshold);
long find_directory_gte(Directory * main_dir, long threshold);

int main() {
    cout << endl << endl << "--------------" << "Day " << day << "--------------" << endl << endl;

    ifstream file;
    //string filename{"../input/test.txt"};
    string filename{"../input/day" + to_string(day) + ".txt"};
    file.open(filename);

    cout << endl << "Input: " << filename << endl << endl;

    if(!file.is_open()){
        std::cerr << "Datei beim Oeffnen der Datei " << filename << endl;
        return 1;
    }

    std::unique_ptr<Directory> file_system = std::make_unique<Directory>();
    file_system->name = '/';
    file_system->parent = file_system.get();
    auto current = file_system.get();

    string line;
    while (getline(file, line)) {
        if(line.ends_with('\r')) line = line.substr(0, line.size()-1);
        cout << line << endl;

        vector<string> v = split(line, ' ');

        if(v[0] == "$"){
            if(v[1] == "cd"){
                if(v[2] == "/"){
                    current = file_system.get();
                } else if(v[2] == ".."){
                    current = current->parent;
                } else {
                    bool found = false;
                    for (const auto& dir : current->dirs) {
                        if (dir->name == v[2]) {
                            found = true;
                            current = dir.get();
                            break;
                        }
                    }
                    if(!found){
                        current->dirs.emplace_back();
                        current->dirs.back()->name = v[2];
                        current->dirs.back()->parent = current;
                        current = current->dirs.back().get();
                    }

                }
            } else if(v[1] == "ls"){
                continue;
            }
        } else if(v[0] == "dir"){
            bool found = false;
            for (const auto& dir : current->dirs) {
                if (dir->name == v[1]) {
                    found = true;
                }
            }
            if(!found){
                current->dirs.push_back(std::make_unique<Directory>());
                current->dirs.back()->parent = current;
                current->dirs.back()->name = v[1];
            }
        } else {
            long size = std::stol(v[0]);
            current->files.push_back(std::make_unique<File>());
            current->files.back()->size = size;
            current->files.back()->name = v[1];
        }
    }

    cout << "dir-tree: " << endl;
    output(file_system.get(), 0);
    update_sizes(file_system.get());

    const long threshold = 100000;
    auto [count, sum] = count_dirs_lte_threshold(file_system.get(), threshold);

    if (file_system->size <= threshold) {
        count +=  1;
        sum += file_system->size;
    }

    cout << "Ergebnis: " << sum << endl;

    const long available = 70000000 - file_system->size;
    const long required = 30000000 - available;

    if (required <= 0) return 0;

    long ergebnis_2 = find_directory_gte(file_system.get(), required);
    cout << "Ergebnis_2: " << ergebnis_2 << endl;

    cout << endl << endl << "--------------" << "Day " << day << "--------------" << endl << endl;
    return 0;
}

vector<string> split (const string& s, const char& delimiter) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delimiter)) {
        result.push_back (item);
    }

    return result;
}

void output(Directory * main_dir, int level) {
    for (int i = 0; i < level; i++) {
        cout << "  ";
    }
    cout << "- " << main_dir->name << "(dir)" << '\n';
    for (const auto& dir : main_dir->dirs) {
        output(dir.get(), level + 1);
    }
    for (const auto& file : main_dir->files) {
        for (int i = 0; i < level+1; i++) {
            cout << "  ";
        }
        cout << "- " << file->name << "(file, size=" << file->size << ')' << '\n';
    }
}

long update_sizes(Directory * main_dir) {
    for (const auto& dir : main_dir->dirs) {
        main_dir->size += update_sizes(dir.get());
    }
    for (const auto& file : main_dir->files) {
        main_dir->size += file->size;
    }
    return main_dir->size;
}

tuple<long, long> count_dirs_lte_threshold(Directory * main_dir, long threshold) {
    long sum = 0;
    long count = 0;
    for (const auto& dir : main_dir->dirs) {
        if (dir->size <= threshold) {
            std::cout << dir->name << '\n';
            count++;
            sum += dir->size;
        }
        const auto ans = count_dirs_lte_threshold(dir.get(), threshold);
        count += std::get<0>(ans);
        sum += std::get<1>(ans);
    }
    return {count, sum};
}

long find_directory_gte(Directory * main_dir, long threshold) {
    auto min = main_dir->size;
    for (const auto& dir : main_dir->dirs) {
        if (dir->size > threshold) {
            const auto min_above_thresh = find_directory_gte(dir.get(), threshold);
            min = std::min(min, min_above_thresh);
        }
    }
    return min;
}
