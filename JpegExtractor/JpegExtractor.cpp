#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
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

void readByte(std::ifstream& fis, unsigned int& previous, unsigned int& current)
{
	char* buffer = new char[1];
	fis.read(buffer, 1);

	previous = current;
	current = static_cast<int>(buffer[0]);
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

JpegExtractor::JpegExtractor(const JpegExtractor& jpegExtractor)
{
	pathToFile_ = jpegExtractor.pathToFile_;
	commentary_ = jpegExtractor.commentary_;
	filesize_ = jpegExtractor.filesize_;
	precisionOfFrameBase_ = jpegExtractor.precisionOfFrameBase_;
	heightOfImage_ = jpegExtractor.heightOfImage_;
	widthOfImage_ = jpegExtractor.widthOfImage_;
	amountOfComponents_ = jpegExtractor.amountOfComponents_;

	for (int i(0); i < jpegExtractor.tablesOfQuantization_.size(); i++)
	{
		tablesOfQuantization_[i] = jpegExtractor.tablesOfQuantization_[i];
	}

	for (int i(0); i < jpegExtractor.components_.size(); i++)
	{
		components_[i] = jpegExtractor.components_[i];
	}
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

	for (int i(0); i < sizeOfTable; i++)
	{
		newTable[i] = new int[sizeOfTable];

		for (int j(0); j < sizeOfTable; j++)
		{
			readByte(fis, previousByte, currentByte);
			newTable[i][j] = currentByte;
		}
	}

	QuantizationTable newQuantizationTable(newTable, sizeOfTable);
	tablesOfQuantization_.push_back(newQuantizationTable);

	int newIndex = tablesOfQuantization_.size() - 1;
	tablesOfQuantization_[newIndex].turnTableToZigzagOrder();
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

std::vector<QuantizationTable> JpegExtractor::getTablesOfQuantization()
{
	return tablesOfQuantization_;
}

std::vector<Component> JpegExtractor::getComponents()
{
	return components_;
}
/*
std::vector<int**> JpegExtractor::getTablesOfHuffman()
{
	// TODO
	return ;
}*/
