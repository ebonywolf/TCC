#ifndef TOOLS_H_
#define TOOLS_H_



double randomN() {
	return (double) rand() / (double) RAND_MAX;
}
double normal(double media, double sigma) {
	double x = randomN();
	double x2 = randomN();

	double pi2 = M_PI * 2;
	double var = sin(pi2 * x2);
	double root = sqrt(-2.0 * log(x));
	double u = root * var;
	return u * sigma + media;
}

double getMean(Matrix vals) {
	double sum = 0;
	for (auto x : vals) {
		sum += x;
	}
	return sum / vals.size();
}
double getVariance(Vetor vals) {
	double mean = getMean(vals);
	double sum = 0;
	for (auto x : vals) {
		double alce = pow((x - mean), 2.0);
		sum += alce;

	}

	sum /= (vals.size() - 1.0);
	return sqrt(sum);
}

double normalP(double x, double mean, double var) {
	double u = mean;
	double o = var;
	double tope = (-1 * pow((x - u), 2));
	double bote = (2 * (pow(o, 2)));
	double ee = (tope / bote);
	double topy = exp(ee);
	double boty = (o * sqrt( M_2_PI));
	double y = topy / boty;
	return y;
}
/*
 double multiP( Matrix x ,  Matrix mean , Matrix var )
 {
 double u = mean;
 double  o = det(var);
 double tope = ( -1*  pow(( x - u ),  2) );
 double bote = ( 2 * ( pow(o , 2) ) );
 double ee = ( tope / bote );
 double topy = exp( ee );
 double boty = ( o * sqrt( M_2_PI ) );
 double y = topy / boty;
 return y;
 }
 */

double covariance(vector<Coord> vals, Coord var) {
	double n = vals.size();
	double sum = 0;
	for (auto val : vals) {
		sum += (val.x - var.x) * (val.y * var.y);
	}
	return sum / (n - 1.0);
}
double covarianceVector(Matrix a, Matrix b) {
	double n = a.n_cols;

	if (n != b.n_cols)
		throw runtime_error("Different size A and B");

	double varA = getMean(a);
	double varB = getMean(b);
	double sum = 0;

	for (int i = 0; i < n; i++) {
		double alce = (a[i] - varA) * (b[i] - varB);
		sum += alce;

	}
	return sum / (n - 1);
}
Matrix covarianceMatrix(Matrix a, Matrix b) {
	if (a.is_vec() && b.is_vec()) {
		Matrix ans(1, 1);
		ans(0, 0) = covarianceVector(a, b);
		return ans;
	}

	Matrix ans(a.n_cols, b.n_cols);
	for (int i = 0; i < a.n_cols; i++) {
		for (int j = 0; j < b.n_cols; j++) {
			Matrix f1 = a.col(i).t();
			Matrix f2 = b.col(j).t();
			double covar = covarianceVector(f1, f2);
			ans(i, j) = covar;
		}

	}
	return ans;
}

struct Gaussian {
	double mean, sigma;
	Gaussian(double mean, double sigma) :
			mean(mean), sigma(sigma) { //mediam and deviation

	}
	double pdf(double dataPoint) {
		return normalP(dataPoint, mean, sigma);
	}
	double operator()(double x) {
		return normalP(x, mean, sigma);
	}
};

struct GaussianMixture {
	vector<Gaussian> gaussians;
	double mix;
	GaussianMixture(int number, double mix = 0.5) :
			mix(mix) {
		for (int i = 0; i < number; i++) {
			gaussians.push_back(Gaussian(rand() % 3 + 5, rand() % 3 + 5));
		}
	}
};

using Pontos = std::vector<std::pair<double, double> >;
template<class T>
Pontos createPontos(int n, double min, double max, T func) {
	double step = (max - min) / (double) n;
	Pontos pts;
	for (double i = min; i < max; i += step) {
		pts.push_back(std::make_pair(i, func(i)));
	}
	return pts;
}



#endif /* TOOLS_H_ */
