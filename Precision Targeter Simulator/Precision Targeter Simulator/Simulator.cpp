#include "Simulator.hpp" // Make sure to include the correct header file name
//#include "PerformanceCurve.hpp"
#include <cmath>

#include <iostream>

Simulator::SystemParameters::SystemParameters()
{

}

Simulator::SystemState::SystemState()

{

}

// Copy constructor for SystemParameters, note that gear_ratio is turntable:stepper_gear, so 20:1 = 20/1 would be 20
Simulator::SystemParameters::SystemParameters(const SystemParameters& other)
    : theta0(other.theta0), omega0(other.omega0), gamma(other.gamma), dt(other.dt), tmax(other.tmax), motor_input(other.motor_input), I (other.I), gear_ratio(other.gear_ratio), voltage(other.voltage) {
    // Copy the values
}



// Simulator constructor
Simulator::Simulator() {
    // Initialize the simulator with default values
    ResetState();
}

// SetParameters method
void Simulator::SetParameters(double dt, double tmax, PerformanceCurve::Voltage voltage, double motor_input, double I, double gear_ratio, double gamma, double theta0, double omega0) {
    parameters.dt = dt;
    parameters.tmax = tmax;
    parameters.motor_input = motor_input;
    parameters.I = I;
	parameters.gear_ratio = gear_ratio;
    parameters.gamma = gamma;
    parameters.theta0 = theta0;
    parameters.voltage = voltage;



    ResetState();
}

// AddControlEvent method
void Simulator::AddControlEvent(double time, double motor_input) {
    ControlEvent* newEvent = new ControlEvent{ time, motor_input };
    control_events.push_back(newEvent);
}

// ClearControlEvents method
void Simulator::ClearControlEvents() {
    for (auto& event : control_events) {
        delete event;
    }
    control_events.clear();
}

// ResetState method
void Simulator::ResetState() {
    history.clear();
    state = SystemState(); // Resets to default state
    // Set initial conditions
    state.theta = parameters.theta0;
    state.omega = parameters.omega0;
    state.time = 0;
    state.motor_input = parameters.motor_input;
}

void Simulator::PrintState()
{
    std::cout << "T = " << state.time << ", Theta = " << state.theta << ", Omega = " << state.omega << ", Motor Input: " << state.motor_input << "\n";
}

// Step method
void Simulator::Step(PerformanceCurve& pc)
{
    
    //Get the motor input for the current step, which is by default the initial setting, but can change if control events are present
    for (auto& event : control_events) {

        if (event->time <= state.time) {
            state.motor_input = event->motor_input;
        }
        else {
            break;
        }
    }

    


    double rpm = state.omega * 60 / (2 * 3.14159265);
    double motor_torque = state.motor_input * pc.EvaluateTorque(rpm, parameters.voltage);

    //angular acceleration due to torque and gear ratio
    double alpha = (motor_torque) / (parameters.I * parameters.gear_ratio);

    //update angular velocity per timestep
    state.omega += alpha * parameters.dt;

    //update angle per timestep
    state.theta += state.omega * parameters.dt;

    //update time
    state.time += parameters.dt;

    //save state to history
    history.push_back(new SystemState(state));
}


// SimulateHeadless method
void Simulator::SimulateHeadless(PerformanceCurve &pc, bool saveHistory)
{
// Reset the state
	ResetState();

    //push initial state to history
    history.push_back(new SystemState(state));


	// Simulate until tmax
	while (state.time < parameters.tmax)
    {

		// Step the simulation
		Step(pc);
	}
    
}

