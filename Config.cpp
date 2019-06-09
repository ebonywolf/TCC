#include "Config.h"

#include <jsoncpp/json/json.h>
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
		config.timeFunctions.push_back(GetTimeFunctions()[name]);

	}
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

	return mapa;
}

}
