#pragma once

#include "DomObject.h"
#include <vector>

namespace SnooDom
{
	class Paragraph : public IDomContainer
	{
	public:
		Paragraph(std::vector<IDomObject*>& children, uint32_t domId) : IDomContainer(children, domId) { }
		virtual void Accept(IDomVisitor* visitor){ visitor->Visit(this); }
	};
}