//
// MarkdownButton.xaml.h
// Declaration of the MarkdownButton class
//

#pragma once

#include "MarkdownButton.g.h"

namespace SnooDom
{
	public delegate bool HistoryResolverDelegate(Platform::String^ url);
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class MarkdownButton sealed
	{
	public:
		static property Windows::UI::Xaml::Media::SolidColorBrush^ HistoryBrush;
		static property Windows::UI::Xaml::Media::SolidColorBrush^ NoHistoryBrush;
		static property HistoryResolverDelegate^ HistoryResolver;

		MarkdownButton(Platform::String^ url, Platform::Object^ content);
	private:
		static Windows::UI::Xaml::DependencyProperty^ _realContentProperty;
		static Windows::UI::Xaml::DependencyProperty^ _urlProperty;
	public:
		property UIElement^ RealContent
		{
			Windows::UI::Xaml::UIElement^ get() { return (Windows::UI::Xaml::UIElement^)GetValue(_realContentProperty); }
			void set(Windows::UI::Xaml::UIElement^ value) { SetValue(_realContentProperty, value); }
		}
		// Using a DependencyProperty as the backing store for Markdown.  This enables animation, styling, binding, etc...
		static property Windows::UI::Xaml::DependencyProperty^ RealContentProperty
		{
			Windows::UI::Xaml::DependencyProperty^ get() { return _realContentProperty; }
		}

		property Platform::String^ Url
		{
			Platform::String^ get() { return (Platform::String^)GetValue(_urlProperty); }
			void set(Platform::String^ value) { SetValue(_urlProperty, value); }
		}
		// Using a DependencyProperty as the backing store for Markdown.  This enables animation, styling, binding, etc...
		static property Windows::UI::Xaml::DependencyProperty^ UrlProperty
		{
			Windows::UI::Xaml::DependencyProperty^ get() { return _urlProperty; }
		}

		static void OnUrlChanged(Windows::UI::Xaml::DependencyObject^ d, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ e);

		void RegisterDependencyProperties()
		{
			Windows::UI::Xaml::DependencyProperty::Register("RealContent", Windows::UI::Xaml::UIElement::typeid, Windows::UI::Xaml::UIElement::typeid, ref new Windows::UI::Xaml::PropertyMetadata(nullptr));
			Windows::UI::Xaml::DependencyProperty::Register("Url", Platform::String::typeid, Platform::String::typeid, ref new Windows::UI::Xaml::PropertyMetadata(nullptr, ref new Windows::UI::Xaml::PropertyChangedCallback(OnUrlChanged)));
		}
	};
}
