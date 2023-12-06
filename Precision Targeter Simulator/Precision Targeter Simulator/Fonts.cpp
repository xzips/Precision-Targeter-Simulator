/*
Fonts.cpp

You will need to modify the paths to the font to match your system.

*/


#include "SFML/Graphics.hpp"


sf::Font* G_font;

void G_LoadFont()
{
	G_font = new sf::Font();

	
	//G_font->loadFromFile("C:/Users/aspen/Desktop/Precision-Targeter-Simulator/TruenoRegular.otf");

	if (!G_font->loadFromFile("C:/Users/aspen/Desktop/Precision-Targeter-Simulator/TruenoRegular.otf"))
	{
		printf("Error loading font\n");
	}

	else
	{
		printf("Font loaded\n");
	}
}
