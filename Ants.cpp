//
// Created by Abdullah Shahid on 5/27/2023.
//

#include "Ants.h"

Ants::Ants(int x, int y)
{
	texture.loadFromFile("Sprites/Ant.png");
	sprite.setTexture(texture);
	Vector2u size = texture.getSize();
	sprite.setOrigin(size.x/2,size.y/2);
}
