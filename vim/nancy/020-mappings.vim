"    File: $HOME/etc/mappings.vim
"  Author: Magnus Woldrich <m@japh.se>
" Updated: 2012-02-04 13:51:07

let mapleader = ';'

map <C-s> :call RemoveTrailingCrap()<cr>
map <C-s> :call ShowFuncName()<cr>
nnoremap b! :b1<cr>
nnoremap b' :b2<cr>
nnoremap b# :b3<cr>
nnoremap b$ :b4<cr>
nnoremap b% :b5<cr>
nnoremap b& :b6<cr>
nnoremap b/ :b7<cr>
nnoremap b( :b8<cr>
nnoremap b) :b9<cr>
nnoremap b= :b10<cr>

nnoremap <silent> <leader>å :%s/\v\d+/\=submatch(0) + 1/g<CR>  :normal gg<CR>
"nmap <leader>O :%w >> ~/vim_output<CR>
"nmap <leader>o :exec ':.w >> ' . eval(string( xclipboard_pipe_path ))<CR>

" searching                                                                  {{{
"nnoremap <silent> ! *:call HL_Search_Cword()<CR>
"  :silent !printf '\e]12;\#ff0000'
"nnoremap <silent> # #:call HL_Search_Cword()<CR>
"  :silent !printf '\e]12;\#56ff00'
"nnoremap <silent> * *:call HL_Search_Cword()<CR>
"  :silent !printf '\e]12;\#ff33'
"nnoremap <silent> N N:call HL_Search_Cword()<CR>
"  :silent !printf '\e]12;\#030407'
"nnoremap <silent> n n:call HL_Search_Cword()<CR>
"  :silent !printf '\e]12;\#030407
" user interface                                                             {{{
"nnoremap <CR>   za
"nnoremap '      `        " switch ' and ` ...
nnoremap `      '        " ... and do the right thing
cmap     qq     qa!<CR>  " quit really, really fast
nnoremap ``     ''       " switch those two as well
nnoremap ''     ``       " '' now goes back to where cursor were before mark
nmap     <C-9>  <C-]>    " my ALT key is all jelly
nmap     Y      y$       " do what Y is supposed to do; d$ <=> D etc

cnoremap $h     e ~/     " quick edit ~/
cnoremap $d     e ~/dev  " quick edit ~/dev
cnoremap $.     e .      " quick edit ./

map      ö      <C-E><C-E><C-E><C-E><C-E><C-E><C-E><C-E><C-E><C-E><C-E>
map      Ö      <C-Y><C-Y><C-Y><C-Y><C-Y><C-Y><C-Y><C-Y><C-Y><C-Y><C-Y>
" }}}
" syntax                                                                     {{{
if &filetype == 'perl'
  nnoremap <C-h> :!perl -MVi::QuickFix='/mnt/Docs/Backup/vim_quickfix_err/%.err' -c %<CR>:cf<CR>
  nnoremap <silent> _t :%!perltidy -q<Enter>
  vnoremap <silent> _t :!perltidy -q<Enter>

  nnoremap <silent> _p :%!perlcritic -q<Enter>
  vnoremap <silent> _p :!perlcritic -q<Enter>
endif

nmap <silent> <leader>sp  :set syn=perl   <CR> :syntax sync fromstart <CR>
nmap <silent> <leader>ss  :set syn=sh     <CR> :syntax sync fromstart <CR>
nmap <silent> <leader>sv  :set syn=vim    <CR> :syntax sync fromstart <CR>
nmap <silent> <leader>sz  :set syn=zsh    <CR> :syntax sync fromstart <CR>
nmap <silent> <leader>sc  :set syn=config <CR> :syntax sync fromstart <CR>
nmap <silent> <leader>sf  :set syn=conf   <CR> :syntax sync fromstart <CR>
" }}}
" window management                                                          {{{
map <C-J> <C-W>j<C-W>_
map <C-h> <C-w><Left>
map <C-h> <C-w><Left>
map <C-h> <C-w><Left>
map <C-j> <C-w><Down>

nnoremap <C-W>J :exe 'resize ' . winheight(0) / 2<CR>
nnoremap <C-W>K :exe 'resize ' . winheight(0) * 2<CR>
"map =  <C-W>-
"map \| :vsplit<CR>
" }}}
" text transformation                                                        {{{
nmap     <leader>cl :left<CR>
nmap     <leader>cr :right<CR>
nmap     <leader>cc :center<CR>
nnoremap <leader>t  :call TitleCaseCenter()<CR>
vnoremap S :        sort<CR>

" make those behave like ci' , ci"
nnoremap ci( f(ci(
nnoremap ci{ f{ci{
nnoremap ci[ f[ci[

vnoremap ci( f(ci(
vnoremap ci{ f{ci{
vnoremap ci[ f[ci[

" Titlecase The Current Line, thank you
nnoremap U          :s/\v[a-zåäö]+/\u&/g<CR>

" allow the use of TAB for jumping between matching pairs
" note https://github.com/trapd00r/configs/commit/d7dc036e#L0R74
nnoremap <TAB> %

"}}}
" movement                                                                   {{{
nnoremap J  10j
nnoremap K  10k
vnoremap J  10j
vnoremap K  10k

inoremap jj <ESC>
inoremap jk <ESC>
inoremap £1 ()<ESC>i
inoremap £2 []<ESC>i
inoremap £3 {<ESC>o}<ESC>O
inoremap £4 {}<ESC>i
inoremap £Q ""<ESC>i
inoremap £q ''<ESC>i
nnoremap d= f=d$a=
nnoremap d> f>d$a>
nnoremap dad /\v^\=head/<CR> W d$xa

nnoremap [7~ :source %<CR>
nnoremap [2~ :source %<CR>

nnoremap [29~ :call AddFoldMarkers()<CR>

" jumping to sub definition
"nnoremap <buffer> ]]    :<C-u>call search('^\s*sub .* {$', 'sW')<CR>
"nnoremap <buffer> [[    :<C-u>call search('^\s*sub .* {$', 'bsW')<CR>
"nnoremap <buffer> ][    :<C-u>call search('^}$', 'sW')<CR>
"nnoremap <buffer> []    :<C-u>call search('^}$', 'bsW')<CR>
" }}}
" spelling                                                                   {{{
"map [29~ z=
map ? z=
nnoremap     za zg
nnoremap     <leader><TAB> :call ToggleSpell()<CR>
" }}}
" buffers                                                                    {{{
" cd to the directory of the open buffer, if possible
map <leader>cd :cd %:p:h<CR>

nnoremap <silent> <C-l> :noh<CR><C-l>

nnoremap <C-n>     :bnext<CR>
nnoremap <C-p>     :bprev<CR>
nnoremap <leader>b :ls<CR>:buffer<space>
nnoremap <leader>g :e#<CR>
nnoremap <leader>l :ls<CR>

nnoremap <leader>1 :set ft=perl<CR>
nnoremap <leader>2 :set ft=c<CR>
nnoremap <leader>3 :set ft=lua<CR>
nnoremap <leader>4 :set ft=bash<CR>
nnoremap <leader>5 :set ft=config<CR>
nnoremap <leader>6 :set ft=vim<CR>

nnoremap <leader>7 :7b<CR>
nnoremap <leader>8 :8b<CR>
nnoremap <leader>9 :9b<CR>
nnoremap <leader>0 :10b<CR>

"nnoremap *     :1b<CR>
"nnoremap "     :2b<CR>
"nnoremap £     :3b<CR>
"nnoremap $     :4b<CR>
"nnoremap €     :5b<CR>
"nnoremap ¥     :6b<CR>
"nnoremap {     :7b<CR>
"nnoremap [     :8b<CR>
"nnoremap ]     :9b<CR>
"nnoremap <leader>a :bdelete!<CR>

nnoremap <leader>f :set paste<CR>
nnoremap <leader>s :call RemoveTrailingCrap()
nnoremap <leader>v V`]

