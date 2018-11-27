#include <iostream>
#include <string>
/*#include "../jpeg_extractor/jpeg_extractor.hpp"
#include "../jpeg_extractor/component.hpp"
#include "../jpeg_extractor/huffman_table.hpp"*/

int main()
{
	/*string path1 = "C:\\Users\\st\\Desktop\\temp\\JpegExtractor\\resimg1.jpg";
	string path2 = "C:\\Users\\rtviw\\source\\repos\\JpegExtractor\\res\\img2.jpg";
	string path3 = "C:\\Users\\rtviw\\source\\repos\\JpegExtractor\\res\\img3.jpg";
	string path4 = "C:\\Users\\rtviw\\source\\repos\\JpegExtractor\\res\\img4.jpg";
	string path5 = "C:\\Users\\rtviw\\source\\repos\\JpegExtractor\\res\\img5.jpg";
	string* paths = new string[5]{ path1, path2, path3, path4, path5 };

	JpegExtractor je(paths[4]);
	je.analyzeFile();

	// Размер файла
	std::cout << "Filesize: " << je.getFileSize() << " bytes" << std::endl;

	// Комментарий
	std::cout << "Comment: " << je.getCommentary() << std::endl;

	// Размеры изображения
	std::cout << "Height: " << je.getHeight() << std::endl;
	std::cout << "Width: " << je.getWidth() << std::endl;

	// Таблица квантования
	for (int i(0); i < je.getQuantizationTables().size(); i++)
	{
		QuantizationTable qTable = je.getQuantizationTables()[i];
		std::cout << "Table of quantization #" << qTable.tableId << ":" << std::endl;
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
	}*/

	return 0;
}
