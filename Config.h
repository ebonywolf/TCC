#ifndef CONFIG_H_
#define CONFIG_H_
#include "PointsGenerator.h"
#include "Simulator.h"

#include <jsoncpp/json/json.h>
namespace wag{

using FunctionMap = std::unordered_map<std::string , std::function<double(double)>>;
using TimeFunctionMap = std::unordered_map<std::string , std::function<double(double,double)>>;



class Config {
public:
	std::vector<Parameters> functions;

	std::vector< std::function<double(double,double)> > timeFunctions;
	Json::Value igmn;
	Json::Value ffnn;

	std::vector<std::string> timeNames;
	static Config ReadFile(std::string file);
	static  FunctionMap& GetFunctions();
	static  TimeFunctionMap& GetTimeFunctions();
};


}
#endif /* CONFIG_H_ */
