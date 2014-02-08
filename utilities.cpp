#include <iostream>

#include "utilities.h"

bool optionsStatut8b(char options, unsigned char p)
{
	return (options >> p) % 2;
}

double dabs(double value)
{
        if (value < 0)
                return -value;
        else
                return  value;
}

int sgn(double value)
{
        if (value < 0)
                return -1;
        else
                return  1;
}