//
// Created by Phil on 02.12.2022.
//
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::to_string;
using std::map;
using std::vector;
using std::stringstream;

int day = 2;

map<string, int> m{
        {"A", 1},
        {"B", 2},
        {"C", 3},
        {"X", 1},
        {"Y", 2},
        {"Z", 3}
};


vector<string> split(const string& s, const char& delimiter);
int compare(int a, int b);
int needToWin(int a, int b);

int main() {
    cout << endl << endl << "--------------" << "Day " << day << "--------------" << endl << endl;

    ifstream file;
    // string filename{"../input/test.txt"};
    string filename{"../input/day" + to_string(day) + ".txt"};
    file.open(filename);

    cout << endl << "Input: " << filename << endl << endl;

    if(!file.is_open()){
        std::cerr << "Datei beim Oeffnen der Datei " << filename << endl;
        return 1;
    }

    string line;
    int fullergibniss = 0;
    int strategie = 0;
    vector<string> letzteergebnis;
    while (std::getline(file, line)){

        vector<string> v = split(line.substr(0,3), ' ');

        int meinewahl = m[v[1]];
        int gegnerwahl = m[v[0]];

        int ergebniss = compare(gegnerwahl, meinewahl);
        letzteergebnis = v;

        cout << v[0] << " gegen " << v[1] << " ist " << ergebniss << " dann ist das ergebniss " << (ergebniss + meinewahl) << endl;

        strategie += needToWin(gegnerwahl, meinewahl);
        fullergibniss += ergebniss + meinewahl;
    }

    cout << endl << "Ergebnis: " << fullergibniss << endl;
    cout << endl << "Ergebnis: " << strategie << endl;

    cout << endl << endl << "--------------" << "Day " << day << "--------------" << endl << endl;
    return 0;
}

int needToWin(int a, int b){
    if(b == 1){
        if(compare(a, 1) == 0){
            return 0 + 1;
        }

        if(compare(a, 2) == 0){
            return 0 + 2;
        }

        if(compare(a, 3) == 0){
            return 0 + 3;
        }
    }

    if(b == 2){
        if(compare(a, 1) == 3){
            return 3 + 1;
        }

        if(compare(a, 2) == 3){
            return 3 + 2;
        }

        if(compare(a, 3) == 3){
            return 3 + 3;
        }
    }

    if(compare(a, 1) == 6){
        return 6 + 1;
    }

    if(compare(a, 2) == 6){
        return 6 + 2;
    }

    if(compare(a, 3) == 6){
        return 6 + 3;
    }

}

int compare(int a, int b){
    if(a == b){
        return 3;
    }

    if(a == 1 && b == 2){
        return 6;
    }

    if(a == 1 && b == 3){
        return 0;
    }

    if(a == 2 && b == 3){
        return 6;
    }

    if(a == 2 && b == 1){
        return 0;
    }

    if(a == 3 && b == 1){
        return 6;
    }

    if(a == 3 && b == 2){
        return 0;
    }

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