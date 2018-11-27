#pragma once
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>

struct Component
{
	Component() = default;
	Component(const Component& component);
	Component(const int id, const int horizontalThinning, const int verticalThinning, const int idQuantizationTable);

	~Component() = default;

	std::ostream& writeTo(std::ostream& ostrm) const;

	Component& operator=(const Component& table) = default;

	int id{ 0 };
	int horizontalThinning{ 0 };
	int verticalThinning{ 0 };
	int idQuantizationTable{ 0 };
};

std::ostream& operator<<(std::ostream& ostrm, const Component& rhs);

#endif