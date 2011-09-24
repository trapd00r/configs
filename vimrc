"    File: $HOME/etc/vimrc
"  Author: Magnus Woldrich <m@japh.se>
" Created: 2009-04-24
" Updated: 2011-07-27 12:34:02
"    What: Highly optimized for Perl, C, Viml and Lua hacking.

if !isdirectory('/tmp/scp1')
  call mkdir("/tmp/scp1", "", 0700)
endif

for f in split(globpath(&runtimepath, '_*.vim'), "\n")
  if(f !~ '_highlights.vim')
    exe 'source ' . f
  endif
endfor

" THIS IS HORRIBLE EVILNESS
"set gdefault 

set nocompatible
set autoread
set autochdir
set autoindent
set backspace=start,indent,eol
set cmdheight=2
set complete=.,w,b,u,t,i,d,k,kspell
set cinoptions=:0,l1,t0,g0,(0
set cinwords=if,else,elsif,while,do,for,foreach,given,when,switch,case
set colorcolumn=+1,+2
set completeopt+=menuone
set cscopeprg=/usr/local/bin/cscope
set cscopetag
set cscopetagorder=0
set cscopeverbose
set cursorline
set define=[^A-Za-z_]
set diffopt=filler,iwhite,context:4,vertical
set display+=lastline,uhex
set expandtab
set fillchars=vert:│
set foldmethod=marker
set foldenable
set formatoptions=tcrqln1
set grepprg=ack\ -a
set guioptions-=m
set guioptions-=T
set helpheight=60
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
"let &lcs = "tab:\273\255,trail:\267,eol:\266,nbsp:\u23b5,precedes:\u2190,extends:\u2192"
set listchars=tab:»\ ,trail:·,eol:¶,nbsp:⎵,precedes:←,extends:→ sbr=↪
set magic
set makeprg=/usr/bin/make
set matchtime=2
set maxmapdepth=500
set matchpairs+==:;
set matchpairs+=<:>
set matchtime=10
set maxfuncdepth=1000
set maxmemtot=200000
set modeline
set modelines=2
set nobackup
set nocscopeverbose
set noequalalways
set noerrorbells
set nostartofline
set noswapfile
set nowritebackup
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
set showmatch
set showmode
set smartcase
set smarttab
set synmaxcol=160
set scrolloff=5
set tabpagemax=50
set tabstop=2
set t_Co=256
set timeout
set timeoutlen=3000
set ttimeoutlen=50
set textwidth=80
set title
set ttyfast
set undofile
set undolevels=512
set undodir=/mnt/Docs/Backup/undo
set visualbell t_vb=
set viminfo=h,'100,\"100,:20,%,n~/var/vim/viminfo
set virtualedit=block
set wildchar=<Tab>
set wildmode=list:longest,full
set wildignore=*.swp,*.bak,*~,blib,*.o,*.png,*.jpe?g
set winfixwidth
set winfixheight
set winwidth=80
set winminwidth=80
set whichwrap=b,s,h,l,<,>

set nomore

runtime macros/matchit.vim
syntax on
setlocal nospell spelllang=en_us

if $TERM == 'linux'
  let &t_Co = 8
  color peachpuff
  set nolist
  set colorcolumn+=81
  hi ColorColumn term=none  cterm=none ctermbg=3
  hi CursorLine  term=none  cterm=none ctermbg=none
else
  color neverland-ansi
endif

exe 'source ' . split($VIMRUNTIME, ':')[0] . '/_highlights.vim'

call pathogen#runtime_append_all_bundles()
