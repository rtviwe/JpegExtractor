#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "JpegExtractor.h"

bool isEmpty(std::ifstream &f)
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

void readTwoBytes(std::ifstream& fis, unsigned int& first, unsigned int& second)
{
	char* buffer = new char[1];
	fis.read(buffer, 1);

	first = second;
	second = (int)buffer[0];
}

JpegExtractor::JpegExtractor(std::string pathToFile)
	: pathToFile_(pathToFile)
{
}

void JpegExtractor::analyzeFile()
{
	if (pathToFile_.empty())
	{
		throw std::exception("Filepath is empty");
	}

	std::ifstream fis(pathToFile_.c_str(), std::ios_base::binary | std::ios_base::in);

	if (isEmpty(fis)) {
		throw std::exception("File is empty");
	}
	
	unsigned int previousByte = 0;
	unsigned int currentByte = 0;
	while (!fis.eof())
	{
		readTwoBytes(fis, previousByte, currentByte);

		// std::cout << currentByte << std::endl;

		if (startOfFrameBase[0] == previousByte && startOfFrameBase[1] == currentByte)
		{
			// std::cout << "Start of frame base" << std::endl;
			// переменный размер
			// TODO
		}

		if (startOfFrameExtended[0] == previousByte && startOfFrameExtended[1] == currentByte)
		{
			// std::cout << "Start of frame base extended" << std::endl;
			// переменный размер
			// TODO
		}

		if (startOfFrameProgress[0] == previousByte && startOfFrameProgress[1] == currentByte)
		{
			// std::cout << "Start of frame base progress" << std::endl;
			// переменный размер
			// TODO
		}

		if (startOfHuffman[0] == previousByte && startOfHuffman[1] == currentByte)
		{
			// std::cout << "Start of huffman" << std::endl;
			// переменный размер
			// TODO
		}

		if (startOfQuantization[0] == previousByte && startOfQuantization[1] == currentByte)
		{
			// std::cout << "Start of quantization" << std::endl;
			// переменный размер
			// TODO
		}

		if (startOfLengthOfRestartInterval[0] == previousByte && startOfLengthOfRestartInterval[1] == currentByte)
		{
			// std::cout << "Start of restart-interval" << std::endl;
			// 4 байта
			// TODO
		}

		if (startOfScan[0] == previousByte && startOfScan[1] == currentByte)
		{
			// std::cout << "Start of scan" << std::endl;
			// переменный размер
			// TODO
		}

		if (startOfCommentary[0] == previousByte && startOfCommentary[1] == currentByte)
		{
			// std::cout << "Start of commentary" << std::endl;
			auto prev = previousByte;
			auto cur = currentByte;
			auto qua1 = startOfQuantization[0];
			auto qua2 = startOfQuantization[1];
			readTwoBytes(fis, previousByte, currentByte);
			while ((startOfQuantization[0] != previousByte) || (startOfQuantization[1] != currentByte))
			{
				commentary_ += (char)currentByte;
				readTwoBytes(fis, previousByte, currentByte);
			}
		}
	}
}

int JpegExtractor::getFileSize()
{
	return filesize_;
}

int JpegExtractor::getStartOffset()
{
	return 0;
}

int JpegExtractor::getStartOfImage()
{
	return 0;
}

int JpegExtractor::getStartOfFrame()
{
	return 0;
}

int JpegExtractor::getTableOfQuantization()
{
	return 0;
}

int JpegExtractor::getTableOfHuffman()
{
	return 0;
}

int JpegExtractor::getLengthOfRestartInteval()
{
	return 0;
}

int JpegExtractor::getStartOfScan()
{
	return 0;
}

int JpegExtractor::getRestart()
{
	return 0;
}

std::string JpegExtractor::getCommentary()
{
	return commentary_;
}
