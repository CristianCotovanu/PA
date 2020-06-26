#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

#ifndef _HOME_CRISTIAN_DESKTOP_YEAR_II_SEM_II_PA_PROJECTS_TEMA1_UTILS_MAGIC_H_
#define _HOME_CRISTIAN_DESKTOP_YEAR_II_SEM_II_PA_PROJECTS_TEMA1_UTILS_MAGIC_H_

class Point {
public:
    int value;
    int partialSum;

    Point() = default;

    static bool ValueComparator(Point& d1, Point& d2) {
        return d1.value < d2.value;
    }

    static bool PartialSumComparator(Point& d1, Point& d2) {
        return d1.partialSum < d2.partialSum;
    }
};

int Min(int x, int y) {
    return x < y ? x : y;
}

void ParseInputMagic(int* N, Point** array) {
    FILE* fin  = fopen("magic.in", "r");

    if (fin == nullptr) {
        cout << "Input file does not exist." << endl;
        exit(EXIT_FAILURE);
    }

    char *line = nullptr;
    char* token;
    size_t aux_len = 0;

    if ((getline(&line, &aux_len, fin)) != -1) {
        token = strtok(line, "\n");

        *N = atoi(token);
    }

    int partialSum = 0;
    getline(&line, &aux_len, fin);
    token = strtok(line, " ");

    *array = static_cast<Point *>(calloc(*N, sizeof(Point)));

    for (int i = 0; i < *N && token != nullptr; i++) {
        int num = atoi(token);
        Point temp{};
        temp.value = i + 1;
        temp.partialSum = partialSum;
        (*array)[i] = temp;

        partialSum += num;
        token = strtok(nullptr, " ");
    }

    fclose(fin);
}

void WriteOutputMagic(int magicNumber, int left, int right) {
    FILE* fout  = fopen("magic.out", "w");

    if (fout == nullptr) {
        cout << "Output file broken." << endl;
        exit(EXIT_FAILURE);
    }

    fprintf(fout, "%d\n", magicNumber);
    left < right ? fprintf(fout, "%d %d\n", left, right)
                    : fprintf(fout, "%d %d\n", right, left);

    fclose(fout);
}

#endif  // _HOME_CRISTIAN_DESKTOP_YEAR_II_SEM_II_PA_PROJECTS_TEMA1_UTILS_MAGIC_H_
