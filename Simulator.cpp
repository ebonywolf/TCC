#include "Simulator.h"
#include "IGMN/igmn.h"

namespace wag {
using Matriz = std::vector<std::vector<double>>;

static const std::vector<double> range = { 2, 2 };

Matriz pontosToMat(Pontos p){
	Matriz m;
	for (auto& x: p) {
		std::vector<double> tu(2);
		tu[0]=x.first;
		tu[1]=x.second;
		m.push_back(tu);
	}
	return m;
}

FFNN_mock::FFNN_mock() {
int n=20;
	nn << tiny_dnn::fully_connected_layer(1, n);
	nn << tiny_dnn::sigmoid_layer();
	nn << tiny_dnn::fully_connected_layer(n, n);
	nn << tiny_dnn::sigmoid_layer();
	nn << tiny_dnn::fully_connected_layer(n, 1);

}
void FFNN_mock::learn(Pontos p) {
//	Matrix<double> mat = pontosToMat(p);
	std::vector<tiny_dnn::vec_t> X;
	 std::vector<tiny_dnn::vec_t> Y;
	 for (auto& x: p) {
		X.push_back({x.first});
		Y.push_back({x.second});
	}
	 Plotter plotter;
	 plotter.addPontos("F(x)", p);
	// vector<double> vDoubles(vFloats.begin(), vFloats.end());
	size_t batch_size = 16;    // 16 samples for each network weight update
	  int epochs        = 1000;  // 2000 presentation of all samples
	  tiny_dnn::gradient_descent opt;

	  // this lambda function will be called after each epoch
	  int iEpoch              = 0;
	  auto on_enumerate_epoch = [&]() {
	    // compute loss and disp 1/100 of the time
	    iEpoch++;
	    if (iEpoch % 50) return;
	    std::cout<< "Epoch:"<< iEpoch<< std::endl;
	    Result result=printResult(p,cout);
	    plotter.pontos["NN"]=result.pontos;
	    plotter.plot();
	  };
	  // learn
	  std::cout << "learning the sinus function with 2000 epochs:" << std::endl;
	  nn.fit<tiny_dnn::mse>(opt, X, Y, batch_size, epochs, []() {},
	                         on_enumerate_epoch);

}
Result FFNN_mock::printResult(Pontos p, std::ostream& os) {
	Result result;
	for (auto& ponto: p) {
		double x =ponto.first;
		auto ans = (*this)(x);
		result.pontos.push_back(std::make_pair(x, ans));
	}
	return result;
}
double FFNN_mock::operator()(double d) {
//	std::vector<double> inputs{d};
//	nn.get_multilayer_perceptron_pointer()->calculate_outputs(inputs);
	tiny_dnn::vec_t alce ={d};
	auto resu = nn.predict(alce);
	double ans = resu[0];
}




IGMN_mock::IGMN_mock(std::vector<double> range,double tau, double delta, double spMin, double vMin) :
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

