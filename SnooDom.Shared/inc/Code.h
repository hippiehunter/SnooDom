#include "DomObject.h"

namespace SnooDom
{
	class Code : public IDomContainer
	{
	public:
		Code(std::vector<IDomObject*>& children, uint32_t domId) : IDomContainer(children, domId) { }

		bool IsBlock;
		virtual void Accept(IDomVisitor* visitor){ visitor->Visit(this); }
	};
}