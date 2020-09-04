#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <vector>
#include <time.h>
#include <sstream>
#include <string>
using namespace std;
class vertex {
public:
    int* colours;
    vector<int> confilict;
    int finalcolour;
};
int main(int argc, char** argv)
{
    int n = 0;
    const char* temp[12] = { "16.txt", "32.txt", "64.txt", "128.txt", "256.txt", "512.txt", "1024.txt",
        "2048.txt", "4096.txt", "8192.txt", "16384.txt", "32768.txt" };
    for (int x = 0; x < 12; x++) {
        cout << "starting " << temp[x] << "\n";
        ifstream input(temp[x], ifstream::in);
        input >> n;
        // int ln = ((log2(n)*3)+1);
        int ln = 0;
        int deg = -1;
        input >> deg;
        srand((int)time(0));
        char edges[n][n];
        for (int i = 0; i < n; i++) {
            for (int c = 0; c < n; c++) {
                input >> edges[i][c];
                edges[i][c] -= '0';
                edges[c][i] = edges[i][c];
            }
        }
        input.close();
        for (int runs = 0; runs < 25; runs++) {
            vector<vertex> vertarr;
            vector<int> sets[deg + 1];
            //initalise vertexs
            for (int i = 0; i < n; i++) {
                vertex v;
                vertarr.push_back(v);
                vertarr[i].colours = new int[ln];
                vertarr[i].finalcolour = -1;
            }
            clock_t start = clock();
            //assign random colours
            for (int i = 0; i < n; i++) {
                for (int c = 0; c < ln; c++) {
                    int colour = rand() % (deg + 1);
                    sets[colour].push_back(i);
                    vertarr[i].colours[c] = colour;
                }
            }
            //fill confilct sets
            for (int i = 0; i < (deg + 1); i++) {
                for (int c = 0; c < sets[i].size(); c++) {
                    for (int t = c; t < sets[i].size(); t++) {
                        if (edges[sets[i].at(c)][sets[i].at(t)]) {
                            vertarr[sets[i].at(c)].confilict.push_back(sets[i].at(t));
                            vertarr[sets[i].at(t)].confilict.push_back(sets[i].at(c));
                        }
                    }
                }
            }
            int x = 0;
            for (int cur = 0; cur < ln; cur++) { //for each colour
                for (int i = 0; i < vertarr.size(); i++) { //for each vertex
                    for (int c = 0; c < vertarr[i].confilict.size() && x == 0; c++) { //for each nebour
                        if (vertarr[vertarr[i].confilict.at(c)].finalcolour == vertarr[i].colours[cur]) {
                            x = 1;
                        }
                    }
                    if (vertarr[i].finalcolour == -1 && x == 0) {
                        vertarr[i].finalcolour = vertarr[i].colours[cur];
                    }
                    x = 0;
                }
            }
            clock_t end = clock();
            double time = (double)(end - start) / CLOCKS_PER_SEC;
            int bads = 0;
            for (int i = 0; i < n; i++) {
                if (vertarr[i].finalcolour == -1) {
                    bads++;
                    int col[deg + 1];
                    for (int cl = 0; cl < deg + 1; cl++) {
                        col[cl] = -1;
                    }
                    for(int c = 0; c < n; c++)
                    {
                        if (edges[i][c] && vertarr[c].finalcolour != -1) {
                            col[vertarr[c].finalcolour] = 1;
                        }
                    }
                    for (int c = 0; c < deg + 1; c++) {
                        if (col[c] == -1) {
                            vertarr[i].finalcolour = c;
                            break;
                        }
                    }
                }
                //cout << vertarr[i].finalcolour << " ";
            }
            clock_t end2 = clock();
            double time2 = (double)(end2 - start) / CLOCKS_PER_SEC;
            cout << time << "," << time2 << "," << bads << "\n";
        }
    }
    return 0;
}
