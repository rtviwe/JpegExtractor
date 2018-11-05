#include "stdafx.h"
#include <iostream>
#include "HuffmanTable.hpp"

HuffmanTable::HuffmanTable(const HuffmanTable& huffmanTable)
{
	size = huffmanTable.size;
	type = huffmanTable.type;
	tableId = huffmanTable.tableId;
	amountOfCodes = new int[size];

	for (int i(0); i < size; i++)
	{
		amountOfCodes[i] = huffmanTable.amountOfCodes[i];
	}
}

HuffmanTable::HuffmanTable(int* amountOfCodes, int size, TypeHuffmanTable type, int tableId)
	:amountOfCodes(amountOfCodes), size(size), type(type), tableId(tableId)
{
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

std::ostream& operator<<(std::ostream& ostrm, const HuffmanTable& rhs)
{
	return rhs.writeTo(ostrm);
}
