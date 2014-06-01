#pragma once
#include "DomObject.h"
#include <vector>

namespace SnooDom
{
	class OrderedList : public IDomContainer
	{
	public:
		OrderedList(std::vector<IDomObject*>& children, uint32_t domId) : IDomContainer(children, domId) { } 
		virtual void Accept(IDomVisitor* visitor){ visitor->Visit(this); }
	};
}