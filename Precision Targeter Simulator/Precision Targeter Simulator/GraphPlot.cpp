/*
GraphPlot.cpp

Plotting class for basic graphing of data with axes, labels, and titles.

*/

#include "GraphPlot.hpp"
#include "Fonts.hpp"
#include <sstream>
#include <iomanip>

GraphPlot::GraphPlot()
{

}

void GraphPlot::SetTitle(std::string title)
{
	this->title = title;
}


void GraphPlot::AddPoint(double x, double y)
{
	this->x.push_back(x);
	this->y.push_back(y);

	//set new min/max
	if (x < xmin)
		xmin = x;
	if (x > xmax)
		xmax = x;
	if (y < ymin)
		ymin = y;
	if (y > ymax)
		ymax = y;

	//if ymin and ymax are spread to -1 and +1 

	double yspread = ymax - ymin;
	if (yspread == 0)
	{
			double ycenter = (ymax + ymin) / 2;
			ymin = ycenter - 0.1;
			ymax = ycenter + 0.1;
	}

}

void GraphPlot::SetScreen(size_t width, size_t height, size_t x, size_t y)
{
	screen_width = width;
	screen_height = height;
	screen_x = x;
	screen_y = y;
}

void GraphPlot::Clear()
{
	x.clear();
	y.clear();

	//reset max and mins
	xmin = INFINITY;
	xmax = -INFINITY;
	ymin = INFINITY;
	ymax = -INFINITY;
	
}

std::string floatToString(float value) {
	std::ostringstream oss;

	// Set precision high enough to handle the fractional part
	oss << std::fixed << std::setprecision(6) << value;

	std::string str = oss.str();

	// Remove trailing zeros
	if (str.find('.') != std::string::npos) {
		str.erase(str.find_last_not_of('0') + 1, std::string::npos);
		str.erase(str.find_last_not_of('.') + 1, std::string::npos);
	}

	return str;
}


