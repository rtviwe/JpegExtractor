#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "JpegExtractor.hpp"

bool isFileEmpty(std::ifstream &f)
{
	char c;
	f >> c;
	if (!f)
	{
		return true;
	}

	f.seekg(0, std::ios::beg);
	return false;
}

void readByte(std::ifstream& fis, unsigned int& first, unsigned int& second)
{
	char* buffer = new char[1];
	fis.read(buffer, 1);

	first = second;
	second = static_cast<int>(buffer[0]);
}

void turnTableToZigzagOrder(int** &table, int sizeOfTable)
{
	int lastValue(sizeOfTable * sizeOfTable - 1);
	int currNum(0);
	int currDiag(0);
	int loopFrom(0);
	int loopTo(0);
	int row(0);
	int col(0);

	int* temoFlatTable = new int[sizeOfTable * sizeOfTable];
	int k(0);
	for (int i(0); i < sizeOfTable; i++)
	{
		for (int j(0); j < sizeOfTable; j++)
		{
			temoFlatTable[k] = table[i][j];
			++k;
		}
	}

	do
	{
		if (currDiag < sizeOfTable)
		{
			loopFrom = 0;
			loopTo = currDiag;
		}
		else
		{
			loopFrom = currDiag - sizeOfTable + 1;
			loopTo = sizeOfTable - 1;
		}

		for (int i = loopFrom; i <= loopTo; i++)
		{
			if (currDiag % 2 == 0)
			{
				row = loopTo - i + loopFrom;
				col = i;
			}
			else
			{
				row = i;
				col = loopTo - i + loopFrom;
			}

			table[row][col] = temoFlatTable[currNum];
			++currNum;
		}

		++currDiag;
	} while (currDiag <= lastValue);
}

JpegExtractor::JpegExtractor(std::string pathToFile)
	: pathToFile_(pathToFile)
{
}

JpegExtractor::~JpegExtractor()
{

}

void JpegExtractor::analyzeFile()
{
	if (pathToFile_.empty())
	{
		throw std::exception("Filepath is empty");
	}

	std::ifstream fis(pathToFile_.c_str(), std::ios_base::binary | std::ios_base::in);

	if (isFileEmpty(fis)) {
		throw std::exception("File is empty");
	}

	// TODO
	// filesize_ = fis.tellg();

	unsigned int previousByte = 0;
	unsigned int currentByte = 0;
	while (!fis.eof())
	{
		readByte(fis, previousByte, currentByte);

		if (startOfFrameBase[0] == previousByte && startOfFrameBase[1] == currentByte)
		{
			readBaseFrame(fis, previousByte, currentByte);
		}

		if (startOfFrameExtended[0] == previousByte && startOfFrameExtended[1] == currentByte)
		{

		}

		if (startOfFrameProgress[0] == previousByte && startOfFrameProgress[1] == currentByte)
		{

		}

		if (startOfHuffman[0] == previousByte && startOfHuffman[1] == currentByte)
		{

		}

		if (startOfQuantization[0] == previousByte && startOfQuantization[1] == currentByte)
		{
			readQuantizationTable(fis, previousByte, currentByte);
		}

		if (startOfLengthOfRestartInterval[0] == previousByte && startOfLengthOfRestartInterval[1] == currentByte)
		{

		}

		if (startOfScan[0] == previousByte && startOfScan[1] == currentByte)
		{

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
		int horizontalThinning = thinning % 10;
		int verticalThinning = static_cast<int>((thinning - horizontalThinning) / 10);

		readByte(fis, previousByte, currentByte);
		int idOfTable = static_cast<int>(currentByte);

		Component component(id, horizontalThinning, verticalThinning, idOfTable);
		components_.push_back(component);
	}
}

void JpegExtractor::readQuantizationTable(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte)
{
	readByte(fis, previousByte, currentByte);
	readByte(fis, previousByte, currentByte);
	int quantizationLength = static_cast<int>(previousByte) * 256 + static_cast<int>(currentByte) - lengthOfQuantizationSize;

	readByte(fis, previousByte, currentByte);
	int data = static_cast<int>(currentByte);
	int identityOfTable = data % 10;
	int lengthOfValuesInTable = data - identityOfTable;
	int sizeOfTable = sqrt(quantizationLength);

	int** newTable = new int*[sizeOfTable];
	tablesOfQuantization_.push_back(newTable);
	int newIndex = tablesOfQuantization_.size() - 1;

	for (int i(0); i < sizeOfTable; i++)
	{
		tablesOfQuantization_[newIndex][i] = new int[sizeOfTable];

		for (int j(0); j < sizeOfTable; j++)
		{
			readByte(fis, previousByte, currentByte);
			tablesOfQuantization_[newIndex][i][j] = currentByte;
		}
	}

	turnTableToZigzagOrder(tablesOfQuantization_[newIndex], sizeOfTable);
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

std::vector<int**> JpegExtractor::getTablesOfQuantization()
{
	return tablesOfQuantization_;
}

std::vector<Component> JpegExtractor::getComponents()
{
	return components_;
}

std::vector<int**> JpegExtractor::getTablesOfHuffman()
{
	// TODO
	return tablesOfQuantization_;
}
