#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#ifndef _HOME_CRISTIAN_DESKTOP_YEAR_II_SEM_II_PA_PROJECTS_TEMA1_UTILS_TEME_H_
#define _HOME_CRISTIAN_DESKTOP_YEAR_II_SEM_II_PA_PROJECTS_TEMA1_UTILS_TEME_H_

class Homework {
public:
    int idx;
    int compTime;
    int score;
    int deadline;

    Homework() = default;

    static bool DeadlineIdxComparator(const Homework& lhs, const Homework& rhs) {
        if (lhs.deadline == rhs.deadline) {
            return lhs.idx < rhs.idx;
        } else {
            return lhs.deadline < rhs.deadline;
        }
    }
};

void ParseInputHomework(int* maximum_deadline, std::vector<Homework>& homeworks) {
    FILE* fin  = fopen("teme.in", "r");

    if (fin == nullptr) {
        cout << "Input file does not exist." << endl;
        exit(EXIT_FAILURE);
    }

    char *line = nullptr;
    size_t aux_len = 0;
    char* token;
    int hws_number;

    if ((getline(&line, &aux_len, fin)) != -1) {
        token = strtok(line, "\n");

        hws_number = atoi(token);
    } else {
        cout << "Input file is broken.";
        exit(EXIT_FAILURE);
    }

    int max_deadline = -1;

    Homework null{};
    null.score = 0;
    null.compTime = 0;
    null.deadline = 0;
    homeworks.push_back(null);

    for (int i = 0; i < hws_number; i++) {
        getline(&line, &aux_len, fin);

        Homework h{};

        token = strtok(line, " ");
        h.compTime = atoi(token);
        token = strtok(nullptr, " ");
        h.score = atoi(token);
        token = strtok(nullptr, " ");
        h.deadline = atoi(token);

        h.idx = i + 1;

        if (max_deadline < h.deadline) {
            max_deadline = h.deadline;
        }

        homeworks.push_back(h);
    }

    *maximum_deadline = max_deadline;

    fclose(fin);
}

void WriteOutputHomework(int maxScore, int **hwsDone, int maxScIdx, vector<Homework> hws) {
    FILE* fout  = fopen("teme.out", "w");
    vector<Homework> hwsInFinalConfig;

    for (int h = hws.size() - 1; h > 0; h--) {
        if (hwsDone[h][maxScIdx]) {
            hwsInFinalConfig.push_back(hws[h]);
            maxScIdx -= hws[h].compTime;
        }
    }

    fprintf(fout, "%d ", maxScore);
    fprintf(fout, "%zu\n", hwsInFinalConfig.size());
    for (int i = hwsInFinalConfig.size() - 1; i >= 0; i--) {
        fprintf(fout, "%d ", hwsInFinalConfig[i].idx);
    }
    fclose(fout);
}

int** MatrixAlloc(int rows, int cols) {
    int** dp = (int **) calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i++) {
        dp[i] = (int *) calloc(cols, sizeof(int));
    }

    return dp;
}

void FreeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

#endif  // _HOME_CRISTIAN_DESKTOP_YEAR_II_SEM_II_PA_PROJECTS_TEMA1_UTILS_TEME_H_
