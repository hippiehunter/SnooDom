#include "DomObject.h"

namespace SnooDom
{
	class Code : public IDomContainer
	{
	public:
    Code(std::vector<IDomObject*>& children, uint32_t domId) : IDomContainer(children, domId), IsBlock(false){}

		bool IsBlock;
		virtual void Accept(IDomVisitor* visitor){ visitor->Visit(this); }
	};
}