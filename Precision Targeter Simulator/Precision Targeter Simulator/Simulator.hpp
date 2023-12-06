/*
Simulator.hpp, main file for the simulation including the current state, parameters, control events, history, and stepping function

//NOTE: gear ratio is the ratio of turntable:motor so usually less than 1, 1:20 would be 0.05
*/




#pragma once




#include <vector>
#include "PerformanceCurve.hpp"


class Simulator
{

public:
	//subclass for SystemState
	class SystemState
	{
	public:
		double time;
		double theta; //rotation angle
		double omega; //rotation speed
		double motor_input; // value in [-1, 1]



		SystemState();
	};

	//subclass for SystemParameters
	class SystemParameters
	{
	public:
		double theta0; //initial angle
		double omega0; //initial speed
		double gamma; //damping factor, the constant multiplied by speed and added to the acceleration to simulate friction
		double dt; //time step
		double tmax; //max time
		double motor_input; //input to the motor, in the range [-1,1]

		double I; //moment of inertia
		double gear_ratio; //gear ratio of the motor to the turntable
		PerformanceCurve::Voltage voltage; //voltage of the motor

		SystemParameters();
		SystemParameters(const SystemParameters& other);

	};


	struct ControlEvent
	{
		double time;
		double motor_input;
	};

	//vector of struct pointers to store the control events

	std::vector<ControlEvent*> control_events;
	
	std::vector<SystemState*> history;


	SystemParameters parameters;
	SystemState state;

	void SetParameters(double dt, double tmax, PerformanceCurve::Voltage voltage, double motor_input, double I, double gear_ratio, double gamma = 0, double theta0 = 0, double omega0 = 0);

	void AddControlEvent(double time, double motor_input);
	void ClearControlEvents();

	//clear the history and reset the state to the initial state
	void ResetState();
	
	void PrintState();
	
	void Step(PerformanceCurve& pc);
	void SimulateHeadless(PerformanceCurve &pc, bool saveHistory = true);
	


	//we would initialize the simulator with the initial state, parameters, and control, and allow that to be modified
	Simulator();

};

