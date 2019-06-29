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


	static TestResult Simulate(Learner& nn, Pontos trainP,Pontos trainTestP,Pontos testP, std::string fname, std::string output){
		bool recursive=false;
		Plotter plot;
		Plotter fplot;

		Plotter* ffplot = recursive ? &fplot: &plot;

		static int cont =0;
		TestResult result;

		Result trainResult;

		nn.learn(trainP);
		trainResult=nn.printResult(trainTestP,false);

		string title= fname;
		plot.pontos[title].clear();
		title+="_";
		title+=nn.name();

		ffplot->style[fname]=Plotter::CIRCLE;

		if(true){
			plot.style[title]=Plotter::POINT;

		}else{
			plot.style[title]=Plotter::LINE;

		}

		ffplot->addPontos(fname, trainTestP);
		plot.addPontos(title, trainResult.pontos);


		Result testResult;
		testResult=nn.printResult(testP,true);
		ffplot->addPontos(fname, testP);
		plot.addPontos(title, testResult.pontos);


		std::string fileName = output;
		fileName+=title;

		if(recursive){
			plot.updateRange(*ffplot);

			ffplot->plot(output+fname);
			plot.plot(fileName);
		}else{

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
