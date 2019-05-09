
#include <bits/stdc++.h>
#include <GnuOutput.h>

#include "Coord.h"

#include "Simulator.h"


using namespace std;
using namespace wag;
using Vetor=vector<double>;

template<class T>
void meuswap(T& t, T& t2) {
	auto alce = t;
	t = t2;
	t2 = alce;
}

void inv(Pontos& m) {
	auto num = m.size();
	for (int i = 0; i < num / 2; i++) {
		meuswap(m[i], m[num - i - 1] );
	}
}

void randomize(Pontos& m) {
	auto num = m.size();
	for (int i = 0; i < num; i++) {
		int s1 = rand() % num;
		meuswap(m[i], m[s1]);
	}
}

void swapHalf(Pontos& m) {
	auto num = m.size();
	for (int i = 0; i < num / 2; i++) {
		meuswap(m[i], m[(num/2)+ i] );
	}
}

double x0(double x){return 1;}
double x1(double x){return x;}
double x2(double x){return x*x;}
double x3(double x){return x*x*x;}
double x4(double x){return x*x*x*x;}


int main(int argc, char** argv) {


	Parameters params;
	params.start= -3;
	params.end= 3;
	params.points=100;
//	params.modifier =

	FFNN_mock ffnn;
	IGMN_mock igmn;

	//Simulator::Simulate(x4, ffnn, params);

	Simulator::Simulate(x3, igmn, params);
	/*
//	ArtmapModelStub stub(1,1);
//	stub.test(in, out)
	Simulator::SimulateIgmn(x2, -3, 3,10);
	Simulator::SimulateIgmn(x2, -3, 3,500);
	Simulator::SimulateIgmn(x2, -3, 3,10000);

	*/
	//Simulator::Simulate(func, nn, params)

}

