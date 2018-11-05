#ifndef JPEG_EXTRACTOR_HPP
#define JPEG_EXTRACTOR_HPP

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "QuantizationTable.hpp"
#include "HuffmanTable.hpp"
#include "Component.hpp"

class JpegExtractor
{
public:
	JpegExtractor() = default;
	JpegExtractor(std::string pathToFile);
	JpegExtractor(const JpegExtractor& jpegExtractor);

	~JpegExtractor() = default;

	void analyzeFile();
	void readCommentary(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte);
	void readBaseFrame(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte);
	void readQuantizationTable(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte);
	void readHuffmanTable(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte);

	int getFileSize();
	int getHeight();
	int getWidth();
	std::string getCommentary();
	std::vector<QuantizationTable> getQuantizationTables();
	std::vector<Component> getComponents();
	std::vector<HuffmanTable> getHuffmanTables();
private:
	std::string pathToFile_;
	std::string commentary_;
	int filesize_{ 0 };
	int precisionOfFrameBase_{ 0 };
	int heightOfImage_{ 0 };
	int widthOfImage_{ 0 };
	int amountOfComponents_{ 0 };
	std::vector<QuantizationTable> quantizationTables_;
	std::vector<Component> components_;
	std::vector<HuffmanTable> huffmanTables_;

	const int lengthOfQuantizationSize = 3;
	const int lengthOfCommentarySize = 2;
	const int lengthOfFrameBaseSize = 2;
	const int lengthOfHuffmanSize = 2;

	// SOI
	const unsigned int startOfFile[2]{ 0xFF, 0xD8 };

	// SOF0
	const unsigned int startOfFrame[2]{ 0xFF, 0xC0 };

	// DHT
	const unsigned int startOfHuffman[2]{ 0xFF, 0xC4 };

	// DQT
	const unsigned int startOfQuantization[2]{ 0xFF, 0xDB };

	// DRI
	const unsigned int startOfLengthOfRestartInterval[2]{ 0xFF, 0xDD };

	// COM
	const unsigned int startOfCommentary[2]{ 0xFF, 0xFE };

	// EOI
	const unsigned int startOfEnd[2]{ 0xFF, 0xD9 };
};

#endif