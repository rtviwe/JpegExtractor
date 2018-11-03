#pragma once
#ifndef QUANTIZATION_TABLE_HPP
#define QUANTIZATION_TABLE_HPP

struct QuantizationTable
{
public:
	QuantizationTable() = default;
	QuantizationTable(int newSize);
	QuantizationTable(const QuantizationTable& newTable);
	QuantizationTable(int** &newTable, int newSize);

	int size{ 0 };
	int** table{ nullptr };

	void turnTableToZigzagOrder();

	~QuantizationTable() = default;
};

#endif
