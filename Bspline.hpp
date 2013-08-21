#ifndef BSPLINE_HPP_
#define BSPLINE_HPP_

#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <cassert>
#include <cstdlib>
#include <algorithm>
using std::max;

extern "C" {
    void curfit_(int&,int&,float[],float[],float[],float&,float&,int&,float&,int&,int&,float[],float[],float&,float[],int&,int[],int&);
}
extern "C" {
    void splev_(float[], int&, float[], int&, float[], float[], int&, int&); 
}


class Bspline {
private:
    int iopt, m;
    float *x;
    float *y;
    float *w;
    float xb, xe;
    int k;
    float s;
    int nest,n;
    float* t;
    float* c;
    float fp;
    float* wrk;
    int lwrk;
    int* iwrk;
    int ier;
public:
    Bspline(vector<double> x_, vector<double> y_) : iopt(0), k(3), s(0.)
    {
        assert(x_.size() == y_.size());
        int lwa;
        float * wa;
        m = x_.size();
        x = new float[m];
        y = new float[m];
        for (int i = 0; i < m; ++i)
        {
            x[i] = float(x_[i]); y[i] = float(y_[i]);
        }
        w = new float[m];
        for (int i = 0; i < m; ++i)
            w[i] = 1.;
        xb = x[0]; xe = x[m-1];
        nest = max(m + k +1,2*k+3);
        
        lwrk = m*(k+1) + nest*(7+3*k);
        lwa = 3*nest + lwrk;
        wa = new float[lwa];
        t = wa;
        c = t + nest;
        wrk = c + nest;
        iwrk = (int *)(wrk + lwrk);
        
        curfit_(iopt,m,x,y,w,xb,xe,k,s,nest,n,t,c,fp,wrk,lwrk,iwrk,ier);
        delete wa;
    }
    ~Bspline()
    {
        delete x;
        delete y;
        delete w;
    }
    double operator()(float xx)
    {
        //assert(xx <= xe and xx >= xb);
        float xxx[1], yyy[1];
        xxx[0] = xx;
        int ierr;
        int mm = 1;
        splev_(t,n,c,k,xxx,yyy,mm,ierr);
        return yyy[0];
    }
};

#endif // BSPLINE_HPP_
