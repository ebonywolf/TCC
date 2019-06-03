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
	 int maxTime=100;
	 Modifier modifier;
};

class PointsGenerator {
public:

	template <class F, class T>
	static Pontos createPoints(F func, T tfunc, Parameters params){
		double timeIncrement = (double)params.maxTime / (double)params.points;
		double time=1;
		Pontos p;
		for (int i = 0; i < params.points; i++) {
			double r = unif(generator);
			double x =params.start+ r*(params.end-params.start);
			double y = func(x);
			double finalY = y*tfunc(time);
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
