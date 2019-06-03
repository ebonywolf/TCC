#include <iostream>
#include <bits/stdc++.h>
#include <GnuOutput.h>

#include "Coord.h"
#include "Simulator.h"
#include "PointsGenerator.h"

using namespace std;
using namespace wag;
using Vetor=std::vector<double>;

template<class T>
void meuswap( T& t , T& t2 )
{
    auto alce = t;
    t = t2;
    t2 = alce;
}

void inv( Pontos& m )
{
    auto num = m.size();
    for ( int i = 0 ; i < num / 2 ; i++ )
    {
        meuswap( m[i] , m[num - i - 1] );
    }
}

void randomize( Pontos& m )
{
    auto num = m.size();
    for ( int i = 0 ; i < num ; i++ )
    {
        int s1 = rand() % num;
        meuswap( m[i] , m[s1] );
    }
}

void swapHalf( Pontos& m )
{
    auto num = m.size();
    for ( int i = 0 ; i < num / 2 ; i++ )
    {
        meuswap( m[i] , m[ ( num / 2 ) + i] );
    }
}

double x0( double x )
{
    return 1;
}
double x1( double x )
{
    return x;
}
double x2( double x )
{
    return x * x;
}
double x3( double x )
{
    return x * x * x;
}
double x4( double x )
{
    return x * x * x * x;
}
double seno( double x)
{
	return std::sin(x);
}


int main( int argc , char** argv )
{
	//test();
	//return 0;

    Parameters params;
    params.start = -4;
    params.end = 4;
    params.points = 100;
    params.maxTime=3;

    Pontos p = PointsGenerator::createPoints(x2,x1,params);
   // params.modifier =randomize;
    Simulator simu;
    FFNN_mock ffnn;
    IGMN_mock igmn;

    simu.Simulate(seno, igmn , p);
  //  vector<double> range = { params.start, params.end };


}

