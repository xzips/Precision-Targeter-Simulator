#pragma once
#include "Simulator.hpp"


void ReplayHistory(std::vector<Simulator::SystemState*> state_history, double dt, double tmax, double replaySpeed = 1);



