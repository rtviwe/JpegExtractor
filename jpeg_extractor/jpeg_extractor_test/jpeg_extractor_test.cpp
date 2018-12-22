#include <iostream>
#include <string>
#include <vector>
#include "../jpeg_extractor/jpeg_extractor.hpp"

bool testFileSize(JpegExtractor &jpeg_extractor) {
    return jpeg_extractor.getFileSize() == 26697;
}

bool testCommentary(JpegExtractor &jpeg_extractor) {
    return jpeg_extractor.getCommentary() == "CREATOR: gd-jpeg v1.0 (using IJG JPEG v80), quality = 90\n";
}

bool testHeight(JpegExtractor &jpeg_extractor) {
    return jpeg_extractor.getHeight() == 626;
}

bool testWidth(JpegExtractor &jpeg_extractor) {
    return jpeg_extractor.getWidth() == 626;
}

void fillMatrix(int **&matrix) {
    matrix[0] = new int[8];
    matrix[0][0] = 3;
    matrix[0][1] = 2;
    matrix[0][2] = 2;
    matrix[0][3] = 3;
    matrix[0][4] = 5;
    matrix[0][5] = 8;
    matrix[0][6] = 10;
    matrix[0][7] = 12;

    matrix[1] = new int[8];
    matrix[1][0] = 2;
    matrix[1][1] = 2;
    matrix[1][2] = 3;
    matrix[1][3] = 4;
    matrix[1][4] = 5;
    matrix[1][5] = 12;
    matrix[1][6] = 12;
    matrix[1][7] = 11;

    matrix[2] = new int[8];
    matrix[2][0] = 3;
    matrix[2][1] = 3;
    matrix[2][2] = 3;
    matrix[2][3] = 5;
    matrix[2][4] = 8;
    matrix[2][5] = 11;
    matrix[2][6] = 14;
    matrix[2][7] = 11;

    matrix[3] = new int[8];
    matrix[3][0] = 3;
    matrix[3][1] = 3;
    matrix[3][2] = 4;
    matrix[3][3] = 6;
    matrix[3][4] = 10;
    matrix[3][5] = 17;
    matrix[3][6] = 16;
    matrix[3][7] = 12;

    matrix[4] = new int[8];
    matrix[4][0] = 4;
    matrix[4][1] = 4;
    matrix[4][2] = 7;
    matrix[4][3] = 11;
    matrix[4][4] = 14;
    matrix[4][5] = 22;
    matrix[4][6] = 21;
    matrix[4][7] = 15;

    matrix[5] = new int[8];
    matrix[5][0] = 5;
    matrix[5][1] = 7;
    matrix[5][2] = 11;
    matrix[5][3] = 13;
    matrix[5][4] = 16;
    matrix[5][5] = 21;
    matrix[5][6] = 23;
    matrix[5][7] = 18;

    matrix[6] = new int[8];
    matrix[6][0] = 10;
    matrix[6][1] = 13;
    matrix[6][2] = 16;
    matrix[6][3] = 17;
    matrix[6][4] = 21;
    matrix[6][5] = 24;
    matrix[6][6] = 24;
    matrix[6][7] = 20;

    matrix[7] = new int[8];
    matrix[7][0] = 14;
    matrix[7][1] = 18;
    matrix[7][2] = 19;
    matrix[7][3] = 20;
    matrix[7][4] = 22;
    matrix[7][5] = 20;
    matrix[7][6] = 21;
    matrix[7][7] = 20;

}

bool testQuantizationTables(JpegExtractor &jpeg_extractor) {
    std::vector<QuantizationTable> rightQTables;
    int **qMatrix = new int *[8];
    fillMatrix(qMatrix);

    QuantizationTable qTable1(8, 1, 0, qMatrix);
    rightQTables.push_back(qTable1);

    QuantizationTable qTable = jpeg_extractor.getQuantizationTables()[0];
    QuantizationTable rightQTable = rightQTables[0];

    if (qTable.size != rightQTable.size) {
        return false;
    }

    if (qTable.valueLength != rightQTable.valueLength) {
        return false;
    }

    if (qTable.tableId != rightQTable.tableId) {
        return false;
    }

    for (int i(0); i < 8; i++) {
        for (int j(0); j < 8; j++) {
            if (qTable.table[i][j] != rightQTable.table[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool testComponents(JpegExtractor &jpeg_extractor) {
    std::vector<Component> components;
    Component rightComponent(1, 2, 2, 0);
    Component component = jpeg_extractor.getComponents()[0];

    if (component.id != rightComponent.id) {
        return false;
    }

    if (component.horizontalThinning != rightComponent.horizontalThinning) {
        return false;
    }

    if (component.verticalThinning != rightComponent.verticalThinning) {
        return false;
    }

    if (component.idQuantizationTable != rightComponent.idQuantizationTable) {
        return false;
    }

    return true;
}

int main() {
    // Для вывода кириллицы
    setlocale(LC_ALL, "Russian");

//    std::string path;
//    std::cout << "Введите путь к файлу: ";
//    // Пример: C:\\Users\\rtviw\\source\\repos\\JpegExtractor\\res\\img1.jpg
//    std::cin >> path;

    std::string path = "./img5.jpg";

    JpegExtractor jpeg_extractor(path);
    jpeg_extractor.analyzeFile();

    std::cout << "Тест размера файла " << (testFileSize(jpeg_extractor) ? "пройден" : "не пройден") << std::endl;
    std::cout << "Тест комментария " << (testCommentary(jpeg_extractor) ? "пройден" : "не пройден") << std::endl;
    std::cout << "Тест высоты " << (testHeight(jpeg_extractor) ? "пройден" : "не пройден") << std::endl;
    std::cout << "Тест ширины " << (testWidth(jpeg_extractor) ? "пройден" : "не пройден") << std::endl;
    std::cout << "Тест таблиц квантования " << (testQuantizationTables(jpeg_extractor) ? "пройден" : "не пройден")
              << std::endl;
    std::cout << "Тест компонентов " << (testComponents(jpeg_extractor) ? "пройден" : "не пройден") << std::endl;

    // Вывести все данные
    std::cout << std::endl << jpeg_extractor << std::endl;

    return 0;
}
