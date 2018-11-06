#pragma once
#ifndef QUANTIZATION_TABLE_HPP
#define QUANTIZATION_TABLE_HPP

#include "stdafx.h"
#include <iostream>

struct QuantizationTable
{
	QuantizationTable() = default;
	QuantizationTable(const QuantizationTable& newTable);
	QuantizationTable(const int size, const int valueLength, const int tableId, int** table);

	~QuantizationTable();

	QuantizationTable& operator=(const QuantizationTable& table);

	void turnTableToZigzagOrder();

	std::ostream& writeTo(std::ostream& ostrm) const;

	int size{ 0 };
	int valueLength{ 0 };
	int tableId{ 0 };
	int** table{ nullptr };
};

std::ostream& operator<<(std::ostream& ostrm, const QuantizationTable& rhs);

#endif
