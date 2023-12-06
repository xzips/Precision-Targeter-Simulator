
#include "Textures.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

std::vector<sf::Texture*> G_textures;

void G_LoadTextures()
{
	//for now don't do this automatically, just load spur 1 and spur 2
	
	std::vector<std::string> filepaths =
	{
		"C:/Users/aspen/Desktop/Precision-Targeter-Simulator/spur 1.png",
		"C:/Users/aspen/Desktop/Precision-Targeter-Simulator/spur 2.png"

	};

	for (int i = 0; i < filepaths.size(); i++)
	{
		sf::Texture* texture = new sf::Texture();
		texture->loadFromFile(filepaths[i]);
		G_textures.push_back(texture);
	}
	
}