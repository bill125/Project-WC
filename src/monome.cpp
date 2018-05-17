#include "monome.h"
#include <iostream>
#include <cstdio>
#include <cassert>
#include <cmath>

using namespace std;

#define eps 1e-6

double Monome::pow(double x, int b)
{
    assert(b >= 0);
    assert(x > 0.);

    double res = 1.;
    while (b > 0) {
        if (b & 1) {
            res *= x;
        }
        x *= x;
        b >>= 1;
    }
    return res;
}

int Monome::size() const
{
    return b.size();
}

void Monome::reset(int n)
{
    if (n != 0) {
        b = vector<int>(n, 0);
    }
    else {
        b.clear();
    }
    c = 0.;
}

void Monome::setb(const std::vector<int> & _b)
{
    b = _b;
}

void Monome::setc(double _c)
{
    c = _c;
}

void Monome::setdeg(int i, int deg) 
{
    assert(i < b.size());
    b[i] = deg;
}

void Monome::print()
{
    // Used for debug
    bool flag = false;
    for (int i = 0; i < b.size(); ++ i) {
        if (b[i] != 0) {
            flag = true;
        }
    }
    printf(" ");
    bool first = true;
    if (c != 1 or !flag) {
        printf("%.2f", c);
        first = false;
    }
    for (int i = 0; i < b.size(); ++ i) {
        if (b[i] != 0) {
            if (first) {
                first = false;
            }
            else {
                printf(" * ");
            }
            printf("x%d", i);
            if (b[i] != 1) {
                printf("^%d", b[i]);
            }
        }
    }
}

double Monome::eval(const vector<double> & x)
{
    double val = c;

    if (x.size() != b.size()) {
        cout << "The size of x does not match." << endl;
        return 0;
    }
    
    int n = x.size();

    for (int i = 0; i < n; ++ i) {
        val *= pow(x[i], b[i]);
    }

    return val;
}

int Monome::deg() const
{
    int res = 0, n = b.size();

    for (int i = 0; i < n; ++ i) {
        res += b[i];
    }

    return res;
}

int Monome::deg(int i) const
{
    assert(i < b.size());
    return b[i];
}

double Monome::coef() const
{
    return c;
}

vector<Monome> Monome::grad()
{
    int n = b.size();
    vector<Monome> res(n);

    for (int i = 0; i < n; ++ i) {
        res[i] = *this;
        
        if (b[i] == 0) {
            for (int j = 0; j < n; ++ j)
                res[i].setdeg(j, 0);
        }
        else {
            res[i].setc(c * b[i]);
            res[i].setdeg(i, b[i] - 1);
        }
    }

    return res;
}

Monome operator*(const Monome & A, const Monome & B) 
{
    assert(A.size() == B.size());

    int n = A.size();
    vector<int> a(n);

    for (int i = 0; i < n; ++ i) {
        a[i] = A.deg(i) + B.deg(i);
    }
    double c = A.coef() * B.coef();

    Monome res;
    res.setb(a);
    res.setc(c);

    return res;
}

Monome operator*(const Monome & A, const double & c)
{
    Monome B = A;
    B.setc(B.coef() * c);
    return B;
}

bool operator==(const Monome & A, const Monome & B) 
{
    if (A.size() != B.size() || fabs(A.coef() - B.coef()) > eps) 
    {
        return false;
    }

    int n = A.size();
    for (int i = 0; i < n; ++ i) {
        if (A.deg(i) != B.deg(i)) {
            return false;
        }
    }
    return true;
}

// used for sort algorithm
bool operator<(const Monome & A, const Monome & B)
{
    if (A.deg() == B.deg()) {
        assert(A.size() == B.size());
        int n = A.size();

        for (int i = 0; i < n; ++ i) {
            if (A.deg(i) > B.deg(i)) return true;
            if (A.deg(i) < B.deg(i)) return false;
        }
        return false;
    }
    else {
        return A.deg() < B.deg();
    }
}