" Highly optimized .vimrc for Perl, C, Lua hacking
" 2009 - 2011 Magnus Woldrich < http://github.com/trapd00r/ >
set nocp

set autoread
set autochdir
set autoindent
set cmdheight=1
set cinoptions=:0,l1,t0,g0,(0
set colorcolumn=+1,+2
"set copyindent
set cot+=menuone
set csprg=/usr/local/bin/cscope
set cst
set csto=0
set csverb
set cursorline
set define=[^A-Za-z_]
set diffopt=filler,iwhite,context:8,vertical
set display+=lastline,uhex
set expandtab
set equalalways
set eadirection=ver
set fillchars=vert:│,fold:-
set foldmethod=manual
set foldenable
set gdefault
set grepprg=ack\ -a
set guioptions-=m
set guioptions-=T
set helpheight=150
set hidden
set history=50
set hlsearch
set ignorecase
set include=\\<\\(use\\\|require\\)\\>  
set includeexpr=substitute(substitute(v:fname,'::','/','g'),'$','.pm','')
set incsearch
set isfname+=:
set laststatus=2
set list
set listchars=tab:\-\ ,trail:-
set magic
set makeprg=/usr/bin/make
set mat=2
set matchpairs+==:;
set matchpairs+=':'
set matchtime=10
set maxfuncdepth=1000
set maxmemtot=200000
set modeline
set modelines=2
set nobackup
set nocsverb
"set noequalalways
set noerrorbells
set noswapfile
set nowb
set nowrap
set nrformats=alpha,octal,hex
set numberwidth=2
set pastetoggle=<F42>
set preserveindent
set relativenumber
set ruler
set rulerformat=%30(%=\:b%n%y%m%r%w\ %l,%c%V\ %P%)
set scrolloff=5
set ssop=buffers,folds,globals,help,localoptions,options,resize,tabpages
set shiftwidth=2
set shortmess=aIoOT
"set shortmess=atI
"set showcmd
set showmatch
set showmode
set smartcase
"set smartindent
set smarttab
set splitbelow
set statusline=%<[%02n]\ %F%(\ %m%h%w%y%r%)\ %a%=\ %8l,%c%V/%L\ (%P)\ [%08O:%02B]
set tabpagemax=50
"set tabstop=2
set t_Co=256
set timeout
set timeoutlen=3000
set ttimeoutlen=50
set tw=80
set title
set ttyfast
set undofile
set undolevels=512
set undodir=/mnt/Docs/Backup/undo
set vb t_vb=
set vb
set wildchar=<Tab>
set wildmode=list:longest,full
set wildignore=*.swp,*.bak,*.un~,blib
set winfixwidth

set nomore

call pathogen#runtime_append_all_bundles()

syntax on

setlocal nospell spelllang=en_us

colorscheme neverland-ansi_bg

filetype plugin indent on

au BufRead,BufNewFile *.markdown set ft=md
au BufRead,BufNewFile *.md set ft=md
au BufRead,BufNewFile *.go set ft=go

au BufWritePost *.{sh,pl} silent exe
autocmd! BufNewFile * silent! 0r ~/configs/vim/templates/template.%:e

au      FileType pl,pm,t set filetype=perl
au      FileType perl :noremap K :!perldoc <cword> <bar><bar> perldoc -f <cword><cr>
au!     FileType perl :noremap <leader>c
    \ :!time perl -Mwarnings::unused -MVi::QuickFix -c %<cr>

autocmd FileType perl setlocal errorformat=%f:%l:%m
autocmd FileType perl setlocal keywordprg=perldoc\ -f
"autocmd BufNewFile,BufRead *.p? compiler perl
"au BufWritePost *.pl,*.pm !perl -c %

"let g:indent_guides_auto = 0
"autocmd VimEnter,Colorscheme * :hi IndentGuidesOdd  ctermbg=233
"autocmd VimEnter,Colorscheme * :hi IndentGuidesEven ctermbg=234




hi CursorLine term=none cterm=none


let mapleader                    = ','
let g:tex_conceal                = 1

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
let perl_pod_formatting          = 1
let perl_pod_spellcheck_headings = 1
let perlhelp_prog                = '/usr/bin/perldoc'

let extradite_width              = 40





cmap W w

"map @ :s/^#//<CR><ESC>$
map <C-h> <C-w><Left> map <C-j> <C-w><Down> map <C-J> <C-W>j<C-W>_


map <C-K> <C-W>k<C-W>_
map <C-k> <C-w><Up>
"map @ I#

nmap <silent>  ;s  :call ToggleSyntax()<CR>
nmap <silent> \sp :set syn=perl<CR>:syntax sync fromstart<CR>
nmap <Space> 10j

nmap Y y$

inoremap <Down> <NOP>
inoremap <Left> <NOP>
inoremap <Up>   <NOP>


nnoremap <C-n> :bnext<CR>
nnoremap <C-p> :bprevious<CR>
"nnoremap <leader>n :bprevious<CR>
"nnoremap <leader>p :bnext<CR>
nnoremap <leader>d :buffers<CR>:buffer<Space>
nnoremap <Leader>l :ls<CR>
nnoremap <Leader>g :e#<CR>

nnoremap <Leader>1 :set ft=perl<CR>
nnoremap <Leader>2 :set ft=c<CR>
nnoremap <Leader>3 :set ft=lua<CR>
nnoremap <Leader>4 :set ft=sh<CR>
nnoremap <Leader>5 :set ft=config<CR>
nnoremap <Leader>6 :set ft=vim<CR>

nnoremap <Leader>7 :7b<CR>
nnoremap <Leader>8 :8b<CR>
nnoremap <Leader>9 :9b<CR>
nnoremap <Leader>0 :10b<CR>

nnoremap <leader>a :bdelete!<CR> " force delete buffer ^

nnoremap ; :
nnoremap <leader>e iuse Data::Dumper;<CR>$Data::Dumper::Terse<TAB><TAB> = 1;<CR>$Data::Dumper::Indent<TAB><TAB> = 1;<CR>$Data::Dumper::Useqq<TAB><TAB> = 1;<CR>$Data::Dumper::Deparse<TAB> = 1;<CR>$Data::Dumper::Quotekeys = 0;<CR>$Data::Dumper::Sortkeys  = 1;<CR><CR><ESC>
nnoremap <leader>f :set paste<CR>i
nnoremap <leader>o i=pod<CR><CR>=head1 NAME<CR><CR>=head1 SYNOPSIS<CR><CR>=head1 DESCRIPTION<CR><CR>=head1 EXPORTS<CR><CR>None by default.<CR><CR>=head1 FUNCTIONS<CR><CR>=head1 AUTHOR<CR><CR><TAB>Magnus Woldrich<CR>CPAN ID: WOLDRICH<CR>magnus@trapd00r.se<CR>http://japh.se<CR><CR>=head1 CONTRIBUTORS<CR><CR>None required yet.<CR><CR>=head1 COPYRIGHT<CR><CR>Copyright 2011 B<THIS PROGRAM>s L</AUTHOR> and L</CONTRIBUTORS> as listed above.<CR><CR>=head1 LICENSE<CR><CR>This program is free software; you may redistribute it and/or modify it under the same terms as Perl itself.<CR><CR>=cut<CR><ESC>
nnoremap <leader>s :%s/\s\+$//<cr>:let @/=''<CR>
nnoremap <leader>w :e /home/scp1/doc/TODO<CR>
nnoremap <leader>r :e /home/scp1/doc/vim.txt<CR>Go<ESC>o
nnoremap <leader>v V`]

nnoremap <leader><TAB> :set spell<CR>
nnoremap <leader>p :set paste<CR><CR>o


" :!perl -wap -e 's/foo/bar/'
nnoremap / /\v
vnoremap / /\v
cnoremap '<,'>s/ '<,'>s/\v
cnoremap '<,'>s# '<,'>s#\v
cnoremap '<,'>s@ '<,'>s@\v
cnoremap %s/ %s/\v
cnoremap %s# %s#\v
cnoremap %s@ %s@\v
cnoremap s/ s/\v
cnoremap s# s#\v
cnoremap s@ s@\v


map [29~ :help keycodes<CR>

nnoremap <silent> <C-l> :nohl<CR>

nmap     <silent> ,/    :nohl<CR>
nmap     <silent> ,,    :nohl<CR>

noremap <C-D>   <C-W>
noremap <Down>  <NOP>
noremap <Left>  <NOP>
noremap <Right> <NOP>
noremap <Up>    <NOP>

runtime macros/matchit.vim

ia dumper Dumper
ia prinnt print
ia repositry repository
ia repo repository
ia MW Magnus Woldrich<CR>L<magnus@trapd00r.se>

" Dump output from external cmd to new buffer
cab ! new<CR>:r !

set formatprg=perl\ -MText::Autoformat\ -e'autoformat'
set formatoptions=qro

function! ToggleRelativeAbsoluteNumber()
  if &number
    set relativenumber
  else
    set number
  endif
endfunction

"" for dvorak on the typematrix
"noremap d h
"noremap h j
"noremap t k
"noremap n l
"noremap k d
"noremap l n
"noremap j t
"noremap ^Wd ^Wh
"noremap ^Wh ^Wj
"noremap ^Wt ^Wk
"noremap ^Wn ^Wl:
"
"map , :noh<CR>
"map <space> i<space><esc><right>
"map <C-c><C-c> :w<CR>:make<CR> " add to .vimrc
"map <C-c><C-v> :!./program<CR> " do this by hand every time
"map q :q<CR> " quit one buffer fast
"map Q :qa<CR> " GET ME OUT OF EVERY BUFFER NOW (unless some are unsaved)