nnoremap ,g :sil exe 'grep! -R '.shellescape("<cWORD>")." ."<CR>:cope<CR>:winc w<CR>
" }}}
" sane regex                                                                {{{
vnoremap /        /\v
" }}}
" emacs keymap in the commandline                                          {{{
cnoremap  <c-a>   <home>
cnoremap  <c-e>   <end>
cnoremap  <c-b>   <left>
cnoremap  <c-d>   <del>
cnoremap  <c-f>   <right>
cnoremap  <C-_>   <c-f>

cnoremap  <c-n>   <down>
cnoremap  <c-p>   <up>
cnoremap  <C-*>   <c-a>
" }}}
" additional commandline mappings                                            {{{
cnoremap  <c-j>   <down>
cnoremap  <c-k>   <up>
" let us get there fast from normal mode as well
nnoremap <c-j>    <down>
nnoremap <c-k>    <up>

cnoremap <C-h> <S-Left>
cnoremap <C-l> <S-Right>
"}}}
" fix xterm keys {{{
map  <Esc>[1;2A <S-Up>
map! <Esc>[1;2A <S-Up>
map  <Esc>[1;2B <S-Down>
map! <Esc>[1;2B <S-Down>
map  <Esc>[1;2C <S-Right>
map! <Esc>[1;2C <S-Right>
map  <Esc>[1;2D <S-Left>
map! <Esc>[1;2D <S-Left>
map  <Esc>[1;2F <S-End>
map! <Esc>[1;2F <S-End>
map  <Esc>[1;2H <S-Home>
map! <Esc>[1;2H <S-Home>
map  <Esc>[2;2~ <S-Insert>
map! <Esc>[2;2~ <S-Insert>
map  <Esc>[3;2~ <S-Delete>
map! <Esc>[3;2~ <S-Delete>
map  <Esc>[5;2~ <S-PageUp>
map! <Esc>[5;2~ <S-PageUp>
map  <Esc>[6;2~ <S-PageDown>
map! <Esc>[6;2~ <S-PageDown>

" Fix up M-motion keys
map  <Esc>[1;3A <M-Up>
map! <Esc>[1;3A <M-Up>
map  <Esc>[1;3B <M-Down>
map! <Esc>[1;3B <M-Down>
map  <Esc>[1;3C <M-Right>
map! <Esc>[1;3C <M-Right>
map  <Esc>[1;3D <M-Left>
map! <Esc>[1;3D <M-Left>
map  <Esc>[1;3F <M-End>
map! <Esc>[1;3F <M-End>
map  <Esc>[1;3H <M-Home>
map! <Esc>[1;3H <M-Home>
map  <Esc>[2;3~ <M-Insert>
map! <Esc>[2;3~ <M-Insert>
map  <Esc>[3;3~ <M-Delete>
map! <Esc>[3;3~ <M-Delete>
map  <Esc>[5;3~ <M-PageUp>
map! <Esc>[5;3~ <M-PageUp>
map  <Esc>[6;3~ <M-PageDown>
map! <Esc>[6;3~ <M-PageDown>

" Fix up S-M-motion keys
map  <Esc>[1;4A <S-M-Up>
map! <Esc>[1;4A <S-M-Up>
map  <Esc>[1;4B <S-M-Down>
map! <Esc>[1;4B <S-M-Down>
map  <Esc>[1;4C <S-M-Right>
map! <Esc>[1;4C <S-M-Right>
map  <Esc>[1;4D <S-M-Left>
map! <Esc>[1;4D <S-M-Left>
map  <Esc>[1;4F <S-M-End>
map! <Esc>[1;4F <S-M-End>
map  <Esc>[1;4H <S-M-Home>
map! <Esc>[1;4H <S-M-Home>
map  <Esc>[2;4~ <S-M-Insert>
map! <Esc>[2;4~ <S-M-Insert>
map  <Esc>[3;4~ <S-M-Delete>
map! <Esc>[3;4~ <S-M-Delete>
map  <Esc>[5;4~ <S-M-PageUp>
map! <Esc>[5;4~ <S-M-PageUp>
map  <Esc>[6;4~ <S-M-PageDown>
map! <Esc>[6;4~ <S-M-PageDown>

" Fix up C-motion keys
map  <Esc>[1;5A <C-Up>
map! <Esc>[1;5A <C-Up>
map  <Esc>[1;5B <C-Down>
map! <Esc>[1;5B <C-Down>
map  <Esc>[1;5C <C-Right>
map! <Esc>[1;5C <C-Right>
map  <Esc>[1;5D <C-Left>
map! <Esc>[1;5D <C-Left>
map  <Esc>[1;5F <C-End>
map! <Esc>[1;5F <C-End>
map  <Esc>[1;5H <C-Home>
map! <Esc>[1;5H <C-Home>
map  <Esc>[2;5~ <C-Insert>
map! <Esc>[2;5~ <C-Insert>
map  <Esc>[3;5~ <C-Delete>
map! <Esc>[3;5~ <C-Delete>
map  <Esc>[5;5~ <C-PageUp>
map! <Esc>[5;5~ <C-PageUp>
map  <Esc>[6;5~ <C-PageDown>
map! <Esc>[6;5~ <C-PageDown>

" Fix up S-C-motion keys
map  <Esc>[1;6A <S-C-Up>
map! <Esc>[1;6A <S-C-Up>
map  <Esc>[1;6B <S-C-Down>
map! <Esc>[1;6B <S-C-Down>
map  <Esc>[1;6C <S-C-Right>
map! <Esc>[1;6C <S-C-Right>
map  <Esc>[1;6D <S-C-Left>
map! <Esc>[1;6D <S-C-Left>
map  <Esc>[1;6F <S-C-End>
map! <Esc>[1;6F <S-C-End>
map  <Esc>[1;6H <S-C-Home>
map! <Esc>[1;6H <S-C-Home>
map  <Esc>[2;6~ <S-C-Insert>
map! <Esc>[2;6~ <S-C-Insert>
map  <Esc>[3;6~ <S-C-Delete>
map! <Esc>[3;6~ <S-C-Delete>
map  <Esc>[5;6~ <S-C-PageUp>
map! <Esc>[5;6~ <S-C-PageUp>
map  <Esc>[6;6~ <S-C-PageDown>
map! <Esc>[6;6~ <S-C-PageDown>

" Fix up M-C-motion keys
map  <Esc>[1;7A <M-C-Up>
map! <Esc>[1;7A <M-C-Up>
map  <Esc>[1;7B <M-C-Down>
map! <Esc>[1;7B <M-C-Down>
map  <Esc>[1;7C <M-C-Right>
map! <Esc>[1;7C <M-C-Right>
map  <Esc>[1;7D <M-C-Left>
map! <Esc>[1;7D <M-C-Left>
map  <Esc>[1;7F <M-C-End>
map! <Esc>[1;7F <M-C-End>
map  <Esc>[1;7H <M-C-Home>
map! <Esc>[1;7H <M-C-Home>
map  <Esc>[2;7~ <M-C-Insert>
map! <Esc>[2;7~ <M-C-Insert>
map  <Esc>[3;7~ <M-C-Delete>
map! <Esc>[3;7~ <M-C-Delete>
map  <Esc>[5;7~ <M-C-PageUp>
map! <Esc>[5;7~ <M-C-PageUp>
map  <Esc>[6;7~ <M-C-PageDown>
map! <Esc>[6;7~ <M-C-PageDown>

" Fix up S-M-C-motion keys
map  <Esc>[1;8A <S-M-C-Up>
map! <Esc>[1;8A <S-M-C-Up>
map  <Esc>[1;8B <S-M-C-Down>
map! <Esc>[1;8B <S-M-C-Down>
map  <Esc>[1;8C <S-M-C-Right>
map! <Esc>[1;8C <S-M-C-Right>
map  <Esc>[1;8D <S-M-C-Left>
map! <Esc>[1;8D <S-M-C-Left>
map  <Esc>[1;8F <S-M-C-End>
map! <Esc>[1;8F <S-M-C-End>
map  <Esc>[1;8H <S-M-C-Home>
map! <Esc>[1;8H <S-M-C-Home>
map  <Esc>[2;8~ <S-M-C-Insert>
map! <Esc>[2;8~ <S-M-C-Insert>
map  <Esc>[3;8~ <S-M-C-Delete>
map! <Esc>[3;8~ <S-M-C-Delete>
map  <Esc>[5;8~ <S-M-C-PageUp>
map! <Esc>[5;8~ <S-M-C-PageUp>
map  <Esc>[6;8~ <S-M-C-PageDown>
map! <Esc>[6;8~ <S-M-C-PageDown>

" M-[character]
map  <Esc>0 <A-0>
map! <Esc>0 <A-0>
map  <Esc>1 <A-1>
map! <Esc>1 <A-1>
map  <Esc>2 <A-2>
map! <Esc>2 <A-2>
map  <Esc>3 <A-3>
map! <Esc>3 <A-3>
map  <Esc>4 <A-4>
map! <Esc>4 <A-4>
map  <Esc>5 <A-5>
map! <Esc>5 <A-5>
map  <Esc>6 <A-6>
map! <Esc>6 <A-6>
map  <Esc>7 <A-7>
map! <Esc>7 <A-7>
map  <Esc>8 <A-8>
map! <Esc>8 <A-8>
map  <Esc>9 <A-9>
map! <Esc>9 <A-9>
map  <Esc>- <A-->
map! <Esc>- <A-->
map  <Esc>= <A-=>
map! <Esc>= <A-=>
" }}}
" dvorak experiment {{{
" > 0x00 = <C-@> maps to 0x40 = @
" > 0x01 = <C-A> maps to 0x41 = A
" > 0x02 = <C-B> maps to 0x42 = B
" > 0x03 = <C-C> maps to 0x43 = C
" > ...
" > 0x1A = <C-Z> maps to 0x5A = Z
" > 0x1B = <C-[> maps to 0x5B = [
" > 0x1C = <C-\> maps to 0x5C = \
" > 0x1D = <C-]> maps to 0x5D = ]
" > 0x1E = <C-^> maps to 0x5E = ^
" > 0x1F = <C-_> maps to 0x5F = _


"map @ :s/^#//<CR><ESC>$

" for dvorak on the typematrix
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
"map <C-c><C-c> :w<CR>:make<CR>
"map <C-c><C-v> :!./program<CR>
"map q :q<CR>
"map Q :qa<CR>


"o d h
"no h j
"no t k
"no n l
"no s :
"no S :
"no j d
"no l n
"no L N
""Added benefits
"no N <C-w><C-w>
"no T <C-w><C-r>
"no H 8<Down>
"no T 8<Up>
"no D <C-w><C-r>
" }}}
