/*
PerformanceCurve.cpp

Contains the classes and methods to facillitate the evaluation of the torque vs rpm curve of the motor in realtime, by interpolating between the data points in the datasheet, from polynomials fitted externally

*/


#include "PerformanceCurve.hpp"
#include <iostream>

PerformanceCurve::PerformanceCurve()
{


	V12_poly.coefficients.push_back(4.3163e-15); // a
	V12_poly.coefficients.push_back(-1.1606e-11); // b
	V12_poly.coefficients.push_back(1.1247e-8); // c
	V12_poly.coefficients.push_back(-0.00000436331); // d
	V12_poly.coefficients.push_back(0.000229399); // f
	V12_poly.coefficients.push_back(0.249403); // g
	V12_poly.domain[0] = 0;
	V12_poly.domain[1] = 900; //up to 900 rpm

	V24_poly.coefficients.push_back(1.4698e-16); // a
	V24_poly.coefficients.push_back(-7.9047e-13); // b
	V24_poly.coefficients.push_back(1.5441e-9); // c
	V24_poly.coefficients.push_back(-0.00000123569); // d
	V24_poly.coefficients.push_back(0.000183646); // f
	V24_poly.coefficients.push_back(0.247334); // g
	V24_poly.domain[0] = 0;
	V24_poly.domain[1] = 1800; //up to 1800 rpm

	V36_poly.coefficients.push_back(-2.7918e-17); // a
	V36_poly.coefficients.push_back(5.7684e-14); // b
	V36_poly.coefficients.push_back(1.1698e-10); // c
	V36_poly.coefficients.push_back(-3.2753e-7); // d
	V36_poly.coefficients.push_back(0.0000761313); // f
	V36_poly.coefficients.push_back(0.248273); // g
	V36_poly.domain[0] = 0;
	V36_poly.domain[0] = 1800;


}



//Returns the torque evaluated from the performance curve for the given rpm and voltage setting using 5th degree polynomials for each voltage setting
double PerformanceCurve::EvaluateTorque(double rpm, Voltage voltage)
{
	//evaluate 5th degree polynomial using the coefficients for the given voltage
	double torque = 0;

	if (voltage == Voltage::V12)
	{
		for (int i = 0; i < 6; i++)
		{
			torque += V12_poly.coefficients[i] * pow(rpm, 5 - i);
		}
	}

	else if (voltage == Voltage::V24)
	{
		for (int i = 0; i < 6; i++)
		{
			torque += V24_poly.coefficients[i] * pow(rpm, 5 - i);
			//print coefficient, power, and torque for each iteration
			//std::cout << "Coefficient: " << V24_poly.coefficients[i] << " Power: " << i << " Torque: " << torque << std::endl;
		
		}
	}

	else if (voltage == Voltage::V36)
	{
		for (int i = 0; i < 6; i++)
		{
			torque += V36_poly.coefficients[i] * pow(rpm, 5 - i);
		}
	}

	return torque;
}

double Polynomial::evaluate( double x )
{
	double y = 0;
	for (int i = 0; i < coefficients.size(); i++)
	{
		y += coefficients[i] * pow(x, i);
	}
	return y;
}

double PerformanceCurve::GetMaxRPM(Voltage voltage)
{
	if (voltage == Voltage::V12)
	{
		return V12_poly.domain[1];
	}
	else if (voltage == Voltage::V24)
	{
		return V24_poly.domain[1];
	}
	else if (voltage == Voltage::V36)
	{
		return V36_poly.domain[1];
	}
	else
	{
		return 0;
	}
}
