#pragma once
#ifndef HUFFMAN_TABLE_HPP
#define HUFFMAN_TABLE_HPP

#include "stdafx.h"

enum class TypeHuffmanTable
{
	DC_COEFFICIENTS, AC_COEFFICIENTS
};

struct HuffmanTable
{
	HuffmanTable() = default;
	HuffmanTable(const HuffmanTable& huffmanTable);
	HuffmanTable(int* table, int size, TypeHuffmanTable type, int tableId);

	~HuffmanTable() = default;

	std::ostream& writeTo(std::ostream& ostrm) const;

	int* amountOfCodes{ nullptr };
	int size{ 0 };
	TypeHuffmanTable type;
	int tableId{ 0 };
};

std::ostream& operator<<(std::ostream& ostrm, const HuffmanTable& rhs);

#endif
