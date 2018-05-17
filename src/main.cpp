#include "monome.h"
#include "polynome.h"
#include <iostream>
#include <vector>

using namespace std;

void genMonoList(int step, int n, int sum, vector<Monome> & res, Monome & now)
{
    if (step == n - 1) {
        now.setdeg(step, sum);
        res.push_back(now);
    }
    else {
        for (int i = sum; i >= 0; -- i) {
            now.setdeg(step, i);
            genMonoList(step + 1, n, sum - i, res, now);
        }
    }
}

vector<Monome> monolist(int n, int dmin, int dmax)
{
    vector<Monome> res;
    Monome now;
    vector<int> b(n);
    now.setb(b);
    now.setc(1.);

    for (int i = dmin; i <= dmax; ++ i) {
        genMonoList(0, n, i, res, now);
    }

    return res;
}

void printMonoList(vector<Monome> & monos)
{
    int n = monos.size();
    printf("{");
    for (int i = 0; i < n; ++ i) {
        monos[i].print();
        if (i != n - 1) {
            printf(",");
        }
    }
    printf("}\n");
}

// Polu

int main()
{
    vector<Monome> list;

    list = monolist(3, 0, 3);
    printMonoList(list);

    return 0;
}