#include "Config.h"

using namespace std;
namespace wag {

Config Config::ReadFile(std::string file) {
	ifstream input(file);
	Json::Value conJ;
	input >> conJ;

	Config config;
	auto& funcJ = conJ["Functions"];

	for (int i = 0; i < funcJ.size(); i++) {
		Parameters params;
		Json::Value func = funcJ[i];
		params.start = func["start"].asDouble();
		params.end = func["end"].asDouble();
		params.points = func["points"].asDouble();
		params.name = func["name"].asString();
		params.function = GetFunctions()[params.name];
		config.functions.push_back(params);
	}

	auto& funcT = conJ["TimeFunctions"];

	for (int i = 0; i < funcT.size(); i++) {
		Json::Value func = funcT[i];
		string name = func.asString();
		config.timeNames.push_back(name);
		config.timeFunctions.push_back(GetTimeFunctions()[name]);

	}
	config.igmn = conJ["IGMN"];
	config.ffnn = conJ["FFNN"];
	return config;

}

FunctionMap& Config::GetFunctions() {
	static FunctionMap mapa;

	if (mapa.size() != 0)
		return mapa;

	mapa["L0"] = [](double x) {
		return 2;
	};
	mapa["L1"] = [](double x) {
		return 2*x-15.0;
	};
	mapa["L2"] = [](double x) {
		return (-5.0*(x*x)/3.0) + 2.0*x-4.0;
	};
	mapa["L3"] = [](double x) {
		return (x-8.0)*(x+4)*(x);
	};
	mapa["L4"] = [](double x) {
		return 2*cos(x);
	};
	mapa["L5"] = [](double x) {
		return pow(x, 0.5);
	};
	mapa["L6"] = [](double x) {
		return pow(-1, x)*2.0*x;
	};

	return mapa;
}

TimeFunctionMap& Config::GetTimeFunctions() {
	static TimeFunctionMap mapa;

	if (mapa.size() != 0)
		return mapa;

	mapa["T0"] = [](double x, double t) {
		return x;
	};
	mapa["T1"] = [](double x, double t) {
		return x*t;
	};
	mapa["T2"] = [](double x, double t) {
		return x/t;
	};
	mapa["T3"] = [](double x, double t) {
		if(t<5.0)return 3*x;
		return x;
	};
	mapa["T4"] = [](double x, double t) {
		double r =PointsGenerator::unif(PointsGenerator::generator);
		double o =PointsGenerator::unif(PointsGenerator::generator);

		if(r<0.08){
			double i = -1;
			if(o<0.5)i=1;
			return x + i*5.0*x;
		}
			return x;
	};
	mapa["T5"] = [](double x, double t) {
			int n=t/3;
			if(n % 2 == 0){
				return x;
			}else{
				return -x;
			}
		};



	return mapa;
}

}
