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

void doshit(Config& config, string output) {

	ofstream ffout(output + "ffnn.txt", ios::trunc);
    ofstream igout(output + "igmn.txt", ios::trunc);

    ffout << "==== FFNN Root relative squared error test=====\n";
    igout << "==== IGMN Root relative squared error test=====\n";


	for (auto& x : config.timeNames) {
	    ffout << "\t  " << x << "\t\t\t\t\t ";
	    igout << "\t  " << x << "\t\t\t\t\t ";
	}
	ffout << endl;
	igout<< endl;
	int i = 0;

	for (auto& funcs : config.functions) {
	    ffout << funcs.name << "";
	    igout << funcs.name << "";

		int i = 0;
		for (auto& timeFuncs : config.timeFunctions) {
			std::cout << "Running:" << funcs.name << " " << config.timeNames[i] << std::endl;
			ffout << "\t  ";
			igout << "\t  ";
			Pontos train = PointsGenerator::createPoints(funcs, timeFuncs, 1, 10);
			Pontos trainTest = PointsGenerator::createPoints(funcs, timeFuncs, 1, 10);
			auto alce =     funcs.points;
			funcs.points= funcs.points/9.0 * 5.0;
			Pontos test = PointsGenerator::createPoints(funcs, timeFuncs, 10, 15);
			funcs.points=alce;
			Simulator simu;
			string fname = funcs.name + "_";
			fname += config.timeNames[i];
			fname += "";


			{
				IGMN_mock igmn(config.igmn["tau"].asDouble(), config.igmn["delta"].asDouble(), 2, 3, config.igmn["timed"].asBool());
				TestResult result = simu.Simulate(igmn, train, trainTest, test, fname, output );
				igout << result.train.error << " " << result.test.error << " ";

			}
			{
				FFNN_mock ffnn(config.ffnn["neurons"].asInt(), config.ffnn["timed"].asBool());
				TestResult result = simu.Simulate(ffnn, train, trainTest, test, fname, output );
				ffout << result.train.error << " " << result.test.error << " ";

			}

			//simu.Simulate(ffnn, p, funcs.name);
			i++;
		}
		ffout << "" << endl;
		igout << "" << endl;
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
	if (inputs.hasParam("-h")) {
	    std::cout<< "usage tester -i [input.json] -o [outputFolder]" << std::endl;
	}
	mkdir(output.c_str(), 0777);

	Config config = Config::ReadFile(input);

	 doshit(config,  output) ;

	// params.modifier =randomize;

	//simu.Simulate( ffnn , p);

}

