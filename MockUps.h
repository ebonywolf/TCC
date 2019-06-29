#ifndef MOCKUPS_H_
#define MOCKUPS_H_

#include "PointsGenerator.h"

#include "GnuOutput.h"
#include <tiny_dnn/tiny_dnn.h>
#include "IGMN/igmn.h"
namespace wag {

using Matriz = std::vector<std::vector<double>>;

struct Result {
	Pontos pontos;
	double error;
};
struct TestResult{
	Result train,test;
};

#include "IGMN/igmn.h"

struct Learner {
	Learner() {
	}
	virtual ~Learner() {
	}
	virtual void learn(Pontos p)=0;

	Result printResult(Pontos p, bool learn){
			Result result;
			double mean = 0;
			for (auto& x : p) {
				mean += x.second;
			}
			mean /= (double) p.size();
			double sum = 1;
			double sum2 = 1;
			for (auto& x : p) {
				double my = (*this)(x.first, time);
				double y = x.second;
				double alce = (my - y) * (my - y);
				sum += alce;
				double alce2 = (mean - y) * (mean - y);
				sum2 += alce2;
				result.pontos.push_back(std::make_pair(x.first, my));
				if (learn)
					learnSingle(x.first, y, time);
				timePlus();
			}
			result.error = sum / sum2;
			return result;
	}

	virtual double operator()(double d, double t=0)=0;
	virtual void learnSingle(double x,double y, double t)=0;
	virtual std::string name()=0;
	void timePlus(){
		time+=0.02;
		//if(time>10)time=0;
	}
	double time=0;
};

struct RecurssiveVector: public std::list<double> {
	int max;
	RecurssiveVector(int n) :
			max(n) {
		for (int i = 0; i < n; i++) {
			push_back(0);
		}
	}

	void push(double val) {
		push_front(val);
		if (size() == max+1) {
			pop_back();
		}
	}

};

struct FFNN_mock: public Learner {

	FFNN_mock(int layers=20, bool timed=0);
	~FFNN_mock() {
	}
	void learn(Pontos p);
	double operator()(double, double t=0);
	void learnSingle(double, double, double);
	std::string name() {
		return "FFNN";
	}

private:
	tiny_dnn::network<tiny_dnn::sequential> nn;
	//RecurssiveVector recurssion;
	bool timed;
	double time;

	tiny_dnn::vec_t toInput(double n,double t);
};

} /* namespace wag */

#endif /* MOCKUPS_H_ */
