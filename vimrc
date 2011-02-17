" Highly optimized .vimrc for Perl, C, Lua hacking
" 2009 - 2011 Magnus Woldrich < http://github.com/trapd00r/ >

set nocp
set hidden
set grepprg=ack\ -a
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
set autochdir
set wildchar=<Tab>
set wildmode=list:longest,full
set wildmode=longest,list
set wildignore=*.swp,*.bak,*.un~


au BufRead,BufNewFile *.markdown set ft=md
au BufRead,BufNewFile *.md set ft=md

au BufWritePost *.{sh,pl} silent exe
autocmd! BufNewFile * silent! 0r ~/configs/vim/templates/template.%:e

au      FileType pl,pm,t set filetype=perl
au      FileType perl :noremap K :!perldoc <cword> <bar><bar> perldoc -f <cword><cr>
au!     FileType perl :noremap <leader>c
    \ :!time perl -Mwarnings::unused -MVi::QuickFix -c %<cr>

" To set some file type specific settings
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
map <C-h> <C-w><Left> map <C-j> <C-w><Down> map <C-J> <C-W>j<C-W>_


map <C-K> <C-W>k<C-W>_
map <C-k> <C-w><Up>
map @ I#

nmap <silent>  ;s  :call ToggleSyntax()<CR>
nmap <silent> \sp :set syn=perl<CR>:syntax sync fromstart<CR>
nmap <Space> 10j


nnoremap <C-n> :bnext<CR>
nnoremap <C-p> :bprevious<CR>
nnoremap <leader>d :buffers<CR>:buffer<Space>
nnoremap <Leader>l :ls<CR>
nnoremap <Leader>g :e#<CR>
nnoremap <Leader>1 :1b<CR>
nnoremap <Leader>2 :2b<CR>
nnoremap <Leader>3 :3b<CR>
nnoremap <Leader>4 :4b<CR>
nnoremap <Leader>5 :5b<CR>
nnoremap <Leader>6 :6b<CR>
nnoremap <Leader>7 :7b<CR>
nnoremap <Leader>8 :8b<CR>
nnoremap <Leader>9 :9b<CR>
nnoremap <Leader>0 :10b<CR>

