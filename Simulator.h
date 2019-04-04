#pragma once

#include <vector>


#include <Eigen/Dense>
#include "IGMN/igmn.h"

#include <GnuOutput.h>

using namespace std;
namespace wag{

struct Result{

	Pontos pontos;
	double error;
};

struct Learner{
	void learn(Pontos p);
	Result printResult(Pontos p, std::ostream& os);
	double operator()(double d);
};

struct IGMN_mock: public Learner{
	IGMN_mock(double tau=0.1, double delta=0.1);
	void learn(Pontos p);
	Result printResult(Pontos p, std::ostream& os=std::cout);
	double operator()(double d);
	liac::IGMN igmn;
};


struct Simulator{
	using Modifier = function<void(Pontos&)>;

	template<class F>
	static Result SimulateIgmn(F func, double start, double end, int points=100,Modifier modifier=Modifier() ){
		Pontos p = Plotter::generatePoints( start, end, func, points);

		Plotter plot;

		static int cont =0;
		if(modifier){
			modifier(p);
		}
		plot.addPontos("F(x)", p);
		IGMN_mock igmn;

		igmn.learn(p);
		auto result=igmn.printResult(p);

		string title="IGMN";
		title+=to_string(cont);
		plot.addPontos(title, result.pontos);


		plot.plot();
		cont++;
		return result;

	}
};

}
