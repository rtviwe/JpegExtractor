﻿/*
 \file component.hpp
 \Author Igor Spiridonov
 \version 1.0.0
 \date 09.12.2018
 */

#ifndef JPEG_EXTRACTOR_HPP
#define JPEG_EXTRACTOR_HPP

#include <iostream>
#include <vector>
#include "quantization_table.hpp"
#include "component.hpp"

/*!
\author Igor Spiridonov
\version 1.0.0
\date 31.10.2018
\brief Заголовочный класс для анализатора файла
\detailed Анализирует JPEG файл по его пути
 */
class JpegExtractor {
public:
    /*!
    \brief Конструктор
    */
    JpegExtractor() = default;

    /*!
    \brief Конструктор
    \param[in] pathToFile Путь к анализируемому файлу
    */
    JpegExtractor(std::string pathToFile);

    /*!
    \brief Конструктор копирования
    \param[in] Объект, из которого копируются данные
    */
    JpegExtractor(const JpegExtractor &jpegExtractor);

    /*!
    \brief Деструктор
    */
    ~JpegExtractor() = default;

    /*!
    \brief Анализировать файл
    \detailed Прочитывает файл от начала до конца, получая из него необходимые данные
    */
    void analyzeFile();

    /*!
    \brief Прочесть комментарий
    \param[in] fis Поток ввода, откуда считываются байты файла
    \param[in] previousByte Предыдущий считанный байт
    \param[in] currentByte Только что считанный байт
    */
    void readCommentary(std::ifstream &fis, unsigned int &previousByte, unsigned int &currentByte);

    /*!
    \brief Прочесть информацию о кодировании
    \param[in] fis Поток ввода, откуда считываются байты файла
    \param[in] previousByte Предыдущий считанный байт
    \param[in] currentByte Только что считанный байт
    */
    void readBaseFrame(std::ifstream &fis, unsigned int &previousByte, unsigned int &currentByte);

    /*!
    \brief Прочесть таблицу квантования
    \param[in] fis Поток ввода, откуда считываются байты файла
    \param[in] previousByte Предыдущий считанный байт
    \param[in] currentByte Только что считанный байт
    */
    void readQuantizationTable(std::ifstream &fis, unsigned int &previousByte, unsigned int &currentByte);

    /*!
    \brief Получить размер файла
    \return Размер файла
    */
    int getFileSize();

    /*!
    \brief Получить высоту изображения
    \return Высота изображения
    */
    int getHeight();

    /*!
    \brief Получить ширину изображения
    \return Ширина изображения
    */
    int getWidth();

    /*!
    \brief Получить комментарий файла
    \return Комментарий файла
    */
    std::string getCommentary();

    /*!
    \brief Получить таблицы квантования
    \return Динамический массив из таблиц квантования
    */
    std::vector<QuantizationTable> getQuantizationTables();

    /*!
    \brief Получить цветовые компоненты
    \return Динамический массив из цветовых компонентов
    */
    std::vector<Component> getComponents();

private:
    /*!
    \brief Путь к файлу
    */
    std::string pathToFile_;

    /*!
    \brief Комментарий файла
    */
    std::string commentary_;

    /*!
    \brief Размер файла
    */
    int filesize_{0};

    /*!
    \brief Разрядность значений каналов
    */
    int precisionOfFrameBase_{0};

    /*!
    \brief Высота изображения
    */
    int heightOfImage_{0};

    /*!
    \brief Ширина изображения
    */
    int widthOfImage_{0};

    /*!
    \brief Количество цветовых компонентов
    */
    int amountOfComponents_{0};

    /*!
    \brief Таблицы квантования
    */
    std::vector<QuantizationTable> quantizationTables_;

    /*!
    \brief Цветовые компоненты
    */
    std::vector<Component> components_;

    /*!
    \brief Проанализирован ли файл
    */
    bool isFileAnalyzed = false;

    /*!
    \brief Длина описания таблицы квантования
    */
    const int lengthOfQuantizationSize = 3;

    /*!
    \brief Длина описания комментария
    */
    const int lengthOfCommentarySize = 2;

    /*!
    \brief Длина описания цветовых компонентов
    */
    const int lengthOfFrameBaseSize = 2;

    /*!
    \brief Байты начала файла
    */
    const unsigned int startOfFile[2]{0xFF, 0xD8};

    /*!
    \brief Байты начала цветовых компонентов
    */
    const unsigned int startOfFrame[2]{0xFF, 0xC0};

    /*!
    \brief Байты начала таблиц квантования
    */
    const unsigned int startOfQuantization[2]{0xFF, 0xDB};

    /*!
    \brief Байты начала комментария
    */
    const unsigned int startOfCommentary[2]{0xFF, 0xFE};

    /*!
    \brief Байты начала конца
    */
    const unsigned int startOfEnd[2]{0xFF, 0xD9};
};

/*!
\brief Проверка файла на пустоту
\param[out] ostrm Поток ввода
\return Пуст ли файл
*/
bool isFileEmpty(std::ifstream &ifs);

/*!
\brief Прочесть следующий байт
\param[in] fis Поток ввода, откуда считываются байты файла
\param[in] previousByte Предыдущий считанный байт
\param[in] currentByte Только что считанный байт
*/
void readByte(std::ifstream &ifs, unsigned int &previous, unsigned int &current);

/*!
\brief Получить шестнадцатеричный символ из десятичного числа
\param[int] number Десятичное число, откуда берём символ
\param[int] position Индекс искомого символа
\return Шестнадцатеричный символ
*/
char getHexLetterFromNumberAt(int number, int position);

/*!
\brief Оператор вывода
\param[out] ostrm Поток вывода
\param[out] rhs Все данные JPEG файла, которые выводится в поток вывода
\return Поток вывода
*/
std::ostream &operator<<(std::ostream &ostrm, JpegExtractor &rhs);

#endif