nnoremap ; :
nnoremap <leader>e iuse Data::Dumper;<CR>$Data::Dumper::Terse<TAB><TAB> = 1;<CR>$Data::Dumper::Indent<TAB><TAB> = 1;<CR>$Data::Dumper::Useqq<TAB><TAB> = 1;<CR>$Data::Dumper::Deparse<TAB> = 1;<CR>$Data::Dumper::Quotekeys = 0;<CR>$Data::Dumper::Sortkeys  = 1;<CR><CR><ESC>
nnoremap <leader>f :set paste<CR>i
nnoremap <leader>n :call ToggleRelativeAbsoluteNumber()<CR>
nnoremap <leader>p i=pod<CR><CR>=head1 NAME<CR><CR>=head1 SYNOPSIS<CR><CR>=head1 DESCRIPTION<CR><CR>=head1 EXPORTS<CR><CR>None by default.<CR><CR>=head1 FUNCTIONS<CR><CR>=head1 AUTHOR<CR><CR><TAB>Magnus Woldrich<CR>CPAN ID: WOLDRICH<CR>magnus@trapd00r.se<CR>http://japh.se<CR><CR>=head1 CONTRIBUTORS<CR><CR>None required yet.<CR><CR>=head1 COPYRIGHT<CR><CR>Copyright 2011 B<THIS PROGRAM>s L</AUTHOR> and L</CONTRIBUTORS> as listed above.<CR><CR>=head1 LICENSE<CR><CR>This program is free software; you may redistribute it and/or modify it under the same terms as Perl itself.<CR><CR>=cut<CR><ESC>
nnoremap <leader>s :%s/\s\+$//<cr>:let @/=''<CR>
nnoremap <leader>t :e /home/scp1/doc/TODO<CR>
nnoremap <leader>v V`]

" I like choice
nnoremap <silent> <C-l> :nohl<CR>
nmap     <silent> ,/    :nohl<CR>
nmap     <silent> ,,    :nohl<CR>

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
" Dump output from external command in new buffer
cab ! new<CR>:r !
" Force delete a buffer, to be used with ^
nnoremap <leader>a :bdelete!<CR>

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

hi x016_Grey0 ctermfg=16 guifg=#000000
hi x017_NavyBlue ctermfg=17 guifg=#00005f
hi x018_DarkBlue ctermfg=18 guifg=#000087
hi x019_Blue3 ctermfg=19 guifg=#0000af
hi x020_Blue3 ctermfg=20 guifg=#0000d7
hi x021_Blue1 ctermfg=21 guifg=#0000ff
hi x022_DarkGreen ctermfg=22 guifg=#005f00
hi x023_DeepSkyBlue4 ctermfg=23 guifg=#005f5f
hi x024_DeepSkyBlue4 ctermfg=24 guifg=#005f87
hi x025_DeepSkyBlue4 ctermfg=25 guifg=#005faf
hi x026_DodgerBlue3 ctermfg=26 guifg=#005fd7
hi x027_DodgerBlue2 ctermfg=27 guifg=#005fff
hi x028_Green4 ctermfg=28 guifg=#008700
hi x029_SpringGreen4 ctermfg=29 guifg=#00875f
hi x030_Turquoise4 ctermfg=30 guifg=#008787
hi x031_DeepSkyBlue3 ctermfg=31 guifg=#0087af
hi x032_DeepSkyBlue3 ctermfg=32 guifg=#0087d7
hi x033_DodgerBlue1 ctermfg=33 guifg=#0087ff
hi x034_Green3 ctermfg=34 guifg=#00af00
hi x035_SpringGreen3 ctermfg=35 guifg=#00af5f
hi x036_DarkCyan ctermfg=36 guifg=#00af87
hi x037_LightSeaGreen ctermfg=37 guifg=#00afaf
hi x038_DeepSkyBlue2 ctermfg=38 guifg=#00afd7
hi x039_DeepSkyBlue1 ctermfg=39 guifg=#00afff
hi x040_Green3 ctermfg=40 guifg=#00d700
hi x041_SpringGreen3 ctermfg=41 guifg=#00d75f
hi x042_SpringGreen2 ctermfg=42 guifg=#00d787
hi x043_Cyan3 ctermfg=43 guifg=#00d7af
hi x044_DarkTurquoise ctermfg=44 guifg=#00d7d7
hi x045_Turquoise2 ctermfg=45 guifg=#00d7ff
hi x046_Green1 ctermfg=46 guifg=#00ff00
hi x047_SpringGreen2 ctermfg=47 guifg=#00ff5f
hi x048_SpringGreen1 ctermfg=48 guifg=#00ff87
hi x049_MediumSpringGreen ctermfg=49 guifg=#00ffaf
hi x050_Cyan2 ctermfg=50 guifg=#00ffd7
hi x051_Cyan1 ctermfg=51 guifg=#00ffff
hi x052_DarkRed ctermfg=52 guifg=#5f0000
hi x053_DeepPink4 ctermfg=53 guifg=#5f005f
hi x054_Purple4 ctermfg=54 guifg=#5f0087
hi x055_Purple4 ctermfg=55 guifg=#5f00af
hi x056_Purple3 ctermfg=56 guifg=#5f00d7
hi x057_BlueViolet ctermfg=57 guifg=#5f00ff
hi x058_Orange4 ctermfg=58 guifg=#5f5f00
hi x059_Grey37 ctermfg=59 guifg=#5f5f5f
hi x060_MediumPurple4 ctermfg=60 guifg=#5f5f87
hi x061_SlateBlue3 ctermfg=61 guifg=#5f5faf
hi x062_SlateBlue3 ctermfg=62 guifg=#5f5fd7
hi x063_RoyalBlue1 ctermfg=63 guifg=#5f5fff
hi x064_Chartreuse4 ctermfg=64 guifg=#5f8700
hi x065_DarkSeaGreen4 ctermfg=65 guifg=#5f875f
hi x066_PaleTurquoise4 ctermfg=66 guifg=#5f8787
hi x067_SteelBlue ctermfg=67 guifg=#5f87af
hi x068_SteelBlue3 ctermfg=68 guifg=#5f87d7
hi x069_CornflowerBlue ctermfg=69 guifg=#5f87ff
hi x070_Chartreuse3 ctermfg=70 guifg=#5faf00
hi x071_DarkSeaGreen4 ctermfg=71 guifg=#5faf5f
hi x072_CadetBlue ctermfg=72 guifg=#5faf87
hi x073_CadetBlue ctermfg=73 guifg=#5fafaf
hi x074_SkyBlue3 ctermfg=74 guifg=#5fafd7
hi x075_SteelBlue1 ctermfg=75 guifg=#5fafff
hi x076_Chartreuse3 ctermfg=76 guifg=#5fd700
hi x077_PaleGreen3 ctermfg=77 guifg=#5fd75f
hi x078_SeaGreen3 ctermfg=78 guifg=#5fd787
hi x079_Aquamarine3 ctermfg=79 guifg=#5fd7af
hi x080_MediumTurquoise ctermfg=80 guifg=#5fd7d7
hi x081_SteelBlue1 ctermfg=81 guifg=#5fd7ff
hi x082_Chartreuse2 ctermfg=82 guifg=#5fff00
hi x083_SeaGreen2 ctermfg=83 guifg=#5fff5f
hi x084_SeaGreen1 ctermfg=84 guifg=#5fff87
hi x085_SeaGreen1 ctermfg=85 guifg=#5fffaf
hi x086_Aquamarine1 ctermfg=86 guifg=#5fffd7
hi x087_DarkSlateGray2 ctermfg=87 guifg=#5fffff
hi x088_DarkRed ctermfg=88 guifg=#870000
hi x089_DeepPink4 ctermfg=89 guifg=#87005f
hi x090_DarkMagenta ctermfg=90 guifg=#870087
hi x091_DarkMagenta ctermfg=91 guifg=#8700af
hi x092_DarkViolet ctermfg=92 guifg=#8700d7
hi x093_Purple ctermfg=93 guifg=#8700ff
hi x094_Orange4 ctermfg=94 guifg=#875f00
hi x095_LightPink4 ctermfg=95 guifg=#875f5f
hi x096_Plum4 ctermfg=96 guifg=#875f87
hi x097_MediumPurple3 ctermfg=97 guifg=#875faf
hi x098_MediumPurple3 ctermfg=98 guifg=#875fd7
hi x099_SlateBlue1 ctermfg=99 guifg=#875fff
hi x100_Yellow4 ctermfg=100 guifg=#878700
hi x101_Wheat4 ctermfg=101 guifg=#87875f
hi x102_Grey53 ctermfg=102 guifg=#878787
hi x103_LightSlateGrey ctermfg=103 guifg=#8787af
hi x104_MediumPurple ctermfg=104 guifg=#8787d7
hi x105_LightSlateBlue ctermfg=105 guifg=#8787ff
hi x106_Yellow4 ctermfg=106 guifg=#87af00
hi x107_DarkOliveGreen3 ctermfg=107 guifg=#87af5f
hi x108_DarkSeaGreen ctermfg=108 guifg=#87af87
hi x109_LightSkyBlue3 ctermfg=109 guifg=#87afaf
hi x110_LightSkyBlue3 ctermfg=110 guifg=#87afd7
hi x111_SkyBlue2 ctermfg=111 guifg=#87afff
hi x112_Chartreuse2 ctermfg=112 guifg=#87d700
hi x113_DarkOliveGreen3 ctermfg=113 guifg=#87d75f
hi x114_PaleGreen3 ctermfg=114 guifg=#87d787
hi x115_DarkSeaGreen3 ctermfg=115 guifg=#87d7af
hi x116_DarkSlateGray3 ctermfg=116 guifg=#87d7d7
hi x117_SkyBlue1 ctermfg=117 guifg=#87d7ff
hi x118_Chartreuse1 ctermfg=118 guifg=#87ff00
hi x119_LightGreen ctermfg=119 guifg=#87ff5f
hi x120_LightGreen ctermfg=120 guifg=#87ff87
hi x121_PaleGreen1 ctermfg=121 guifg=#87ffaf
hi x122_Aquamarine1 ctermfg=122 guifg=#87ffd7
hi x123_DarkSlateGray1 ctermfg=123 guifg=#87ffff
hi x124_Red3 ctermfg=124 guifg=#af0000
hi x125_DeepPink4 ctermfg=125 guifg=#af005f
hi x126_MediumVioletRed ctermfg=126 guifg=#af0087
hi x127_Magenta3 ctermfg=127 guifg=#af00af
hi x128_DarkViolet ctermfg=128 guifg=#af00d7
hi x129_Purple ctermfg=129 guifg=#af00ff
hi x130_DarkOrange3 ctermfg=130 guifg=#af5f00
hi x131_IndianRed ctermfg=131 guifg=#af5f5f
hi x132_HotPink3 ctermfg=132 guifg=#af5f87
hi x133_MediumOrchid3 ctermfg=133 guifg=#af5faf
hi x134_MediumOrchid ctermfg=134 guifg=#af5fd7
hi x135_MediumPurple2 ctermfg=135 guifg=#af5fff
hi x136_DarkGoldenrod ctermfg=136 guifg=#af8700
hi x137_LightSalmon3 ctermfg=137 guifg=#af875f
hi x138_RosyBrown ctermfg=138 guifg=#af8787
hi x139_Grey63 ctermfg=139 guifg=#af87af
hi x140_MediumPurple2 ctermfg=140 guifg=#af87d7
hi x141_MediumPurple1 ctermfg=141 guifg=#af87ff
hi x142_Gold3 ctermfg=142 guifg=#afaf00
hi x143_DarkKhaki ctermfg=143 guifg=#afaf5f
hi x144_NavajoWhite3 ctermfg=144 guifg=#afaf87
hi x145_Grey69 ctermfg=145 guifg=#afafaf
hi x146_LightSteelBlue3 ctermfg=146 guifg=#afafd7
hi x147_LightSteelBlue ctermfg=147 guifg=#afafff
hi x148_Yellow3 ctermfg=148 guifg=#afd700
hi x149_DarkOliveGreen3 ctermfg=149 guifg=#afd75f
hi x150_DarkSeaGreen3 ctermfg=150 guifg=#afd787
hi x151_DarkSeaGreen2 ctermfg=151 guifg=#afd7af
hi x152_LightCyan3 ctermfg=152 guifg=#afd7d7
hi x153_LightSkyBlue1 ctermfg=153 guifg=#afd7ff
hi x154_GreenYellow ctermfg=154 guifg=#afff00
hi x155_DarkOliveGreen2 ctermfg=155 guifg=#afff5f
hi x156_PaleGreen1 ctermfg=156 guifg=#afff87
hi x157_DarkSeaGreen2 ctermfg=157 guifg=#afffaf
hi x158_DarkSeaGreen1 ctermfg=158 guifg=#afffd7
hi x159_PaleTurquoise1 ctermfg=159 guifg=#afffff
hi x160_Red3 ctermfg=160 guifg=#d70000
hi x161_DeepPink3 ctermfg=161 guifg=#d7005f
hi x162_DeepPink3 ctermfg=162 guifg=#d70087
hi x163_Magenta3 ctermfg=163 guifg=#d700af
hi x164_Magenta3 ctermfg=164 guifg=#d700d7
hi x165_Magenta2 ctermfg=165 guifg=#d700ff
hi x166_DarkOrange3 ctermfg=166 guifg=#d75f00
hi x167_IndianRed ctermfg=167 guifg=#d75f5f
hi x168_HotPink3 ctermfg=168 guifg=#d75f87
hi x169_HotPink2 ctermfg=169 guifg=#d75faf
hi x170_Orchid ctermfg=170 guifg=#d75fd7
hi x171_MediumOrchid1 ctermfg=171 guifg=#d75fff
hi x172_Orange3 ctermfg=172 guifg=#d78700
hi x173_LightSalmon3 ctermfg=173 guifg=#d7875f
hi x174_LightPink3 ctermfg=174 guifg=#d78787
hi x175_Pink3 ctermfg=175 guifg=#d787af
hi x176_Plum3 ctermfg=176 guifg=#d787d7
hi x177_Violet ctermfg=177 guifg=#d787ff
hi x178_Gold3 ctermfg=178 guifg=#d7af00
hi x179_LightGoldenrod3 ctermfg=179 guifg=#d7af5f
hi x180_Tan ctermfg=180 guifg=#d7af87
hi x181_MistyRose3 ctermfg=181 guifg=#d7afaf
hi x182_Thistle3 ctermfg=182 guifg=#d7afd7
hi x183_Plum2 ctermfg=183 guifg=#d7afff
hi x184_Yellow3 ctermfg=184 guifg=#d7d700
hi x185_Khaki3 ctermfg=185 guifg=#d7d75f
hi x186_LightGoldenrod2 ctermfg=186 guifg=#d7d787
hi x187_LightYellow3 ctermfg=187 guifg=#d7d7af
hi x188_Grey84 ctermfg=188 guifg=#d7d7d7
hi x189_LightSteelBlue1 ctermfg=189 guifg=#d7d7ff
hi x190_Yellow2 ctermfg=190 guifg=#d7ff00
hi x191_DarkOliveGreen1 ctermfg=191 guifg=#d7ff5f
hi x192_DarkOliveGreen1 ctermfg=192 guifg=#d7ff87
hi x193_DarkSeaGreen1 ctermfg=193 guifg=#d7ffaf
hi x194_Honeydew2 ctermfg=194 guifg=#d7ffd7
hi x195_LightCyan1 ctermfg=195 guifg=#d7ffff
hi x196_Red1 ctermfg=196 guifg=#ff0000
hi x197_DeepPink2 ctermfg=197 guifg=#ff005f
hi x198_DeepPink1 ctermfg=198 guifg=#ff0087
hi x199_DeepPink1 ctermfg=199 guifg=#ff00af
hi x200_Magenta2 ctermfg=200 guifg=#ff00d7
hi x201_Magenta1 ctermfg=201 guifg=#ff00ff
hi x202_OrangeRed1 ctermfg=202 guifg=#ff5f00
hi x203_IndianRed1 ctermfg=203 guifg=#ff5f5f
hi x204_IndianRed1 ctermfg=204 guifg=#ff5f87
hi x205_HotPink ctermfg=205 guifg=#ff5faf
hi x206_HotPink ctermfg=206 guifg=#ff5fd7
hi x207_MediumOrchid1 ctermfg=207 guifg=#ff5fff
hi x208_DarkOrange ctermfg=208 guifg=#ff8700
hi x209_Salmon1 ctermfg=209 guifg=#ff875f
hi x210_LightCoral ctermfg=210 guifg=#ff8787
hi x211_PaleVioletRed1 ctermfg=211 guifg=#ff87af
hi x212_Orchid2 ctermfg=212 guifg=#ff87d7
hi x213_Orchid1 ctermfg=213 guifg=#ff87ff
hi x214_Orange1 ctermfg=214 guifg=#ffaf00
hi x215_SandyBrown ctermfg=215 guifg=#ffaf5f
hi x216_LightSalmon1 ctermfg=216 guifg=#ffaf87
hi x217_LightPink1 ctermfg=217 guifg=#ffafaf
hi x218_Pink1 ctermfg=218 guifg=#ffafd7
hi x219_Plum1 ctermfg=219 guifg=#ffafff
hi x220_Gold1 ctermfg=220 guifg=#ffd700
hi x221_LightGoldenrod2 ctermfg=221 guifg=#ffd75f
hi x222_LightGoldenrod2 ctermfg=222 guifg=#ffd787
hi x223_NavajoWhite1 ctermfg=223 guifg=#ffd7af
hi x224_MistyRose1 ctermfg=224 guifg=#ffd7d7
hi x225_Thistle1 ctermfg=225 guifg=#ffd7ff
hi x226_Yellow1 ctermfg=226 guifg=#ffff00
hi x227_LightGoldenrod1 ctermfg=227 guifg=#ffff5f
hi x228_Khaki1 ctermfg=228 guifg=#ffff87
hi x229_Wheat1 ctermfg=229 guifg=#ffffaf
hi x230_Cornsilk1 ctermfg=230 guifg=#ffffd7
hi x231_Grey100 ctermfg=231 guifg=#ffffff
hi x232_Grey3 ctermfg=232 guifg=#080808
hi x233_Grey7 ctermfg=233 guifg=#121212
hi x234_Grey11 ctermfg=234 guifg=#1c1c1c
hi x235_Grey15 ctermfg=235 guifg=#262626
hi x236_Grey19 ctermfg=236 guifg=#303030
hi x237_Grey23 ctermfg=237 guifg=#3a3a3a
hi x238_Grey27 ctermfg=238 guifg=#444444
hi x239_Grey30 ctermfg=239 guifg=#4e4e4e
hi x240_Grey35 ctermfg=240 guifg=#585858
hi x241_Grey39 ctermfg=241 guifg=#626262
hi x242_Grey42 ctermfg=242 guifg=#6c6c6c
hi x243_Grey46 ctermfg=243 guifg=#767676
hi x244_Grey50 ctermfg=244 guifg=#808080
hi x245_Grey54 ctermfg=245 guifg=#8a8a8a
hi x246_Grey58 ctermfg=246 guifg=#949494
hi x247_Grey62 ctermfg=247 guifg=#9e9e9e
hi x248_Grey66 ctermfg=248 guifg=#a8a8a8
hi x249_Grey70 ctermfg=249 guifg=#b2b2b2
hi x250_Grey74 ctermfg=250 guifg=#bcbcbc
hi x251_Grey78 ctermfg=251 guifg=#c6c6c6
hi x252_Grey82 ctermfg=252 guifg=#d0d0d0
hi x253_Grey85 ctermfg=253 guifg=#dadada
hi x254_Grey89 ctermfg=254 guifg=#e4e4e4
hi x255_Grey93 ctermfg=255 guifg=#eeeeee

