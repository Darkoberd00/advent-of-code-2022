//
// Created by Phil on 05.12.2022.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <sstream>

using std::stringstream;
using std::cout;
using std::vector;
using std::endl;
using std::ifstream;
using std::string;
using std::to_string;
using std::map;
using std::stack;

int day = 5;
map<int, stack<char>> stack_map;
map<int, stack<char>> stack_map2;


void stackmove(int anzahl, int stacka, int stackb);
void stackmoveotherway(int anzahl, int stacka, int stackb);
string erzeuge_ergebnis(map<int, stack<char>>);

vector<string> split (const string& s, const char& delimiter);

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
    vector<string> vector_stack;
    vector<string> vector_move;

    bool is_stack{true};

    while (std::getline(file,line)){
        if(line.substr(0, line.size()-1).empty()){
            is_stack = false;
            continue;
        }
        if(is_stack){
            vector_stack.push_back(line);
            continue;
        }
        vector_move.push_back(line);
    }

    cout << "Stack:" << endl;
    string lastline = vector_stack[vector_stack.size()-1];
    cout << lastline << endl;
    vector_stack.pop_back();
    for (int i = (int) vector_stack.size()-1; i >= 0; i--){
        string stack = vector_stack[i].substr(0, vector_stack[i].size()-1);
        int map_int = 0;
        int times = 0;
        for(char& a: stack){
            if(times == 4){
                map_int++;
                times = 0;
            }
            if(a == ' ' or a == '[' or a == ']'){
                times++;
                continue;
            }
            stack_map[map_int].push(a);
            times++;
        }
        cout << stack << endl;
    }

    stack_map2 = stack_map;

    cout << endl << "Moves:" << endl;


    for (string& move: vector_move) {
        cout << move << endl;
        vector<string> v = split(move, ' ');
        int anzanl = std::stoi(v[1]);
        int stacka = std::stoi(v[3]);
        int stackb = std::stoi(v[5]);

        stackmove(anzanl,stacka,stackb);
        stackmoveotherway(anzanl,stacka,stackb);
    }

    cout << endl << "Ergebnis: " << erzeuge_ergebnis(stack_map) << endl;
    cout << "Ergebnis 2: " << erzeuge_ergebnis(stack_map2) << endl;

    cout << endl << endl << "--------------" << "Day " << day << "--------------" << endl << endl;
    return 0;
}

void stackmove(int anzahl, int stacka, int stackb) {
    for (int i = 0; i < anzahl; ++i) {
        stack_map[stackb-1].push(stack_map[stacka-1].top());
        stack_map[stacka-1].pop();
    }
}

void stackmoveotherway(int anzahl, int stacka, int stackb) {
    stack<char> temp;
    for (int i = 0; i < anzahl; ++i) {
        temp.push(stack_map2[stacka-1].top());
        stack_map2[stacka-1].pop();
    }
    while (!temp.empty()){
        stack_map2[stackb-1].push(temp.top());
        temp.pop();
    }
}

string erzeuge_ergebnis(map<int, stack<char>> m){
    string ergebnis;
    for(const auto& elem : m)
    {
        ergebnis += elem.second.top();
    }
    return ergebnis;
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
