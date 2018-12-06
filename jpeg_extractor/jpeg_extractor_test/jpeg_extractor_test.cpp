#include <iostream>
#include <string>
#include "../jpeg_extractor/jpeg_extractor.hpp"
#include "../jpeg_extractor/component.hpp"

int main()
{
	std::string path1 = "C:\\Users\\rtviw\\source\\repos\\JpegExtractor\\res\\img1.jpg";
	std::string path2 = "C:\\Users\\rtviw\\source\\repos\\JpegExtractor\\res\\img2.jpg";
	std::string path3 = "C:\\Users\\rtviw\\source\\repos\\JpegExtractor\\res\\img3.jpg";
	std::string path4 = "C:\\Users\\rtviw\\source\\repos\\JpegExtractor\\res\\img4.jpg";
	std::string path5 = "C:\\Users\\rtviw\\source\\repos\\JpegExtractor\\res\\img5.jpg";
	std::string* paths = new std::string[5]{ path1, path2, path3, path4, path5 };

	JpegExtractor jpeg_extractor(paths[0]);
	jpeg_extractor.analyzeFile();

	// Размер файла
	std::cout << "Filesize: " << jpeg_extractor.getFileSize() << " bytes" << std::endl;

	// Комментарий
	std::cout << "Comment: " << jpeg_extractor.getCommentary() << std::endl;

	// Размеры изображения
	std::cout << "Height: " << jpeg_extractor.getHeight() << std::endl;
	std::cout << "Width: " << jpeg_extractor.getWidth() << std::endl;

	// Таблица квантования
	for (int i(0); i < jpeg_extractor.getQuantizationTables().size(); i++)
	{
		QuantizationTable qTable = jpeg_extractor.getQuantizationTables()[i];
		std::cout << "Table of quantization #" << qTable.tableId << ":" << std::endl;
		std::cout << "Value length = " << qTable.valueLength << " byte" << std::endl;
		std::cout << qTable;
	}

	// Компоненты
	for (int i(0); i < jpeg_extractor.getComponents().size(); i++)
	{
		std::cout << "Component #" << i << " " << jpeg_extractor.getComponents()[i] << std::endl;
	}

	std::cout << std::endl;

	// Для вывода кириллицы
	setlocale(LC_ALL, "Russian");
	// Вывести все данные
	std::cout << jpeg_extractor << std::endl;

	return 0;
}
