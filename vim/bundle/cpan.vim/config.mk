
NAME=cpan.vim
DIRS=autoload plugin
VERSION=3.0

bundle-deps:
	$(call fetch_github,c9s,search-window.vim,master,vimlib/autoload/swindow.vim,autoload/swindow.vim)
	$(call fetch_github,c9s,perldoc.vim,master,vimlib/autoload/perldoc.vim,autoload/perldoc.vim)
