#ifndef MONOME_H_
#define MONOME_H_

#include <vector>

class Monome
{
public:
    Monome() { reset(); }
    ~Monome() {}

    Monome& operator=(const Monome & A)
    {      
        int n = A.size();
        reset(n);
        setc(A.coef());
        for (int i = 0; i < n; ++ i) {
            b[i] = A.deg(i);
        }
        return *this;
    }
    friend Monome operator*(const Monome & A, const Monome & B);
    friend Monome operator*(const Monome & A, const double & c);
    friend bool operator==(const Monome & A, const Monome & B);
    friend bool operator<(const Monome & A, const Monome & B);

    double eval(const std::vector<double> & x);
    int deg() const;
    int deg(int i) const;
    double coef() const;
    std::vector<Monome> grad();

    int size() const;
    void reset(int n = 0);
    void setb(const std::vector<int> & _b);
    void setc(double c);
    void setdeg(int i, int deg);
    void print();

protected:
    std::vector<int> b;
    double c;

    double pow(double x, int b);
};

#endif