#include "DomObject.h"
#include "DomRenderer.h"
#include "MarkdownButton.xaml.h"
#include "MarkdownList.xaml.h"
#include "MarkdownQuote.xaml.h"
#include "MarkdownTable.xaml.h"

using namespace Windows::UI;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Text;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Documents;
using namespace Windows::UI::Xaml::Markup;
using Platform::String;
using std::vector;

namespace SnooDom
{
	public interface class ICommandFactory
	{
	public:
		Windows::Foundation::TypedEventHandler<Windows::UI::Xaml::Documents::Hyperlink^, Windows::UI::Xaml::Documents::HyperlinkClickEventArgs^>^ MakeLinkCommand(Platform::String^ url);
	};

	public interface class IStyleProvider
	{
	public:
		property Windows::UI::Xaml::Style^ RichTextBlockStyle { Windows::UI::Xaml::Style^ get(); }
		property Windows::UI::Xaml::Style^ TextBlockStyle { Windows::UI::Xaml::Style^ get(); }
		property Windows::UI::Xaml::Style^ BorderStyle { Windows::UI::Xaml::Style^ get(); }
		property Windows::UI::Xaml::Style^ RunStyle { Windows::UI::Xaml::Style^ get(); }
	};

	public ref class MarkdownControl sealed : ContentControl
	{
	private:
		static void OnSomethingContentChanged(DependencyObject^ d, DependencyPropertyChangedEventArgs^ e);
		static DependencyProperty^ _markdownProperty;
		static DependencyProperty^ _commandFactoryProperty;
		static DependencyProperty^ _styleFactoryProperty;
	public:
		property SnooDom^ Markdown
		{
			SnooDom^ get() { return (SnooDom^)GetValue(_markdownProperty); }
			void set(SnooDom^ value) { SetValue(_markdownProperty, value); }
		}
		property ICommandFactory^ CommandFactory
		{
			ICommandFactory^ get() { return (ICommandFactory^)GetValue(_commandFactoryProperty); }
			void set(ICommandFactory^ value) { SetValue(_commandFactoryProperty, value); }
		}
		property IStyleProvider^ StyleProvider
		{
			IStyleProvider^ get() { return (IStyleProvider^)GetValue(_styleFactoryProperty); }
			void set(IStyleProvider^ value) { SetValue(_styleFactoryProperty, value); }
		}

		// Using a DependencyProperty as the backing store for Markdown.  This enables animation, styling, binding, etc...
		static property DependencyProperty^ MarkdownProperty
		{
			DependencyProperty^ get() { return _markdownProperty; }
		}

		static property DependencyProperty^ CommandFactoryProperty
		{
			DependencyProperty^ get() { return _commandFactoryProperty; }
		}

		static property DependencyProperty^ StyleProviderProperty
		{
			DependencyProperty^ get() { return _styleFactoryProperty; }
		}

		

		TextBlock^ MakePlain(String^ value)
		{
			auto textBlock = ref new TextBlock();
			textBlock->Text = value != nullptr ? value : "";
			if (StyleProvider->TextBlockStyle != nullptr)
				textBlock->Style = StyleProvider->TextBlockStyle;
			return textBlock;
		}

	private:
		static Platform::String^ toPlatformString(const std::string& value)
		{
			if (value.size() == 0)
				return nullptr;

			wchar_t* buffer = (wchar_t*)_alloca(value.size() * 2);
			auto len = MultiByteToWideChar(CP_UTF8, 0, value.data(), value.size(), buffer, value.size() * 2);
			return ref new Platform::String(buffer, len);
		}

		class SnooDomFullUIVisitor : public IDomVisitor
		{
		private:
			Brush^ _forgroundBrush;
			ICommandFactory^ _commandFactory;
			IStyleProvider^ _styleProvider;
			int _textLengthInCurrent = 0;

			bool StringStartsWith(const std::string& str1, const std::string& str2)
			{
				return str1.compare(0, str2.length(), str2) == 0;
			}

		private:
			void FlatenVisitParagraph(IDomVisitor* visitor, ::SnooDom::Paragraph* paragraph)
			{
				for each(auto item in paragraph->Children)
				{
					auto ppItem = dynamic_cast<::SnooDom::Paragraph*>(item);
					if (ppItem != nullptr)
					{
						FlatenVisitParagraph(visitor, ppItem);
					}
					else
						item->Accept(visitor);
				}
			}
			void MaybeSplitForParagraph()
			{
				if (_textLengthInCurrent > 1000)
				{
					if (ResultGroup == nullptr)
					{
						ResultGroup = ref new StackPanel();
						ResultGroup->Orientation = Orientation::Vertical;
						ResultGroup->Children->Append(Result);
						Result->Margin = Thickness(-6);
					}

					Result = ref new RichTextBlock();
					Result->Style = _styleProvider->RichTextBlockStyle;
					ResultGroup->Children->Append(Result);
					_textLengthInCurrent = 0;
				}

				if (_currentParagraph != nullptr)
				{
					_currentParagraph->Inlines->Append(ref new Windows::UI::Xaml::Documents::LineBreak());
				}

				_currentParagraph = ref new Windows::UI::Xaml::Documents::Paragraph();
				_currentParagraph->TextAlignment = TextAlignment::Left;
				Result->Blocks->Append(_currentParagraph);
			}

			void DirectlyPlaceUIContent(UIElement^ element)
			{
				
				if (ResultGroup == nullptr)
				{
					ResultGroup = ref new StackPanel();
					ResultGroup->Orientation = Orientation::Vertical;
					ResultGroup->Margin = Thickness(0);
					if (Result->Blocks->Size == 0)
					{
						//nothing here yet so lets just ignore the current result and move on
					}
					else
					{
						ResultGroup->Children->Append(Result);
					}
				}
        else
        {
          auto rtb = dynamic_cast<RichTextBlock^>(ResultGroup->Children->GetAt(ResultGroup->Children->Size - 1));
          if (rtb != nullptr && rtb->Blocks->Size == 0)
          {
            ResultGroup->Children->RemoveAt(ResultGroup->Children->Size - 1);
          }
        }

				ResultGroup->Children->Append(element);

				Result = ref new RichTextBlock();
				Result->Style = _styleProvider->RichTextBlockStyle;
				ResultGroup->Children->Append(Result);
				_textLengthInCurrent = 0;
			}

			vector<UIElement^> BuildChildUIList(const vector<IDomObject*>& objects)
			{
				vector<UIElement^> results;
				for each(auto item in objects)
				{
					auto column = dynamic_cast<TableColumn*>(item);
					SnooDomCategoryVisitor categoryVisitor;
					if (column != nullptr)
					{
						for each(auto contents in column->Children)
						{
							contents->Accept(&categoryVisitor);
						}
					}
					else
					{
						item->Accept(&categoryVisitor);
					}


					
					auto paragraph = dynamic_cast<::SnooDom::Paragraph*>(item);
					IDomObject* columnFirstContent = nullptr;

					if (categoryVisitor.Category == MarkdownCategory::PlainText)
					{
						SnooDomPlainTextVisitor plainTextVisitor;
						//this might be a pp
						if (column != nullptr)
						{
							for each(auto contents in column->Children)
							{
								contents->Accept(&plainTextVisitor);
							}
						}
						else if (paragraph != nullptr)
						{
							item->Accept(&plainTextVisitor);
						}
						auto newTextBlock = ref new TextBlock();
						newTextBlock->Style = _styleProvider->TextBlockStyle;
						newTextBlock->Text = toPlatformString(plainTextVisitor.Result);
						results.push_back(newTextBlock);
					}
					else if (column != nullptr && column->Children.size() == 1 && (columnFirstContent = (*column->Children.begin())) != nullptr &&
						(dynamic_cast<Text*>(columnFirstContent) != nullptr))
					{
						auto lnk = dynamic_cast<Link*>(columnFirstContent);
						if (lnk != nullptr)
						{
							SnooDomPlainTextVisitor plainTextVisitor;
							if (lnk->Display.size() > 0)
								lnk->Display[0]->Accept(&plainTextVisitor);

							results.push_back(ref new MarkdownButton(toPlatformString(lnk->Url), toPlatformString((plainTextVisitor.Result))));
						}
						else
						{
							auto newTextBlock = ref new TextBlock();
							newTextBlock->Style = _styleProvider->TextBlockStyle;
							newTextBlock->Text = toPlatformString(((Text*)columnFirstContent)->Contents);
							results.push_back(newTextBlock);
						}
					}
					else
					{
						SnooDomFullUIVisitor fullUIVisitor(_forgroundBrush, _commandFactory, _styleProvider);
						auto itemPP = dynamic_cast<::SnooDom::Paragraph*>(item);
						if (column != nullptr)
						{
							for each(auto contents in column->Children)
							{
								contents->Accept(&fullUIVisitor);
							}
						}
						else if (itemPP != nullptr)
						{
							FlatenVisitParagraph(&fullUIVisitor, itemPP);
						}

						if (fullUIVisitor.ResultGroup != nullptr)
							results.push_back(fullUIVisitor.ResultGroup);
						else
							results.push_back(fullUIVisitor.Result);
					}

					if (column != nullptr)
					{
						switch (column->Alignment)
						{
						case ColumnAlignment::Center:
							results.back()->SetValue(FrameworkElement::HorizontalAlignmentProperty, Windows::UI::Xaml::HorizontalAlignment::Center);
							break;
						case ColumnAlignment::Left:
							results.back()->SetValue(FrameworkElement::HorizontalAlignmentProperty, Windows::UI::Xaml::HorizontalAlignment::Left);
							break;
						case ColumnAlignment::Right:
							results.back()->SetValue(FrameworkElement::HorizontalAlignmentProperty, Windows::UI::Xaml::HorizontalAlignment::Right);
							break;
						}

						results.back()->SetValue(FrameworkElement::VerticalAlignmentProperty, Windows::UI::Xaml::VerticalAlignment::Top);
					}
				}
				return results;
			}


		public:
			SnooDomFullUIVisitor(Brush^ forgroundBrush, ICommandFactory^ commandFactory, IStyleProvider^ styleProvider)
			{
				_styleProvider = styleProvider;
				_forgroundBrush = forgroundBrush;
				_commandFactory = commandFactory;
				Result = ref new RichTextBlock();
				Result->Style = _styleProvider->RichTextBlockStyle;
			};
			RichTextBlock^ Result;
			StackPanel^ ResultGroup = nullptr;
			Windows::UI::Xaml::Documents::Paragraph^ _currentParagraph;


			void Visit(Text* text)
			{
				auto madeRun = ref new Run();
				madeRun->Text = toPlatformString(text->Contents);
				_textLengthInCurrent += text->Contents.size();

				if (text->Italic)
					madeRun->FontStyle = Windows::UI::Text::FontStyle::Italic;

				if (text->Bold)
					madeRun->FontWeight = FontWeights::Bold;


				if (text->HeaderSize != 0)
				{
					switch (text->HeaderSize)
					{
					case 1:
						madeRun->FontSize = 24;
						break;
					case 2:
						madeRun->FontSize = 24;
						madeRun->FontWeight = FontWeights::Bold;
						madeRun->Foreground = _forgroundBrush;
						break;
					case 3:
					case 4:
					case 5:
					case 6:
						madeRun->FontSize = 28;
						madeRun->FontWeight = FontWeights::Bold;
						break;
					}
					MaybeSplitForParagraph();
					_currentParagraph->Inlines->Append(madeRun);
					if (text->HeaderSize == 1)
					{
						auto inlineContainer = ref new Windows::UI::Xaml::Documents::InlineUIContainer();
						auto border = ref new Border();
						border->Style = _styleProvider->BorderStyle;
						inlineContainer->Child = border;
						_currentParagraph->Inlines->Append(inlineContainer);
					}
					else
						_currentParagraph->Inlines->Append(ref new Windows::UI::Xaml::Documents::LineBreak());

				}
				else
				{
					if (_currentParagraph == nullptr)
					{
						_currentParagraph = ref new Windows::UI::Xaml::Documents::Paragraph();
						_currentParagraph->TextAlignment = TextAlignment::Left;
						Result->Blocks->Append(_currentParagraph);
					}
					_currentParagraph->Inlines->Append(madeRun);
				}
			}

			void Visit(::SnooDom::Paragraph* paragraph)
			{
				MaybeSplitForParagraph();
				for each(auto elem in paragraph->Children)
				{
					elem->Accept(this);
				}

			}

			void Visit(HorizontalRule* horizontalRule)
			{
				auto inlineContainer = ref new Windows::UI::Xaml::Documents::InlineUIContainer();
				auto border = ref new Border();
				border->Style = _styleProvider->BorderStyle;
				inlineContainer->Child = border;
				MaybeSplitForParagraph();
				_currentParagraph->Inlines->Append(inlineContainer);
			}

			void Visit(::SnooDom::LineBreak* lineBreak)
			{
				_currentParagraph->Inlines->Append(ref new Windows::UI::Xaml::Documents::LineBreak());
			}

			void Visit(Link* link)
			{
				if (link->Display.size() == 0 &&
					(StringStartsWith(link->Url, "#") || StringStartsWith(link->Url, "/#") ||
					StringStartsWith(link->Url, "//#") || (StringStartsWith(link->Url, "/") && std::count(link->Url.begin(), link->Url.end(), '/') == 1)))
				{
					return;
				}

				Inline^ inlineContainer = nullptr;
				SnooDomCategoryVisitor categoryVisitor;
				if (link->Display.size() > 0)
				{
					for each(auto item in link->Display)
					{
						item->Accept(&categoryVisitor);
					}
				}
				else
					return;

				auto hyperLink = ref new Windows::UI::Xaml::Documents::Hyperlink();
				if (categoryVisitor.Category == MarkdownCategory::PlainText)
				{
					SnooDomPlainTextVisitor plainTextVisitor;
					if (link->Display.size() > 0)
					{
						for each(auto item in link->Display)
							item->Accept(&plainTextVisitor);
					}
					else
						plainTextVisitor.Result = link->Url;


					inlineContainer = hyperLink;
					hyperLink->Click += _commandFactory->MakeLinkCommand(toPlatformString(link->Url));
					auto plainTextRun = ref new Windows::UI::Xaml::Documents::Run();
					plainTextRun->Text = toPlatformString(plainTextVisitor.Result);
					hyperLink->Inlines->Append(plainTextRun);
					//inlineContainer.Child = new MarkdownButton(link.Url, plainTextVisitor.Result);
				}
				else
				{
					inlineContainer = hyperLink;
					hyperLink->Click += _commandFactory->MakeLinkCommand(toPlatformString(link->Url));
					auto text = dynamic_cast<Text*>(link->Display[0]);
					if (text != nullptr)
					{
						if (text->Italic)
							inlineContainer->FontStyle = Windows::UI::Text::FontStyle::Italic;

						if (text->Bold)
							inlineContainer->FontWeight = FontWeights::Bold;


						if (text->HeaderSize != 0)
						{
							switch (text->HeaderSize)
							{
							case 1:
								inlineContainer->FontSize = 24;
								break;
							case 2:
								inlineContainer->FontSize = 24;
								inlineContainer->FontWeight = FontWeights::Bold;
								inlineContainer->Foreground = _forgroundBrush;
								break;
							case 3:
							case 4:
							case 5:
							case 6:
								inlineContainer->FontSize = 28;
								inlineContainer->FontWeight = FontWeights::Bold;
								break;
							}
						}

						SnooDomPlainTextVisitor plainTextVisitor;
						if (link->Display.size() > 0)
						{
							for each(auto item in link->Display)
								item->Accept(&plainTextVisitor);
						}
						else
							plainTextVisitor.Result = link->Url;

						auto plainTextRun = ref new Windows::UI::Xaml::Documents::Run();
						plainTextRun->Text = toPlatformString(plainTextVisitor.Result);
						hyperLink->Inlines->Append(plainTextRun);
					}
					else
					{
						inlineContainer = ref new Windows::UI::Xaml::Documents::InlineUIContainer();
						SnooDomFullUIVisitor fullUIVisitor(_forgroundBrush, _commandFactory, _styleProvider);
						//cant be null in this category
						for each(auto item in link->Display)
							item->Accept(&fullUIVisitor);

						((InlineUIContainer^)inlineContainer)->Child = ref new MarkdownButton(toPlatformString(link->Url), fullUIVisitor.Result);
					}
				}

				if (_currentParagraph == nullptr)
				{
					MaybeSplitForParagraph();
				}

				_currentParagraph->Inlines->Append(inlineContainer);
			}

			void Visit(Code* code)
			{
				SnooDomPlainTextVisitor plainTextVisitor;

				for each(auto item in code->Children)
					item->Accept(&plainTextVisitor);

				auto plainTextRun = ref new Windows::UI::Xaml::Documents::Run();
				plainTextRun->Text = toPlatformString(plainTextVisitor.Result);
				if (_currentParagraph == nullptr || code->IsBlock)
				{
					MaybeSplitForParagraph();
				}
				_currentParagraph->Inlines->Append(plainTextRun);
			}

			void Visit(Quote* code)
			{
				SnooDomCategoryVisitor categoryVisitor;
				UIElement^ result = nullptr;
				for each(auto item in code->Children)
				{
					item->Accept(&categoryVisitor);
				}


				if (categoryVisitor.Category == MarkdownCategory::PlainText && code->Children.size() == 1)
				{
					SnooDomPlainTextVisitor plainTextVisitor;

					for each(auto item in code->Children)
						item->Accept(&plainTextVisitor);


					result = ref new MarkdownQuote(toPlatformString(plainTextVisitor.Result), _styleProvider->TextBlockStyle);
				}
				else
				{
					SnooDomFullUIVisitor fullUIVisitor(_forgroundBrush, _commandFactory, _styleProvider);
					//cant be null in this category
					for each(auto item in code->Children)
						item->Accept(&fullUIVisitor);

					if (fullUIVisitor.ResultGroup != nullptr)
					{
						result = ref new MarkdownQuote(fullUIVisitor.ResultGroup);
					}
					else
					{
						result = ref new MarkdownQuote(fullUIVisitor.Result);
					}

				}

				DirectlyPlaceUIContent(result);
			}

			void Visit(OrderedList* orderedList)
			{
				auto uiElements = BuildChildUIList(orderedList->Children);
				DirectlyPlaceUIContent(ref new MarkdownList(true, uiElements));
			}

			void Visit(UnorderedList* unorderedList)
			{
				auto uiElements = BuildChildUIList(unorderedList->Children);
				DirectlyPlaceUIContent(ref new MarkdownList(false, uiElements));
			}

			void Visit(Table* table)
			{
				auto headerUIElements = BuildChildUIList(vector<IDomObject*>(table->Headers.begin(), table->Headers.end()));
				std::vector<std::vector<UIElement^>> tableBody;
				for each(auto row in table->Rows)
				{
					tableBody.push_back(BuildChildUIList(vector<IDomObject*>(row->Columns.begin(), row->Columns.end())));
				}

				DirectlyPlaceUIContent(ref new MarkdownTable(headerUIElements, tableBody));
			}

			void Visit(Document* document)
			{
				for each(auto elem in document->Children)
				{
					elem->Accept(this);
				}
			}

			void Visit(TableRow* tableRow)
			{
				throw ref new Platform::Exception(-1, "cannot visit table row directly within FullUIVisitor");
			}

			void Visit(TableColumn* tableColumn)
			{
				for each(auto elem in tableColumn->Children)
				{
					elem->Accept(this);
				}
			}
		};
	};

