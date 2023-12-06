#include <iostream>

#include "PerformanceCurve.hpp"
#include "InertiaMomentCalculator.hpp"
#include "Simulator.hpp"
#include "SFML/Graphics.hpp"
#include "GraphPlot.hpp"
#include "Fonts.hpp"
#include "HistoryReplay.hpp"
#include "Textures.hpp"

int main()
{
	G_LoadFont();
	G_LoadTextures();
	
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
	- [Turntable] Hollow cylinder centered at origin (center of rotation), with radius 0.09 and mass  0.18kg 
	- [Components Attatchment Plate] Disc centered at origin, radius 0.1m, mass                      0.303kg
	- [Motor, Bracket] Disc at a distance of 0.115m from origin, radius 0.05m , mass 0.24kg + 0.04 = 0.28kg
	- [Large Outer Spur Gear] Hollow cylinder at the origin 0.10m from origin, radius 0.1m, mass  0.12kg
	*/

	//mass, radius, distance from origin
	imc.AddHollowCylinder(0.18, 0.09, 0.0);
	imc.AddDisk(0.303, 0.1, 0.0);
	imc.AddDisk(0.28, 0.05, 0.115);
	imc.AddHollowCylinder(0.12, 0.1, 0);

	double inertiaMoment = imc.ComputeTotalMomentOfInertia();

	//std::cout << "Total moment of inertia: " << inertiaMoment << " kg*m^2" << std::endl;

	Simulator sim;

	double dt = 0.05;
	double tmax = 5;
	PerformanceCurve::Voltage voltage = PerformanceCurve::Voltage::V24;
	


	
	
	sim.SetParameters(dt, tmax, voltage, 0.5, inertiaMoment, 20);
	sim.AddControlEvent(3, -1);
	sim.AddControlEvent(4.545, 0);

	
	
	//sim.SetParameters(dt, tmax, voltage, 1, inertiaMoment, 20);
	//sim.AddControlEvent(2.5, -1);
	

	
	sim.SimulateHeadless(pc, true, false);
	ReplayHistory(sim.history, dt, tmax, 1);

}
