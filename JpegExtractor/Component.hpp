#pragma once
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "stdafx.h"
#include <iostream>

struct Component
{
	Component() = default;
	Component(const Component& component);
	Component(int id, int hor, int ver, int idOfTable);

	~Component() = default;

	std::ostream& writeTo(std::ostream& ostrm) const;

	int id{ 0 };
	int horizontalThinning{ 0 };
	int verticalThinning{ 0 };
	int idOfTableOfQuantization{ 0 };
};

std::ostream& operator<<(std::ostream& ostrm, const Component& rhs);

#endif