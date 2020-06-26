#include "utils_ratisoare.h"

void GetKthFallingDuck(int cols, int k, int ducksNr, vector<Duck> ducks) {
    int ducksFellTillKth = 0;
    vector<int> oldIdx;
    oldIdx.reserve(ducksNr);
    sort(ducks.begin(), ducks.end(), Duck::FallComparator);
    int KthDuckFallingTime = ducks[k - 1].fallingTime;
    sort(ducks.begin(), ducks.end(), Duck::CoordComparator);

    for (int i = 0; i < ducksNr; i++) {
        oldIdx.push_back(ducks[i].id);
    }

    for (int i = 0; i < ducksNr; i++) {
        if (ducks[i].direction == 'S') {
            ducks[i].y = ducks[i].y - KthDuckFallingTime;
        }
        if (ducks[i].direction == 'D') {
            ducks[i].y = ducks[i].y + KthDuckFallingTime;
        }
        if (ducks[i].y <+ -1 || ducks[i].y >= cols + 1) {
            ducksFellTillKth++;
        }
    }

    sort(ducks.begin(), ducks.end(), Duck::CoordComparator);
    for (int i = 0; i < ducksNr; i++) {
        ducks[i].id = oldIdx[i];
    }

    vector<Duck> ducksFallenKth;
    int ducksFallenAtK = k - ducksFellTillKth;

    for (int i = 0; i < ducksNr; i++) {
        if (ducks[i].y == -1 || ducks[i].y == cols) {
            ducksFallenKth.push_back(ducks[i]);
        }
    }

    sort(ducksFallenKth.begin(), ducksFallenKth.end(), Duck::IdComparator);
    WriteOutputDucks(ducksFallenKth[ducksFallenAtK - 1].id);
}

int main() {
    int cols;
    int K;
    int ducksNr;
    vector<Duck> ducks;
    ParseInputDucks(&cols, &K, &ducksNr, ducks);
    GetKthFallingDuck(cols, K, ducksNr, ducks);
    return 0;
}
