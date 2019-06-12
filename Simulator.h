#pragma once

#ifndef SIMULATOR
#define SIMULATOR

#include <vector>
#include "GnuOutput.h"
#include "PointsGenerator.h"
#include "MockUps.h"

using namespace std;

namespace wag{


struct Simulator{
	using Modifier = function<void(Pontos&)>;


	static TestResult Simulate(Learner& nn, Pontos trainP,Pontos trainTestP,Pontos testP, std::string name, std::string output, bool recursive){

		Plotter plot;
		Plotter fplot;

		Plotter* ffplot = recursive ? &fplot: &plot;

		static int cont =0;
		TestResult result;

		Result trainResult;

		nn.learn(trainP);
		trainResult=nn.printResult(trainTestP,cout);

		string title=nn.name();
		plot.pontos[title].clear();

		ffplot->style[name]=Plotter::POINT;

		if(recursive){
			plot.style[title]=Plotter::POINT;

		}else{
			plot.style[title]=Plotter::LINE;

		}

		ffplot->addPontos(name, trainTestP);
		plot.addPontos(title, trainResult.pontos);

		Result testResult;
		testResult=nn.printResult(testP,cout);

		ffplot->addPontos(name, testP);
		plot.addPontos(title, testResult.pontos);

		std::cout<< "Train Error:"<<trainResult.error << " Test Error"<<testResult.error<<std::endl;


		if(recursive){
			std::string fileName = output;

			fplot.plot(output+title);
			plot.plot(output+name);
		}else{
			std::string fileName = output;
			fileName+=title+"_";
			fileName+=name;
			plot.plot(fileName);
		}

		cont++;

		result.train=trainResult;
		result.test=testResult;

		return result;

	}

};

}

#endif
