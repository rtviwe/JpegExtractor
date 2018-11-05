#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "JpegExtractor.hpp"

bool isFileEmpty(std::ifstream &ifs)
{
	char c;
	ifs >> c;
	if (!ifs)
	{
		return true;
	}

	ifs.seekg(0, std::ios::beg);
	return false;
}

void readByte(std::ifstream& ifs, unsigned int& previous, unsigned int& current)
{
	uint8_t buffer[1] = { 0 };
	ifs.read((char*)buffer, sizeof(buffer));

	previous = current;
	current = buffer[0];
}

char getHexLetterFromNumberAt(int number, int position)
{
	int quotient(number);
	int num(0);
	int i(1);
	std::vector<char> hexadecimalNumber;

	while (quotient != 0)
	{
		num = quotient % 16;
		hexadecimalNumber.push_back(num);
		quotient = quotient / 16;
	}

	hexadecimalNumber.push_back(0);
	hexadecimalNumber.push_back(0);
	return hexadecimalNumber[position];
}

JpegExtractor::JpegExtractor(std::string pathToFile)
	: pathToFile_(pathToFile)
{
}

JpegExtractor::JpegExtractor(const JpegExtractor& jpegExtractor)
	: pathToFile_(jpegExtractor.pathToFile_),
	commentary_(jpegExtractor.commentary_),
	filesize_(jpegExtractor.filesize_),
	precisionOfFrameBase_(jpegExtractor.precisionOfFrameBase_),
	heightOfImage_(jpegExtractor.heightOfImage_),
	widthOfImage_(jpegExtractor.widthOfImage_),
	amountOfComponents_(jpegExtractor.amountOfComponents_),
	quantizationTables_(jpegExtractor.quantizationTables_),
	huffmanTables_(jpegExtractor.huffmanTables_),
	components_(jpegExtractor.components_)
{
}

void JpegExtractor::analyzeFile()
{
	if (pathToFile_.empty())
	{
		throw std::exception("Filepath is empty");
	}

	std::ifstream fis(pathToFile_, std::ios_base::binary | std::ios_base::in);

	if (isFileEmpty(fis)) {
		throw std::exception("File is empty");
	}

	struct stat st_one;
	stat(pathToFile_.c_str(), &st_one);
	filesize_ = st_one.st_size;

	unsigned int previousByte = 0;
	unsigned int currentByte = 0;

	while (!fis.eof())
	{
		readByte(fis, previousByte, currentByte);

		if (startOfFrame[0] == previousByte && startOfFrame[1] == currentByte)
		{
			readBaseFrame(fis, previousByte, currentByte);
		}

		if (startOfHuffman[0] == previousByte && startOfHuffman[1] == currentByte)
		{
			readHuffmanTable(fis, previousByte, currentByte);
		}

		if (startOfQuantization[0] == previousByte && startOfQuantization[1] == currentByte)
		{
			readQuantizationTable(fis, previousByte, currentByte);
		}

		if (startOfCommentary[0] == previousByte && startOfCommentary[1] == currentByte)
		{
			readCommentary(fis, previousByte, currentByte);
		}
	}
}

void JpegExtractor::readCommentary(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte)
{
	readByte(fis, previousByte, currentByte);
	readByte(fis, previousByte, currentByte);
	int commentaryLength = static_cast<int>(previousByte) * 256 + static_cast<int>(currentByte - lengthOfCommentarySize);

	for (int i(0); i < commentaryLength; i++)
	{
		readByte(fis, previousByte, currentByte);
		commentary_ += static_cast<char>(currentByte);
	}
}

