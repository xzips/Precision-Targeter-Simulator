/*
Textures.hpp

You will need to modify the paths to the textures to match your system.

*/


#pragma once


#include "SFML/Graphics.hpp"
#include <vector>

extern std::vector<sf::Texture*> G_textures;

void G_LoadTextures();