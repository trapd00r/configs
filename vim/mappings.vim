let mapleader = ','


cmap W w
map <C-h> <C-w><Left>
map <C-j> <C-w><Down>
map <C-J> <C-W>j<C-W>_
map <C-h> <C-w><Left>
map <C-h> <C-w><Left>

map =  <C-W>-
map +  <C-W>+
map \| :vsplit<CR>
map -  :split<CR>

nmap <silent> <leader>sp :set syn=perl<CR>:syntax sync fromstart<CR>

map ö <C-E><C-E><C-E><C-E><C-E><C-E><C-E><C-E><C-E><C-E><C-E>
map Ö <C-Y><C-Y><C-Y><C-Y><C-Y><C-Y><C-Y><C-Y><C-Y><C-Y><C-Y>

nmap Y y$
nmap <leader>w :w!<CR>

nmap <silent> <leader>d "_d
vmap <silent> <leader>d "_d

nmap <leader>al :left<CR>
nmap <leader>ar :right<CR>
nmap <leader>ac :center<CR>

nnoremap <leader>t :call TitleCaseCenter()<CR>

nnoremap <TAB> %
vnoremap <TAB> %

nnoremap ci( f(ci(
nnoremap ci{ f{ci{
nnoremap ci[ f[ci[

vnoremap ci( f(ci(
vnoremap ci{ f{ci{
vnoremap ci[ f[ci[

nnoremap dad /\v^\=head/<CR> W d$xa
nnoremap d= f=d$a=
nnoremap d> f>d$a>

inoremap <Down> <NOP>
inoremap <Left> <NOP>
inoremap <Up>   <NOP>

nnoremap ; :

nnoremap <C-h> :!perl -MVi::QuickFix='/mnt/Docs/Backup/vim_quickfix_err/%.err' -c %<CR>:cf<CR>
nnoremap <C-j> :cn<CR>
"nnoremap <C-m> :cwindow 5<CR>

nnoremap <C-n> :bnext<CR>
nnoremap <C-p> :bprev<CR>

inoremap <C-n> <ESC>:bnext<CR>
inoremap <C-p> <ESC>:bprev<CR>

inoremap £1 ()<ESC>i
inoremap £2 []<ESC>i
inoremap £3 {<ESC>o}<ESC>O

inoremap £4 {}<ESC>i
inoremap £q ''<ESC>i
inoremap £Q ""<ESC>i

inoremap jj <ESC>
inoremap jk <ESC>

nnoremap [7~ :source %<CR>


" jumping to sub definition
nnoremap <buffer> ]]    :<C-u>call search('^\s*sub .* {$', 'sW')<CR>
nnoremap <buffer> [[    :<C-u>call search('^\s*sub .* {$', 'bsW')<CR>
nnoremap <buffer> ][    :<C-u>call search('^}$', 'sW')<CR>
nnoremap <buffer> []    :<C-u>call search('^}$', 'bsW')<CR>


nnoremap <C-n> :bnext<CR>
nnoremap <C-p> :bprev<CR>
nnoremap <leader>r :buffers<CR>:buffer<space>
nnoremap <leader>l :ls<CR>
nnoremap <leader>g :e#<CR>

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

nnoremap <leader>a :bdelete!<CR>

nnoremap <leader>f :set paste<CR>

nnoremap <leader>s :%s/\s\+$//<CR>:let @/=''<CR>

nnoremap <leader>v V`]

nnoremap <leader><TAB> :call ToggleSpell()<CR>
nnoremap <leader>p :set paste<CR>

nnoremap <silent> <C-l> :nohl<CR>
nnoremap <silent> ,,    :nohl<CR>

nnoremap <C-D> <C-W>

nnoremap <silent> _t :%!perltidy -q<Enter>
vnoremap <silent> _t :!perltidy -q<Enter>

nnoremap <silent> _p :%!perlcritic -q<Enter>
vnoremap <silent> _p :!perlcritic -q<Enter>


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

cnoremap $h e ~/
cnoremap $d e ~/devel
cnoremap $. e .

cnoremap <C-a> <HOME>

"map [29~ :let &number = &number ? 0 : 1<CR>
map [29~ z=

map [3~ xx

" cd to the directory of the open buffer, if possible
map <leader>cd :cd %:p:h<CR>



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
