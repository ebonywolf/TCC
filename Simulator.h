#pragma once

#include <vector>
#include "GnuOutput.h"
#include "PointsGenerator.h"
#include "MockUps.h"
#include <tiny_dnn/tiny_dnn.h>

using namespace std;

namespace wag{


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
		plot.style[name]=Plotter::POINT;

		plot.addPontos(name, p);
		plot.addPontos(title, result.pontos);

		plot.plot();
		std::cout<< "Error:"<<result.error << std::endl;

		cont++;

		return result;

	}

};

}
