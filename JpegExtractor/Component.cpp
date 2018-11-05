#include "stdafx.h"
#include "Component.hpp"

Component::Component(const Component& component)
{
	id = component.id;
	horizontalThinning = component.horizontalThinning;
	verticalThinning = component.verticalThinning;
	idQuantizationTable = component.idQuantizationTable;
}

Component::Component(int id, int horizontalThinning, int verticalThinning, int idOfTable)
	: id(id),
	horizontalThinning(horizontalThinning), 
	verticalThinning(verticalThinning), 
	idQuantizationTable(idOfTable)
{
}

std::ostream& operator<<(std::ostream& ostrm, const Component& rhs)
{
	return rhs.writeTo(ostrm);
}

std::ostream& Component::writeTo(std::ostream& ostrm) const
{
	ostrm << "id: " << id << " horizontal thinning: " << horizontalThinning
		<< " vertical thinning: " << verticalThinning << " id of table quantization: " << idQuantizationTable;
	return ostrm;
}
