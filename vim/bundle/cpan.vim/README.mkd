cpan.vim
========

Vim plugin for perl hackers

Screencast
==========
http://www.youtube.com/watch?v=erF0NWUIbr4

FEATURES
========

* provide a quick way to search/install/query/edit cpan modules

INSTALL
=========

Just run make:

		$ make install

cpan.vim also use cpanm as default cpan command , to install cpanminus (optional):

		$ make install-cpanm

USAGE
=========

CPAN Window:
------------


- *C-c C-m* - to open cpan window horizontally

- *C-c C-v* - to open cpan window vertically

#### Insert Mode

- *Enter*  - to go to the first matched module file.

- *C-t*    - to go to the first matched module file in new tab.

- *@*      - to search module by current pattern in your browser

- *Tab*    - to switch cpan window mode (search all modules or installed modules)

- *C-n*    - next result

- *C-p*    - previous result


(support bash style bindings , eg: `<C-a>, <C-e>, <C-f>, <C-b>` )


#### Normal Mode

- *C-n*      - next result

- *C-p*      - previous result

- *Enter*    - to go to the first matched module file.

- *t*        - to go to the module file in new tab

- *@*        - to see the module documentation in your browser

- *!*        - to see the module documentation by perldoc command

- *$*        - to see the module documentation inside vim window

- *I*        - to install the module

- *ESC ESC*  - to close cpan window

- *?*        - to show commands


Commands
========

- *:ReloadModuleCache*
- *:ReloadInstalledModuleCache*
- *:ReloadCurrentLibModuleCache*

Options
==============

- *g:cpan_win_type*         : (vsplit|split)
- *g:cpan_win_width*        : (int)
- *g:cpan_win_height*       : (int)
- *g:cpan_mod_cachef*       : (filepath)
- *g:cpan_ins_mod_cachef*   : (filepath)
- *g:cpan_cache_expiry*     : (int)(days)
- *g:cpan_default_mapping*  : (bool)

