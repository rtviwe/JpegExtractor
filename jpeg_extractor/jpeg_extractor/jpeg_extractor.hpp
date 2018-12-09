/*
 @file component.hpp
 @Author Igor Spiridonov
 @date 09.12.2018
 */

#ifndef JPEG_EXTRACTOR_HPP
#define JPEG_EXTRACTOR_HPP

#include <iostream>
#include <vector>
#include "quantization_table.hpp"
#include "component.hpp"

/*
@author Igor Spiridonov
@version 1.0.0
@date 31.10.2018
@brief Заголовочный класс для анализатора файла
@detailed Анализирует jpeg файл по его пути
 */
class JpegExtractor
{
public:
	/*
	@brief Конструктор
	*/
	JpegExtractor() = default;

	/*
	@brief Конструктор
	@param[in] pathToFile Путь к анализируемому файлу
	*/
	JpegExtractor(std::string pathToFile);

	/*
	@brief Конструктор копирования
	@param[in] Объект, из которого копируются данные
	*/
	JpegExtractor(const JpegExtractor& jpegExtractor);

	/*
	@brief Деструктор
	*/
	~JpegExtractor() = default;

	/*
	@brief Анализировать файл
	@detailed Прочитывает файл от начала до конца, получая из него необходимые данные
	*/
	void analyzeFile();

	/*
	@brief Прочесть комментарий
	@param[in] fis Поток ввода, откуда считываются байты файла
	@param[in] previousByte Предыдущий считанный байт
	@param[in] currentByte Только что считанный байт
	*/
	void readCommentary(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte);

	/*
	@brief Прочесть информацию о кодировании
	@param[in] fis Поток ввода, откуда считываются байты файла
	@param[in] previousByte Предыдущий считанный байт
	@param[in] currentByte Только что считанный байт
	*/
	void readBaseFrame(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte);

	/*
	@brief Прочесть таблицу квантования
	@param[in] fis Поток ввода, откуда считываются байты файла
	@param[in] previousByte Предыдущий считанный байт
	@param[in] currentByte Только что считанный байт
	*/
	void readQuantizationTable(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte);

	/*
	@brief Получить размер файла
	@return Размер файла
	*/
	int getFileSize();

	/*
	@brief Получить высоту изображения
	@return Высота изображения
	*/
	int getHeight();

	/*
	@brief Получить ширину изображения
	@return Ширина изображения
	*/
	int getWidth();

	/*
	@brief Получить комментарий файла
	@return Комментарий файла
	*/
	std::string getCommentary();

	/*
	@brief Получить таблицы квантования
	@return Динамический массив из таблиц квантования
	*/
	std::vector<QuantizationTable> getQuantizationTables();

	/*
	@brief Получить цветовые компоненты
	@return Динамический массив из цветовых компонентов
	*/
	std::vector<Component> getComponents();
private:
	std::string pathToFile_; //< Путь к файлу
	std::string commentary_; //< Комментарий файла
	int filesize_{ 0 }; //< Размер файла
	int precisionOfFrameBase_{ 0 }; //< Разрядность значений каналов
	int heightOfImage_{ 0 }; //< Высота изображения
	int widthOfImage_{ 0 }; //< Ширина изображения
	int amountOfComponents_{ 0 }; //< Количество цветовых компонентов
	std::vector<QuantizationTable> quantizationTables_; //< Таблицы квантования
	std::vector<Component> components_; //< Цветовые компоненты
	bool isFileAnalyzed = false; //< Проанализирован ли файл

	const int lengthOfQuantizationSize = 3; //< Длина описания таблицы квантования
	const int lengthOfCommentarySize = 2; //< Длина описания комментария
	const int lengthOfFrameBaseSize = 2; //< Длина описания цветовых компонентов

	const unsigned int startOfFile[2]{ 0xFF, 0xD8 }; //< Байты начала файла

	const unsigned int startOfFrame[2]{ 0xFF, 0xC0 }; //< Байты начала цветовых компонентов

	const unsigned int startOfQuantization[2]{ 0xFF, 0xDB }; //< Байты начала таблиц квантования

	const unsigned int startOfCommentary[2]{ 0xFF, 0xFE }; //< Байты начала комментария

	const unsigned int startOfEnd[2]{ 0xFF, 0xD9 }; //< Байты начала конца
};

/*
@brief Проверка файла на пустоту
@param[out] ostrm Поток ввода
@return Пуст ли файл
*/
bool isFileEmpty(std::ifstream &ifs);

/*
@brief Прочесть следующий байт
@param[in] fis Поток ввода, откуда считываются байты файла
@param[in] previousByte Предыдущий считанный байт
@param[in] currentByte Только что считанный байт
*/
void readByte(std::ifstream& ifs, unsigned int& previous, unsigned int& current);

/*
@brief Получить шестнадцатеричный символ из десятичного числа
@param[int] number Десятичное число, откуда берём символ
@param[int] position Индекс искомого символа
@return Шестнадцатеричный символ
*/
char getHexLetterFromNumberAt(int number, int position);

/*
@brief Оператор вывода
@param[out] ostrm Поток вывода
@param[out] rhs Все данные JPEG файла, которые выводится в поток вывода
@return Поток вывода
*/
std::ostream& operator<<(std::ostream& ostrm, JpegExtractor& rhs);

#endif