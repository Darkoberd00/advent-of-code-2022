//
// Created by Phil on 05.12.2022.
//
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::to_string;
using std::list;

int day = 6;

int find_marker(const string& input, int size);

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

    string line;
    string s;
    while (getline(file, line)){
        if(line.ends_with('\r')){
            line = line.substr(0, line.size()-1);
        }
        s += line;
    }

    cout << "String: " << s << endl;

    cout << "Ergebnis: " << find_marker(s, 4) << endl;
    cout << "Ergebnis: " << find_marker(s, 14) << endl;
    cout << "Ergebnis: " << find_marker(s, 10) << endl;

    cout << endl << endl << "--------------" << "Day " << day << "--------------" << endl << endl;
    return 0;
}

int find_marker(const string& input, int size) {
    list<char> l;
    int ergebnis;
    for(char c: input){
        if(l.size() == size){
            break;
        }
        while (std::find(l.begin(), l.end(), c) != l.end()){
            l.pop_front();
        }
        l.push_back(c);
        ergebnis++;
    }
    if(l.empty() or l.size() != size){
        return 0;
    }
    return ergebnis;
}
