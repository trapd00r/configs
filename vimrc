" Highly optimized .vimrc for Perl, C, Lua hacking
" 2009 - 2011 Magnus Woldrich < http://github.com/trapd00r/ >

source /home/scp1/.vim/functions.vim
source /home/scp1/.vim/filetypes.vim
source /home/scp1/.vim/abbrevations.vim
source /home/scp1/.vim/mappings.vim

set nocp

set autoread
set autochdir
set autoindent
set cmdheight=2
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
set foldmethod=manual
set foldenable
set foldlevelstart=99
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
set listchars=trail:⋅
set listchars+=tab:→\ ,eol:⋅
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
set nostartofline
set noswapfile
set nowb
set nowrap
set nrformats=alpha,octal,hex
set numberwidth=2
set pastetoggle=<F42>
set preserveindent

set printoptions=paper:A4,syntax:n,wrap:y,header:0,number:y,duplex:off
set printoptions+=left:4,right:4,top:2,bottom:2
set printfont=-windows-montecarlo-medium-r-normal--11-110-72-72-c-60-microsoft-cp1252
set printmbfont=r:-windows-montecarlo-medium-r-normal--11-110-72-72-c-60-microsoft-cp1252
set printmbfont+=b:-windows-montecarlo-bold-r-normal--11-110-72-72-c-60-microsoft-cp1252
set printmbfont+=i:-windows-montecarlo-medium-r-normal--11-110-72-72-c-60-microsoft-cp1252

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
set splitright
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
set virtualedit=block
set wildchar=<Tab>
set wildmode=list:longest,full
set wildignore=*.swp,*.bak,*~,blib,*.o
set winfixwidth
set whichwrap=b,s,h,l,<,>

set nomore

call pathogen#runtime_append_all_bundles()
runtime macros/matchit.vim
syntax on
setlocal nospell spelllang=en_us

colorscheme neverland-ansi
hi CursorLine term=none cterm=none

syn match wsEOL display '\v[ ]+$' conceal cchar=O

hi wsEOL ctermfg=196 cterm=bold
