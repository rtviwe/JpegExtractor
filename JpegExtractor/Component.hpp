#pragma once
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "stdafx.h"
#include <iostream>

struct Component
{
	Component() = default;
	Component(const Component& component);
	Component(int id, int horizontalThinning, int verticalThinning, int idQuantizationTable);

	~Component() = default;

	std::ostream& writeTo(std::ostream& ostrm) const;

	int id{ 0 };
	int horizontalThinning{ 0 };
	int verticalThinning{ 0 };
	int idQuantizationTable{ 0 };
};

std::ostream& operator<<(std::ostream& ostrm, const Component& rhs);

#endif