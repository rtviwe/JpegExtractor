#include <iostream>
#include <string>
#include "../jpeg_extractor/jpeg_extractor.hpp"

int main() {
    // Для вывода кириллицы
    setlocale(LC_ALL, "Russian");

//    std::string path;
//    std::cout << "Введите путь к файлу: ";
//    // Пример: C:\\Users\\rtviw\\source\\repos\\JpegExtractor\\res\\img1.jpg
//    std::cin >> path;

    std::string path2 = "./img1.jpg";

    JpegExtractor jpeg_extractor(path2);
    jpeg_extractor.analyzeFile();

    std::cout << "Размер файла: " << jpeg_extractor.getFileSize() << " байтов" << std::endl;

    std::cout << "Комментарий: " << jpeg_extractor.getCommentary() << std::endl;

    std::cout << "Высота: " << jpeg_extractor.getHeight() << std::endl;
    std::cout << "Ширина: " << jpeg_extractor.getWidth() << std::endl;

    for (int i(0); i < jpeg_extractor.getQuantizationTables().size(); i++) {
        QuantizationTable qTable = jpeg_extractor.getQuantizationTables()[i];
        std::cout << "Таблица квантования #" << qTable.tableId << ":" << std::endl;
        std::cout << "Длина значения = " << qTable.valueLength << " байт" << std::endl;
        std::cout << qTable;
    }

    for (int i(0); i < jpeg_extractor.getComponents().size(); i++) {
        std::cout << "Компонент #" << i << " " << jpeg_extractor.getComponents()[i] << std::endl;
    }

    std::cout << std::endl;

    std::cout << jpeg_extractor << std::endl;

    return 0;
}