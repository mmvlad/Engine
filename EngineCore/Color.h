#pragma once
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>

#include "Logger.h"

class Color
{
public:
	Color();
	Color(const float normR, const float normG, const float normB, const float normA);
	Color(const Color& other);

	virtual ~Color();

	const float R() const;
	const float G() const;
	const float B() const;
	const float A() const;

	static Color FromBytes(float r = 255, float g = 255, float b = 255, float a = 255) {
		return Color(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
	}

	// TODO: optimize this
	static Color FromHexRGB(const std::string & hex) {
		float r = Color::HexByteToInt(hex.substr(0, 2));
		float g = Color::HexByteToInt(hex.substr(2, 2));
		float b = Color::HexByteToInt(hex.substr(4, 2));


		return Color::FromBytes(r, g, b);
	}

	static Color FromHexRGBA(const std::string & hex) {
		float r = Color::HexByteToInt(hex.substr(0, 2));
		float g = Color::HexByteToInt(hex.substr(2, 2));
		float b = Color::HexByteToInt(hex.substr(4, 2));
		float a = Color::HexByteToInt(hex.substr(6, 2));

		return Color::FromBytes(r, g, b, a);
	}

	static float HexByteToInt(const std::string & hexStr) {
		assert(hexStr.length() == 2);
		unsigned int x = strtoul(hexStr.substr(0, 2).c_str(), NULL, 16);
		return (float)x;
	}

private:
	Color& operator=(const Color&) = delete;

	// normalized values
	float _r;
	float _g;
	float _b;
	float _a;

};

std::ostream& operator<<(std::ostream& os, const Color& obj);