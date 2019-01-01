#include "../string.h"

/**
 * Returns the length of string string
 * @param  string The string to measure
 * @return        The length of the string
 */
int strlen(char string[]){
	int result = 0;
	while ( string[result] )
		result++;
	return result;
}
