#include <iostream>

#include "PerformanceCurve.hpp"
#include "InertiaMomentCalculator.hpp"


int main()
{
	PerformanceCurve pc;


	//Crude tests of the performance curve 
	//std::cout << "Torque at 12VDC, 300RPM: " << pc.EvaluateTorque(300, PerformanceCurve::Voltage::V12) << std::endl;
	//0.145674 roughly as expected

	//std::cout << "Torque at 24VDC, 600RPM: " << pc.EvaluateTorque(600, PerformanceCurve::Voltage::V24) << std::endl;
	//0.155183 roughly as expected

	//std::cout << "Torque at 36VDC, 600RPM: " << pc.EvaluateTorque(600, PerformanceCurve::Voltage::V36) << std::endl;
	//0.206614 roughly as expected

	InertiaMomentCalculator imc;

	//for now, manually build the list of components
	/*
	PROTOTYPE V1.0 specs:
	- [Turntable] Hollow cylinder centered at origin (center of rotation), with radius 0.9 and mass 0.4kg 
	- [Components Attatchment Plate] Disc centered at origin, radius 0.1m, mass 0.5kg
	- [Motor, Bracket, & Small Spur Gear] Disc at a distance of 0.115m from origin, radius 0.05m , mass 0.24kg + 0.1kg + 0.05kg = 0.39kg
	- [Large Outer Spur Gear] Hollow cylinder at a distance of 0.10m from origin, radius 0.1m, mass 0.5kg
	*/

	//mass, radius, distance from origin
	imc.AddHollowCylinder(0.4, 0.9, 0.0);
	imc.AddDisk(0.5, 0.1, 0.0);
	imc.AddDisk(0.39, 0.05, 0.115);
	imc.AddHollowCylinder(0.5, 0.1, 0.10);

	double inertiaMoment = imc.ComputeTotalMomentOfInertia();

	std::cout << "Total moment of inertia: " << inertiaMoment << " kg*m^2" << std::endl;



}
