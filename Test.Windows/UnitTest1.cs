using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.VisualStudio.TestPlatform.UnitTestFramework;
#if WINRT
using Microsoft.VisualStudio.TestPlatform.UnitTestFramework.AppContainer;
#endif
using Windows.Foundation;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Documents;

namespace Test.Windows
{
	class MarkdownHelpers : SnooDom.ICommandFactory, SnooDom.IStyleProvider
	{
		public TypedEventHandler<Hyperlink, HyperlinkClickEventArgs> MakeLinkCommand(string url)
		{
			return new TypedEventHandler<Hyperlink, HyperlinkClickEventArgs>((link, args) => { });
		}

		public Style BorderStyle
		{
			get { return null; }
		}

		public Style RichTextBlockStyle
		{
			get { return null; }
		}

		public Style RunStyle
		{
			get { return null; }
		}

		public Style TextBlockStyle
		{
			get { return null; }
		}
	}

    [TestClass]
    public class SnuDownTests
	{
		[TestMethod]
		public void advancedLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("[foo](http://en.wikipedia.org/wiki/Link_(film\\))");
		}
		[TestMethod]
		public void UnfinishedLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("(http://tsfr.org)");
		}
		[TestMethod]
		public void SubredditLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("[A link with a /r/subreddit in it](/lol)");
		}
		[TestMethod]
		public void LinkLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("[A link with a http://www.url.com in it](/lol)");
		}
		[TestMethod]
		public void EmptyLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("[Empty Link]()");
			}
		[TestMethod]
		public void UnicodeLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("http://en.wikipedia.org/wiki/café_racer");
		}
		[TestMethod]
		public void SuperHeader()
		{
			SnooDom.SnooDom.MarkdownToDOM("#####################################################hi");
		}
		[TestMethod]
		public void EscapeLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("[foo](http://bar\nbar)");
		}
		[TestMethod]
		public void BasicRedditLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("/r/test");
		}
		[TestMethod]
		public void ContainsRedditLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("Words words /r/test words");
		}
		[TestMethod]
		public void UnfinishedRedditLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("/r/");
		}
		[TestMethod]
		public void EscapedRedditLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("escaped \\/r/test");
		}
		[TestMethod]
		public void AmpersandLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("ampersands http://www.google.com?test&blah");
		}
		[TestMethod]
		public void LinkNesting()
		{
			SnooDom.SnooDom.MarkdownToDOM("[_regular_ link with nesting](/test)");
		}
		[TestMethod]
		public void LinkWithSpace()
		{
			SnooDom.SnooDom.MarkdownToDOM(" www.a.co?with&test");
		}
		[TestMethod]
		public void NormalSuperScript()
		{
			SnooDom.SnooDom.MarkdownToDOM("Normal^superscript");
		}
		[TestMethod]
		public void EscapeSuperScript()
		{
			SnooDom.SnooDom.MarkdownToDOM("Escape\\^superscript");
		}
		[TestMethod]
		public void NormalStrikethrough()
		{
			SnooDom.SnooDom.MarkdownToDOM("~~normal strikethrough~~");
		}
		[TestMethod]
		public void EscapedStrikethrough()
		{
			SnooDom.SnooDom.MarkdownToDOM("\\~~escaped strikethrough~~");
		}
		[TestMethod]
		public void Unicode()
		{
			SnooDom.SnooDom.MarkdownToDOM("anywhere\\x03, you");
		}
		[TestMethod]
		public void SlashyLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("[Test](//test)");
		}
		[TestMethod]
		public void SlashyHeaderLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("[Test](//#test)");
		}
		[TestMethod]
		public void HeaderLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("[Test](#test)");
		}
		[TestMethod]
		public void NotHttpLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("[Test](git://github.com)");
		}

		[TestMethod]
		public void NotHttpLink2()
		{
			var dom = SnooDom.SnooDom.MarkdownToDOM("[Test](git://github.com)");
			var link =dom.GetLinks().First();
			if (link.Key != "git://github.com" || link.Value != "Test")
				throw new Exception("link didnt parse correctly");
		}

		[TestMethod]
		public void Speculation()
		{
			SnooDom.SnooDom.MarkdownToDOM("[Speculation](//?)");
		}
		[TestMethod]
		public void RedditWithUnderscores()
		{
			SnooDom.SnooDom.MarkdownToDOM("/r/sr_with_underscores");
		}
		[TestMethod]
		public void LinkWithEscapedSlashHeader()
		{
			SnooDom.SnooDom.MarkdownToDOM("[Test](///#test)");
		}
		[TestMethod]
		public void MultiRedditLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("/r/multireddit+test+yay");
		}
		[TestMethod]
		public void Tag()
		{
			SnooDom.SnooDom.MarkdownToDOM("<test>");
		}
		[TestMethod]
		public void Underscores()
		{
			SnooDom.SnooDom.MarkdownToDOM("words_with_underscores");
		}
		[TestMethod]
		public void Asterisks()
		{
			SnooDom.SnooDom.MarkdownToDOM("words*with*asterisks");
		}
		[TestMethod]
		public void Tilde()
		{
			SnooDom.SnooDom.MarkdownToDOM("~test");
		}
		[TestMethod]
		public void User()
		{
			SnooDom.SnooDom.MarkdownToDOM("/u/test");
		}
		[TestMethod]
		public void UserSub()
		{
			SnooDom.SnooDom.MarkdownToDOM("/u/test/m/test test");
		}
		[TestMethod]
		public void BadUser()
		{
			SnooDom.SnooDom.MarkdownToDOM("/U/nope");
		}
		[TestMethod]
		public void BadRedditLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("/r/test/m/test test");
		}
		[TestMethod]
		public void MoreBadRedditLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("/r/test/w/test test");
		}
		[TestMethod]
		public void BadCommentLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("/r/test/comments/test test");
		}
		[TestMethod]
		public void BadUserCommentLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("/u/test/commentscommentscommentscommentscommentscommentscomments/test test");
		}
		[TestMethod]
		public void BadRedditCommentLink()
		{
			SnooDom.SnooDom.MarkdownToDOM("/r/test/commentscommentscommentscommentscommentscommentscomments/test test");
			SnooDom.SnooDom.MarkdownToDOM("blah \\\\");
			SnooDom.SnooDom.MarkdownToDOM("/r/whatever: fork");
			SnooDom.SnooDom.MarkdownToDOM("/r/t:timereddit");
			SnooDom.SnooDom.MarkdownToDOM("/r/reddit.com");
			SnooDom.SnooDom.MarkdownToDOM("/r/not.cool");
			SnooDom.SnooDom.MarkdownToDOM("/r/very+clever+multireddit+reddit.com+t:fork+yay");
			SnooDom.SnooDom.MarkdownToDOM("/r/t:heatdeathoftheuniverse");
			SnooDom.SnooDom.MarkdownToDOM("/r/all-minus-something");
			SnooDom.SnooDom.MarkdownToDOM("/r/all-minus-something");
			SnooDom.SnooDom.MarkdownToDOM("/r/notall-minus");
			SnooDom.SnooDom.MarkdownToDOM("/R/reddit.com");
        }
    }
}
