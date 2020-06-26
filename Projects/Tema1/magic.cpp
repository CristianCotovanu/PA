#include "utils_magic.h"

#define INF 100000

int UpdateMinimumMagic(Point x, Point y, int* leftIdx, int* rightIdx, int* minMagicNumber) {
    int crtMagic = ((x.value - y.value) * (x.value - y.value)
                    + (x.partialSum - y.partialSum)
                    * (x.partialSum - y.partialSum));

    if (crtMagic > *minMagicNumber) {
        return *minMagicNumber;
    } else if (crtMagic == *minMagicNumber) {
        if (x.value < *leftIdx || y.value < *rightIdx) {
            *leftIdx = x.value;
            *rightIdx = y.value;
        }
    } else {
        *minMagicNumber = crtMagic;
        *leftIdx = x.value;
        *rightIdx = y.value;
    }
    return crtMagic;
}

void ClosestPairOfPoints(Point *numbers, int n, int* leftIdx, int* rightIdx, int* magicNumber) {
    if (n <= 10) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                    UpdateMinimumMagic(numbers[i], numbers[j], leftIdx, rightIdx, magicNumber);
            }
        }
        return;
    }

    //  Split initial interval in 2 sub-intervals
    int midIdx = n / 2;

    //  Compute magic_num for left and right intervals
    ClosestPairOfPoints(numbers, midIdx, leftIdx, rightIdx, magicNumber);
    int leftMagicNr = *magicNumber;
    ClosestPairOfPoints(numbers + midIdx, n - midIdx, leftIdx, rightIdx, magicNumber);
    int rightMagicNr = *magicNumber;
    int minimumDistance = Min(leftMagicNr, rightMagicNr);

    Point remaining[n];
    int numsRemaining = 0;
    for (int i = 0; i < n; i++) {
        if (abs(numbers[i].value - numbers[midIdx].value) < minimumDistance) {
            remaining[numsRemaining] = numbers[i];
            numsRemaining++;
        }
    }

    sort(remaining, remaining + numsRemaining, Point::PartialSumComparator);
    for (int i = 0; i < numsRemaining - 1; i++) {
        for (int j = i + 1; j < numsRemaining && (remaining[j].partialSum - remaining[i].partialSum) < minimumDistance; j++) {
                UpdateMinimumMagic(remaining[i], remaining[j], leftIdx, rightIdx, magicNumber);
        }
    }
}

void SolveProblem(Point *numbers, int n) {
    int left = INF;
    int right = INF;
    int magicNumber = INF;

    sort(numbers, numbers + n, Point::ValueComparator);
    ClosestPairOfPoints(numbers, n, &left, &right, &magicNumber);
    WriteOutputMagic(magicNumber, left, right);
}

int main() {
    int N;
    Point* input;
    ParseInputMagic(&N, &input);
    SolveProblem(input, N);
    return 0;
}
