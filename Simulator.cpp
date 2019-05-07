#include "Simulator.h"
#include "IGMN/igmn.h"

namespace wag {

static const vector<double> range = {2,2} ;

FFNN_mock::FFNN_mock(){
}
void FFNN_mock::learn(Pontos p){
    NNTrainer nntrainer;
    nn = nntrainer.trainFromPoints(p);
    //nntrainer.trainBasicFunction(f);
}

Result FFNN_mock::printResult(Pontos p, std::ostream& os){
	Result result;
	double sum;

	for (auto& x: p) {
		double _in =2;// nn(x.first) ;
		double _res = x.second ;
		result.pontos.push_back(std::make_pair(x.first, _res));
		sum += (_in - _res) * (_in - _res);
	}

	sum /= (double) p.size();
	result.error = sum;
	return result;
}

double FFNN_mock::operator()(double d){
	return nn(d);
}


IGMN_mock::IGMN_mock(double tau, double delta):
		igmn(range,tau,delta) {
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
	m(0,0)=d;
	MatrixXd res = igmn.recall(m);
	double _res = res(0, 0);
	return _res;
}


}