	void MarkdownControl::OnSomethingContentChanged(DependencyObject^ d, DependencyPropertyChangedEventArgs^ e)
	{
		auto markdownControl = dynamic_cast<MarkdownControl^>(d);
		auto markdownData = markdownControl->Markdown;
		auto styleProvider = markdownControl->StyleProvider;
		auto commandFactory = markdownControl->CommandFactory;

		if (markdownControl == nullptr)
			return;

		//need to make sure we have a command factory and a style provider before we actually bind this
		if (markdownControl->StyleProvider != nullptr && markdownControl->Markdown != nullptr && markdownControl->CommandFactory != nullptr)
		{
			try
			{
				SnooDomCategoryVisitor categoryVisitor;
				markdownData->document->Accept(&categoryVisitor);
				switch (categoryVisitor.Category)
				{
				case MarkdownCategory::PlainText:
				{
					SnooDomPlainTextVisitor visitor;
					markdownData->document->Accept(&visitor);
					auto plainControl = markdownControl->MakePlain(toPlatformString(visitor.Result));
					markdownControl->Content = plainControl;
					break;
				}
				case MarkdownCategory::Formatted:
				case MarkdownCategory::Full:
				{
					SnooDomFullUIVisitor visitor(ref new SolidColorBrush(Colors::White), markdownControl->CommandFactory, markdownControl->StyleProvider);
					markdownData->document->Accept(&visitor);
					if (visitor.ResultGroup != nullptr)
						markdownControl->Content = visitor.ResultGroup;
					else
						markdownControl->Content = visitor.Result;
					break;
				}
				default:
					auto textBlock = ref new TextBlock();
					textBlock->Text = "";
					textBlock->Style = markdownControl->StyleProvider->TextBlockStyle;
					markdownControl->Content = textBlock;
					break;
				}
			}
			catch (Platform::Exception^ ex)
			{
				markdownControl->Content = markdownControl->MakePlain(ex->ToString());
			}
			catch (...)
			{
				markdownControl->Content = toPlatformString("somethings wrong");
			}
		}
	}
	DependencyProperty^ MarkdownControl::_markdownProperty = DependencyProperty::Register("Markdown", 
		SnooDom::typeid, MarkdownControl::typeid, ref new PropertyMetadata(nullptr, 
		ref new Windows::UI::Xaml::PropertyChangedCallback(&MarkdownControl::OnSomethingContentChanged)));

	DependencyProperty^ MarkdownControl::_commandFactoryProperty = DependencyProperty::Register("CommandFactory",
		ICommandFactory::typeid, MarkdownControl::typeid, ref new PropertyMetadata(nullptr, 
		ref new Windows::UI::Xaml::PropertyChangedCallback(&MarkdownControl::OnSomethingContentChanged)));

	DependencyProperty^ MarkdownControl::_styleFactoryProperty = DependencyProperty::Register("StyleFactory", 
		IStyleFactory::typeid, MarkdownControl::typeid, ref new PropertyMetadata(nullptr, 
		ref new Windows::UI::Xaml::PropertyChangedCallback(&MarkdownControl::OnSomethingContentChanged)));
}