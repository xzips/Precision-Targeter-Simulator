/*

HistoryReplay.cpp
Single function to load the state history from a simulation, and replay it by instantiating graphs and drawing the gear visualization in real time.

Also includes helper function to draw the gear visualization.

*/

#include "HistoryReplay.hpp"
#include "SFML/Graphics.hpp"
#include "GraphPlot.hpp"
#include "Textures.hpp"


void DrawGearVisualization(sf::RenderWindow& window, double theta, double zoom)
{
	// Ensure zoom is never zero to avoid division by zero errors
	if (zoom == 0) zoom = 1;

	// Gear 1 setup
	sf::Sprite gear1;
	gear1.setTexture(*G_textures[0]);
	sf::Vector2f gear1Origin(0.5 * G_textures[0]->getSize().x, 0.5 * G_textures[0]->getSize().y);
	gear1.setOrigin(gear1Origin);
	gear1.setRotation(-(theta * 180 / 3.14159));
	gear1.setScale(0.5 * zoom, 0.5 * zoom);

	// Gear 2 setup
	sf::Sprite gear2;
	gear2.setTexture(*G_textures[1]);
	sf::Vector2f gear2Origin(0.5 * G_textures[1]->getSize().x, 0.5 * G_textures[1]->getSize().y);
	gear2.setOrigin(gear2Origin);
	gear2.setRotation(20 * theta * 180 / 3.14159 - 15);
	gear2.setScale(0.045 * zoom, 0.045 * zoom);

	// Initial positions for the gears
	sf::Vector2f gear1InitialPos(1460, 400);
	sf::Vector2f gear2InitialPos(1460, 800);

	// Calculate the touch point
	float gear1BottomBound = gear1InitialPos.y + gear1Origin.y * 0.5 * zoom;
	float gear2TopBound = gear2InitialPos.y - gear2Origin.y * 0.045 * zoom;
	sf::Vector2f touchPoint(
		(gear1InitialPos.x + gear2InitialPos.x) / 2, // Average of the two x positions
		(gear1BottomBound + gear2TopBound) / 2       // Midpoint between the bottom of gear 1 and top of gear 2
	);

	// Adjust positions based on zoom and touching point
	sf::Vector2f gear1Position(
		gear1InitialPos.x - (touchPoint.x - gear1InitialPos.x) * (zoom - 1),
		gear1InitialPos.y - (touchPoint.y - gear1InitialPos.y) * (zoom - 1)
	);
	sf::Vector2f gear2Position(
		gear2InitialPos.x - (touchPoint.x - gear2InitialPos.x) * (zoom - 1),
		gear2InitialPos.y - (touchPoint.y - gear2InitialPos.y) * (zoom - 1)
	);

	gear1.setPosition(gear1Position);
	gear2.setPosition(gear2Position);

	// Draw gears
	window.draw(gear1);
	window.draw(gear2);
}





void ReplayHistory(std::vector<Simulator::SystemState *> state_history, double dt, double tmax, double replaySpeed)
{
	//create window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "History Replay");
	window.setFramerateLimit(60);

	//create graph plots for each variable, theta, omega, motor_input with respect to time

	GraphPlot theta_plot;
	theta_plot.SetScreen(1000, 270, 0, 0);
	theta_plot.SetTitle("Theta [rad]");
	
	GraphPlot omega_plot;
	omega_plot.SetScreen(1000, 270, 0, 270);
	omega_plot.SetTitle("Omega [rad/sec]");

	GraphPlot motor_input_plot;
	motor_input_plot.SetScreen(1000, 270, 0, 540);
	motor_input_plot.SetTitle("Motor Input");

	GraphPlot motor_torque_plot;
	motor_torque_plot.SetScreen(1000, 270, 0, 810);
	motor_torque_plot.SetTitle("Motor Torque [N/m]");

	double simTime = 0;
	double simTimeReplay = 0;
	

	size_t cur_hist_idx = 0;

	double gearTheta = 0;

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

		
		DrawGearVisualization(window, gearTheta, 1);

		//draw graphs
		theta_plot.Draw(window);
		omega_plot.Draw(window);
		motor_input_plot.Draw(window);
		motor_torque_plot.Draw(window);
		
		

		if (cur_hist_idx < state_history.size())
		{
			gearTheta = state_history[cur_hist_idx]->theta;
			
			//assuming we're running at 60fps, we need to add up to the right cur_hist_idx
			while (simTime < simTimeReplay && cur_hist_idx < state_history.size())
			{
				//if we've reached the end of the history, stop
			
		
			
				//update graphs
				theta_plot.AddPoint(simTime, state_history[cur_hist_idx]->theta);
				omega_plot.AddPoint(simTime, state_history[cur_hist_idx]->omega);
				motor_input_plot.AddPoint(simTime, state_history[cur_hist_idx]->motor_input);
				motor_torque_plot.AddPoint(simTime, state_history[cur_hist_idx]->motor_torque);
				

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