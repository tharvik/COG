#include "utilities.h"

bool optionsStatut8b(const char options, const unsigned char p)
{
	return (options >> p) % 2;
}
