#pragma once

#include <vector>
#include "IGMN/igmn.h"
#include "GnuOutput.h"
#include "PointsGenerator.h"
#include <tiny_dnn/tiny_dnn.h>
using namespace std;

namespace wag{

struct Result{
	Pontos pontos;
	double error;
};


struct Learner{
	Learner(){}
	virtual ~Learner(){}
	virtual void learn(Pontos p)=0 ;
	virtual Result printResult(Pontos p, std::ostream& os)=0;
	virtual double operator()(double d)=0;
	virtual std::string name()=0;

};

struct IGMN_mock: public Learner{
	IGMN_mock(std::vector<double> range,double tau=0.04, double delta=0.03, double spMin=2, double vMin=3);
	void learn(Pontos p)override;
	Result printResult(Pontos p, std::ostream& os);
	double operator()(double d);
	std::string name(){return "IGMN";}

	liac::IGMN igmn;

};

struct FFNN_mock: public Learner{
	FFNN_mock();
	~FFNN_mock(){}
	void learn(Pontos p);
	Result printResult(Pontos p, std::ostream& os);
	double operator()(double d);
	std::string name(){return "FFNN";}
	tiny_dnn::network<tiny_dnn::sequential> nn;

};


struct Simulator{
	using Modifier = function<void(Pontos&)>;

	static Result Simulate(Learner& nn, Pontos p, std::string name){
				Plotter plot;


		static int cont =0;

		Result result;

		nn.learn(p);
		result=nn.printResult(p,cout);

		string title=nn.name();
		plot.pontos[title].clear();

		plot.addPontos(name+to_string(cont), p);

		plot.addPontos(title, result.pontos);

		plot.plot();
		std::cout<< "Error:"<<result.error << std::endl;

		cont++;

		return result;

	}

};

}
