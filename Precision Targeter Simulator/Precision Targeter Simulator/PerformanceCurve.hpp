#include <vector>




struct Polynomial
{
	//define a vector for the coefficients
	std::vector<double> coefficients;

	//define a range for the polynomial
	double domain[2];

	//define a function to evaluate the polynomial
	double evaluate(double x)
	{
		double y = 0;
		for (int i = 0; i < coefficients.size(); i++)
		{
			y += coefficients[i] * pow(x, i);
		}
		return y;
	}
};

class PerformanceCurve
{
	//class enum for voltage, 12VDC, 24VDC, 36VDC, 48VDC
	enum Voltage {V12, V24, V36, V48};

	//define for each voltage, holding the polynomial coefficients, and the domain
	Polynomial V12;
	Polynomial V24;
	Polynomial V36;
	Polynomial V48;

	PerformanceCurve();
	




};