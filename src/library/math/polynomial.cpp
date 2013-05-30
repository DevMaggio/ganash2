#include "polynomial.h"

#include <math.h>
#include <iostream>

/* zsolve_cubic.c - finds the complex roots of x^3 + a x^2 + b x + c = 0 */
typedef struct complex_t
{
    double r;
    double i;
}Complex;

int
gsl_poly_complex_solve_cubic (double a, double b, double c,
                              Complex *z0, Complex *z1,
                              Complex *z2)
{
  double q = (a * a - 3 * b);
  double r = (2 * a * a * a - 9 * a * b + 27 * c);

  double Q = q / 9;
  double R = r / 54;

  double Q3 = Q * Q * Q;
  double R2 = R * R;

  double CR2 = 729 * r * r;
  double CQ3 = 2916 * q * q * q;

  if (R == 0 && Q == 0)
    {
      z0->r = -a / 3;
      z0->i = 0;
      z1->r = -a / 3;
      z1->i = 0;
      z2->r = -a / 3;
      z2->i = 0;
      return 3;
    }
  else if (CR2 == CQ3)
    {
      /* this test is actually R2 == Q3, written in a form suitable
         for exact computation with integers */

      /* Due to finite precision some double roots may be missed, and
         will be considered to be a pair of complex roots z = x +/-
         epsilon i close to the real axis. */

      double sqrtQ = sqrt (Q);

      if (R > 0)
        {
          z0->r = -2 * sqrtQ - a / 3;
          z0->i = 0;
          z1->r = sqrtQ - a / 3;
          z1->i = 0;
          z2->r = sqrtQ - a / 3;
          z2->i = 0;
        }
      else
        {
          z0->r = -sqrtQ - a / 3;
          z0->i = 0;
          z1->r = -sqrtQ - a / 3;
          z1->i = 0;
          z2->r = 2 * sqrtQ - a / 3;
          z2->i = 0;
        }
      return 3;
    }
  else if (CR2 < CQ3)  /* equivalent to R2 < Q3 */
    {
      double sqrtQ = sqrt (Q);
      double sqrtQ3 = sqrtQ * sqrtQ * sqrtQ;
      double theta = acos (R / sqrtQ3);
      double norm = -2 * sqrtQ;
      double r0 = norm * cos (theta / 3) - a / 3;
      double r1 = norm * cos ((theta + 2.0 * M_PI) / 3) - a / 3;
      double r2 = norm * cos ((theta - 2.0 * M_PI) / 3) - a / 3;

      /* Sort r0, r1, r2 into increasing order */

      double tmp;
      if (r0 > r1)
      {
          tmp = r1;
          r1 = r0;
          r0 = tmp;
      }

      if (r1 > r2)
        {
          tmp = r2;
          r2 = r1;
          r1 = tmp;

          if (r0 > r1)
          {
              tmp = r1;
              r1 = r0;
              r0 = tmp;
          }
        }

      z0->r = r0;
      z0->i = 0;

      z1->r = r1;
      z1->i = 0;

      z2->r = r2;
      z2->i = 0;

      return 3;
    }
  else
    {
      double sgnR = (R >= 0 ? 1 : -1);
      double A = -sgnR * pow (fabs (R) + sqrt (R2 - Q3), 1.0 / 3.0);
      double B = Q / A;

      if (A + B < 0)
        {
          z0->r = A + B - a / 3;
          z0->i = 0;

          z1->r = -0.5 * (A + B) - a / 3;
          z1->i = -(sqrt (3.0) / 2.0) * fabs(A - B);

          z2->r = -0.5 * (A + B) - a / 3;
          z2->i = (sqrt (3.0) / 2.0) * fabs(A - B);
        }
      else
        {
          z0->r = -0.5 * (A + B) - a / 3;
          z0->i = -(sqrt (3.0) / 2.0) * fabs(A - B);

          z1->r = -0.5 * (A + B) - a / 3;
          z1->i = (sqrt (3.0) / 2.0) * fabs(A - B);

          z2->r = A + B - a / 3;
          z2->i = 0;
        }

      return 3;
    }
}

