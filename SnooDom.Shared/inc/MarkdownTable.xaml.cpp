//
// MarkdownTable.xaml.cpp
// Implementation of the MarkdownTable class
//

#include "MarkdownTable.xaml.h"

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

MarkdownTable::MarkdownTable(const std::vector<Windows::UI::Xaml::UIElement^>& headers, const std::vector<std::vector<Windows::UI::Xaml::UIElement^>>& body)
{
	InitializeComponent();

	Thickness margin(2, 6, 2, 6);
	Thickness margin2(2, 6, 2, 6);
	int x = 0, y = 0;
	auto theGrid = ref new Grid();
	theGrid->Margin = Thickness(0, 0, 0, 9);
	bool twoOrLess = headers.size() <= 2;
	if (twoOrLess)
	{
		Content = theGrid;
	}
	else
	{
		auto viewer = ref new ScrollViewer();
		viewer->HorizontalScrollBarVisibility = ScrollBarVisibility::Auto;
		viewer->VerticalScrollBarVisibility = ScrollBarVisibility::Disabled;
		viewer->Content = theGrid;
		Content = viewer;
	}

	auto rowDef = ref new RowDefinition();
	rowDef->Height = GridLength::Auto;
	theGrid->RowDefinitions->Append(rowDef);
	int maxX = headers.size() - 1;
	for each(auto header in headers)
	{
		auto columDef = ref new ColumnDefinition();
		columDef->MaxWidth = 200;
		theGrid->ColumnDefinitions->Append(columDef);
		header->SetValue(Grid::ColumnProperty, x);
		header->SetValue(Grid::RowProperty, y);
		if (!twoOrLess)
			header->SetValue(FrameworkElement::MaxWidthProperty, 200);
		header->SetValue(FrameworkElement::MarginProperty, margin);
		theGrid->Children->Append(header);
		x++;
	}

	for each(auto row in body)
	{
		auto rowDef = ref new RowDefinition();
		rowDef->Height = GridLength::Auto;
		theGrid->RowDefinitions->Append(rowDef);
		x = 0;
		y++;
		for each(auto column in row)
		{
			column->SetValue(Grid::ColumnProperty, x);
			column->SetValue(Grid::RowProperty, y);
			if (!twoOrLess)
				column->SetValue(FrameworkElement::MaxWidthProperty, 200);
			if (dynamic_cast<RichTextBlock^>(column) != nullptr)
				column->SetValue(FrameworkElement::MarginProperty, margin2);
			else
				column->SetValue(FrameworkElement::MarginProperty, margin);
			theGrid->Children->Append(column);
			x++;
		}

	}
}
