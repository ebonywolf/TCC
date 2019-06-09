#include <iostream>
#include <bits/stdc++.h>
#include <GnuOutput.h>

#include "Coord.h"
#include "Simulator.h"
#include "PointsGenerator.h"
#include "Config.h"

using namespace std;
using namespace wag;
using Vetor=std::vector<double>;

template<class T>
void meuswap(T& t, T& t2) {
	auto alce = t;
	t = t2;
	t2 = alce;
}

void inv(Pontos& m) {
	auto num = m.size();
	for (int i = 0; i < num / 2; i++) {
		meuswap(m[i], m[num - i - 1]);
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
		meuswap(m[i], m[(num / 2) + i]);
	}
}

double x0(double x) {
	return 1;
}
double x1(double x) {
	return x;
}
double x2(double x) {
	return -5.0 * (x * x) / 3.0 + 2 * x - 4;
}
double x3(double x) {
	return x * x * x;
}
double x4(double x) {
	return x * x * x * x;
}
double seno(double x) {
	return std::sin(x);
}

std::vector<double> getRange(Pontos p) {
	double xMin = 99999, yMin = 99999, xMax = -99999, yMax = -99999;
	for (auto& c : p) {
		if (c.first < xMin) {
			xMin = c.first;
		}
		if (c.second < yMin) {
			yMin = c.second;
		}
		if (c.second > yMax) {
			yMax = c.second;
		}
		if (c.first > xMax) {
			xMax = c.first;
		}
	}
	std::vector<double> range = { xMax - xMin, yMax - yMin };
	if(range[0]==0)range[0]=1;
	if(range[1]==0)range[1]=1;

	return range;
}

int main(int argc, char** argv) {
	//test();
	//return 0;

	Config config = Config::ReadFile("test.json");

	for (auto& funcs : config.functions) {
		for (auto& timeFuncs : config.timeFunctions) {
			Pontos p = PointsGenerator::createTestPoints(funcs, timeFuncs);
			Simulator simu;
			FFNN_mock ffnn;
			std::vector<double> range = getRange(p);
			std::cout<< "Pontos"<<p.size() << std::endl;
			for (auto& x: p) {
				std::cout<< "X "<<x.first<<" Y "<<x.second << std::endl;
			}

			std::cout << "Range:" << range[0] << " " << range[1] << std::endl;

			IGMN_mock igmn(range, 0.04, 0.1);
			simu.Simulate(igmn, p, "f");

		}
	}

	// params.modifier =randomize;

	//simu.Simulate( ffnn , p);

}

