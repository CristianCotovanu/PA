#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

struct Object {
    int weight;
    int price;

    Object(int _weight, int _price) : weight(_weight), price(_price) {}

//    bool operator < (const Object& o1) const {
//        return o1.price < price;
//    }
};

struct ratio_comparator {
    bool operator() (const Object& obj1, const Object& obj2) {
        return (double)obj2.price / (double)obj2.weight < (double)obj1.price / (double)obj1.weight;
    }
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, w;
    vector<Object> objs;

    void read_input() {
        ifstream fin("in");
        fin >> n >> w;
        for (int i = 0, weight, price; i < n; i++) {
            fin >> weight >> price;
            objs.push_back(Object(weight, price));
        }
        fin.close();
    }

    double get_result() {
        double maxProfit = 0.0;

        std::sort(objs.begin(), objs.end(), ratio_comparator());

        for (int i = 0; i < objs.size() && w > 0; i++) {
            if (objs[i].weight <= w) {
                maxProfit += objs[i].price;
                w -= objs[i].weight;
            } else {
                maxProfit += ((double) objs[i].price / (double) objs[i].weight ) * (double) w;
                w = 0;
            }
        }

        return maxProfit;
    }

    void print_output(double result) {
        ofstream fout("out");
        fout << setprecision(4) << fixed << result;
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
