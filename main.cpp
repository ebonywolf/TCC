
#include <iostream>
#include <bits/stdc++.h>
#include <armadillo>
#include "gnuplot-iostream.h"
#include <boost/tuple/tuple.hpp>
#include <GnuOutput.h>

#include <iostream>
#include <Eigen/Dense>
#include "igmn.h"

using namespace std;
struct Coord{
    double x,y;
};


using Matrix = arma::Mat<double>;
using Vetor=vector<double>;
double randomN()
{
    return (double) rand() / (double) RAND_MAX;
}
double normal( double media , double sigma )
{
    double x = randomN();
    double x2 = randomN();

    double pi2 = M_PI * 2;
    double var = sin( pi2 * x2 );
    double root = sqrt( -2.0 * log( x ) );
    double u = root * var;
    return u * sigma + media;
}

double getMean( Matrix vals ){
    double sum=0;
    for (auto x: vals) {
        sum+=x;
    }
    return sum/vals.size();
}
double getVariance( Vetor vals){
    double mean = getMean( vals);
    double sum=0;
    for (auto x: vals) {
        double alce = pow( (x - mean), 2.0);
        sum+=alce;

    }

    sum/= (vals.size()-1.0);
    return sqrt(sum);
}

double normalP( double x , double mean , double var )
{
    double u = mean;
    double o = var;
    double tope = ( -1*  pow(( x - u ),  2) );
    double bote = ( 2 * ( pow(o , 2) ) );
    double ee = ( tope / bote );
    double topy = exp( ee );
    double boty = ( o * sqrt( M_2_PI ) );
    double y = topy / boty;
    return y;
}
/*
double multiP( Matrix x ,  Matrix mean , Matrix var )
{
    double u = mean;
   double  o = det(var);
    double tope = ( -1*  pow(( x - u ),  2) );
    double bote = ( 2 * ( pow(o , 2) ) );
    double ee = ( tope / bote );
    double topy = exp( ee );
    double boty = ( o * sqrt( M_2_PI ) );
    double y = topy / boty;
    return y;
}
*/


double covariance (vector<Coord> vals, Coord var){
    double n = vals.size();
    double sum =0;
    for (auto val: vals) {
       sum+=(val.x -var.x) * (val.y*var.y);
    }
    return sum/(n-1.0);
}
double covarianceVector(Matrix a, Matrix b){
    double n = a.n_cols;

    if(n != b.n_cols )throw runtime_error("Different size A and B");

    double varA =getMean(a);
    double varB = getMean(b);
    double sum = 0;

    for (int i = 0; i < n; i++) {
        double alce =  (a[i]  -  varA  )*(b[i] -varB);
        sum+=alce;

    }
    return sum/(n-1);
}
Matrix covarianceMatrix(Matrix a, Matrix b){
    if(a.is_vec() && b.is_vec()){
        Matrix ans(1,1);
        ans(0,0)=covarianceVector(a ,b);
        return ans;
    }

    Matrix ans (a.n_cols, b.n_cols);
    for (int i = 0; i < a.n_cols; i++) {
        for (int j = 0; j < b.n_cols; j++) {
            Matrix f1 = a.col(i).t();
            Matrix f2 = b.col(j).t();
            double covar = covarianceVector(f1,f2);
            ans(i,j) = covar;
        }

    }
    return ans;
}


struct Gaussian {
    double mean, sigma;
    Gaussian(double mean, double sigma):mean(mean),sigma(sigma){//mediam and deviation

    }
    double pdf(double dataPoint){
        return normalP(dataPoint, mean, sigma);
    }
    double operator()(double x){
        return normalP(x, mean, sigma);
    }
};

struct GaussianMixture{
    vector<Gaussian> gaussians;
    double mix;
    GaussianMixture(int number, double mix=0.5):mix(mix){
        for (int i = 0; i < number; i++) {
            gaussians.push_back(  Gaussian( rand()%3+5,   rand()%3+5      ));
        }
    }
};



using Pontos =   std::vector<std::pair<double, double> >;
template<class T>
Pontos createPontos(int  n, double min, double max, T func){
    double step = (max-min)/(double)n;
    Pontos pts;
    for (double i = min; i < max; i+=step) {
        pts.push_back(std::make_pair(i,func(i)));
    }
    return pts;
}


using Eigen::MatrixXd;

template <class T>
void meuswap(T& t, T& t2){
	auto alce =t;
	t = t2;
	t2=alce;
}

template <class M>
void inv(M& m, int num){
for (int i = 0; i < num/2; i++) {
		auto alce = m(0,i);
		auto alce2 = m(1, i);
		m(0,i) = m(0,num-i-1);
		m(1,i) = m(1,num-i-1);

		m(0,num-i-1) = alce;
		m(1,num-i-1) = alce2;
	}
}

template <class T>
void randomize(T& m, int num){
	for (int i = 0; i < num; i++) {
		int s1 = rand()%num;

		meuswap( m(0,i), m(0,s1) );
		meuswap( m(1,i), m(1,s1) );
	}
}


int main()
{
    std::cout<< "Hello world" << std::endl;
    std::cout << Statistic::chi2inv(12, 2) <<std::endl;
    vector<double> range (2);
    range[0] = range[1] = 2;

    liac::IGMN loigmn(range, 0.1, 0.3);

    //cout<<loigmn<<endl;
    int num = 63;
    MatrixXd m(2, num);
    int i = 0;

    vector<double> inputs(num);
    for (float x = 0; x <= 2 * Constants::PI && i < num; x += 0.1f)
    {
        m(0, i) = x;
        m(1, i) = std::sin(x);
        i++;
    }

    inv(m,num);
   // randomize(m, num);

    loigmn.train(m);
    wag::Plotter plot;

    double sum=0;

    for (int j = 0; j < i; j++)
    {
        MatrixXd input = m.block(0, j, 1, 1);
        MatrixXd res = loigmn.recall(input);
        double _in = input(0,0);
        double _res = res(0,0);
        sum += (_in-_res)*(_in-_res);


        cout << "Input: " << input  << " Real: " << m(1, j) << " Recall: " << res << endl;
    }
    sum/=(double)i;

    cout<<"Error:"<<sum;

}

