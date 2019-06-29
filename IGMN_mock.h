#ifndef IGMN_MOCK
#define IGMN_MOCK

#include "MockUps.h"

namespace wag {

struct IGMN_mock: public Learner {

	std::string name() {
		return "IGMN";
	}
	bool init = false;
	bool timed = false;
	IGMN_mock(double tau = 0.04, double delta = 0.03, double spMin = 2, double vMin = 3, bool timed = 0) :
			igmn(tau, delta), tau(tau), delta(delta), spMin(spMin), vMin(vMin), timed(timed) {
	}

	void learn(Pontos p) override {
		time =0;
		if (!init) {
			auto range = getRange(p);
			igmn.init(range, tau, delta, spMin, vMin);
		}
		init = true;
		int i = 0;
		int num = p.size();
		MatrixXd m(2 + timed, num);
		double last = 0;


		for (auto& x : p) {
			m(0, i) = x.first;
			int j = 0;
			if(timed)
				m(1 , i) = time;


			m(1 + timed, i) = x.second;
			auto mat = m.block(0, i, m.rows(), 1);
			//std::cout<< "P:"<<x << std::endl;
			igmn.learn(mat);
			double novoY = (*this)(x.first);
			i++;
			timePlus();
		}
		time =0;
	}
	void learnSingle(double x, double y, double t) {
		MatrixXd m(2 + timed, 1);
		m(0, 0) = x;
		if (timed) {
			m(1, 0) = t;
		}
		m(1 + timed, 0) = y;
		auto mat = m.block(0, 0, m.rows(), 1);
		//std::cout<< "P:"<<x << std::endl;
		igmn.learn(mat);
	}
	double operator()(double d, double t = 0) {
		MatrixXd m(1 + timed, 1);
		m(0, 0) = d;
		int j = 0;
		if (timed) {
			m(1, 0) = t;
		}

		MatrixXd res = igmn.recall(m);
		double _res = res(0, 0);
		return _res;
	}

private:
	liac::IGMN igmn;

	double loop = 0;
	double tau, delta, spMin, vMin;

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
		std::vector<double> range(timed + 2);
		int i = 0;
		range[0] = xMax - xMin;
		if (timed)
			range[1] = 20;

		range[1+timed] = (yMax - yMin) * 10;
		for (auto& x : range) {
			if (x == 0)
				x = 1;
		}
		return range;
	}

};

}
#endif
