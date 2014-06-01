#pragma once

#include "markdown.h"
#include <collection.h>
#include <vector>
#include <list>
#include <map>
#include <array>
#include <Windows.Foundation.h>
#include "DomObject.h"
#include "Link.h"
#include "Code.h"
#include "Quote.h"
#include "HorizontalRule.h"
#include "LineBreak.h"
#include "OrderedList.h"
#include "UnorderedList.h"
#include "Paragraph.h"
#include "Table.h"
#include "SimpleSessionMemoryPool.h"

namespace SnooDom
{
	public ref class SnooDom sealed
	{
	internal:
		std::unique_ptr<Document> document;
		SnooDom();
	public:
		static SnooDom^ MarkdownToDOM(Platform::String^ source);
	};

	class SnooDomPlainTextVisitor : public IDomVisitor
	{
	public:
		std::string Result;
		SnooDomPlainTextVisitor()
		{
			Result = "";
		}

		virtual void Visit(Text* text)
		{
			Result += text->Contents;
		}
		virtual void Visit(Code* code) { }
		virtual void Visit(Quote* quote) { }
		virtual void Visit(OrderedList* orderedList) { }
		virtual void Visit(UnorderedList* unorderedList) { }
		virtual void Visit(HorizontalRule* horizontalRule) { }
		virtual void Visit(Table* table) { }
		virtual void Visit(Link* link) { }
		virtual void Visit(Paragraph* paragraph)
		{
			for (auto elem : paragraph->Children)
			{
				elem->Accept(this);
			}
		}
		virtual void Visit(Document* document)
		{
			for (auto elem : document->Children)
			{
				elem->Accept(this);
			}
		}
		virtual void Visit(TableRow* tableRow) {}
		virtual void Visit(TableColumn* tableColumn) {}
		virtual void Visit(LineBreak* lineBreak) { }
	};

	public enum class MarkdownCategory
	{
		PlainText,
		Formatted,
		Full
	};

	class SnooDomCategoryVisitor : public IDomVisitor
	{
	private:
		void UpgradeCategory(MarkdownCategory category)
		{
			if ((int)Category < (int)category)
				Category = category;
		}

	public:
		SnooDomCategoryVisitor()
		{
			Category = MarkdownCategory::PlainText;
		}

		MarkdownCategory Category;

		virtual void Visit(Text* text)
		{
			if (text->Bold || text->Italic || text->HeaderSize != 0)
				UpgradeCategory(MarkdownCategory::Formatted);

			if (text->Strike || text->Superscript)
				UpgradeCategory(MarkdownCategory::Full);
		}
		virtual void Visit(Code* code)
		{
			Category = MarkdownCategory::Full;
		}
		virtual void Visit(Quote* quote)
		{
			Category = MarkdownCategory::Full;
		}
		virtual void Visit(OrderedList* orderedList)
		{
			Category = MarkdownCategory::Full;
		}
		virtual void Visit(UnorderedList* unorderedList)
		{
			Category = MarkdownCategory::Full;
		}
		virtual void Visit(HorizontalRule* horizontalRule)
		{
			Category = MarkdownCategory::Full;
		}
		virtual void Visit(Table* table)
		{
			Category = MarkdownCategory::Full;
		}
		virtual void Visit(Link* link)
		{
			Category = MarkdownCategory::Full;
		}
		virtual void Visit(Paragraph* paragraph)
		{
			int count = 0;
			for (auto elem : paragraph->Children)
			{
				if (count == 1)
				{
					UpgradeCategory(MarkdownCategory::Formatted);
				}
				count++;
				elem->Accept(this);
			}
		}
		virtual void Visit(Document* document)
		{
			int count = 0;
			for (auto elem : document->Children)
			{
				if (count == 1)
				{
					UpgradeCategory(MarkdownCategory::Formatted);
				}
				count++;
				elem->Accept(this);
				if (Category == MarkdownCategory::Full)
					break;
			}
		}
		virtual void Visit(TableRow* tableRow)
		{
			for (auto elem : tableRow->Columns)
			{
				elem->Accept(this);
			}
		}
		virtual void Visit(TableColumn* tableColumn)
		{
			for (auto elem : tableColumn->Children)
			{
				elem->Accept(this);
			}
		}
		virtual void Visit(LineBreak* lineBreak)
		{
			UpgradeCategory(MarkdownCategory::Full);
		}
	};

	class SnooDomLinkVisitor : public IDomVisitor
	{

	public:
		std::vector<Link*> Links;

		virtual void Visit(Text* text)
		{
		}
		virtual void Visit(Code* code)
		{
		}
		virtual void Visit(Quote* quote)
		{
		}
		virtual void Visit(OrderedList* orderedList)
		{
			for (auto elem : orderedList->Children)
			{
				elem->Accept(this);
			}
		}
		virtual void Visit(UnorderedList* unorderedList)
		{
			for (auto elem : unorderedList->Children)
			{
				elem->Accept(this);
			}
		}
		virtual void Visit(HorizontalRule* horizontalRule)
		{

		}
		virtual void Visit(Table* table)
		{
			for (auto elem : table->Rows)
			{
				elem->Accept(this);
			}
		}
		virtual void Visit(Link* link)
		{
			Links.push_back(link);
		}
		virtual void Visit(Paragraph* paragraph)
		{
			for (auto elem : paragraph->Children)
			{
				elem->Accept(this);
			}
		}
		virtual void Visit(Document* document)
		{
			for (auto elem : document->Children)
			{
				elem->Accept(this);
			}
		}
		virtual void Visit(TableRow* tableRow)
		{
			for (auto elem : tableRow->Columns)
			{
				elem->Accept(this);
			}
		}
		virtual void Visit(TableColumn* tableColumn)
		{
			for (auto elem : tableColumn->Children)
			{
				elem->Accept(this);
			}
		}
		virtual void Visit(LineBreak* lineBreak)
		{

		}
	};
}