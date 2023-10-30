#pragma once

/*
* ****************************
*       Hayden Zeller        *
*	    PaintText.hpp (V1.0) *
*		2023-10-30			 *
* ********************************************
*											 *
* This file contains the paint function,	 *
* which is used to color text in the console *
* using ANSII escape codes.					 *
*											 *
* ********************************************
*/


#include <string>

/*
* ***********************
* ENUM of common colors *
* ***********************
*/
enum Color { RED=0, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET, TEAL }; 

/*
* *****************************************************
* paint function, takes a string and a color and	  *
* returns the string with the color applied to it.	  *
* *****************************************************
*/
std::string paint(std::string str, int colour)
{
	switch (colour)
	{
	case 0:
		return "\033[31m" + str + "\033[0m";
		break;
	case 1:
		return "\033[38;5;208m" + str + "\033[0m";
		break;
	case 2:
		return "\033[33m" + str + "\033[0m";
		break;
	case 3:
		return "\033[32m" + str + "\033[0m";
		break;
	case 4:
		return "\033[34m" + str + "\033[0m";
		break;
	case 5:
		return "\033[38;2;75;0;130m" + str + "\033[0m";
		break;
	case 6:
		return "\033[38;2;238;130;238m" + str + "\033[0m";
		break;

	case 7:
		return "\033[38;2;0;128;128m" + str + "\033[0m";
		break;

	default:
		return str;
		break;
	}
}

/*
* ******************************************************
* paint function, takes a string and an rgb value and  *
* returns the string with the color applied to it.	   *
* ******************************************************
*/
std::string paint(std::string str, int r, int g, int b)
{
	if (r < 0) r = 0;
	if (r > 255) r = 255;
	if (g < 0) g = 0;
	if (g > 255) g = 255;
	if (b < 0) b = 0;
	if (b > 255) b = 255;
	return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m" + str + "\033[0m";
}

/*
* *****************************************************
* paint function, takes a string and a hex value and  *
* returns the string with the color applied to it.	  *
* *****************************************************
*/
std::string paint(std::string str, std::string hex)
{
	int hex_value = std::stoi(hex.substr(1), nullptr, 16);
	int r = (hex_value >> 16) & 0xFF;
	int g = (hex_value >> 8) & 0xFF;
	int b = hex_value & 0xFF;

	std::string out = paint(str, r, g, b);
	return out;
}