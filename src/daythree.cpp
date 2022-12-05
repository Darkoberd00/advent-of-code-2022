//
// Created by Phil on 03.12.2022.
//
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::map;
using std::string;
using std::vector;
using std::to_string;

int day = 3;

map<char, int> m{
        {'a', 1},
        {'b', 2},
        {'c', 3},
        {'d', 4},
        {'e', 5},
        {'f', 6},
        {'g', 7},
        {'h', 8},
        {'i', 9},
        {'j', 10},
        {'k', 11},
        {'l', 12},
        {'m', 13},
        {'n', 14},
        {'o', 15},
        {'p', 16},
        {'q', 17},
        {'r', 18},
        {'s', 19},
        {'t', 20},
        {'u', 21},
        {'v', 22},
        {'w', 23},
        {'x', 24},
        {'y', 25},
        {'z', 26},
        {'A', 27},
        {'B', 28},
        {'C', 29},
        {'D', 30},
        {'E', 31},
        {'F', 32},
        {'G', 33},
        {'H', 34},
        {'I', 35},
        {'J', 36},
        {'K', 37},
        {'L', 38},
        {'M', 39},
        {'N', 40},
        {'O', 41},
        {'P', 42},
        {'Q', 43},
        {'R', 44},
        {'S', 45},
        {'T', 46},
        {'U', 47},
        {'V', 48},
        {'W', 49},
        {'X', 50},
        {'Y', 51},
        {'Z', 52}
};

char containsborth(string a,string b);
char containsborth(string a,string b, string c);

int main() {
    cout << endl << endl << "--------------" << "Day " << day << "--------------" << endl << endl;

    vector<string> v;

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
    int endergebnis = 0;
    int endergebnis_2 = 0;
    while (std::getline(file, line)){
        line = line.substr(0, line.size()-1);

        v.push_back(line);

        string line_1 = line.substr(0, (line.size()/2));
        string line_2 = line.substr(line.size()/2, line.size()-1);
        char ergibnis = containsborth(line_1, line_2);
        cout << line << "; erste helfte: " << line_1 << "; zweite helfte: " << line_2 << "; beide haben " << ergibnis << " im string;" << endl;
        endergebnis += m[ergibnis];

        if(v.size() == 3){
            char ergibnis_2 = containsborth(v[0], v[1], v[2]);
            cout << ergibnis_2 << endl;
            endergebnis_2 += m[ergibnis_2];

            v = {};
        }

    }


    cout << "Ergebnis: " << endergebnis << endl;
    cout << "Ergebnis 2: " << endergebnis_2 << endl;

    cout << endl << endl << "--------------" << "Day " << day << "--------------" << endl << endl;
    return 0;
}

char containsborth(string a,string b){

    for(char& c : a) {
        for(char& d : b){
            if(c == d){
                return c;
            }
        }
    }

}

char containsborth(string a,string b, string c){

    for(char& x : a) {
        for(char& y : b){
            for(char& z : c){
                if(x == y){
                    if(y == z){
                        return z;
                    }
                }
            }
        }
    }

}
