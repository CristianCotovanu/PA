#include <bits/stdc++.h>
using namespace std;

struct Homework {
    int deadline;
    int score;

    Homework(int _deadline, int _score) : deadline(_deadline), score(_score) {}

    bool operator < (const Homework& h) const {
        return h.deadline > deadline;
    }
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n;
    vector<Homework> hws;

    static void print_vector(const vector<Homework>& hws) {
        for (auto & hw : hws) {
            printf("d:%d p:%d\n", hw.deadline, hw.score);
        }
    }

    void read_input() {
        ifstream fin("in");
        fin >> n;
        for (int i = 0, deadline, score; i < n; i++) {
            fin >> deadline >> score;
            hws.push_back(Homework(deadline, score));
        }
        fin.close();
    }

    int get_result() {
        /*
        TODO: Aflati punctajul maxim pe care il puteti obtine planificand
        optim temele.
        */
        print_vector(hws);
        cout << "\n";

        std::sort(hws.begin(), hws.end());

        print_vector(hws);

        int maxScore = 0;

        for (int i = hws.size() - 1; i >= 0; i--) {
            int crtMax = 0;
//            int maxIdx = 0;
            for (int j = i - 1; j >= 0 ; j--) {
                if (hws[i].score > crtMax) {
                    crtMax = hws[i].score;
//                    maxIdx= i;
                }
            }

//            hws[maxIdx].score = 0;
            maxScore += crtMax;
        }

        return maxScore;
    }

    void print_output(int result) {
        ofstream fout("out");
        fout << result;
        fout.close();
    }
};

// Please always keep this simple main function!
int main() {
    // Allocate a Task object on heap in order to be able to
    // declare huge static-allocated data structures inside the class.
    Task *task = new Task();
    task->solve();
    delete task;
    return 0;
}
