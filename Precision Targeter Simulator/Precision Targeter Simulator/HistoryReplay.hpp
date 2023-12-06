/*

HistoryReplay.hpp
Single function to load the state history from a simulation, and replay it by instantiating graphs and drawing the gear visualization in real time.

*/


#pragma once
#include "Simulator.hpp"




void ReplayHistory(std::vector<Simulator::SystemState*> state_history, double dt, double tmax, double replaySpeed = 1);



