" perldo {$/='';if($_!~ /my/){$_='';print $_}}
let g:tex_conceal="admgs"
set autoread                    " auto read when file is changed
set tabpagemax=50
set colorcolumn=81
set number                      " line numbering
set relativenumber
set undofile
set nobackup                    " I have git...
set nowb
set noswapfile
set magic                       " magic RE
set mat=2                       "
set cmdheight=1
set nocp                        " no-compatible mode
set t_Co=256                    " use 256 colors
set vb                          " visual bell
set undolevels=512              " undo
set history=50                  " q:
set ruler                       " cursor position
set display+=lastline,uhex
set shortmess=aotTWI
"set shortmess=aIoO              " short msg, no intro
set showmode                    " show current mode
set noequalalways               " no need to always keep windows same size
set splitbelow                  " splitted window under current one
set laststatus=2                " status line, always
set maxfuncdepth=1000           " depth for subs
set wildchar=<Tab>              " tab for autocompletion
set wildmode=longest,list       " bash-style completion
set incsearch                   " show partial matches
set hlsearch                    " hilight patterns
set ignorecase                  " ignore case when searching
set smartcase                   " ... unless there is capitals in the pattern
set tabstop=2                   " tabstop
"set softtabstop=2               "
set expandtab                   " spaces, not tabs
set shiftwidth=2
"set shiftround                  " shift to next round tabstop
set smarttab                    " outdent by one level using bkspc
set showmatch                   " show matching brackets etc
set matchpairs+==:;
set matchpairs+=':'
set autoindent
set smartindent
"set cindent
set showmode
set textwidth=80                " be nice!
set title
set isfname+=:
set helpheight=150
set ttimeoutlen=50
set ttyfast

set nowrap                      " dont wrap long lines
set scrolloff=5                 " number of lines to keep above cursor
set shortmess=atI
"set wildmenu                    " fancy menu
set wildmode=list:longest,full  " bash style completioness
set guioptions-=m               " just in case we happened to..
set guioptions=-T               " ..be using gvim
set cursorline                  " hilight line where cursor is
set noerrorbells
set vb t_vb=
set scrolloff=5

"set cursorcolumn
set cot+=menuone                " show preview of function prototype
"set fo+=r                       " annoying comments on far left
filetype plugin indent on       " def filetype settings. Mail gets textwidth 72
                                " cindent is on in C files etc
                                " loads indent files to automatically do
                                " language specific indenting
"runtime ftplugin/man.vim
runtime macros/matchit.vim
setlocal nospell spelllang=en_us
"map <space> /
"map <c-space> ?
map <C-J> <C-W>j<C-W>_
map <C-K> <C-W>k<C-W>_
map @ I#
map ² :s/^#//<CR><ESC>$
noremap <Left>  <NOP>
noremap <Right> <NOP>
noremap <Up>    <NOP>
noremap <Down>  <NOP>
inoremap <Left> <NOP>
"inoremap <Right><NOP>
inoremap <Up>   <NOP>
inoremap <Down> <NOP>

iab dumper Dumper

" window switching
map <C-k> <C-w><Up>
map <C-j> <C-w><Down>
map <C-l> <C-w><Right>
map <C-h> <C-w><Left>

:sign define fixme text=!! linehl=Todo

" ^d is easier
noremap <C-D> <C-W>
cmap W w
nnoremap / /\v
vnoremap / /\v
set gdefault

function! ToggleSyntax()
   if exists("g:syntax_on")
      syntax off
   else
      syntax enable
   endif
endfunction

nmap <silent>  ;s  :call ToggleSyntax()<CR>



let mapleader = ","
nnoremap <leader>s :%s/\s\+$//<cr>:let @/=''<CR>
nnoremap <leader>p i#!/usr/bin/perl<CR><BS>use vars qw($APP $VERSION);<CR>$APP     = undef;<CR>$VERSION = '0.0.1';<CR>use strict;<CR>use Pod::Usage;<CR>use Getopt::Long;<CR>use Data::Dumper;<CR>$Data::Dumper::Terse<TAB><TAB> = 1;<CR>$Data::Dumper::Indent<TAB><TAB> = 1;<CR>$Data::Dumper::Useqq<TAB><TAB> = 1;<CR>$Data::Dumper::Deparse<TAB> = 1;<CR>$Data::Dumper::Quotekeys = 0;<CR>$Data::Dumper::Sortkeys  = 1;<CR><CR><CR><CR><CR>=pod<CR><CR>=head1 NAME<CR><CR>=head1 USAGE<CR><CR>=head1 DESCRIPTION<CR><CR>=head1 OPTIONS<CR><CR>=head1 AUTHOR<CR><CR><TAB>Magnus Woldrich<CR>CPAN ID: WOLDRICH<CR>magnus@trapd00r.se<CR>http://japh.se<CR><CR>=head1 REPORTING BUGS<CR><CR>Report bugs on rt.cpan.org or to magnus@trapd00r.se<CR><CR>=head1 COPYRIGHT<CR><CR>Copyright (C) 2010 Magnus Woldrich. All right reserved.<CR>This program is free software; you can redistribute it and/or modify it under the same terms as Perl itself.<CR><CR>License GPLv2<CR><CR>=cut<CR><ESC>16gg
nnoremap <leader>d iuse Data::Dumper;<CR>$Data::Dumper::Terse<TAB><TAB> = 1;<CR>$Data::Dumper::Indent<TAB><TAB> = 1;<CR>$Data::Dumper::Useqq<TAB><TAB> = 1;<CR>$Data::Dumper::Deparse<TAB> = 1;<CR>$Data::Dumper::Quotekeys = 0;<CR>$Data::Dumper::Sortkeys  = 1;<CR><CR><ESC>

