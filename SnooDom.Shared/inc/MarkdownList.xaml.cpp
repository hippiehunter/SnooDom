//
// MarkdownList.xaml.cpp
// Implementation of the MarkdownList class
//

#include "MarkdownList.xaml.h"

using namespace SnooDom;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The User Control item template is documented at http://go.microsoft.com/fwlink/?LinkId=234236

MarkdownList::MarkdownList(bool numbered, const std::vector<Windows::UI::Xaml::UIElement^>& elements)
{
	InitializeComponent();

	int number = 1;
	int rowCount = 0;
	for each(auto element in elements)
	{
		theGrid->RowDefinitions->Append(ref new RowDefinition());
		auto text = ref new TextBlock();
		text->TextWrapping = TextWrapping::Wrap;
		text->Margin = Thickness(0, 0, 5, 0);
		text->Text = numbered ? (number++).ToString() + L"." : L"\u25CF";

		text->SetValue(Grid::RowProperty, rowCount);
		text->SetValue(Grid::ColumnProperty, (Object^)0);
		element->SetValue(Grid::RowProperty, rowCount++);
		element->SetValue(Grid::ColumnProperty, 1);
		if (dynamic_cast<RichTextBlock^>(element))
		{
			element->SetValue(FrameworkElement::MarginProperty, Thickness(0, 0, 0, 0));
		}
		else
		{
			element->SetValue(FrameworkElement::MarginProperty, Thickness(0, 0, 0, 0));
		}
		theGrid->Children->Append(text);
		theGrid->Children->Append(element);
	}
}
