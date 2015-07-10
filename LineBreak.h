#pragma once

#include "DomObject.h"

namespace SnooDom
{
	class LineBreak : public IDomObject
	{
	public:
		LineBreak(uint32_t domId) : IDomObject(domId) { }
		virtual void Accept(IDomVisitor* visitor){ visitor->Visit(this); }
	};
}