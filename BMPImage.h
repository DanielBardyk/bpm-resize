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
	BMPParser *BPMParser;
	BMPHEAD fHeaders;

public:
	void read(const string& fname);
	void resize(double fname);
	void save(const string& fname);
};