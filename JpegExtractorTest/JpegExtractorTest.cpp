#include "pch.h"
#include <iostream>
#include <string>
#include "../JpegExtractor/JpegExtractor.hpp"
#include "../JpegExtractor/Component.hpp"

using namespace std;

int main()
{
	string path1 = "C:\\Users\\rtviw\\Desktop\\картинки для курсача\\img1.jpg";
	string path2 = "C:\\Users\\rtviw\\Desktop\\картинки для курсача\\img2.jpg";
	string path3 = "C:\\Users\\rtviw\\Desktop\\картинки для курсача\\img3.jpg";
	string path4 = "C:\\Users\\rtviw\\Desktop\\картинки для курсача\\img4.jpg";
	string path5 = "C:\\Users\\rtviw\\Desktop\\картинки для курсача\\img5.jpg";
	string* paths = new string[5]{ path1, path2, path3, path4, path5 };

	JpegExtractor je(paths[0]);
	je.analyzeFile();

	// Размер файла
	std::cout << "Filesize: " << je.getFileSize() << std::endl;

	// Комментарий
	std::cout << "Commentary: " << std::endl;
	std::cout << je.getCommentary() << std::endl;

	// Размеры изображения
	std::cout << "Height: " << je.getHeight() << std::endl;
	std::cout << "Width: " << je.getWidth() << std::endl;

	// Таблица квантования
	for (int i(0); i < je.getTablesOfQuantization().size(); i++)
	{
		std::cout << "Table of quantization #" << i << ":" << std::endl;
		for (int j(0); j < 8; j++)
		{
			for (int k(0); k < 8; k++)
			{
				std::cout << je.getTablesOfQuantization()[i][j][k] << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	// Компоненты
	for (int i(0); i < je.getComponents().size(); i++)
	{
		std::cout << je.getComponents()[i] << std::endl;
	}
	return 0;
}
