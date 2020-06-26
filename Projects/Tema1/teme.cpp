#include "utils_teme.h"

void HomeworkBestScore(int maximumDeadline, vector<Homework>& hws) {
    //  Indexing started from 1, added 1 dummy homework
    int hwsNr = (int) hws.size() - 1;
    int** dp = MatrixAlloc(hwsNr + 1, maximumDeadline + 1);
    int** hwsDone = MatrixAlloc(hwsNr + 1, maximumDeadline + 1);
    sort(hws.begin(), hws.end(), &Homework::DeadlineIdxComparator);

    for (int h = 0; h < hwsNr; h++) {
        for (int w = 0; w < hws[h + 1].deadline + 1; w++) {
            dp[h][w] > dp[h + 1][w] ? dp[h + 1][w] = dp[h][w], hwsDone[h + 1][w] = 0 : 0;

            if (w + hws[h + 1].compTime < hws[h + 1].deadline + 1
                && dp[h][w] + hws[h + 1].score > dp[h + 1][w + hws[h + 1].compTime]) {
                dp[h + 1][w + hws[h + 1].compTime] = dp[h][w] + hws[h + 1].score;
                hwsDone[h + 1][w + hws[h + 1].compTime] = 1;
            }
        }
    }

    int maxScIdx = 0;
    for (int w = 0; w < maximumDeadline + 1; w++) {
        if (dp[hwsNr][w] > dp[hwsNr][maxScIdx]) {
            maxScIdx = w;
        }
    }

    WriteOutputHomework(dp[hwsNr][maxScIdx], hwsDone, maxScIdx, hws);
    FreeMatrix(dp, hwsNr + 1);
    FreeMatrix(hwsDone, hwsNr + 1);
}

int main() {
    int maxDeadline;
    vector<Homework> homeworks;
    ParseInputHomework(&maxDeadline, homeworks);
    HomeworkBestScore(maxDeadline, homeworks);
    return 0;
}
