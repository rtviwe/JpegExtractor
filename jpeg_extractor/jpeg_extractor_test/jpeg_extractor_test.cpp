#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "../jpeg_extractor/jpeg_extractor.hpp"

bool testFileSize(JpegExtractor &jpeg_extractor, int &answer) {
    return jpeg_extractor.getFileSize() == answer;
}

bool testCommentary(JpegExtractor &jpeg_extractor, const std::string &answer) {
    return jpeg_extractor.getCommentary() == answer;
}

bool testHeight(JpegExtractor &jpeg_extractor, int &answer) {
    return jpeg_extractor.getHeight() == answer;
}

bool testWidth(JpegExtractor &jpeg_extractor, int &answer) {
    return jpeg_extractor.getWidth() == answer;
}

bool testQuantizationTables(JpegExtractor &jpeg_extractor, QuantizationTable &answer) {
    QuantizationTable qTable = jpeg_extractor.getQuantizationTables()[0];

    if (qTable.size != answer.size) {
        return false;
    }

    if (qTable.valueLength != answer.valueLength) {
        return false;
    }

    if (qTable.tableId != answer.tableId) {
        return false;
    }

    for (int i(0); i < 8; i++) {
        for (int j(0); j < 8; j++) {
            if (qTable.table[i][j] != answer.table[i][j]) {
                return false;
            }
        }
    }

    return true;
}

bool testComponents(JpegExtractor &jpeg_extractor, Component &answer) {
    std::vector<Component> components;
    Component component = jpeg_extractor.getComponents()[0];

    if (component.id != answer.id) {
        return false;
    }

    if (component.horizontalThinning != answer.horizontalThinning) {
        return false;
    }

    if (component.verticalThinning != answer.verticalThinning) {
        return false;
    }

    if (component.idQuantizationTable != answer.idQuantizationTable) {
        return false;
    }

    return true;
}

int main() {
    // Для вывода кириллицы
    setlocale(LC_ALL, "Russian");

    std::string path = "./resources/img4.jpg";

    JpegExtractor jpeg_extractor(path);
    jpeg_extractor.analyzeFile();

    std::string answerpath = "./resources/answers4.txt";
    std::ifstream fis(answerpath, std::ios_base::in);

    std::vector<std::string> lines;
    std::string line;
    if (fis.is_open()) {
        while (getline(fis, line)) {
            lines.push_back(line);
        }
    }

    fis.close();

    int filesize = std::stoi(lines[0]);
    std::string commentary = lines[1];
    int height = std::stoi(lines[2]);
    int width = std::stoi(lines[3]);
    int qsize = std::stoi(lines[4]);
    int qvalueLength = std::stoi(lines[5]);
    int qtableid = std::stoi(lines[6]);

    int **qtable = new int *[qsize + 1];

    int k = 0;
    int i = 7;
    for (i; i < qsize * qsize + 7; i += 8) {
        qtable[k] = new int[qsize];

        for (int j(0); j < qsize; j++) {
            std::string temp;
            temp.append(lines[i + j]);
            qtable[k][j] = std::stoi(temp);
        }

        k += 1;
    }

    QuantizationTable rightTable(qsize, qvalueLength, qtableid, qtable);

    int id = std::stoi(lines[i]);
    int horizontalThinning = std::stoi(lines[i + 1]);
    int verticalThinning = std::stoi(lines[i + 2]);
    int idQuantizationTable = std::stoi(lines[i + 3]);

    Component component(id, horizontalThinning, verticalThinning, idQuantizationTable);

    std::cout << "Тест размера файла " << (testFileSize(jpeg_extractor, filesize) ? "пройден" : "не пройден")
              << std::endl;
    std::cout << "Тест комментария " << (testCommentary(jpeg_extractor, commentary + "\n") ? "пройден" : "не пройден")
              << std::endl;
    std::cout << "Тест высоты " << (testHeight(jpeg_extractor, height) ? "пройден" : "не пройден") << std::endl;
    std::cout << "Тест ширины " << (testWidth(jpeg_extractor, width) ? "пройден" : "не пройден") << std::endl;

    std::cout << "Тест таблиц квантования "
              << (testQuantizationTables(jpeg_extractor, rightTable) ? "пройден" : "не пройден") << std::endl;
    std::cout << "Тест компонентов " << (testComponents(jpeg_extractor, component) ? "пройден" : "не пройден")
              << std::endl;

    // Вывести все данные
    std::cout << std::endl << jpeg_extractor << std::endl;

    return 0;
}
