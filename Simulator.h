#pragma once

#include <vector>
#include "IGMN/igmn.h"
#include "BasicNN.h"
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
	IGMN_mock(double tau=0.1, double delta=0.1);
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
	Result printResult(Pontos p, std::ostream& os){};
	double operator()(double d){};
	std::string name(){return "FFNN";}


	BasicNN nn;
};


struct Simulator{
	using Modifier = function<void(Pontos&)>;

	template<class F>
	static Result Simulate(F func,Learner& nn, Parameters& params){
		Pontos p = Plotter::generatePoints( params.start, params.end, func, params.points);

		Plotter plot;

		static int cont =0;
		if(params.modifier){
			params.modifier(p);
		}
		plot.addPontos("F(x)", p);

		nn.learn(p);
		auto result=nn.printResult(p,cout);

		string title=nn.name();
		title+=to_string(cont);
		plot.addPontos(title, result.pontos);

		plot.plot();
		cont++;
		return result;

	}

};

}
