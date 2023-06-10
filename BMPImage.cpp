#include "BMPImage.h"

void BMPImage::read(const string& fname) 
{
	ifstream file(fname, ios::binary);
	if(!file.is_open())
	{
		throw runtime_error("Cannot open the file " + fname);
	}

	BPMParser->parseBMP(fname);

	file.read((char *)(&fHeaders), sizeof(fHeaders));

	file.seekg(fHeaders.headersize);

	const int padding = ((4 - (fHeaders.width * 3) % 4) % 4);

	for (int i = 0; i < fHeaders.depth; i++)
	{
		PIXELDATA pixel;
		vector<PIXELDATA> row;
		for (int j = 0; j < this->fHeaders.width; j++)
		{
			file.read((char *)(&pixel), sizeof(pixel));
			row.push_back(pixel);
		}

		file.ignore(padding);
		pixels.push_back(row);
	}
	file.close();
}

void BMPImage::resize(double scaleFactor)
{
	int resizedWidth = this->fHeaders.width * scaleFactor;
	int resizedDepth = this->fHeaders.depth * scaleFactor;

	vector<vector<PIXELDATA>> newPixels(resizedDepth, vector<PIXELDATA>(resizedWidth));

	for (int y = 0; y < resizedDepth; y++)
	{
		for (int x = 0; x < resizedWidth; x++)
		{
			int originalX = x / scaleFactor;
			int originalY = y / scaleFactor;

			PIXELDATA nearestPixel = this->pixels[originalY][originalX];

			newPixels[y][x] = nearestPixel;
		}
	}

	this->fHeaders.filesize = sizeof(this->fHeaders) + sizeof(this->pixels);
	this->fHeaders.width = resizedWidth;
	this->fHeaders.depth = resizedDepth;

	this->pixels = newPixels;
}

void BMPImage::save(const string& fname)
{
	ofstream file(fname, ios::out | ios::binary);
	if(!file.is_open())
	{
		throw runtime_error("Cannot open the file " + fname);
	}

	fHeaders.headersize = 54L;
	fHeaders.infoSize = 40L;

	file.write((char *)(&fHeaders), sizeof(fHeaders));

	const int padding = (4 - (3 * fHeaders.width % 4)) % 4;
	for (int i = 0; i < pixels.size(); i++)
	{
		vector<PIXELDATA>& row = pixels[i];

		for (int j = 0; j < row.size(); j++)
		{
			PIXELDATA &pixel = row[j];
			file.write((char *)(&pixel), sizeof(pixel));
		}

		for (int i = 0; i < padding; i++)
		{
			file.put(0);
		}
	}
	file.close();
}
