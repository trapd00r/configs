"    File: $HOME/etc/vimrc
"  Author: Magnus Woldrich <m@japh.se>
" Created: 2009-04-24
" Updated: 2011-07-02 17:48:48
"    What: Highly optimized for Perl, C, Viml and Lua hacking.

if !isdirectory('/tmp/scp1')
  call mkdir("/tmp/scp1", "", 0700)
endif

if !exists('g:vim_functions_loaded')
  source /home/scp1/etc/vim/functions.vim
endif

source /home/scp1/etc/vim/ftdetect.vim
source /home/scp1/etc/vim/abbrevations.vim
source /home/scp1/etc/vim/mappings.vim


set nocp

set autoread
set autochdir
set autoindent
set backspace=start,indent,eol
set cmdheight=2
set complete=.,w,b,u,t,i,d,k,kspell
set cinoptions=:0,l1,t0,g0,(0
set cinwords=if,else,elsif,while,do,for,foreach,given,when,switch,case
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
"set foldmethod=manual
set foldenable
"set foldlevelstart=99
set formatoptions=tcrqln1

" THIS IS HORRIBLE EVILNESS
"set gdefault 
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
"set listchars=trail:⋅
"set listchars+=tab:→\ ,eol:⋅
"let &lcs = "tab:\273\255,trail:\267,eol:\266,nbsp:\u23b5,precedes:\u2190,extends:\u2192"
set listchars=tab:»­,trail:·,eol:¶,nbsp:⎵,precedes:←,extends:→ sbr=↪
set magic
set makeprg=/usr/bin/make
set mat=2
set matchpairs+==:;
set matchpairs+=<:>
set matchtime=10
set maxfuncdepth=1000
set maxmemtot=200000
set modeline
set modelines=2
set nobackup
set nocsverb
"set noequalalways
set noerrorbells
set nostartofline
set noswapfile
set nowb
set nowrap
set nrformats=alpha,octal,hex
set numberwidth=2
set pastetoggle=<F42>
set preserveindent

set printoptions=paper:A4,syntax:n,wrap:y,header:0,number:n,duplex:off
set printoptions+=left:2,right:2,top:2,bottom:2
set printfont=-windows-montecarlo-medium-r-normal--11-110-72-72-c-60-microsoft-cp1252
set printmbfont=r:-windows-montecarlo-medium-r-normal--11-110-72-72-c-60-microsoft-cp1252
set printmbfont+=b:-windows-montecarlo-bold-r-normal--11-110-72-72-c-60-microsoft-cp1252
set printmbfont+=i:-windows-montecarlo-medium-r-normal--11-110-72-72-c-60-microsoft-cp1252

set pumheight=10
set relativenumber
set report=0
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
set synmaxcol=160
set so=5
"set splitright
set tabpagemax=50
set ts=2
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
set viminfo='10,\"100,:20,%,n~/var/vim/viminfo
set virtualedit=block
set wildchar=<Tab>
set wildmode=list:longest,full
set wildignore=*.swp,*.bak,*~,blib,*.o
"set winfixwidth
set whichwrap=b,s,h,l,<,>

set nomore

call pathogen#runtime_append_all_bundles()
runtime macros/matchit.vim
syntax on
setlocal nospell spelllang=en_us

if $TERM == 'linux'
  let &t_Co = 8
  color peachpuff
  set nolist
  set colorcolumn+=81
  hi ColorColumn term=none cterm=none ctermbg=3
  hi CursorLine  term=none  cterm=none ctermbg=none
else
  color neverland-ansi
endif


syn match wsEOL display '\v[ ]+$' conceal cchar=O

hi wsEOL ctermfg=196 cterm=bold
