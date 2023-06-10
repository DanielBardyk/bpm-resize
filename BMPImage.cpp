#include "BMPImage.h"

void BMPImage::read(string& fname) 
{
	ifstream file(fname, ios::binary);
	if(!file.is_open())
	{
		throw runtime_error("Cannot open the file " + fname);
	}

	bmpParser->parseBMP(fname);

	file.read((char *)(&fileHeaders), sizeof(fileHeaders));

	file.seekg(fileHeaders.headersize);

	const int padding = ((4 - (fileHeaders.width * 3) % 4) % 4);

	for (int i = 0; i < fileHeaders.depth; i++)
	{
		PIXELDATA pixel;
		vector<PIXELDATA> row;
		for (int j = 0; j < this->fileHeaders.width; j++)
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
	int resizedWidth = this->fileHeaders.width * scaleFactor;
	int resizedDepth = this->fileHeaders.depth * scaleFactor;

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

	this->fileHeaders.filesize = sizeof(this->fileHeaders) + sizeof(this->pixels);
	this->fileHeaders.width = resizedWidth;
	this->fileHeaders.depth = resizedDepth;

	this->pixels = newPixels;
}

void BMPImage::save(string& fname)
{
	ofstream file(fname, ios::out | ios::binary);
	if(!file.is_open())
	{
		throw runtime_error("Cannot open the file " + fname);
	}

	fileHeaders.headersize = 54L;
	fileHeaders.infoSize = 40L;

	file.write((char *)(&fileHeaders), sizeof(fileHeaders));

	const int padding = (4 - (3 * fileHeaders.width % 4)) % 4;
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
