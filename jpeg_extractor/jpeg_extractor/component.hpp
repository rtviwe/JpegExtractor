#pragma once
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>

/*
@author Igor Spiridonov
@version 1.0.0
@date 11.11.2018
@brief ������������ ���� ��� ��������� ����������
@detailed �������� � ���� ������ � ������ �������� ����������
 */
struct Component
{
	/*
	@brief �����������
	*/
	Component() = default;

	/*
	@brief ����������� �����������
	@param[in] component �������� ���������, �� �������� ���������� ������
	*/
	Component(const Component& component);

	/*
	@brief �����������
	@param[in] id ������������� ����������
	@param[in] horizontalThinning �������������� ������������
	@param[in] verticalThinning ������������ ������������
	@param[in] idQuantizationTable ������������� ������� �����������
	*/
	Component(const int id, const int horizontalThinning, const int verticalThinning, const int idQuantizationTable);

	/*
	@brief ����������
	*/
	~Component() = default;
	
	/*
	@brief ����� ������ � ����������
	@param[out] ostrm ����� ������
	@return ����� ������
	*/
	std::ostream& writeTo(std::ostream& ostrm) const;

	/*
	@brief �������� ������������
	@param[in] table �������� ���������, � �������� ������������� ������� ������
	@return ����� �������� ���������
	*/
	Component& operator=(const Component& table) = default;

	int id{ 0 }; //< �������������
	int horizontalThinning{ 0 }; //< �������������� ������������
	int verticalThinning{ 0 }; //< ������������ ������������
	int idQuantizationTable{ 0 }; //< ������������� ������� �����������
};

/*
@brief �������� ������
@param[out] ostrm ����� ������
@param[out] rhs ���������, ������� ��������� � ����� ������
@return ����� ������
*/
std::ostream& operator<<(std::ostream& ostrm, const Component& rhs);

#endif