/*
 * MockUps.cpp
 *
 *  Created on: 10 de jun de 2019
 *      Author: wagner
 */

#include "MockUps.h"
using namespace std;
namespace wag
{

std::vector<double> getRange(Pontos p) ;
std::vector<double> getLoopRange(Pontos p) ;

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
//  Matrix<double> mat = pontosToMat(p);
    std::vector<tiny_dnn::vec_t> X;
     std::vector<tiny_dnn::vec_t> Y;
     for (auto& x: p) {
        X.push_back({x.first});
        Y.push_back({x.second});
    }
     Plotter plotter;
     plotter.addPontos("F(x)", p);
     plotter.style["F(x)"]=Plotter::POINT;
    // vector<double> vDoubles(vFloats.begin(), vFloats.end());
    size_t batch_size = 10;
      int epochs        = 1;100000/p.size();  // 2000 presentation of all samples
      tiny_dnn::gradient_descent opt;
      opt.alpha=0.1;

      // this lambda function will be called after each epoch
      int iEpoch              = 0;
      auto on_enumerate_epoch = [&]() {
        // compute loss and disp 1/100 of the time
        iEpoch++;
        if (iEpoch % 5) return;
        std::cout<< "Epoch:"<< iEpoch<< std::endl;
        Result result=printResult(p,cout);
        plotter.pontos["NN"]=result.pontos;
        plotter.plot();
      };
      // learn
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
//  std::vector<double> inputs{d};
//  nn.get_multilayer_perceptron_pointer()->calculate_outputs(inputs);
    tiny_dnn::vec_t alce ={d};
    auto resu = nn.predict(alce);
    double ans = resu[0];
}





} /* namespace wag */
