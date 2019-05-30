#include "Simulator.h"
#include "IGMN/igmn.h"

namespace wag {

static const std::vector<double> range = { 2, 2 };

FFNN_mock::FFNN_mock() {
	nn = BasicNN({1,3,2,1});



}

void FFNN_mock::learn(Pontos p) {
	PropagationTrainer trainer(&nn);
	Plotter plot;
	plot.addPontos("F(x)", p);

	for (int i = 0; i < 100000; i++) {
		if(i==231){
			int a=1;
		}
		trainer.train(p);
/*
		//usleep(2*1000);
		std::cout<< "=====LAYERS=====" << std::endl;
		for (auto& x: nn.layers) {
			std::cout<< x << std::endl;
		}
		std::cout<< "Bias" << std::endl;
		for (auto& x: nn.bias) {
			std::cout<< x << std::endl;
		}
		std::cout<< "" << std::endl;
*/
		//getchar();
		auto result=printResult(p,cout);
		plot.pontos["FFNN"].clear();
		plot.addPontos("FFNN", result.pontos);
		plot.plot();
	}
}
Result FFNN_mock::printResult(Pontos p, std::ostream& os) {
	Result result;
	double sum;
	for (auto& x : p) {
		double _in = x.second;
		double _res = nn(x.first);
		result.pontos.push_back(std::make_pair(x.first, _res));
	//	std::cout<< "P:"<<x.first<<" "<<_res << std::endl;
		sum += (_in - _res) * (_in - _res);
	}
	sum /= (double) p.size();
	result.error = sum;
	return result;
}
double FFNN_mock::operator()(double d) {
	return nn(d);
}

GeneNN_mock::GeneNN_mock() {
}
void GeneNN_mock::learn(Pontos p) {
	NNTrainer nntrainer;

	nn = nntrainer.trainFromPoints(p);
	//nntrainer.trainBasicFunction(f);
}

Result GeneNN_mock::printResult(Pontos p, std::ostream& os) {
	Result result;
	double sum;
	for (auto& x : p) {
		double _in = x.second;
		double _res = nn(x.first);
		result.pontos.push_back(std::make_pair(x.first, _res));

		sum += (_in - _res) * (_in - _res);
	}
	sum /= (double) p.size();
	result.error = sum;
	return result;
}

double GeneNN_mock::operator()(double d) {
	return nn(d);
}

IGMN_mock::IGMN_mock(double tau, double delta, double spMin, double vMin, std::vector<double> range) :
		igmn(tau, delta) {

	igmn.init(range, tau, delta, spMin, vMin);

}

void IGMN_mock::learn(Pontos p) {

	int i = 0;
	int num = p.size();
	MatrixXd m(2, num);
	for (auto& x : p) {
		m(0, i) = x.first;
		m(1, i) = x.second;
		i++;
	}

	igmn.train(m);
//	igmn.train(m);
	//igmn.train(m);
}

Result IGMN_mock::printResult(Pontos p, std::ostream& os) {
	//   wag::Plotter plot;
	double sum = 0;
	int i = 0;
	int num = p.size();
	MatrixXd m(2, num);
	for (auto& x : p) {
		m(0, i) = x.first;
		m(1, i) = x.second;
		i++;
	}
	Result result;

	for (int j = 0; j < i; j++) {
		MatrixXd input = m.block(0, j, 1, 1);
		MatrixXd res = igmn.recall(input);
		double _in = m(1, j);
		double _res = res(0, 0);
		result.pontos.push_back(std::make_pair(m(0, j), _res));
		sum += (_in - _res) * (_in - _res);
	}
	sum /= (double) i;
	result.error = sum;
	return result;
}

double IGMN_mock::operator()(double d) {
	MatrixXd m(1, 1);
	m(0, 0) = d;
	MatrixXd res = igmn.recall(m);
	double _res = res(0, 0);
	return _res;
}

}

