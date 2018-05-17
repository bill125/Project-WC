#ifndef POLYNOME_H_
#define POLYNOME_H_

#include "monome.h"
#include <vector>

class Polynome
{
public:
    Polynome() {}
    ~Polynome() {}

    Polynome& operator=(const Polynome & A)
    {  
        seta(A.mono());
        return *this;
    }
    friend Polynome operator*(const Polynome & A, const Polynome & B);
    friend Polynome operator*(const Polynome & A, const double & c);
    friend Polynome operator-(const Polynome & A, const Polynome & B);
    friend Polynome operator+(const Polynome & A, const Polynome & B);
    friend bool operator==(const Polynome & A, const Polynome & B);

    double eval(const std::vector<double> & x);
    int deg() const;
    std::vector<Monome> mono() const;
    std::vector<double> coef() const;

    int size() const;
    void seta(const std::vector<Monome> & _a);
    void setcoef(int i, int c);
    std::vector<Monome> mergeMonome(const std::vector<Monome> & a);

protected:
    std::vector<Monome> a;

};

#endif