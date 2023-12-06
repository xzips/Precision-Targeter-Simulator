#include "HistoryReplay.hpp"
#include "SFML/Graphics.hpp"
#include "GraphPlot.hpp"

void ReplayHistory(std::vector<Simulator::SystemState *> state_history, double dt, double tmax, double replaySpeed)
{
	//create window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "History Replay");
	window.setFramerateLimit(60);

	//create graph plots for each variable, theta, omega, motor_input with respect to time

	GraphPlot theta_plot;
	theta_plot.SetScreen(1000, 360, 0, 0);
	theta_plot.SetTitle("Theta [rad]");
	
	GraphPlot omega_plot;
	omega_plot.SetScreen(1000, 360, 0, 360);
	omega_plot.SetTitle("Omega [rad/sec]");

	GraphPlot motor_input_plot;
	motor_input_plot.SetScreen(1000, 360, 0, 720);
	motor_input_plot.SetTitle("Motor Input");

	double simTime = 0;
	double simTimeReplay = 0;
	

	size_t cur_hist_idx = 0;

	while (window.isOpen())
	{
		//handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			//close window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//clear window
		window.clear(sf::Color::Black);

		//draw graphs
		theta_plot.Draw(window);
		omega_plot.Draw(window);
		motor_input_plot.Draw(window);
		

		if (cur_hist_idx < state_history.size())
		{
			//assuming we're running at 60fps, we need to add up to the right cur_hist_idx
			while (simTime < simTimeReplay && cur_hist_idx < state_history.size())
			{
				//if we've reached the end of the history, stop
			
		
			
				//update graphs
				theta_plot.AddPoint(simTime, state_history[cur_hist_idx]->theta);
				omega_plot.AddPoint(simTime, state_history[cur_hist_idx]->omega);
				motor_input_plot.AddPoint(simTime, state_history[cur_hist_idx]->motor_input);

				//increment sim time
				simTime += dt;

				//increment history index
				cur_hist_idx++;
			}

		}

		//display window
		window.display();

		simTimeReplay += replaySpeed * dt;
	}
	
	
}