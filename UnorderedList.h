#pragma once
#include "DomObject.h"
#include <vector>

namespace SnooDom
{
	class UnorderedList : public IDomContainer
	{
	public:
		UnorderedList(std::vector<IDomObject*>& children, uint32_t domId) : IDomContainer(children, domId) { }

		virtual void Accept(IDomVisitor* visitor){ visitor->Visit(this); }
	};
}