void GraphPlot::Draw(sf::RenderWindow& window)
{
	
	//draw the plot within the bounds of the screen
	size_t border_margin = 60;
	
	size_t effective_width = screen_width - 2 * border_margin;
	size_t effective_height = screen_height - 2 * border_margin;
	size_t effective_x = screen_x + border_margin;
	size_t effective_y = screen_y + border_margin;


	sf::RectangleShape background(sf::Vector2f(screen_width, screen_height));
	background.setPosition(screen_x, screen_y);
	background.setFillColor(sf::Color(250, 250, 250));
	window.draw(background);


	//draw title use *G_font
	sf::Text title_text;
	title_text.setFont(*G_font);
	title_text.setString(title);
	title_text.setCharacterSize(26);
	title_text.setFillColor(sf::Color::Black);
	//get local bounds of text and use that to center it at top of graph with marign
	sf::FloatRect text_bounds = title_text.getLocalBounds();
	title_text.setPosition(screen_x + screen_width / 2 - text_bounds.width / 2, screen_y + border_margin / 2 - text_bounds.height / 2);
	window.draw(title_text);
	
	

	
	//draw the axes, if they are within the bounds of the screen
	if (xmin <= 0 && xmax >= 0)
	{

		//draw rect for x axis
		sf::RectangleShape xaxis(sf::Vector2f(effective_width, lineThickness));
		
		xaxis.setPosition(effective_x, effective_y + effective_height * (1 - (-ymin) / (ymax - ymin)));

		xaxis.setFillColor(sf::Color::Black);
		window.draw(xaxis);
		


	}

	if (ymin <= 0 && ymax >= 0)
	{
		//draw rect for y axis
		sf::RectangleShape yaxis(sf::Vector2f(lineThickness, effective_height));
		yaxis.setPosition(effective_x + effective_width * (-xmin) / (xmax - xmin), effective_y);
		yaxis.setFillColor(sf::Color::Black);
		window.draw(yaxis);
	}

	//find the biggest power of 10 that is smaller than the max value of x and y
	//use that to determine the spacing of the tick marks
	double xtick_spacing = std::pow(10, std::floor(std::log10(xmax - xmin)));
	double ytick_spacing = std::pow(10, std::floor(std::log10(ymax - ymin)));

	

	double tickLength = 10;

	//if xmax and ymax are inf or -inf, then the spacing will be inf, so set it to 1
	if (!isinf(xmax) and !isinf(ymax) and !isinf(ymin) and !isinf(xmin) and xmax - xmin != 0 and ymax - ymin !=0)
	{




		//positive y ticks
		for (double ytick = ytick_spacing; ytick <= ymax; ytick += ytick_spacing)
		{
			double ytick_pos = effective_y + effective_height * (1 - (ytick - ymin) / (ymax - ymin));
			sf::RectangleShape ytick_rect(sf::Vector2f(tickLength, lineThickness));
			ytick_rect.setPosition(effective_x + effective_width * (-xmin) / (xmax - xmin), ytick_pos);
			ytick_rect.setFillColor(sf::Color::Black);
			window.draw(ytick_rect);

			//labels
			sf::Text ytick_text;
			ytick_text.setFont(*G_font);
			ytick_text.setString(floatToString(ytick));
			ytick_text.setCharacterSize(22);
			ytick_text.setFillColor(sf::Color::Black);
			//get local bounds of text and use that to center it at top of graph with marign
			sf::FloatRect text_bounds = ytick_text.getLocalBounds();
			ytick_text.setPosition(effective_x + effective_width * (-xmin) / (xmax - xmin) - text_bounds.width - 5, ytick_pos - text_bounds.height / 2);
			window.draw(ytick_text);

		}


		//negative y ticks
		for (double ytick = -ytick_spacing; ytick >= ymin; ytick -= ytick_spacing)
		{
			double ytick_pos = effective_y + effective_height * (1 - (ytick - ymin) / (ymax - ymin));
			sf::RectangleShape ytick_rect(sf::Vector2f(tickLength, lineThickness));
			ytick_rect.setPosition(effective_x + effective_width * (-xmin) / (xmax - xmin), ytick_pos);
			ytick_rect.setFillColor(sf::Color::Black);
			window.draw(ytick_rect);

			//labels
			sf::Text ytick_text;
			ytick_text.setFont(*G_font);
			ytick_text.setString(floatToString(ytick));
			ytick_text.setCharacterSize(22);
			ytick_text.setFillColor(sf::Color::Black);
			//get local bounds of text and use that to center it at top of graph with marign
			sf::FloatRect text_bounds = ytick_text.getLocalBounds();
			ytick_text.setPosition(effective_x + effective_width * (-xmin) / (xmax - xmin) - text_bounds.width - 5, ytick_pos - text_bounds.height / 2);
			window.draw(ytick_text);

		}





		
		//positive x ticks
		for (double xtick = xtick_spacing; xtick <= xmax; xtick += xtick_spacing)
		{
			double xtick_pos = effective_x + effective_width * (xtick - xmin) / (xmax - xmin);
			sf::RectangleShape xtick_rect(sf::Vector2f(lineThickness, tickLength));
			xtick_rect.setPosition(xtick_pos, effective_y + effective_height * (1 - (-ymin) / (ymax - ymin)));
			xtick_rect.setFillColor(sf::Color::Black);
			window.draw(xtick_rect);

			//labels
			sf::Text xtick_text;
			xtick_text.setFont(*G_font);
			xtick_text.setString(floatToString(xtick));
			xtick_text.setCharacterSize(22);
			xtick_text.setFillColor(sf::Color::Black);
			//get local bounds of text and use that to center it at top of graph with marign
			sf::FloatRect text_bounds = xtick_text.getLocalBounds();
			xtick_text.setPosition(xtick_pos - text_bounds.width / 2, effective_y + effective_height * (1 - (-ymin) / (ymax - ymin)) + text_bounds.height + 5);
			window.draw(xtick_text);
		}

		//also plot zero on y axis if it is in range
		if (ymin <= 0 and ymax >= 0)
		{
			double ytick_pos = effective_y + effective_height * (1 - (-ymin) / (ymax - ymin));
			sf::RectangleShape ytick_rect(sf::Vector2f(tickLength, lineThickness));
			ytick_rect.setPosition(effective_x + effective_width * (-xmin) / (xmax - xmin), ytick_pos);
			ytick_rect.setFillColor(sf::Color::Black);
			window.draw(ytick_rect);

			//labels
			sf::Text ytick_text;
			ytick_text.setFont(*G_font);
			ytick_text.setString("0");
			ytick_text.setCharacterSize(22);
			ytick_text.setFillColor(sf::Color::Black);
			sf::FloatRect text_bounds = ytick_text.getLocalBounds();
			ytick_text.setPosition(effective_x + effective_width * (-xmin) / (xmax - xmin) - text_bounds.width - 5, ytick_pos - text_bounds.height / 2);
			window.draw(ytick_text);
		}
	


		
	}

	
	

	if (x.size() < 2)
		return;
	

	
	for (size_t i = 0; i < x.size() - 1; i++)
	{
		double x1 = effective_x + effective_width * (x[i] - xmin) / (xmax - xmin);
		double y1 = effective_y + effective_height * (1 - (y[i] - ymin) / (ymax - ymin));
		double x2 = effective_x + effective_width * (x[i + 1] - xmin) / (xmax - xmin);
		double y2 = effective_y + effective_height * (1 - (y[i + 1] - ymin) / (ymax - ymin));

		sf::Vector2f point1(x1, y1);
		sf::Vector2f point2(x2, y2);

		sf::RectangleShape line;
		line.setSize(sf::Vector2f(std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2)) + 1, lineThickness));
		line.setPosition(point1);
		line.setFillColor(sf::Color::Red);

		// Calculate the angle
		float angle = std::atan2(y2 - y1, x2 - x1) * 180 / 3.14159265;
		line.setRotation(angle);

		window.draw(line);
	}

	


	/*
	// Offset for simulating thickness
	float offset = lineThickness / 2.0f;

	for (size_t i = 0; i < x.size() - 1; i++)
	{
		// Your existing code to calculate x1, y1, x2, y2

		double x1 = effective_x + effective_width * (x[i] - xmin) / (xmax - xmin);
		double y1 = effective_y + effective_height * (1 - (y[i] - ymin) / (ymax - ymin));
		double x2 = effective_x + effective_width * (x[i + 1] - xmin) / (xmax - xmin);
		double y2 = effective_y + effective_height * (1 - (y[i + 1] - ymin) / (ymax - ymin));


		for (float j = -offset; j <= offset; j += 1.0f)
		{
			sf::VertexArray thickLine(sf::Lines, 2);
			thickLine[0].position = sf::Vector2f(x1, y1 + j);
			thickLine[1].position = sf::Vector2f(x2, y2 + j);
			thickLine[0].color = sf::Color::Red;
			thickLine[1].color = sf::Color::Red;

			window.draw(thickLine);
		}
	}

	*/

	
	
}



