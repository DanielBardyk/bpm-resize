#include "BMPParser.h"

void BMPParser::isBMPType(const BMPHEAD& fHeaders, const string& fname)
{
	if(fHeaders.id[0] != 'B' || fHeaders.id[1] != 'M') {
		throw runtime_error("File " + fname + " is not of BMP format");
	}
}

void BMPParser::is24Bits(const BMPHEAD& fHeaders, const string& fname)
{
	if (fHeaders.bits != 24)
	{
		throw runtime_error("File " + fname + " contains non-24bit image. Bitmap supports only 24bits per pixel");
	}
}

void BMPParser::isNotCompressed(const BMPHEAD& fHeaders, const string& fname)
{
	if (fHeaders.biCompression != 0L)
	{
		throw runtime_error("File " + fname + " contains a compressed image. Bitmap supports only uncompressed.");
	}
}

void BMPParser::parseBMP(const string& fname)
{
	ifstream file(fname, ios::binary);
	if(!file.is_open())
	{
		throw runtime_error("Cannot open the file " + fname);
	}

	BMPHEAD fHeaders;
	file.read((char *)(&fHeaders), sizeof(fHeaders));

	isBMPType(fHeaders, fname);
	is24Bits(fHeaders, fname);
	isNotCompressed(fHeaders, fname);
	
	file.close();
}