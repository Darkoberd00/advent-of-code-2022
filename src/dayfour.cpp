//
// Created by Phil on 04.12.2022.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using std::cout;
using std::stringstream;
using std::endl;
using std::ifstream;
using std::string;
using std::to_string;
using std::vector;

int day = 4;

vector<string> split (const string& s, const char& delimiter);

string migrade(int a, int b);

bool fullcontains(int start_1, int start_2, int end_1, int end_2);
bool overlab(int start_1, int start_2, int end_1, int end_2);

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

    // TODO: code
    string line;
    int fully_contains{0};
    int overlab_int{0};

    while(getline(file, line)){
        line = line.substr(0, line.size()-1);

        vector<string> v = split(line, ',');

        vector<string> v2 = split(v[0], '-');
        vector<string> v3 = split(v[1], '-');

        int start_teil_1 = std::stoi(v2[0]);
        int end_teil_1 = std::stoi(v2[1]);

        int start_teil_2 = std::stoi(v3[0]);
        int end_teil_2 = std::stoi(v3[1]);

        string aussehen_1 = migrade(start_teil_1, end_teil_1);
        string aussehen_2 = migrade(start_teil_2, end_teil_2);

        bool b= fullcontains(start_teil_1, start_teil_2, end_teil_1, end_teil_2);
        bool b_2 = overlab(start_teil_1, start_teil_2, end_teil_1, end_teil_2);

        if(b){
            fully_contains++;
        }
        if(b_2){
            overlab_int++;
        }

        cout << aussehen_1 << " " << v[0] << endl << aussehen_2 << " " << v[1] << endl << " fully contains = " << b << " overlab = " << b_2 << endl << endl;
    }

    cout << "Ergebnis: " << fully_contains << endl;
    cout << "Ergebnis_2: " << overlab_int << endl;

    cout << endl << endl << "--------------" << "Day " << day << "--------------" << endl << endl;
    return 0;
}

bool fullcontains(int start_1, int start_2, int end_1, int end_2) {
    if(start_1 >= start_2){
        if(end_1 <= end_2){
            return true;
        }
    }
    if(start_2 >= start_1){
        if(end_2 <= end_1){
            return true;
        }
    }

    return false;
}

bool overlab(int start_1, int start_2, int end_1, int end_2) {
    bool b{false};

    for (int i = start_1; i <= end_1; ++i) {
        if(i>= start_2 && i <= end_2){
            b = true;
            continue;
        }
        b = false;
    }

    if(!b){
        for (int i = start_2; i <= end_2; ++i) {
            if(i>= start_1 && i <= end_1){
                b = true;
                continue;
            }
            b = false;
        }
    }

    return b;
}

string migrade(int a, int b) {
    string s;
    for (int i = 1; i <= 100; ++i) {
        if(i>=a && i<=b){
            s += std::to_string(i);
            continue;
        }
        s += ".";
    }

    return s;
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
