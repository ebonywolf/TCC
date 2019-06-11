
#ifndef IGMN_MOCK
#define IGMN_MOCK

#include "MockUps.h"

namespace wag{



struct IGMN_mock: public Learner{

    std::string name(){return "IGMN";}

    IGMN_mock(double tau=0.04, double delta=0.03, double spMin=2, double vMin=3, int rMax=0) :
            igmn(tau, delta), tau(tau),delta(delta), spMin(spMin),vMin(vMin), rMax(rMax),recurssion(rMax) {
    }

    void learn(Pontos p) override {
        auto range = getRange(p);
        igmn.init(range, tau, delta, spMin, vMin);
        int i = 0;
        int num = p.size();
        MatrixXd m(2+rMax, num);
        double last = 0;
        for (auto& x : p) {

            m(0, i) = x.first;
            int j=0;
            for (auto& r: recurssion) {
				m(1+j,i)=r;
				j++;
			}


            m(1+rMax, i) = x.second;
            auto mat = m.block(0, i, m.rows(), 1);
			//std::cout<< "P:"<<x << std::endl;
			igmn.learn(mat);
			double novoY= (*this)(x.first);

            i++;
        }
    }

    Result printResult(Pontos p, std::ostream& os) {
        //   wag::Plotter plot;
        double sum = 0;
        Result result;

        for (auto& x: p) {
        	double my =(*this)(x.first);
        	double y = x.second;
        	sum+=(my -y )*(my - y);
        	result.pontos.push_back(std::make_pair(x.first,my));

		}


        sum /= p.size();
        result.error = sum;
        return result;
    }

    double operator()(double d) {
        MatrixXd m(1+rMax, 1);

       // MatrixXd m(1,1);
        m(0, 0) = d;
        int j=0;
    	for (auto& r: recurssion) {
			m(1 + j, 0) = r;
			j++;
		}
        MatrixXd res = igmn.recall(m);
        double _res = res(0, 0);

        recurssion.push(_res);

        return _res;
    }


private :
    liac::IGMN igmn;
    RecurssiveVector recurssion;

    double loop=0;
    double tau,  delta,  spMin,  vMin;
    int rMax;

    std::vector<double> getRange(Pontos p) {
        double xMin = 99999, yMin = 99999, xMax = -99999, yMax = -99999;
        for (auto& c : p) {
            if (c.first < xMin) {
                xMin = c.first;
            }
            if (c.second < yMin) {
                yMin = c.second;
            }
            if (c.second > yMax) {
                yMax = c.second;
            }
            if (c.first > xMax) {
                xMax = c.first;
            }
        }
        std::vector<double> range(rMax+2);
        range[0]=xMax - xMin;
        for (int i = 1; i < range.size(); i++) {
			range[i]=  yMax - yMin;
		}
        for (auto& x: range) {
            if(x==0)x=1;
        }
        return range;
    }



};

}
#endif