nnoremap <leader>f :set paste<CR>i

" select the just pasted text
nnoremap <leader>v V`]
nnoremap ; :

nnoremap <silent> <C-l> :nohl<CR><C-l>

" Toggle number column: {{{
  " <A-1> to toggle between nu and rnu
"if exists('+relativenumber')
"  nnoremap <expr> � ToggleNumberDisplay()
"  xnoremap <expr> � ToggleNumberDisplay()
"  onoremap <expr> � ToggleNumberDisplay()
"
"  function! ToggleNumberDisplay()
"      if &l:nu | setlocal rnu | else | setlocal nu | endif | redraw
"  endfunction
"
"endif


" toggle between number and relative number on
nnoremap <leader>n :call ToggleRelativeAbsoluteNumber()<CR>
function! ToggleRelativeAbsoluteNumber()
  if &number
    set relativenumber
  else
    set number
  endif
endfunction

if has("cscope")
    set csprg=/usr/local/bin/cscope
    set csto=0
    set cst
    set nocsverb
    " add any database in current directory
    if filereadable("cscope.out")
        cs add cscope.out
    " else add database pointed to by environment
    elseif $CSCOPE_DB != ""
        cs add $CSCOPE_DB
    endif
    set csverb
endif

:nmap <Space> 10j

autocmd! BufNewFile * silent! 0r ~/configs/vim/templates/template.%:e
autocmd FileType perl setlocal errorformat=%f:%l:%m
nmap <silent> \sp :set syn=perl<CR>:syntax sync fromstart<CR>
autocmd FileType perl setlocal keywordprg=perldoc\ -f
au BufWritePost *.{sh,pl} silent exe "!chmod +x %"


"augroup vimrc_autocmds
"  autocmd BufRead * highlight OverLength ctermbg=236 guibg=#592929
"  autocmd BufRead * match OverLength /\%74v.*/
"augroup END



"set list listchars=tab:\|-,trail:.
"set backspace=indent,eol,start
"colorscheme darkburn
colorscheme neverland-ansi_bg
"colorscheme charged-256
syntax on

au BufRead,BufNewFile *.markdown set ft=md
au BufRead,BufNewFile *.md set ft=md

au FileType pl,pm,t set filetype=perl
au! FileType perl :noremap <leader>c
    \ :!time perl -Mwarnings::unused -MVi::QuickFix -c %<cr>

"set errorformat+=%m\ at\ %f\ line\ %l\.
"set errorformat+=%m\ at\ %f\ line\ %l

"au FileType perl set makeprg=perl\ -c\ %\ $*
"au FileType perl set errorformat=%f:%l:%m
"au FileType perl set autowrite
au FileType perl :noremap K :!perldoc <cword> <bar><bar> perldoc -f <cword><cr>
"au FileType text call TextMode()
"au FileType mail call TextMode()
"au FileType vim  set iskeyword+=. iskeyword+=/ iskeyword+=~

let perl_string_as_statement=1
let perl_sync_dist=1000
"let perl_fold=1                   " let subs fold themselves
let perl_include_pod=1            " no idea but seems nice
let perl_extended_vars = 1        " syntax hl for 'complicated' stuff

"au BufReadPost *                " opens file on last edited position
"    \ if line("'\"") > 0 && line("'\"") <= line("$") |
"    \   exe "normal g`\"" |
"    \ endif

"setlocal omnifunc=syntaxcomplete#Complete
"vmap_c:s/^/#/gi<Enter>
"vmap_C:s/^#//gi<Enter>
"nnoremap <silent> _d :.!perl -MO=Deparse 2>/dev/null<cr>
"vnoremap <silent> _d :!perl -MO=Deparse 2>/dev/null<cr>

hi CursorLine term=none cterm=none

set rulerformat=%30(%=\:b%n%y%m%r%w\ %l,%c%V\ %P%)
set showcmd     " Show partial command in status line

"set statusline=%<%f\ %=\:\b%n%y%m%r%w\ %l,%c%V\ %P
set statusline=%<[%02n]\ %F%(\ %m%h%w%y%r%)\ %a%=\ %8l,%c%V/%L\ (%P)\ [%08O:%02B]
"autocmd BufNewFile,BufRead *.p? compiler perl
"autocmd BufNewFile,BufRead *.p6 setf perl6
"match Error80 /\%>80v.\+/ " highlight anything past 80 in red
"
" vertical indent
set list
set listchars=tab:\-\ ,trail:-

