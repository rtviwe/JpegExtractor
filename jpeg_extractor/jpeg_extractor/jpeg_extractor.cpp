/*
 \file component.hpp
 \Author Igor Spiridonov
 \version 1.0.0
 \date 09.12.2018
 \mainpage Главная страница
 */

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include "jpeg_extractor.hpp"

/*
\brief Проверка файла на пустоту
\param[out] ostrm Поток ввода
\return Пуст ли файл
*/
bool isFileEmpty(std::ifstream &ifs) {
    char c;
    ifs >> c;
    if (!ifs) {
        return true;
    }

    ifs.seekg(0, std::ios::beg);
    return false;
}

/*
\brief Прочесть следующий байт
\param[in] fis Поток ввода, откуда считываются байты файла
\param[in] previousByte Предыдущий считанный байт
\param[in] currentByte Только что считанный байт
*/
void readByte(std::ifstream &ifs, unsigned int &previous, unsigned int &current) {
    uint8_t buffer[1] = {0};
    ifs.read((char *) buffer, sizeof(buffer));

    previous = current;
    current = buffer[0];
}

/*
\brief Получить шестнадцатеричный символ из десятичного числа
\param[int] number Десятичное число, откуда берём символ
\param[int] position Индекс искомого символа
\return Шестнадцатеричный символ
*/
char getHexLetterFromNumberAt(int number, int position) {
    int quotient(number);
    int num(0);
    int i(1);
    std::vector<char> hexadecimalNumber;

    while (quotient != 0) {
        num = quotient % 16;
        hexadecimalNumber.push_back(num);
        quotient = quotient / 16;
    }

    hexadecimalNumber.push_back(0);
    hexadecimalNumber.push_back(0);
    return hexadecimalNumber[position];
}

/*
\brief Конструктор
\param[in] pathToFile Путь к анализируемому файлу
*/
JpegExtractor::JpegExtractor(std::string pathToFile)
        : pathToFile_(pathToFile) {
}

/*
\brief Конструктор копирования
\param[in] Объект, из которого копируются данные
*/
JpegExtractor::JpegExtractor(const JpegExtractor &jpegExtractor)
        : pathToFile_(jpegExtractor.pathToFile_),
          commentary_(jpegExtractor.commentary_),
          filesize_(jpegExtractor.filesize_),
          precisionOfFrameBase_(jpegExtractor.precisionOfFrameBase_),
          heightOfImage_(jpegExtractor.heightOfImage_),
          widthOfImage_(jpegExtractor.widthOfImage_),
          amountOfComponents_(jpegExtractor.amountOfComponents_),
          quantizationTables_(jpegExtractor.quantizationTables_),
          components_(jpegExtractor.components_) {
}

/*
\brief Анализировать файл
\detailed Прочитывает файл от начала до конца, получая из него необходимые данные
*/
void JpegExtractor::analyzeFile() {
    if (pathToFile_.empty()) {
        throw std::exception("Filepath is empty");
    }

    std::ifstream fis(pathToFile_, std::ios_base::binary | std::ios_base::in);

    if (isFileEmpty(fis)) {
        throw std::exception("File is empty");
    }

    struct stat st_one;
    stat(pathToFile_.c_str(), &st_one);
    filesize_ = st_one.st_size;

    unsigned int previousByte = 0;
    unsigned int currentByte = 0;

    readByte(fis, previousByte, currentByte);
    readByte(fis, previousByte, currentByte);
    if (previousByte != startOfFile[0] || currentByte != startOfFile[1]) {
        throw std::exception("File is not JPEG");
    }

    isFileAnalyzed = true;

    while (!fis.eof()) {
        readByte(fis, previousByte, currentByte);

        if (startOfFrame[0] == previousByte && startOfFrame[1] == currentByte) {
            readBaseFrame(fis, previousByte, currentByte);
        }

        if (startOfQuantization[0] == previousByte && startOfQuantization[1] == currentByte) {
            readQuantizationTable(fis, previousByte, currentByte);
        }

        if (startOfCommentary[0] == previousByte && startOfCommentary[1] == currentByte) {
            readCommentary(fis, previousByte, currentByte);
        }
    }
}

/*
\brief Прочесть комментарий
\param[in] fis Поток ввода, откуда считываются байты файла
\param[in] previousByte Предыдущий считанный байт
\param[in] currentByte Только что считанный байт
*/
void JpegExtractor::readCommentary(std::ifstream &fis, unsigned int &previousByte, unsigned int &currentByte) {
    readByte(fis, previousByte, currentByte);
    readByte(fis, previousByte, currentByte);
    int commentaryLength =
            static_cast<int>(previousByte) * 256 + static_cast<int>(currentByte - lengthOfCommentarySize);

    for (int i(0); i < commentaryLength; i++) {
        readByte(fis, previousByte, currentByte);
        commentary_ += static_cast<char>(currentByte);
    }
}

