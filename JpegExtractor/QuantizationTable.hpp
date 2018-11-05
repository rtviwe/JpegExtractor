#pragma once
#ifndef QUANTIZATION_TABLE_HPP
#define QUANTIZATION_TABLE_HPP

#include "stdafx.h"
#include <iostream>

struct QuantizationTable
{
	QuantizationTable() = default;
	QuantizationTable(const QuantizationTable& newTable);
	QuantizationTable(int size, int valueLength, int tableId, int** table);

	~QuantizationTable() = default;

	QuantizationTable& operator=(const QuantizationTable& table) = default;

	void turnTableToZigzagOrder();

	std::ostream& writeTo(std::ostream& ostrm) const;

	int size{ 0 };
	int valueLength{ 0 };
	int tableId{ 0 };
	int** table{ nullptr };
};

std::ostream& operator<<(std::ostream& ostrm, const QuantizationTable& rhs);

#endif
