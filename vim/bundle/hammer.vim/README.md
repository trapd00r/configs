![Hammer Mario!](http://i.imgur.com/HUuvF.png)

Hammer.vim can translate a bunch of markup languages to HTML, and preview them in your browser of choice. All from within vim!  
By default, the preview is a clone of how GitHub would render _README.md_, but custom templates of your own are supported too.  

This project was formerly _vim-markdown-preview_.

Supported Markup
----------------

Anything _github-markup_ supports:  

* [.markdown](http://daringfireball.net/projects/markdown/) -- `gem install redcarpet`
* [.textile](http://www.textism.com/tools/textile/) -- `gem install RedCloth`
* [.rdoc](http://rdoc.sourceforge.net/)
* [.org](http://orgmode.org/) -- `gem install org-ruby`
* [.creole](http://wikicreole.org/) -- `gem install creole`
* [.mediawiki](http://www.mediawiki.org/wiki/Help:Formatting) -- `gem install wikicloth`
* [.rst](http://docutils.sourceforge.net/rst.html) -- `easy_install docutils`
* [.asciidoc](http://www.methods.co.nz/asciidoc/) -- `brew install asciidoc`
* [.pod](http://search.cpan.org/dist/perl/pod/perlpod.pod) -- `Pod::Simple::HTML`
  comes with Perl >= 5.10. Lower versions should install Pod::Simple from CPAN.
* .1 -- Requires [`groff`](http://www.gnu.org/software/groff/)
* .html
* .xhtml

Requirements
------------

* vim built with Ruby support.
* github-markup (_See install instructions_)
* You might need to install an extra dependency depending on the markup language you want to render (See Above).

Install 
-------

    $ [sudo] gem install github-markup
    $ git clone git://github.com/robgleeson/hammer.vim.git
    $ cp -R hammer.vim/plugin/* $HOME/.vim/plugin


Usage
-----

The `:Hammer` command will try to draw a preview of whatever file is currently in your buffer.  
It helps to map it to a key though, and I personally use: `map <leader>p :Hammer<CR>`

There are a few options, too:  

* g:HammerTemplate  
  The template to render with. Default is `default`, a GitHub-esque design.

* g:HammerDirectory  
  Where previews are written to. Default is `/tmp`

* g:HammerBrowser  
  The template to open the preview with. Default is OS-dependent.  
  `open` on OSX, `start` on Windows, and `xdg-open` on xorg-running machines.



Templates!
----------

If you don't like the default template, you can write your own.  
Templates are ERB layouts with rendered markup passed on as a partial.  
Templates have access to paths used by Hammer, so you can link to assets(CSS, etc) easily.  

The [default template](http://bit.ly/jaNkaJ) serves as a good example to get you going.   
Pull requests for new templates would be awesome ;-)

Screenshots
-----------

* [POD](http://d.pr/16YG)
* [Markdown](http://d.pr/GEuT)



Thanks
------

Many thanks to the @github team for _github-markup_!

License
--------

_Hammer.vim_ is released under the [_MIT License_](http://en.wikipedia.org/wiki/MIT_License).  
See [LICENSE](http://github.com/robgleeson/hammer.vim/blob/master/LICENSE) for details.

