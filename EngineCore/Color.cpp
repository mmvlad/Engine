#include "Color.h"


std::ostream& operator<<(std::ostream& os, const Color& obj) {
	os << "Color (r: " << obj.R() << ", g: " << obj.G() << ", b: " << obj.B() << ", a: " << obj.A() << ")";
	return os;
}

Color::Color() :
	_r(0),
	_g(0),
	_b(0),
	_a(0)
{
	//Log::Info("Color empty constructor");
}

Color::Color(const Color& other) {
	_r = other._r;
	_g = other._g;
	_b = other._b;
	_a = other._a;

	//Log::Info("Color copy constructor");

	if (_r > 1 || _g > 1 || _b > 1 || _a > 1) {
		Log::Error("One or more of color values are > 1. They should be normalized to [0, 1]");
	}
}

Color::Color(const float normR, const float normG, const float normB, const float normA) :
	_r(normR),
	_g(normG),
	_b(normB),
	_a(normA)
{
	//Log::Info("Color param constructor");
}


Color::~Color()
{
}


const float Color::R() const {
	return _r;
}

const float Color::G() const {
	return _g;
}

const float Color::B() const {
	return _b;
}

const float Color::A() const {
	return _a;
}