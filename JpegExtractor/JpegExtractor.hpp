#ifndef JPEG_EXTRACTOR_HPP
#define JPEG_EXTRACTOR_HPP

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "Component.hpp"

class JpegExtractor
{
public:
	JpegExtractor() = default;
	JpegExtractor(std::string pathToFile);

	~JpegExtractor();

	void analyzeFile();
	void readCommentary(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte);
	void readBaseFrame(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte);
	void readQuantizationTable(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte);

	int getFileSize();
	int getHeight();
	int getWidth();
	std::string getCommentary();
	std::vector<int**> getTablesOfQuantization();
	std::vector<Component> getComponents();
	std::vector<int**> getTablesOfHuffman();
private:
	std::string pathToFile_;
	std::string commentary_;
	int filesize_{ 0 };
	int precisionOfFrameBase_{ 0 };
	int heightOfImage_{ 0 };
	int widthOfImage_{ 0 };
	int amountOfComponents_{ 0 };
	std::vector<int**> tablesOfQuantization_;
	std::vector<Component> components_;
	std::vector<int**> tablesOfHuffman_;

	const int lengthOfQuantizationSize = 3;
	const int lengthOfCommentarySize = 2;
	const int lengthOfFrameBaseSize = 2;

	// SOI
	const unsigned int startOfFile[2]{ 0xFFFFFFFF, 0xFFFFFFD8 };

	// SOF0
	const unsigned int startOfFrameBase[2]{ 0xFFFFFFFF, 0xFFFFFFC0 };

	// SOF1
	const unsigned int startOfFrameExtended[2]{ 0xFFFFFFFF, 0xFFFFFFC1 };

	// SOF2
	const unsigned int startOfFrameProgress[2]{ 0xFFFFFFFF, 0xFFFFFFC2 };

	// DHT
	const unsigned int startOfHuffman[2]{ 0xFFFFFFFF, 0xFFFFFFC4 };

	// DQT
	const unsigned int startOfQuantization[2]{ 0xFFFFFFFF, 0xFFFFFFDB };

	// DRI
	const unsigned int startOfLengthOfRestartInterval[2]{ 0xFFFFFFFF, 0xFFFFFFDD };

	// SOS
	const unsigned int startOfScan[2]{ 0xFFFFFFFF, 0xFFFFFFDA };

	// COM
	const unsigned int startOfCommentary[2]{ 0xFFFFFFFF, 0xFFFFFFFE };

	// EOI
	const unsigned int startOfEnd[2]{ 0xFFFFFFFF, 0xFFFFFFD9 };
};

#endif 