#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <exception>

using namespace std;

#include "BMPHeader.h"

class BMPParser {
private:
	void isBMPType(const BMPHEAD& fHeaders, const string& fname);
	void is24Bits(const BMPHEAD &fHeaders, const string& fname);
	void isNotCompressed(const BMPHEAD& fHeaders, const string& fname);

public:
	void parseBMP(const string& fname);
};