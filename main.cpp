#include <iostream>

#include "BMPImage.h"

bool isPositiveNumber(const string& str);

int main(int argc, char **argv)
{
	// g++ main.cpp BMPImage.cpp BMPParser.cpp -o main.exe
	// main.exe examples_4/bmp.bmp resized.bmp 3.1
	if(argc != 4)
	{
		std::cerr << "You need to supply three arguments to this program" << std::endl;
		return 1;
	}

	std::string inputFile = argv[1];
	std::string outputFile = argv[2];
	
	if (!isPositiveNumber(argv[3]))
	{
		cerr << "Third argument must be a positive number" << endl;
		return 1;
	}

	double scaleFactor = stod(argv[3]);

	BMPImage bmpImage;

	try
	{
		bmpImage.read(inputFile);
		bmpImage.resize(scaleFactor);
		bmpImage.save(outputFile);
	}
	catch(const std::runtime_error& e)
	{
		std::cerr << e.what() << '\n';
	}
}

bool isPositiveNumber(const string& str)
{
	if (str.empty())
		return false;

	for (char c : str) {
		if (!std::isdigit(c) && c != '.')
			return false;
	}

	if (str[0] == '.')
		return false;

	if (str[str.size() - 1] == '.')
		return false;

	int numDecimalPoints = 0;
	for (char c : str) {
		if (c == '.')
			numDecimalPoints++;

		if (numDecimalPoints > 1)
			return false;
	}

	double value = std::stod(str);
	return value > 0.0;
}