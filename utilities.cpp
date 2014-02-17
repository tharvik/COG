#include "utilities.h"

bool optionsStatut8b(char options, unsigned char p)
{
	return (options >> p) % 2;
}
