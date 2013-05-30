
#include "geom/bezier.h"
#include "math/polynomial.h"

#include <glibmm.h>

#include <iostream>
#include <math.h>

int main (int argc, char *argv[])
{
    g_test_init(&argc, &argv, NULL);

    std::vector<double> coef;
    coef.push_back(1.0);
    coef.push_back(2.0);
    coef.push_back(3.0);
    coef.push_back(4.0);
    coef.push_back(5.0);
    Ganash::Math::Polynomial p(coef);

    Ganash::Math::Polynomial p1(1.0, 2.0, 3.0);
    g_assert_cmpfloat(1.0,  ==, p1.f(0.0));
    g_assert_cmpfloat(6.0,  ==, p1.f(1.0));
    g_assert_cmpfloat(17.0,  ==, p1.f(2.0));

    Ganash::Math::Polynomial p2(1.0, 2.0, 3.0, 4.0);
    g_assert_cmpfloat(1.0,  ==, p2.f(0.0));
    g_assert_cmpfloat(10.0,  ==, p2.f(1.0));
    g_assert_cmpfloat(49.0,  ==, p2.f(2.0));

    Ganash::Math::Polynomial p3 = *p2.d();
    g_assert_cmpfloat(2.0,  ==, p3.f(0.0));
    g_assert_cmpfloat(20.0,  ==, p3.f(1.0));
    g_assert_cmpfloat(62.0,  ==, p3.f(2.0));


    Ganash::Math::Polynomial p4(1.0, 3.0, -4.0);
    std::vector<double> r = p4.roots();
    g_assert_cmpint(2,  ==, r.size());
    g_assert_cmpfloat(1.0,  ==, r.at(0));
    g_assert_cmpfloat(-0.25,  ==, r.at(1));

    Ganash::Geom::Bezier::Cubic bezier(0.0, 0.0,
                                       0.0, 4.0,
                                       4.0, 4.0,
                                       4.0, 0.0);
    Ganash::Geom::Rectangle rect = bezier.getBoundingBox();
    g_assert_cmpfloat(0.0,  ==, rect.x());
    g_assert_cmpfloat(0.0,  ==, rect.y());
    g_assert_cmpfloat(4.0,  ==, rect.width());
    g_assert_cmpfloat(3.0,  ==, rect.height());

    Ganash::Geom::Bezier::Cubic bezier_yoffset(1.0, 1.0,
                                               1.0, 5.0,
                                               5.0, 5.0,
                                               5.0, 1.0);
    Ganash::Geom::Rectangle rect_y = bezier_yoffset.getBoundingBox();
    g_assert_cmpfloat(1.0,  ==, rect_y.x());
    g_assert_cmpfloat(1.0,  ==, rect_y.y());
    g_assert_cmpfloat(4.0,  ==, rect_y.width());
    g_assert_cmpfloat(3.0,  ==, round(rect_y.height()));

    Ganash::Geom::Bezier::Cubic bezier_vertical(1.0, 1.0,
                                                5.0, 1.0,
                                                5.0, 5.0,
                                                1.0, 5.0);
    Ganash::Geom::Rectangle rect_v = bezier_vertical.getBoundingBox();
    g_assert_cmpfloat(1.0,  ==, rect_v.x());
    g_assert_cmpfloat(1.0,  ==, rect_v.y());
    g_assert_cmpfloat(3.0,  ==, round(rect_v.width()));
    g_assert_cmpfloat(4.0,  ==, rect_v.height());

    return g_test_run();
}
