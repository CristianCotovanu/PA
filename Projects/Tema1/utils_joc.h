#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#ifndef _HOME_CRISTIAN_DESKTOP_YEAR_II_SEM_II_PA_PROJECTS_TEMA1_UTILS_JOC_H_
#define _HOME_CRISTIAN_DESKTOP_YEAR_II_SEM_II_PA_PROJECTS_TEMA1_UTILS_JOC_H_

class Parity {
public:
    int even = 0;
    int odd = 0;

    Parity() = default;
};

void ParseInputOdds(int* N, int* K, int* L, vector<int>& numbers) {
    FILE* fin  = fopen("joc.in", "r");

    if (fin == nullptr) {
        cout << "Input file does not exist." << endl;
        exit(EXIT_FAILURE);
    }

    char *line = nullptr;
    size_t aux_len = 0;
    char* token;

    if ((getline(&line, &aux_len, fin)) != -1) {
        token = strtok(line, " ");
        *N = atoi(token);
        token = strtok(nullptr, " ");
        *K = atoi(token);
        token = strtok(nullptr, " ");
        *L = atoi(token);
    } else {
        cout << "Input file is broken.";
    }

    getline(&line, &aux_len, fin);

    //  indexing starts from 1, dummy number
    numbers.push_back(-1);
    token = strtok(line, " ");
    while (token != nullptr) {
        numbers.push_back(atoi(token));
        token = strtok(nullptr, " ");
    }

    fclose(fin);
}

void WriteOutputOdds(int result) {
    FILE* output = fopen("joc.out", "w");
    fprintf(output, "%d", result != 0 ? result : -1);
    fclose(output);
}

#endif  // _HOME_CRISTIAN_DESKTOP_YEAR_II_SEM_II_PA_PROJECTS_TEMA1_UTILS_JOC_H_
