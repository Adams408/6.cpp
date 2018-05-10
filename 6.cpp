/*
 * Author: James Adams
 * Date: May 2, 2018
 * File: 6.cpp
 */

#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

string convert(int i) { // converts the path number to a letter
    switch (i) {
        case 0:
            return "A";
        case 1:
            return "B";
        case 2:
            return "C";
        case 3:
            return "D";
        case 4:
            return "E";
        case 5:
            return "F";
        case 6:
            return "G";
        case 7:
            return "H";
        case 8:
            return "I";
    }
}

int main(int argc, char *argv[]) {
    ifstream in;
    in.open("graph.txt");
    if (!in) {
        cout << "unable to open file";
        exit(1);
    }
    int size;
    in >> size;
    int a[size][size];
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i == j) {
                a[i][j] = 0; // 0 for the diagonal
            } else {
                in >> a[i][j];
                a[j][i] = a[i][j]; // adds values for mirrored locations
            }
        }
    }
    in.close();

    int pv[size]; // array to hold path value
    string p[size]; // array to hold path 
    int b[size]; // array to keep track which paths found
    for (int k = 0; k < size; k++) {
        pv[k] = 1000;
        p[k] = "";
        b[k] = 1;
    }
    b[0] = 0; // 0 means its path has been found, start from A

    int est = 0; // current path being checked
    int min = 0; // index of the lowest path/value
    int turnMin; // lowest path value found from est

    for (int i = 0; i < size; i++) { // finds a path for each point
        turnMin = 1000;
        for (int j = 0; j < size; j++) { // loop to find path from est
            if (a[est][j] != 0 && b[j] != 0) {
                if (a[est][j] < pv[j] && pv[est] == 1000) {
                    pv[j] = a[est][j];
                    p[j] = convert(est) + convert(j);
                    if (pv[j] < turnMin) { // saves the smallest current path value seen so far
                        turnMin = pv[j];
                        min = j;
                    }
                } else if (a[est][j] + pv[est] < pv[j]) { // if total path weight less than saved path weight
                    pv[j] = a[est][j] + pv[est];
                    p[j] = p[est] + convert(j);
                    if (pv[j] < turnMin) {
                        turnMin = pv[j];
                        min = j;
                    }
                }
            }
        }
        b[min] = 0;
        est = min;
    }

    ofstream out;
    out.open("result.txt");
    for (int i = 1; i < size; i++) {
//        cout << p[i] << " = " << pv[i] << endl;
        out << "Shortest path from " << convert(0) << " to " << convert(i) << " is: " << pv[i] << endl;
        out << "Path taken: " << p[i] << endl;
        out << endl;
    }
    out.close();

    return 0;
}