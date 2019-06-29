/*
 * MockUps.cpp
 *
 *  Created on: 10 de jun de 2019
 *      Author: wagner
 */

#include "MockUps.h"
using namespace std;
namespace wag {

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

FFNN_mock::FFNN_mock(int layers, bool timed) :
		timed(timed) {
	nn << tiny_dnn::fully_connected_layer(1 + timed, layers);
	nn << tiny_dnn::sigmoid_layer();
	nn << tiny_dnn::fully_connected_layer(layers, layers);
	nn << tiny_dnn::sigmoid_layer();
//	nn << tiny_dnn::fully_connected_layer(layers, layers);
//	nn << tiny_dnn::sigmoid_layer();
	nn << tiny_dnn::fully_connected_layer(layers, 1);

}
void FFNN_mock::learn(Pontos p, double start, double end) {
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
		double var = end-start;
		double timeIncrement = var / (double)p.size();
		double time=start;

		for (auto& x : p) {
			std::vector<tiny_dnn::vec_t> X;
			std::vector<tiny_dnn::vec_t> Y;
			X.push_back(toInput(x.first,time));
			Y.push_back( { x.second });
			nn.fit<tiny_dnn::mse>(opt, X, Y, batch_size, epochs, []() {}, on_enumerate_epoch);
			time+=timeIncrement;

		}
	}
}

void FFNN_mock::learnSingle(double x, double y, double t) {
	size_t batch_size = 1;
	int epochs = 2; //100000 / p.size();  // 2000 presentation of all samples
	tiny_dnn::gradient_descent opt;
	opt.alpha = 0.01;
	std::vector<tiny_dnn::vec_t> X;
	std::vector<tiny_dnn::vec_t> Y;

	X.push_back(toInput(x,t));

	Y.push_back( { y });
	nn.fit<tiny_dnn::mse>(opt, X, Y, batch_size, epochs, []() {}, []() {});
}
tiny_dnn::vec_t FFNN_mock::toInput(double d, double time) {
	tiny_dnn::vec_t alce = { d };
	if(timed)
		alce.push_back(time);

	return alce;
}

double FFNN_mock::operator()(double d,double t) {
//  std::vector<double> inputs{d};
//  nn.get_multilayer_perceptron_pointer()->calculate_outputs(inputs);
	tiny_dnn::vec_t alce = toInput(d, t);
	auto resu = nn.predict(alce);
	double ans = resu[0];

	return ans;

}

} /* namespace wag */
