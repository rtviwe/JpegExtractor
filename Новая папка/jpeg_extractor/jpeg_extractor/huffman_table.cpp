#include <iostream>
#include "huffman_table.hpp"

HuffmanTable::HuffmanTable(const HuffmanTable& huffmanTable)
	: size(huffmanTable.size),
	type(huffmanTable.type),
	tableId(huffmanTable.tableId)
{
	amountOfCodes = new int[size];
	std::copy(huffmanTable.amountOfCodes, huffmanTable.amountOfCodes + size, huffmanTable.amountOfCodes);
}

HuffmanTable::HuffmanTable(int* amountOfCodes, const int size, const TypeHuffmanTable type, const int tableId)
	:amountOfCodes(amountOfCodes), size(size), type(type), tableId(tableId)
{
}

HuffmanTable::~HuffmanTable()
{
	delete[] amountOfCodes;
}

void HuffmanTable::generateTree()
{
	// TODO
}

std::ostream& HuffmanTable::writeTo(std::ostream& ostrm) const
{
	if (type == TypeHuffmanTable::AC_COEFFICIENTS)
	{
		ostrm << "AC_COEFFICIENTS";
	}
	else if (type == TypeHuffmanTable::DC_COEFFICIENTS)
	{
		ostrm << "DC_COEFFICIENTS";
	}
	return ostrm;
}

HuffmanTable& HuffmanTable::operator=(const HuffmanTable& obj)
{
	if (this != &obj)
	{
		int* newAmountOfCodes(new int[obj.size]);
		delete[] amountOfCodes;
		amountOfCodes = newAmountOfCodes;
		std::copy(obj.amountOfCodes, obj.amountOfCodes + obj.size, amountOfCodes);

		size = obj.size;
		type = obj.type;
		tableId = obj.tableId;
	}
	return *this;
}

std::ostream& operator<<(std::ostream& ostrm, const HuffmanTable& rhs)
{
	return rhs.writeTo(ostrm);
}
