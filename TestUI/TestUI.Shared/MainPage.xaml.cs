using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace TestUI
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            this.NavigationCacheMode = NavigationCacheMode.Required;
        }

		class MarkdownHelpers : SnooDom.ICommandFactory, SnooDom.IStyleProvider
		{
			public TypedEventHandler<Windows.UI.Xaml.Documents.Hyperlink, Windows.UI.Xaml.Documents.HyperlinkClickEventArgs> MakeLinkCommand(string url)
			{
				return new TypedEventHandler<Windows.UI.Xaml.Documents.Hyperlink, Windows.UI.Xaml.Documents.HyperlinkClickEventArgs>((link, arg) => { });
			}

			public Style BorderStyle
			{
				get { return new Style(); }
			}

			public Style RichTextBlockStyle
			{
				get { return new Style(); }
			}

			public Style RunStyle
			{
				get { return new Style(); }
			}

			public Style TextBlockStyle
			{
				get { return null; }
			}
		}

        /// <summary>
        /// Invoked when this page is about to be displayed in a Frame.
        /// </summary>
        /// <param name="e">Event data that describes how this page was reached.
        /// This parameter is typically used to configure the page.</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            // TODO: Prepare page for display here.

            // TODO: If your application contains multiple pages, ensure that you are
            // handling the hardware Back button by registering for the
            // Windows.Phone.UI.Input.HardwareButtons.BackPressed event.
            // If you are using the NavigationHelper provided by some templates,
            // this event is handled for you.
			var helper = new MarkdownHelpers();
			var mdControl = new SnooDom.MarkdownControl();
			mdControl.StyleProvider = helper;
			mdControl.CommandFactory = helper;
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("[A link with a /r/subreddit in it](/lol)");
			//Content = mdControl;
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("http://www.reddit.com");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("[foo](http://en.wikipedia.org/wiki/Link_(film\\))");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("(http://tsfr.org)");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("[A link with a /r/subreddit in it](/lol)");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("[A link with a http://www.url.com in it](/lol)");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("[Empty Link]()");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("http://en.wikipedia.org/wiki/café_racer");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("#####################################################hi");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("[foo](http://bar\nbar)");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/test");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("Words words /r/test words");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("escaped \\/r/test");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("ampersands http://www.google.com?test&blah");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("[_regular_ link with nesting](/test)");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM(" www.a.co?with&test");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("Normal^superscript");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("Escape\\^superscript");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("~~normal strikethrough~~");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("\\~~escaped strikethrough~~");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("anywhere\\x03, you");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("[Test](//test)");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("[Test](//#test)");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("[Test](#test)");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("[Test](git://github.com)");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("[Speculation](//?)");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/sr_with_underscores");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("[Test](///#test)");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/multireddit+test+yay");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("<test>");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("words_with_underscores");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("words*with*asterisks");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("~test");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/u/test");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/u/test/m/test test");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/U/nope");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/test/m/test test");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/test/w/test test");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/test/comments/test test");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/u/test/commentscommentscommentscommentscommentscommentscomments/test test");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/test/commentscommentscommentscommentscommentscommentscomments/test test");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("blah \\\\");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/whatever: fork");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/t:timereddit");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/reddit.com");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/not.cool");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/very+clever+multireddit+reddit.com+t:fork+yay");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/t:heatdeathoftheuniverse");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/all-minus-something");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/all-minus-something");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/r/notall-minus");
			mdControl.Markdown = SnooDom.SnooDom.MarkdownToDOM("/R/reddit.com");
        }
    }
}
