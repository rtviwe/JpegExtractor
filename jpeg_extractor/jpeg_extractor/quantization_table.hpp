#pragma once
#ifndef QUANTIZATION_TABLE_HPP
#define QUANTIZATION_TABLE_HPP

#include <iostream>

/*
@author Igor Spiridonov
@version 1.0.0
@date 1.11.2018
@brief ������������ ���� ��� ������� �����������
@detailed �������� � ���� ������ � ������� �����������
 */
struct QuantizationTable
{
	/*
	@brief �����������
	*/
	QuantizationTable() = default;

	/*
	@brief ����������� �����������
	@param[in] component ������� ����������, �� ������� ���������� ������	
	*/
	QuantizationTable(const QuantizationTable& newTable);

	/*
	@brief �����������
	@param[in] size ������ ���������� �������
	@param[in] valueLength ����� ������� �������� �������
	@param[in] tableId ������������� �������
	@param[in] table �������
	*/
	QuantizationTable(const int size, const int valueLength, const int tableId, int** table);

	/*
	@brief ����������
	*/
	~QuantizationTable();

	/*
	@brief �������� ������������
	@param[in] table ������� �����������, � ������� ������������� ������� ������
	@return ����� ������� �����������
	*/
	QuantizationTable& operator=(const QuantizationTable& table);

	/*
	@brief �������������� ������� ��������
	*/
	void turnTableToZigzagOrder();

	/*
	@brief ����� ������ � ����������
	@param[out] ostrm ����� ������
	@return ����� ������
	*/
	std::ostream& writeTo(std::ostream& ostrm) const;

	int size{ 0 }; //< ������ ���������� �������
	int valueLength{ 0 }; //< ����� ������� �������� �������
	int tableId{ 0 }; //< ������������� �������
	int** table{ nullptr }; //< �������
};

/*
@brief �������� ������
@param[out] ostrm ����� ������
@param[out] rhs ������� �����������, ������� ��������� � ����� ������
@return ����� ������
*/
std::ostream& operator<<(std::ostream& ostrm, const QuantizationTable& rhs);

#endif
