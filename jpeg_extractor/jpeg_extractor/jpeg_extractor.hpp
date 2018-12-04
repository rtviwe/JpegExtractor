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
@brief ������������ ����� ��� ����������� �����
@detailed ����������� jpeg ���� �� ��� ����
 */
class JpegExtractor
{
public:
	/*
	@brief �����������
	*/
	JpegExtractor() = default;

	/*
	@brief �����������
	@param[in] pathToFile ���� � �������������� �����
	*/
	JpegExtractor(std::string pathToFile);

	/*
	@brief ����������� �����������
	@param[in] ������, �� �������� ���������� ������
	*/
	JpegExtractor(const JpegExtractor& jpegExtractor);

	/*
	@brief ����������
	*/
	~JpegExtractor() = default;

	/*
	@brief ������������� ����
	@detailed ����������� ���� �� ������ �� �����, ������� �� ���� ����������� ������
	*/
	void analyzeFile();

	/*
	@brief �������� �����������
	@param[in] fis ����� �����, ������ ����������� ����� �����
	@param[in] previousByte ���������� ��������� ����
	@param[in] currentByte ������ ��� ��������� ����
	*/
	void readCommentary(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte);

	/*
	@brief �������� ���������� � �����������
	@param[in] fis ����� �����, ������ ����������� ����� �����
	@param[in] previousByte ���������� ��������� ����
	@param[in] currentByte ������ ��� ��������� ����
	*/
	void readBaseFrame(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte);

	/*
	@brief �������� ������� �����������
	@param[in] fis ����� �����, ������ ����������� ����� �����
	@param[in] previousByte ���������� ��������� ����
	@param[in] currentByte ������ ��� ��������� ����
	*/
	void readQuantizationTable(std::ifstream& fis, unsigned int& previousByte, unsigned int& currentByte);

	/*
	@brief �������� ������ �����
	@return ������ �����
	*/
	int getFileSize();

	/*
	@brief �������� ������ �����������
	@return ������ �����������
	*/
	int getHeight();

	/*
	@brief �������� ������ �����������
	@return ������ �����������
	*/
	int getWidth();

	/*
	@brief �������� ����������� �����
	@return ����������� �����
	*/
	std::string getCommentary();

	/*
	@brief �������� ������� �����������
	@return ������������ ������ �� ������ �����������
	*/
	std::vector<QuantizationTable> getQuantizationTables();

	/*
	@brief �������� �������� ����������
	@return ������������ ������ �� �������� �����������
	*/
	std::vector<Component> getComponents();
private:
	std::string pathToFile_; //< ���� � �����
	std::string commentary_; //< ����������� �����
	int filesize_{ 0 }; //< ������ �����
	int precisionOfFrameBase_{ 0 }; //< ����������� �������� �������
	int heightOfImage_{ 0 }; //< ������ �����������
	int widthOfImage_{ 0 }; //< ������ �����������
	int amountOfComponents_{ 0 }; //< ���������� �������� �����������
	std::vector<QuantizationTable> quantizationTables_; //< ������� �����������
	std::vector<Component> components_; //< �������� ����������

	const int lengthOfQuantizationSize = 3; //< ����� �������� ������� �����������
	const int lengthOfCommentarySize = 2; //< ����� �������� �����������
	const int lengthOfFrameBaseSize = 2; //< ����� �������� �������� �����������

	const unsigned int startOfFile[2]{ 0xFF, 0xD8 }; //< ����� ������ �����

	const unsigned int startOfFrame[2]{ 0xFF, 0xC0 }; //< ����� ������ �������� �����������

	const unsigned int startOfQuantization[2]{ 0xFF, 0xDB }; //< ����� ������ ������ �����������

	const unsigned int startOfCommentary[2]{ 0xFF, 0xFE }; //< ����� ������ �����������

	const unsigned int startOfEnd[2]{ 0xFF, 0xD9 }; //< ����� ������ �����
};

/*
@brief �������� ����� �� �������
@param[out] ostrm ����� �����
@return ���� �� ����
*/
bool isFileEmpty(std::ifstream &ifs);

/*
@brief �������� ��������� ����
@param[in] fis ����� �����, ������ ����������� ����� �����
@param[in] previousByte ���������� ��������� ����
@param[in] currentByte ������ ��� ��������� ����
*/
void readByte(std::ifstream& ifs, unsigned int& previous, unsigned int& current);

/*
@brief �������� ����������������� ������ �� ����������� �����
@param[int] number ���������� �����, ������ ���� ������
@param[int] position ������ �������� �������
@return ����������������� ������
*/
char getHexLetterFromNumberAt(int number, int position);

#endif