/*
\brief Прочесть информацию о кодировании
\param[in] fis Поток ввода, откуда считываются байты файла
\param[in] previousByte Предыдущий считанный байт
\param[in] currentByte Только что считанный байт
*/
void JpegExtractor::readBaseFrame(std::ifstream &fis, unsigned int &previousByte, unsigned int &currentByte) {
    readByte(fis, previousByte, currentByte);
    readByte(fis, previousByte, currentByte);
    int frameBaseLength = static_cast<int>(previousByte) * 256 + static_cast<int>(currentByte) - lengthOfFrameBaseSize;

    readByte(fis, previousByte, currentByte);
    precisionOfFrameBase_ = static_cast<int>(currentByte);

    readByte(fis, previousByte, currentByte);
    readByte(fis, previousByte, currentByte);
    heightOfImage_ = static_cast<int>(previousByte) * 256 + static_cast<int>(currentByte);

    readByte(fis, previousByte, currentByte);
    readByte(fis, previousByte, currentByte);
    widthOfImage_ = static_cast<int>(previousByte) * 256 + static_cast<int>(currentByte);

    readByte(fis, previousByte, currentByte);
    amountOfComponents_ = static_cast<int>(currentByte);

    for (int i(0); i < amountOfComponents_; i++) {
        readByte(fis, previousByte, currentByte);
        int id = static_cast<int>(currentByte);

        readByte(fis, previousByte, currentByte);
        int thinning = static_cast<int>(currentByte);
        char horizontalThinning = getHexLetterFromNumberAt(thinning, 0);
        char verticalThinning = getHexLetterFromNumberAt(thinning, 1);

        readByte(fis, previousByte, currentByte);
        int idOfTable = static_cast<int>(currentByte);

        Component component(id, horizontalThinning, verticalThinning, idOfTable);
        components_.emplace_back(component);
    }
}

/*
\brief Прочесть таблицу квантования
\param[in] fis Поток ввода, откуда считываются байты файла
\param[in] previousByte Предыдущий считанный байт
\param[in] currentByte Только что считанный байт
*/
void JpegExtractor::readQuantizationTable(std::ifstream &fis, unsigned int &previousByte, unsigned int &currentByte) {
    readByte(fis, previousByte, currentByte);
    readByte(fis, previousByte, currentByte);
    int quantizationLength =
            static_cast<int>(previousByte) * 256 + static_cast<int>(currentByte) - lengthOfQuantizationSize;

    readByte(fis, previousByte, currentByte);
    int data = static_cast<int>(currentByte);
    int tableId = static_cast<int>(getHexLetterFromNumberAt(data, 0));
    int valueLength = static_cast<int>(getHexLetterFromNumberAt(data, 1)) + 1;

    int sizeOfTable = sqrt(quantizationLength);
    int **newTable = new int *[sizeOfTable];

    for (int i(0); i < sizeOfTable; i++) {
        newTable[i] = new int[sizeOfTable];

        for (int j(0); j < sizeOfTable; j++) {
            readByte(fis, previousByte, currentByte);
            newTable[i][j] = currentByte;
        }
    }

    QuantizationTable newQuantizationTable(sizeOfTable, valueLength, tableId, newTable);
    quantizationTables_.emplace_back(newQuantizationTable);

    int newIndex = quantizationTables_.size() - 1;
    quantizationTables_[newIndex].turnTableToZigzagOrder();
}

/*
\brief Оператор вывода
\param[out] ostrm Поток вывода
\param[out] rhs Все данные JPEG файла, которые выводится в поток вывода
\return Поток вывода
*/
std::ostream &operator<<(std::ostream &ostrm, JpegExtractor &rhs) {
    ostrm << "Размер файла: " << rhs.getFileSize() << std::endl;
    ostrm << "Комментарий: " << rhs.getCommentary() << std::endl;
    ostrm << "Высота: " << rhs.getHeight() << std::endl;
    ostrm << "Ширина: " << rhs.getWidth() << std::endl;

    for (QuantizationTable table : rhs.getQuantizationTables()) {
        ostrm << "Таблица квантования #" << table.tableId << ":" << std::endl;
        ostrm << "Длина значения = " << table.valueLength << " byte" << std::endl;
        ostrm << table << std::endl;
    }

    for (Component component : rhs.getComponents()) {
        ostrm << component << std::endl;
    }

    return ostrm;
}

/*
\brief Получить размер файла
\return Размер файла
*/
int JpegExtractor::getFileSize() {
    if (!isFileAnalyzed) {
        throw std::exception("File is not analyzed");
    }

    return filesize_;
}

/*
\brief Получить высоту изображения
\return Высота изображения
*/
int JpegExtractor::getHeight() {
    if (!isFileAnalyzed) {
        throw std::exception("File is not analyzed");
    }

    return heightOfImage_;
}

/*
\brief Получить ширину изображения
\return Ширина изображения
*/
int JpegExtractor::getWidth() {
    if (!isFileAnalyzed) {
        throw std::exception("File is not analyzed");
    }

    return widthOfImage_;
}

/*
\brief Получить комментарий файла
\return Комментарий файла
*/
std::string JpegExtractor::getCommentary() {
    if (!isFileAnalyzed) {
        throw std::exception("File is not analyzed");
    }

    return commentary_;
}

/*
\brief Получить таблицы квантования
\return Динамический массив из таблиц квантования
*/
std::vector<QuantizationTable> JpegExtractor::getQuantizationTables() {
    if (!isFileAnalyzed) {
        throw std::exception("File is not analyzed");
    }

    return quantizationTables_;
}

/*
\brief Получить цветовые компоненты
\return Динамический массив из цветовых компонентов
*/
std::vector<Component> JpegExtractor::getComponents() {
    if (!isFileAnalyzed) {
        throw std::exception("File is not analyzed");
    }

    return components_;
}
