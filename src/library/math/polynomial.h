#ifndef GANASH_GEOM_POLYNOMIAL_H
#define GANASH_GEOM_POLYNOMIAL_H

#include <ostream>
#include <vector>

namespace Ganash {
namespace Math {

class Polynomial
{
public :
    Polynomial(std::vector<double> a);
    Polynomial(double a0, double a1=0.0, double a2=0.0, double a3=0.0);
    inline int degree() const { return _degree;}
    double f(double x);
    std::vector<double> roots();
    Polynomial* d();
    std::vector<double> _a;

    Polynomial& operator+=(const Polynomial & polynomial);
protected:
    int _degree;
    void compute_degree();
};


} // namespace Math
} // namespace Ganash

std::ostream& operator <<(std::ostream& stream, const Ganash::Math::Polynomial& polynomial);

#endif // GANASH_GEOM_POLYNOMIAL_H
