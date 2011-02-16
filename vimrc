" Highly optimized .vimrc for Perl hacking
" 2009 - 2011 Magnus Woldrich < http://github.com/trapd00r/ >

set autoindent
set autoread
set cmdheight=1
set colorcolumn=81
set cot+=menuone
set csprg=/usr/local/bin/cscope
set cst
set csto=0
set csverb
set cursorline
set display+=lastline,uhex
set expandtab
set gdefault
set guioptions-=m
set guioptions-=T
set helpheight=150
set history=50
set hlsearch
set ignorecase
set incsearch
set isfname+=:
set laststatus=2
set list
set listchars=tab:\-\ ,trail:-
setlocal nospell spelllang=en_us
set magic
set mat=2
set matchpairs+==:;
set matchpairs+=':'
set maxfuncdepth=1000
set nobackup
set nocp
set nocsverb
set noequalalways
set noerrorbells
set noswapfile
set nowb
set nowrap
set number
set relativenumber
set ruler
set rulerformat=%30(%=\:b%n%y%m%r%w\ %l,%c%V\ %P%)
set scrolloff=5
set shiftwidth=2
set shortmess=aIoOT
"set shortmess=atI
"set showcmd
set showmatch
set showmode
set smartcase
set smartindent
set smarttab
set splitbelow
set statusline=%<[%02n]\ %F%(\ %m%h%w%y%r%)\ %a%=\ %8l,%c%V/%L\ (%P)\ [%08O:%02B]
set tabpagemax=50
set tabstop=2
set t_Co=256
set textwidth=80
set title
set ttimeoutlen=50
set ttyfast
set undofile
set undolevels=512
set vb t_vb=
set vb
set wildchar=<Tab>
set wildmode=list:longest,full
set wildmode=longest,list


au BufRead,BufNewFile *.markdown set ft=md
au BufRead,BufNewFile *.md set ft=md

au BufWritePost *.{sh,pl} silent exe
autocmd! BufNewFile * silent! 0r ~/configs/vim/templates/template.%:e

au      FileType pl,pm,t set filetype=perl
au      FileType perl :noremap K :!perldoc <cword> <bar><bar> perldoc -f <cword><cr>
au!     FileType perl :noremap <leader>c
    \ :!time perl -Mwarnings::unused -MVi::QuickFix -c %<cr>

autocmd FileType perl setlocal errorformat=%f:%l:%m
autocmd FileType perl setlocal keywordprg=perldoc\ -f

cmap W w
colorscheme neverland-ansi_bg

filetype plugin indent on

hi CursorLine term=none cterm=none

inoremap <Down> <NOP>
inoremap <Left> <NOP>
inoremap <Up>   <NOP>

let g:tex_conceal                = 1
let mapleader                    = ','

let perl_moose_stuff             = 1
let perl_no_scope_in_variables   = 1
let perl_no_sync_on_sub          = 1
let perl_no_sync_on_global_var   = 1
let perl_extended_vars           = 1
let perl_include_pod             = 1
let perl_string_as_statement     = 1
let perl_nofold_packages         = 1
let perl_sync_dist               = 1000
let perl_want_scope_in_variables = 1

map @ :s/^#//<CR><ESC>$
map <C-h> <C-w><Left>
map <C-j> <C-w><Down>
map <C-J> <C-W>j<C-W>_
map <C-K> <C-W>k<C-W>_
map <C-k> <C-w><Up>
map <C-l> <C-w><Right>
map <F5> <Esc> :perl use Text::FindIndent;VIM::DoCommand($_) for Text::FindIndent->to_vim_commands(join
map @ I#

nmap <silent>  ;s  :call ToggleSyntax()<CR>
nmap <silent> \sp :set syn=perl<CR>:syntax sync fromstart<CR>
nmap <Space> 10j

nnoremap ; :
nnoremap <leader>d iuse Data::Dumper;<CR>$Data::Dumper::Terse<TAB><TAB> = 1;<CR>$Data::Dumper::Indent<TAB><TAB> = 1;<CR>$Data::Dumper::Useqq<TAB><TAB> = 1;<CR>$Data::Dumper::Deparse<TAB> = 1;<CR>$Data::Dumper::Quotekeys = 0;<CR>$Data::Dumper::Sortkeys  = 1;<CR><CR><ESC>
nnoremap <leader>f :set paste<CR>i
nnoremap <leader>n :call ToggleRelativeAbsoluteNumber()<CR>
nnoremap <leader>p i=pod<CR><CR>=head1 NAME<CR><CR>=head1 SYNOPSIS<CR><CR>=head1 DESCRIPTION<CR><CR>=head1 EXPORTS<CR><CR>None by default.<CR><CR>=head1 FUNCTIONS<CR><CR>=head1 AUTHOR<CR><CR><TAB>Magnus Woldrich<CR>CPAN ID: WOLDRICH<CR>magnus@trapd00r.se<CR>http://japh.se<CR><CR>=head1 CONTRIBUTORS<CR><CR>None required yet.<CR><CR>=head1 COPYRIGHT<CR><CR>Copyright 2011 B<THIS PROGRAM>s L</AUTHOR> and L</CONTRIBUTORS> as listed above.<CR><CR>=head1 LICENSE<CR><CR>This program is free software; you may redistribute it and/or modify it under the same terms as Perl itself.<CR><CR>=cut<CR><ESC>
nnoremap <leader>s :%s/\s\+$//<cr>:let @/=''<CR>
nnoremap <leader>t :e /home/scp1/doc/TODO<CR>
nnoremap <leader>v V`]
nnoremap <silent> <C-l> :nohl<CR><C-l>
nnoremap / /\v

noremap <C-D>   <C-W>
noremap <Down>  <NOP>
noremap <Left>  <NOP>
noremap <Right> <NOP>
noremap <Up>    <NOP>

vnoremap / /\v

runtime macros/matchit.vim

syntax on

ia dumper Dumper

set formatprg=perl\ -MText::Autoformat\ -e'autoformat'
set formatoptions=qro

function! ToggleRelativeAbsoluteNumber()
  if &number
    set relativenumber
  else
    set number
  endif
endfunction

function! ToggleSyntax()
   if exists(
      syntax off
   else
      syntax enable
   endif
endfunction
