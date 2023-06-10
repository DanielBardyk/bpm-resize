#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <exception>

#include "BMPHeader.h"
#include "BMPParser.h"

using namespace std;

class BMPImage {
private:
	vector<vector<PIXELDATA>> pixels;
	BMPParser *bmpParser;
	BMPHEAD fileHeaders;

public:
	void read(string& fname);
	void save(string& fname);
	void resize(double fname);
};