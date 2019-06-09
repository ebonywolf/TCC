#ifndef POINTSGENERATOR_H_
#define POINTSGENERATOR_H_

#include <vector>
#include <functional>

#include <random>
namespace wag{

using Pontos =   std::vector<std::pair<double, double> >;
using Modifier = std::function<void(Pontos&)>;

struct Parameters{
	 double start,end;
	 int points=100;
	 std::string name;
	 std::function<double(double)> function;
	 double operator()(double x){
		 return function(x);
	 }
};

class PointsGenerator {
public:

	static Pontos createTestPoints(Parameters func, std::function<double(double,double)> tfunc){

		double timeIncrement = (double)10.0 / (double)func.points;
		double time=1;
		Pontos p;
		for (int i = 0; i < func.points; i++) {
			double r = unif(generator);
			double x =func.start+ r*(func.end-func.start);
			double y = func(x);
			double finalY = tfunc(y,time);
			time+=timeIncrement;
			p.push_back( std::make_pair(x,finalY));
		}
		return p;

	}
private:
    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> unif;//(0, 1);
};
}
#endif /* POINTSGENERATOR_H_ */
