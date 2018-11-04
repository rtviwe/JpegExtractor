#include "pch.h"
#include <iostream>
#include <string>
#include "../JpegExtractor/JpegExtractor.hpp"
#include "../JpegExtractor/Component.hpp"
#include "../JpegExtractor/HuffmanTable.hpp"

using namespace std;

int main()
{
	string path1 = "C:\\Users\\rtviw\\Desktop\\картинки для курсача\\img1.jpg";
	string path2 = "C:\\Users\\rtviw\\Desktop\\картинки для курсача\\img2.jpg";
	string path3 = "C:\\Users\\rtviw\\Desktop\\картинки для курсача\\img3.jpg";
	string path4 = "C:\\Users\\rtviw\\Desktop\\картинки для курсача\\img4.jpg";
	string* paths = new string[4]{ path1, path2, path3, path4 };

	JpegExtractor je(paths[0]);
	je.analyzeFile();

	// Размер файла
	std::cout << "Filesize: " << je.getFileSize() << " bytes" << std::endl;

	// Комментарий
	std::cout << "Commentary: " << je.getCommentary() << std::endl;

	// Размеры изображения
	std::cout << "Height: " << je.getHeight() << std::endl;
	std::cout << "Width: " << je.getWidth() << std::endl;

	// Таблица квантования
	for (int i(0); i < je.getQuantizationTables().size(); i++)
	{
		QuantizationTable qTable = je.getQuantizationTables()[i];
		std::cout << "Table of quantization #" << i << ":" << std::endl;
		std::cout << "Value length = " << qTable.valueLength << " byte" << std::endl;
		std::cout << qTable;
	}

	// Компоненты
	for (int i(0); i < je.getComponents().size(); i++)
	{
		std::cout << "Component #" << i << " " << je.getComponents()[i] << std::endl;
	}

	// Таблицы Хаффмана
	for (int i(0); i < je.getHuffmanTables().size(); i++)
	{
		HuffmanTable table = je.getHuffmanTables()[i];
		std::cout << table << std::endl;
	}

	return 0;
}
