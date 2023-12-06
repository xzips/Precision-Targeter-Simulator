/*
GraphPlot.hpp

Plotting class for basic graphing of data with axes, labels, and titles.

*/


#pragma once




#include <vector>
#include "SFML/Graphics.hpp"

class GraphPlot
{
public:
	std::vector<double> x;
	std::vector<double> y;

	double xmin = INFINITY;
	double xmax = -INFINITY;
	double ymin = INFINITY;
	double ymax = -INFINITY;
	double lineThickness = 3.f;

	size_t screen_width = 0;
	size_t screen_height = 0;
	size_t screen_x = 0;
	size_t screen_y = 0;

	std::string title = "";

	GraphPlot();
	
	void AddPoint(double x, double y);
	
	void SetScreen(size_t width, size_t height, size_t x, size_t y);

	void SetTitle(std::string title);

	void Clear();

	void Draw(sf::RenderWindow& window);
	
	
};

