#include "utils_joc.h"

#define kMax 150
#define lMax 250

Parity InitFirstSeq(int number) {
    Parity result;
    number % 2 == 0 ? result.even = number : result.odd = number;
    return result;
}

void AddNewSequence(int number, int k, int l, Parity aux[kMax][lMax], Parity dp[2][kMax][lMax]) {
    for (int seq = 2; seq <= k; seq++) {
        for (int len = 2; len <= l; len++) {
            if (dp[0][seq - 1][len - 1].even != 0) {
                if (number % 2 == 0) {
                    aux[seq][len].even = dp[0][seq - 1][len - 1].even + number;
                } else {
                    aux[seq][len].odd = dp[0][seq - 1][len - 1].even + number;
                }
            }

            if (dp[0][seq - 1][len - 1].odd != 0) {
                if (number % 2 == 0) {
                    aux[seq][len].odd = dp[0][seq - 1][len - 1].odd + number;
                } else {
                    aux[seq][len].even = dp[0][seq - 1][len - 1].odd + number;
                }
            }
        }
    }
}

void ContinueLastSequence(int number, int k, int l, Parity aux[kMax][lMax], Parity dp[2][kMax][lMax]) {
    for (int seq = 1; seq <= k; seq++) {
        for (int len = 1; len <= l; len++) {
            if (dp[1][seq][len - 1].even != 0) {
                if (number % 2 == 0 && aux[seq][len].even < dp[1][seq][len - 1].even + number) {
                    aux[seq][len].even = dp[1][seq][len - 1].even + number;
                }
                else if (number % 2 != 0 && aux[seq][len].odd < dp[1][seq][len - 1].even + number) {
                    aux[seq][len].odd = dp[1][seq][len - 1].even + number;
                }
            }

            if (dp[1][seq][len - 1].odd != 0) {
                if (number % 2 == 0 && aux[seq][len].odd < dp[1][seq][len - 1].odd + number) {
                    aux[seq][len].odd = dp[1][seq][len - 1].odd + number;
                } else if (number % 2 != 0 && aux[seq][len].even < dp[1][seq][len - 1].odd + number) {
                    aux[seq][len].even = dp[1][seq][len - 1].odd + number;
                }
            }
        }
    }
}

void RemakeReccurence(int k, int l, Parity aux[kMax][lMax], Parity dp[2][kMax][lMax]) {
    for (int seq = 1; seq < k + 1; seq++) {
        for (int len = 1; len <= l; len++) {
            if (dp[0][seq][len].even < dp[1][seq][len].even) {
                dp[0][seq][len].even = dp[1][seq][len].even;
            }

            if (dp[0][seq][len].odd < dp[1][seq][len].odd) {
                dp[0][seq][len].odd = dp[1][seq][len].odd;
            }
        }
    }
    memcpy(dp[1], aux, kMax * lMax * sizeof(Parity));
}

void SolveProblem(int n, int k, int l, vector<int> numbers, Parity dp[][kMax][lMax]) {
    for (int i = 1; i <= n; i++) {
        Parity aux[kMax][lMax];
        aux[1][1] = InitFirstSeq(numbers[i]);
        AddNewSequence(numbers[i], k, l, aux, dp);
        ContinueLastSequence(numbers[i], k, l, aux, dp);
        RemakeReccurence(k, l, aux, dp);
    }
    RemakeReccurence(k, l, dp[1], dp);
}

int main() {
    int n, k, l;
    vector<int> numbers;
    Parity dp[2][kMax][lMax];
    ParseInputOdds(&n, &k, &l, numbers);
    SolveProblem(n, k, l, numbers, dp);
    WriteOutputOdds(dp[0][k][l].odd);
    return 0;
}
