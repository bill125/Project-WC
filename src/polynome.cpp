#include "polynome.h"
#include <cassert>
#include <cmath>

using namespace std;

#define eps 1e-6

void Polynome::seta(const std::vector<Monome> & _a)
{
    a = _a;
    bool flag = true;
    int n = a.size();

    for (int i = 0; i < n - 1; ++ i) {
        if (a[i + 1] < a[i]) {
            flag = false;
            break;
        }
    }

    if (!flag) {
        sort(a.begin(), a.end());
    }
}

int Polynome::size() const 
{
    return a.size();
}

std::vector<Monome> Polynome::mergeMonome(const std::vector<Monome> & a)
{
    // ensure that a is sorted.
    vector<Monome> res;

    int n = a.size();
    Monome now = a[0];
    for (int i = 1; i < n; ++ i) {
        double now_c = now.coef();
        now.setc(a[i].coef());
        if (now == a[i]) {
            now.setc(now_c + a[i].coef());
        }
        else {
            if (fabs(now.coef()) > eps) {
                res.push_back(now);
            }
            now = a[i];
        }
    }

    if (fabs(now.coef()) > eps) {
        res.push_back(now);
    }

    return res;
}

double Polynome::eval(const vector<double> & x)
{
    int n = a.size();
    double res = 0.;

    for (int i = 0; i < n; ++ i) {
        res += a[i].eval(x);
    }

    return res;
}

int Polynome::deg() const
{
    int n = a.size();
    int res = 0;

    for (int i = 0; i < n; ++ i) {
        res = max(res, a[i].deg());
    }

    return res;
}

vector<Monome> Polynome::mono() const
{
    return a;
}

vector<double> Polynome::coef() const
{
    vector<double> res;

    int n = a.size();
    for (int i = 0; i < n; ++ i) {
        res.push_back(a[i].coef());
    }

    return res;
}

Polynome operator+(const Polynome & A, const Polynome & B)
{
    Polynome C;
    vector<Monome> a = A.mono(), b = B.mono(), c;
    int n = a.size(), m = b.size();

    for (int i = 0, j = 0; i < n || j < m; ) {
        if (j == m || (i != n && a[i] < b[j])) {
            c.push_back(a[i ++]);
        }
        else {
            c.push_back(b[j ++]);
        }
    }

    C.seta(C.mergeMonome(c));

    return C;
}

Polynome operator-(const Polynome & A, const Polynome & B)
{
    Polynome B_ = B * (-1.);
    return A + B_;
} 

Polynome operator*(const Polynome & A, const double & c) 
{
    Polynome B = A;
    int n = A.size();
    vector<Monome> a = A.mono();

    for (int i = 0; i < n; ++ i) {
        a[i] = a[i] * c;
    }

    B.seta(a);

    return B;
}

Polynome operator*(const Polynome & A, const Polynome & B)
{
    Polynome C;
    vector<Monome> a = A.mono(), b = B.mono(), c;
    int n = A.size(), m = B.size();

    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m; ++ j) {
            c.push_back(a[i] * b[j]);
        }
    }
    sort(c.begin(), c.end());
    C.seta(C.mergeMonome(c));
    
    return C;
}

bool operator==(const Polynome & A, const Polynome & B)
{
    if (A.size() != B.size()) {
        return false;
    }
    int n = A.size();
    vector<Monome> a = A.mono(), b = B.mono();
    for (int i = 0; i < n; ++ i) {
        if (!(a[i] == b[i])) {
            return false;
        }
    }
    return true;
}

