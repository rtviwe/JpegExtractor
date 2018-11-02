#ifndef JPEG_EXTRACTOR_HPP
#define JPEG_EXTRACTOR_HPP

#include <iostream>
#include <vector>
#include "stdafx.h"

class JpegExtractor
{
public:
	JpegExtractor() = default;
	JpegExtractor(std::string pathToFile);

	void analyzeFile();

	int getFileSize();
	int getStartOffset();
	int getStartOfImage();
	int getStartOfFrame();
	int getTableOfQuantization();
	int getTableOfHuffman();
	int getLengthOfRestartInteval();
	int getStartOfScan();
	int getRestart();
	std::string getCommentary();
private:
	std::string commentary_;
	std::string pathToFile_;
	int filesize_{ 0 };

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