#pragma once

#include <iostream>
#include <string>
#include "Includes.h"

INTRFC IPrintable
{

	virtual const std::string ToString() const = 0;
	
};

inline std::ostream& operator<<(std::ostream& os, const IPrintable& printable)
{
	os << printable.ToString();
	return os;
}
