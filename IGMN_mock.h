#ifndef IGMN_MOCK
#define IGMN_MOCK

#include "MockUps.h"

namespace wag {

struct IGMN_mock: public Learner {

	std::string name() {
		return "IGMN";
	}
	bool init = false;

	IGMN_mock(double tau = 0.04, double delta = 0.03, double spMin = 2, double vMin = 3, int rMax = 0) :
			igmn(tau, delta), tau(tau), delta(delta), spMin(spMin), vMin(vMin), rMax(rMax), recurssion(rMax) {
	}

	void learn(Pontos p) override {
		RecurssiveVector recurssionMemory = recurssion;

		if(!init){
		    auto range = getRange(p);
		    igmn.init(range, tau, delta, spMin, vMin);
		}
		init = true;
		int i = 0;
		int num = p.size();
		MatrixXd m(2 + rMax, num);
		double last = 0;
		for (auto& x : p) {

			m(0, i) = x.first;
			int j = 0;
			for (auto& r : recurssion) {
				m(1 + j, i) = r;
				j++;
			}

			m(1 + rMax, i) = x.second;
			auto mat = m.block(0, i, m.rows(), 1);
			//std::cout<< "P:"<<x << std::endl;
			igmn.learn(mat);
			double novoY = (*this)(x.first);
			i++;

		}
		recurssion = recurssionMemory;
	}

	Result printResult(Pontos p, std::ostream& os) {
	    if(!init){
	        auto range = getRange(p);
	        igmn.init(range, tau, delta, spMin, vMin);
	        init = true;
	    }
		//   wag::Plotter plot;
		RecurssiveVector recurssionMemory = recurssion;
		Result result;
		double mean = 0;
		for (auto& x : p) {
			mean += x.second;
		}
		mean /= (double) p.size();
		double sum = 0;
		double sum2 = 1;
		for (auto& x : p) {
			double my = (*this)(x.first);
			double y = x.second;
			double alce = (my - y) * (my - y);
			sum += alce;
			double alce2 = (mean - y) * (mean - y);
			sum2 += alce2;
			result.pontos.push_back(std::make_pair(x.first, my));
			learnSingle(x.first, y);
		}
		result.error = sum / sum2;

		recurssion = recurssionMemory;
		return result;
	}
	void learnSingle(double x, double y){
		MatrixXd m(2 + rMax,1);
		m(0, 0) = x;
		int j = 0;
		for (auto& r : recurssion) {
			m(1 + j, 0) = r;
			j++;
		}
		m(1 + rMax, 0) = y;
		auto mat = m.block(0, 0, m.rows(), 1);
		//std::cout<< "P:"<<x << std::endl;
		igmn.learn(mat);
		double novoY = (*this)(x);

	}
	double operator()(double d) {
		MatrixXd m(1 + rMax, 1);

		// MatrixXd m(1,1);
		m(0, 0) = d;
		int j = 0;
		for (auto& r : recurssion) {
			m(1 + j, 0) = r;
			j++;
		}
		MatrixXd res = igmn.recall(m);
		double _res = res(0, 0);

		recurssion.push(d);

		return _res;
	}

private:
	liac::IGMN igmn;
	RecurssiveVector recurssion;

	double loop = 0;
	double tau, delta, spMin, vMin;
	int rMax;

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
		std::vector<double> range(rMax + 2);

		int i = 0;
		for (; i < range.size() - 1; i++) {
			range[i] = xMax - xMin;
		}
		range[i] = (yMax - yMin)*10;

		for (auto& x : range) {
			if (x == 0)
				x = 1;
		}
		return range;
	}

};

}
#endif
