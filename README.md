# HaydensHeaders
Collection of useful C++ headers

# Paint.hpp:
Adds the correct ANSII escape codes to a given string based on the ENUM COLOUR / HEX / RGB Provided
```c++
#include "Paint.hpp"
int main()
{
	// ENUM (ROY G BIV + TEAL)
	std::cout << paint("I'm Red!", RED) << std::endl;
	// RGB
	std::cout << paint("I'm Orange!", 255, 165, 0) << std::endl;
	// HEX
	std::cout << paint("I'm Yellow!", "#FFFF00") << std::endl;

	return 0;
}
```
