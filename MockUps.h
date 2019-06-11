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

#include "IGMN/igmn.h"

struct Learner {
	Learner() {
	}
	virtual ~Learner() {
	}
	virtual void learn(Pontos p)=0;
	virtual Result printResult(Pontos p, std::ostream& os)=0;
	virtual double operator()(double d)=0;
	virtual std::string name()=0;

};

struct RecurssiveVector: public std::list<double> {
	int max;
	RecurssiveVector(int n) :
			max(n) {
		for (int i = 0; i < n; i++) {
			push_back(0);
		}
	}
	;
	void push(double val) {

		push_front(val);
		if (size() == max+1) {
			pop_back();
		}
	}

};

struct FFNN_mock: public Learner {
	FFNN_mock();
	~FFNN_mock() {
	}
	void learn(Pontos p);
	Result printResult(Pontos p, std::ostream& os);
	double operator()(double d);
	std::string name() {
		return "FFNN";
	}
	tiny_dnn::network<tiny_dnn::sequential> nn;

};

} /* namespace wag */

#endif /* MOCKUPS_H_ */
