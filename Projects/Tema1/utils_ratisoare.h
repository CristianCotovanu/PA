#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#ifndef _HOME_CRISTIAN_DESKTOP_YEAR_II_SEM_II_PA_PROJECTS_TEMA1_UTILS_RATISOARE_H_
#define _HOME_CRISTIAN_DESKTOP_YEAR_II_SEM_II_PA_PROJECTS_TEMA1_UTILS_RATISOARE_H_

class Duck {
public:
    int id;
    int x;
    int y;
    int fallingTime;
    char direction;

    Duck() = default;

    static bool FallComparator(const Duck& d1, const Duck& d2) {
        if (d1.fallingTime == d2.fallingTime) {
            return d1.id < d2.id;
        } else {
            return d1.fallingTime < d2.fallingTime;
        }
    }

    static bool IdComparator(const Duck& d1, const Duck& d2) {
        return d1.id < d2.id;
    }

    static bool CoordComparator(const Duck& d1, const Duck& d2) {
        if (d1.x == d2.x) {
            if (d1.y == d2.y) {
                return d1.id < d2.id;
            } else {
                return d1.y < d2.y;
            }
        } else {
            return d1.x < d2.x;
        }
    }
};

void ParseInputDucks(int* cols, int* K, int* ducks_nr, vector<Duck>& ducks) {
    FILE* fin  = fopen("ratisoare.in", "r");

    if (fin == nullptr) {
        cout << "Input file does not exist." << endl;
        exit(EXIT_FAILURE);
    }

    char *line = nullptr;
    size_t aux_len = 0;
    char* token;

    if ((getline(&line, &aux_len, fin)) != -1) {
        token = strtok(line, " ");
        token = strtok(nullptr, " ");
        *cols = atoi(token);
        token = strtok(nullptr, " ");
        *K = atoi(token);
        token = strtok(nullptr, " ");
        *ducks_nr = atoi(token);
    }

    for (int i = 0; i < *ducks_nr; i++) {
        getline(&line, &aux_len, fin);

        Duck d{};

        token = strtok(line, " ");
        d.id = atoi(token);
        token = strtok(nullptr, " ");
        d.x = atoi(token) - 1;
        token = strtok(nullptr, " ");
        d.y = atoi(token) - 1;
        token = strtok(nullptr, " ");
        d.direction = *token;

        if (d.direction == 'S') {
            d.fallingTime = d.y + 1;
        } else {
            d.fallingTime = *cols - d.y;
        }

        ducks.push_back(d);
    }

    fclose(fin);
}

void WriteOutputDucks(int kth_duck) {
    FILE* fout  = fopen("ratisoare.out", "w");

    if (fout == nullptr) {
        cout << "Output file broken." << endl;
        exit(EXIT_FAILURE);
    }

    fprintf(fout, "%d\n", kth_duck);
    fclose(fout);
}

#endif  // _HOME_CRISTIAN_DESKTOP_YEAR_II_SEM_II_PA_PROJECTS_TEMA1_UTILS_RATISOARE_H_
