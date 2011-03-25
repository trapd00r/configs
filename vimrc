" Highly optimized .vimrc for Perl, C, Lua hacking
" 2009 - 2011 Magnus Woldrich < http://github.com/trapd00r/ >

source ~/.vim/filetypes.vim
source ~/.vim/abbrevations.vim
source ~/.vim/functions.vim
source ~/.vim/mappings.vim

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
set so=5
set splitbelow
set statusline=%<[%02n]\ %F%(\ %m%h%w%y%r%)\ %a%=\ %8l,%c%V/%L\ (%P)\ [%08O:%02B]
set tabpagemax=50
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
runtime macros/matchit.vim
syntax on
setlocal nospell spelllang=en_us
colorscheme neverland-ansi_bg
hi CursorLine term=none cterm=none