Ganash::Math::Polynomial::Polynomial(std::vector<double> a) :
    _a(a)
{
    compute_degree();
}

Ganash::Math::Polynomial::Polynomial(double a0, double a1, double a2, double a3)
{
    _a.push_back(a0);
    _a.push_back(a1);
    _a.push_back(a2);
    _a.push_back(a3);
    compute_degree();
}

double Ganash::Math::Polynomial::f(double x)
{
    double ret = 0.0;
    for(int i=0; i<_a.size(); i++)
    {
        ret += _a[i] * pow(x, i);
    }
    return ret;
}

void Ganash::Math::Polynomial::compute_degree()
{
    _degree = 0;
    for(int i=_a.size()-1; i>=0; i--)
    {
        if(_a[i] != 0.0)
        {
            _degree = i;
            break;
        }
    }
}

std::vector<double> Ganash::Math::Polynomial::roots()
{
    std::vector<double> r;

    switch(_degree)
    {
    case 0:
        break;
    case 1:
        {
            r.push_back(-_a[0]/_a[1]);
        }
        break;
    case 2:
        {
            double delta = (_a[1] * _a[1]) - (4 * _a[2] * _a[0]);
            if(delta>0.0)
            {
                r.push_back((- _a[1] - pow(delta, 0.5)) / (2 * _a[2]));
                r.push_back((- _a[1] + pow(delta, 0.5)) / (2 * _a[2]));
            }
            else if(delta==0.0)
            {
                r.push_back(- _a[1] / (2 * _a[2]));
            }
        }
        break;
    case 3:
        {
            // _a[3]x^3 + _a[2]x^2 + _a[1]x + _a[0]
            Complex z0;
            Complex z1;
            Complex z2;
            int num = gsl_poly_complex_solve_cubic(_a[2]/_a[3], _a[1]/_a[3], _a[0]/_a[3], &z0, &z1, &z2);
            if(z0.i==0.0)
            {
                r.push_back(z0.r);
            }
            if(z1.i==0.0)
            {
                r.push_back(z1.r);
            }
            if(z2.i==0.0)
            {
                r.push_back(z2.r);
            }
        }
        break;
    default:
        break;
    }

    return r;
}
Ganash::Math::Polynomial* Ganash::Math::Polynomial::d()
{
    std::vector<double> r;

    switch(_degree)
    {
    case 0:
        r.push_back(0.0);
        break;
    case 1:
        r.push_back(_a[1]);
        break;
    case 2:
        {
            r.push_back(_a[1]);
            r.push_back(2*_a[2]);
        }
        break;
    case 3:
        {
            r.push_back(_a[1]);
            r.push_back(2*_a[2]);
            r.push_back(3*_a[3]);
        }
        break;
    default:
        break;
    }

    return new Ganash::Math::Polynomial(r);
}

std::ostream& operator <<(std::ostream& stream, const Ganash::Math::Polynomial &polynomial)
{
    char pow[10][4] = {"⁰", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹"};
    int len = 0;
    for(int i = polynomial._a.size()-1; i >= 0; i--)
    {
        if(polynomial._a[i] == 0.0)
        {
            continue;
        }

        if(len > 0)
        {
            stream << " + " ;
        }

        stream << polynomial._a[i];
        if(i > 0)
        {
            stream  << "*x";
        }

        if(i > 1)
        {
            stream << pow[i];
        }
        len++;
    }
    return stream;
}

Ganash::Math::Polynomial& Ganash::Math::Polynomial::operator+=(const Ganash::Math::Polynomial &polynomial)
{
    int len = std::max(degree(), polynomial.degree());
    if(len>degree())
    {
        _a.resize(len+1);
    }

    int empty = 0;
    for(int i=len; i>=0; i--)
    {
        _a[i] += polynomial._a[i];
        if(_a[i]!=0.0 && empty==0)
        {
             empty=i;
        }
    }
    _degree = empty;
    return *this;
}
