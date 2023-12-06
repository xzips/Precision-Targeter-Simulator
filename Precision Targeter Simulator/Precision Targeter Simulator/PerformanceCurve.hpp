/*
PerformanceCurve.hpp

Contains the classes and methods to facillitate the evaluation of the torque vs rpm curve of the motor in realtime, by interpolating between the data points in the datasheet, from polynomials fitted externally

*/

#pragma once

#include <vector>




struct Polynomial
{
	//define a vector for the coefficients
	std::vector<double> coefficients;

	//define a range for the polynomial
	double domain[2];

	//define a function to evaluate the polynomial
	double evaluate(double x);
};

class PerformanceCurve
{
public:
	//class enum for voltage, 12VDC, 24VDC, 36VDC
	enum Voltage {V12, V24, V36};

	//define for each voltage, holding the polynomial coefficients, and the domain
	Polynomial V12_poly;
	Polynomial V24_poly;
	Polynomial V36_poly;
	//Note only up to 36V is supported, as that's what's within the scope of the project

	PerformanceCurve();
	
	double EvaluateTorque(double rpm, Voltage voltage);
	double GetMaxRPM(Voltage voltage);




};