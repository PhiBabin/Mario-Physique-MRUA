#ifndef INCLUDES_HPP_INCLUDED
#define INCLUDES_HPP_INCLUDED

#define SCREENWIDTH 800 //Px width of the screen
#define SCREENHEIGHT 600 //Px height of the screen
#define TILEWIDTH 16 //Px width a tile
#define TILEHEIGHT 15  //Px height a tile
#define TILESETWIDTH 9 //Number of tile in a tile set image
#define TILESETHEIGHT 8 //Number of tile in a tile set image

#define LEFT true
#define RIGHT false


#define PLAYERCOLLISIONWIDTH 17
#define PLAYERCOLLISIONHEIGHT 17
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <map>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



sf::Clock Clock;
using namespace std;
#include "LayerAnim.cpp"
#include "ImgAnim.cpp"

#include "dataPoint.cpp"

#include "Player.cpp"

#include "Map.cpp"

#endif // INCLUDES_HPP_INCLUDED
