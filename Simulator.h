#pragma once

#include <vector>
#include "IGMN/igmn.h"
#include "GeneticNN.h"
using namespace std;

namespace wag{
using Modifier = function<void(Pontos&)>;

struct Result{
	Pontos pontos;
	double error;
};

struct Parameters{

	 double start,end;
	 int points=100;
	 Modifier modifier;
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
	IGMN_mock(double tau=0.1, double delta=0.1, double spMin=0, double vMin=0, std::vector<double> range= std::vector<double>());
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

	BasicNN nn;
};
struct GeneNN_mock: public Learner{
	GeneNN_mock();
	~GeneNN_mock(){}
	void learn(Pontos p);
	Result printResult(Pontos p, std::ostream& os);
	double operator()(double d);
	std::string name(){return "GeneNN";}

	BasicNN nn;
};


struct Simulator{
	using Modifier = function<void(Pontos&)>;

	template<class F>
	static Result Simulate(F func,Learner& nn, Parameters& params){
		Pontos p = Plotter::generatePoints( params.start, params.end, func, params.points);
		Pontos original = p;
		Plotter plot;

		plot.addPontos("F(x)", original);

		static int cont =0;
		if(params.modifier){
			params.modifier(p);
		}

		Result result;

		nn.learn(p);
		result=nn.printResult(original,cout);

		string title=nn.name();
		plot.pontos[title].clear();

		title+=to_string(cont);
		plot.addPontos(title, result.pontos);

		plot.plot();
		std::cout<< "Error:"<<result.error << std::endl;

		cont++;

		return result;

	}

};

}
