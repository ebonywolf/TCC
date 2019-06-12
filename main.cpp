#include "Simulator.h"

#include "PointsGenerator.h"
#include "Config.h"
#include "IGMN_mock.h"
#include <fstream>

#include <sys/stat.h>
#include <sys/types.h>
using namespace std;
using namespace wag;
using Vetor=std::vector<double>;

class InputParser {
public:
	InputParser(int &argc, char **argv) {
		for (int i = 1; i < argc; ++i)
			this->tokens.push_back(std::string(argv[i]));
	}
	/// @author iain
	const std::string& getValue(const std::string &option) const {
		std::vector<std::string>::const_iterator itr;
		itr = std::find(this->tokens.begin(), this->tokens.end(), option);
		if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
			return *itr;
		}
		static const std::string empty_string("");
		return empty_string;
	}
	/// @author iain
	bool hasParam(const std::string &option) const {
		return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
	}
private:
	std::vector<std::string> tokens;
};

void doshit(Config& config, string output, bool igmn) {
	string outfile = "ffnn.txt";
	if(igmn)outfile="igmn.txt";

	ofstream out(output + outfile, ios::trunc);

	if (igmn) {
	    out << "====IGMN Root relative squared error test=====\n";
	}else{
		out << "==== FFNN Root relative squared error test=====\n";

	}
	for (auto& x : config.timeNames) {
		out << "\t  " << x << "\t\t\t\t\t ";
	}
	out << endl;
	int i = 0;

	for (auto& funcs : config.functions) {
		out << funcs.name << "";
		int i = 0;
		for (auto& timeFuncs : config.timeFunctions) {
			std::cout << "Running:" << funcs.name << " " << config.timeNames[i] << std::endl;
			out << "\t  ";
			Pontos train = PointsGenerator::createPoints(funcs, timeFuncs, 1, 11);
			Pontos trainTest = PointsGenerator::createPoints(funcs, timeFuncs, 1, 11);
			Pontos test = PointsGenerator::createPoints(funcs, timeFuncs, 11, 16);

			Simulator simu;
			string fname = funcs.name + "_";
			fname += config.timeNames[i];
			fname += "";
			TestResult result;

			if (igmn) {
				IGMN_mock igmn(config.igmn["tau"].asDouble(), config.igmn["delta"].asDouble(), 2, 3, config.igmn["rMax"].asInt());
				result = simu.Simulate(igmn, train, trainTest, test, fname, output );

			} else {
				FFNN_mock ffnn(config.ffnn["layer"].asInt(), config.ffnn["rMax"].asInt());
				result = simu.Simulate(ffnn, train, trainTest, test, fname, output );
			}

			out << result.train.error << " " << result.test.error << " ";
			//simu.Simulate(ffnn, p, funcs.name);
			i++;
		}
		out << "" << endl;
	}
}

int main(int argc, char** argv) {
	InputParser inputs(argc, argv);

	string output = "output/";
	string input = "test.json";
	if (inputs.hasParam("-o")) {
		output = inputs.getValue("-o") + "/";
	}
	if (inputs.hasParam("-i")) {
		input = inputs.getValue("-i");
	}
	mkdir(output.c_str(), 0777);

	Config config = Config::ReadFile(input);

	 doshit(config,  output, 0) ;
	 doshit(config,  output, 1) ;

	// params.modifier =randomize;

	//simu.Simulate( ffnn , p);

}

