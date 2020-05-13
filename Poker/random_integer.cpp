/* 
 * Template to generate random integer variable
 */

#include "random_integer.hpp"



int randomInteger(int min, int max) {

	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(min, max);

	return distribution(generator);
}