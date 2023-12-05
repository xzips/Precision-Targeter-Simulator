

#include "PerformanceCurve.hpp"



PerformanceCurve::PerformanceCurve()
{


	V12.coefficients.push_back(4.3163e-15); // a
	V12.coefficients.push_back(-1.1606e-11); // b
	V12.coefficients.push_back(1.1247e-8); // c
	V12.coefficients.push_back(-0.00000436331); // d
	V12.coefficients.push_back(0.000229399); // f
	V12.coefficients.push_back(0.249403); // g
	V12.domain[0] = 0;
	V12.domain[1] = 900; //up to 900 rpm

	V24.coefficients.push_back(1.4698e-16); // a
	V24.coefficients.push_back(-7.9047e-13); // b
	V24.coefficients.push_back(1.5441e-9); // c
	V24.coefficients.push_back(-0.00000123569); // d
	V24.coefficients.push_back(0.000183646); // f
	V24.coefficients.push_back(0.247334); // g
	V12.domain[0] = 0;
	V12.domain[1] = 1800; //up to 1800 rpm


}