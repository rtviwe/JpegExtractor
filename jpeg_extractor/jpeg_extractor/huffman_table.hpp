#pragma once
#ifndef HUFFMAN_TABLE_HPP
#define HUFFMAN_TABLE_HPP

#include <iostream>

enum class TypeHuffmanTable
{
	DC_COEFFICIENTS, AC_COEFFICIENTS
};

struct HuffmanTable
{
	HuffmanTable() = default;
	HuffmanTable(const HuffmanTable& huffmanTable);
	HuffmanTable(int* table, const int size, const TypeHuffmanTable type, const int tableId);

	~HuffmanTable();

	void generateTree();

	std::ostream& writeTo(std::ostream& ostrm) const;

	HuffmanTable& operator=(const HuffmanTable& table);

	int* amountOfCodes{ nullptr };
	int size{ 0 };
	TypeHuffmanTable type;
	int tableId{ 0 };
};

std::ostream& operator<<(std::ostream& ostrm, const HuffmanTable& rhs);

#endif