void JpegExtractor::readBaseFrame(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte)
{
	readByte(fis, previousByte, currentByte);
	readByte(fis, previousByte, currentByte);
	int frameBaseLength = static_cast<int>(previousByte) * 256 + static_cast<int>(currentByte) - lengthOfFrameBaseSize;

	readByte(fis, previousByte, currentByte);
	precisionOfFrameBase_ = static_cast<int>(currentByte);

	readByte(fis, previousByte, currentByte);
	readByte(fis, previousByte, currentByte);
	heightOfImage_ = static_cast<int>(previousByte) * 256 + static_cast<int>(currentByte);

	readByte(fis, previousByte, currentByte);
	readByte(fis, previousByte, currentByte);
	widthOfImage_ = static_cast<int>(previousByte) * 256 + static_cast<int>(currentByte);

	readByte(fis, previousByte, currentByte);
	amountOfComponents_ = static_cast<int>(currentByte);

	for (int i(0); i < amountOfComponents_; i++)
	{
		readByte(fis, previousByte, currentByte);
		int id = static_cast<int>(currentByte);

		readByte(fis, previousByte, currentByte);
		int thinning = static_cast<int>(currentByte);
		char horizontalThinning = getHexLetterFromNumberAt(thinning, 0);
		char verticalThinning = getHexLetterFromNumberAt(thinning, 1);

		readByte(fis, previousByte, currentByte);
		int idOfTable = static_cast<int>(currentByte);

		Component component(id, horizontalThinning, verticalThinning, idOfTable);
		components_.emplace_back(component);
	}
}

void JpegExtractor::readQuantizationTable(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte)
{
	readByte(fis, previousByte, currentByte);
	readByte(fis, previousByte, currentByte);
	int quantizationLength = static_cast<int>(previousByte) * 256 + static_cast<int>(currentByte) - lengthOfQuantizationSize;

	readByte(fis, previousByte, currentByte);
	int data = static_cast<int>(currentByte);
	int tableId = static_cast<int>(getHexLetterFromNumberAt(data, 0));
	int valueLength = static_cast<int>(getHexLetterFromNumberAt(data, 1)) + 1;

	int sizeOfTable = sqrt(quantizationLength);
	int** newTable = new int*[sizeOfTable];

	for (int i(0); i < sizeOfTable; i++)
	{
		newTable[i] = new int[sizeOfTable];

		for (int j(0); j < sizeOfTable; j++)
		{
			readByte(fis, previousByte, currentByte);
			newTable[i][j] = currentByte;
		}
	}

	QuantizationTable newQuantizationTable(sizeOfTable, valueLength, tableId, newTable);
	quantizationTables_.emplace_back(newQuantizationTable);

	int newIndex = quantizationTables_.size() - 1;
	quantizationTables_[newIndex].turnTableToZigzagOrder();
}

void JpegExtractor::readHuffmanTable(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte)
{
	readByte(fis, previousByte, currentByte);
	readByte(fis, previousByte, currentByte);
	int huffmanLength = static_cast<int>(previousByte) * 256 + static_cast<int>(currentByte) - lengthOfHuffmanSize;

	readByte(fis, previousByte, currentByte);
	int data = static_cast<int>(currentByte);
	char tableId = getHexLetterFromNumberAt(data, 0);
	char classTypeRaw = getHexLetterFromNumberAt(data, 1);

	TypeHuffmanTable type;
	switch (classTypeRaw)
	{
	case 0:
		type = TypeHuffmanTable::DC_COEFFICIENTS;
		break;
	case 1:
		type = TypeHuffmanTable::AC_COEFFICIENTS;
		break;
	default:
		throw std::exception("Unknown type of huffman table");
		break;
	}

	int* table = new int[huffmanLength];
	for (int i(0); i < huffmanLength; i++)
	{
		readByte(fis, previousByte, currentByte);
		table[i] = static_cast<int>(currentByte);
	}

	HuffmanTable huffmanTable(table, lengthOfHuffmanSize, type, tableId);
	huffmanTable.generateTree();
	huffmanTables_.emplace_back(huffmanTable);
}

int JpegExtractor::getFileSize()
{
	return filesize_;
}

int JpegExtractor::getHeight()
{
	return heightOfImage_;
}

int JpegExtractor::getWidth()
{
	return widthOfImage_;
}

std::string JpegExtractor::getCommentary()
{
	return commentary_;
}

std::vector<QuantizationTable> JpegExtractor::getQuantizationTables()
{
	return quantizationTables_;
}

std::vector<Component> JpegExtractor::getComponents()
{
	return components_;
}

std::vector<HuffmanTable> JpegExtractor::getHuffmanTables()
{
	return huffmanTables_;
}
