#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <cassert>
#include "Bspline.hpp"
#include <cmath>
using std::sin;
using std::fabs;

double f(double x) {return sin(x); } 
int main()
{
    const double pi = 3.1415926535897932384626433832795029;
    vector<double> x;
    vector<double> y;
    size_t N = 20;
    x.resize(N); y.resize(N);
    for (size_t i = 0; i < N; ++i)
    {
        x[i] = i*2.*pi/N;
        y[i] = f(x[i]);
    }
    Bspline bspl(x,y);
    for (size_t i = 0; i <100; ++i){
        double xx = i*2.*pi/100;
        cout << xx << "\t" << bspl(xx) << "\t" <<  fabs(bspl(xx)-f(xx)) << endl;
    }
    return 0;
}
