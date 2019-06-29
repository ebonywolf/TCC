/*
 * MockUps.cpp
 *
 *  Created on: 10 de jun de 2019
 *      Author: wagner
 */

#include "MockUps.h"
using namespace std;
namespace wag {

std::vector<double> getRange(Pontos p);
std::vector<double> getLoopRange(Pontos p);

template<class T>
void meuswap(T& t, T& t2) {
	auto alce = t;
	t = t2;
	t2 = alce;
}

void randomize(Pontos& m) {
	auto num = m.size();
	for (int i = 0; i < num; i++) {
		int s1 = rand() % num;
		meuswap(m[i], m[s1]);
	}
}

Matriz pontosToMat(Pontos p) {
	Matriz m;
	for (auto& x : p) {
		std::vector<double> tu(2);
		tu[0] = x.first;
		tu[1] = x.second;
		m.push_back(tu);
	}
	return m;
}

FFNN_mock::FFNN_mock(int layers, int rMax) :
		rMax(rMax), recurssion(rMax) {
	//int n = 20;
	nn << tiny_dnn::fully_connected_layer(1 + rMax, layers);
	nn << tiny_dnn::sigmoid_layer();
	nn << tiny_dnn::fully_connected_layer(layers, layers);
	nn << tiny_dnn::sigmoid_layer();
	nn << tiny_dnn::fully_connected_layer(layers, 1);

}
void FFNN_mock::learn(Pontos p) {
//  Matrix<double> mat = pontosToMat(p);

	int realEpoch = 5;

	// vector<double> vDoubles(vFloats.begin(), vFloats.end());
	size_t batch_size = 1;
	int epochs = 2; //100000 / p.size();  // 2000 presentation of all samples
	tiny_dnn::gradient_descent opt;
	opt.alpha = 0.01;
	int iEpoch = 0;

	auto on_enumerate_epoch = [&]() {
		// compute loss and disp 1/100 of the time
			iEpoch++;
			if (iEpoch % 5) return;

		};
	// learn
	for (int i = 0; i < realEpoch; i++) {
		for (auto& x : p) {
			std::vector<tiny_dnn::vec_t> X;
			std::vector<tiny_dnn::vec_t> Y;
			X.push_back(toInput(x.first));
			Y.push_back( { x.second });
			nn.fit<tiny_dnn::mse>(opt, X, Y, batch_size, epochs, []() {}, on_enumerate_epoch);

		}
	}

	// this lambda function will be called after each epoch

}
Result FFNN_mock::printResult(Pontos p, bool learn ) {
	//   wag::Plotter plot;
	RecurssiveVector recurssionMemory = recurssion;
	Result result;
	double mean = 0;
	for (auto& x : p) {
		mean += x.second;
	}
	mean /= (double) p.size();
	double sum = 1;
	double sum2 = 1;
	for (auto& x : p) {
		double my = (*this)(x.first);
		double y = x.second;
		double alce = (my - y) * (my - y);
		sum += alce;
		double alce2 = (mean - y) * (mean - y);
		sum2 += alce2;
		result.pontos.push_back(std::make_pair(x.first, my));
		if(learn)
		    learnSingle( x.first ,y);
	}
	result.error = sum / sum2;

	recurssion = recurssionMemory;
	return result;
}

void FFNN_mock::learnSingle(double x, double y) {
	size_t batch_size = 1;
	int epochs = 2; //100000 / p.size();  // 2000 presentation of all samples
	tiny_dnn::gradient_descent opt;
	opt.alpha = 0.01;
	std::vector<tiny_dnn::vec_t> X;
	std::vector<tiny_dnn::vec_t> Y;

	X.push_back(toInput(x));
	Y.push_back( { y });
	nn.fit<tiny_dnn::mse>(opt, X, Y, batch_size, epochs, []() {}, []() {});

}
tiny_dnn::vec_t FFNN_mock::toInput(double d) {
	tiny_dnn::vec_t alce = { d };
	for (auto& x : recurssion) {
		alce.push_back(x);
	}
	return alce;
}

double FFNN_mock::operator()(double d) {
//  std::vector<double> inputs{d};
//  nn.get_multilayer_perceptron_pointer()->calculate_outputs(inputs);
	tiny_dnn::vec_t alce = toInput(d);
	auto resu = nn.predict(alce);
	double ans = resu[0];
	recurssion.push(d);
	return ans;

}

} /* namespace wag */
