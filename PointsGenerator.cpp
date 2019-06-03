#include "PointsGenerator.h"

namespace wag{

std::default_random_engine PointsGenerator::generator = std::default_random_engine(time(0));
std::uniform_real_distribution<double> PointsGenerator::unif = std::uniform_real_distribution<double>(0, 1);


}
