//
// Created by Phil on 01.12.2022.
//
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <functional>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::to_string;
using std::stoi;
using std::list;

int day = 1;

void outputliste(const list<int>& list){
    std::cout << "l = { ";
    for (int n : list)
        std::cout << n << ", ";
    std::cout << "};\n";
}

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
    int current = 0;
    int last = 0;
    list<int> alleElfen;

    while (getline(file, line)){

        if(line.size() == 1){
            if(current > last){
                last = current;
            }
            alleElfen.push_back(current);
            current = 0;
            cout << "" << endl;
            continue;
        }

        int read = stoi(line);
        current += read;
        cout << read << endl;

    }

    if(current > last){
        last = current;
    }
    alleElfen.push_back(current);
    current = 0;
    cout << "reset" << endl;

    cout << endl << endl << "Ergebnis: " << last << endl << endl;

    alleElfen.sort(std::greater<int>());

    outputliste(alleElfen);

    int topdrei = alleElfen.front();
    alleElfen.pop_front();
    topdrei += alleElfen.front();
    alleElfen.pop_front();
    topdrei += alleElfen.front();

    cout << endl << endl << "Ergebnis: " << topdrei << endl << endl;

    file.close();
    cout << endl << endl << "--------------" << "Day " << day << "--------------" << endl << endl;
    return 0;
}