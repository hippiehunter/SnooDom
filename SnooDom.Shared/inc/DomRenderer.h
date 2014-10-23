#pragma once

#include "markdown.h"

#include <vector>
#include <list>
#include <map>
#include <array>
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

#ifdef _WINRT_DLL
#include <collection.h>
#include <Windows.Foundation.h>
#endif

namespace SnooDom
{
#ifdef _WINRT_DLL
	public ref class SnooDom sealed
	{
	internal:
		std::unique_ptr<Document> document;
		SnooDom();
	public:
		static SnooDom^ MarkdownToDOM(Platform::String^ source);
    Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ GetLinks();
    bool IsPlainText();
    Platform::String^ BasicText();
	};
#else
	class SnooDom
	{
	public:
		virtual std::unique_ptr<Document> MarkdownToDocument(const std::string& source);
    virtual std::map<std::string, std::string> GetLinks(std::unique_ptr<Document>& document);
	};
#endif
	

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

	enum class MarkdownCategory
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

	
}