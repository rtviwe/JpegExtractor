#include "stdafx.h"
#include "QuantizationTable.hpp"

/*QuantizationTable::QuantizationTable(const QuantizationTable& qTable)
{
	size = qTable.size;
	table = new int*[size];

	for (int i(0); i < size; i++)
	{
		table[i] = new int[size];

		for (int j(0); j < size; j++)
		{
			table[i][j] = qTable.table[i][j];
		}
	}
}*/

QuantizationTable::QuantizationTable(int size, int valueLength, int tableId, int** table)
{
	this->size = size;
	this->valueLength = valueLength;
	this->tableId = tableId;

	this->table = new int*[size];

	for (int i(0); i < size; i++)
	{
		this->table[i] = new int[size];

		for (int j(0); j < size; j++)
		{
			this->table[i][j] = table[i][j];
		}
	}
}

void QuantizationTable::turnTableToZigzagOrder()
{
	int lastValue(size * size - 1);
	int currNum(0);
	int currDiag(0);
	int loopFrom(0);
	int loopTo(0);
	int row(0);
	int col(0);

	int* tempFlatTable = new int[size * size];
	int k(0);
	for (int i(0); i < size; i++)
	{
		for (int j(0); j < size; j++)
		{
			tempFlatTable[k] = table[i][j];
			++k;
		}
	}

	do
	{
		if (currDiag < size)
		{
			loopFrom = 0;
			loopTo = currDiag;
		}
		else
		{
			loopFrom = currDiag - size + 1;
			loopTo = size - 1;
		}

		for (int i = loopFrom; i <= loopTo; i++)
		{
			if (currDiag % 2 == 0)
			{
				row = loopTo - i + loopFrom;
				col = i;
			}
			else
			{
				row = i;
				col = loopTo - i + loopFrom;
			}

			table[row][col] = tempFlatTable[currNum];
			++currNum;
		}

		++currDiag;
	} while (currDiag <= lastValue);
}

std::ostream& operator<<(std::ostream& ostrm, const QuantizationTable& rhs)
{
	return rhs.writeTo(ostrm);
}

std::ostream& QuantizationTable::writeTo(std::ostream& ostrm) const
{
	for (int j(0); j < size; j++)
	{
		for (int k(0); k < size; k++)
		{
			ostrm << table[j][k] << "\t";
		}
		ostrm << std::endl;
	}
	ostrm << std::endl;

	return ostrm;
}
