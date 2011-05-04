let mapleader = ','

"nmap <leader>O :%w >> ~/vim_output<CR>
"nmap <leader>o :exec ':.w >> ' . eval(string( xclipboard_pipe_path ))<CR>

if &filetype == 'perl'
  nnoremap <C-h> :!perl -MVi::QuickFix='/mnt/Docs/Backup/vim_quickfix_err/%.err' -c %<CR>:cf<CR>
  nnoremap <silent> _t :%!perltidy -q<Enter>
  vnoremap <silent> _t :!perltidy -q<Enter>

  nnoremap <silent> _p :%!perlcritic -q<Enter>
  vnoremap <silent> _p :!perlcritic -q<Enter>
endif

" Switch language
nmap <silent> <leader>sp  :set syn=perl   <CR> :syntax sync fromstart <CR>
nmap <silent> <leader>ss  :set syn=sh     <CR> :syntax sync fromstart <CR>
nmap <silent> <leader>sv  :set syn=vim    <CR> :syntax sync fromstart <CR>
nmap <silent> <leader>sz  :set syn=zsh    <CR> :syntax sync fromstart <CR>
nmap <silent> <leader>sc  :set syn=config <CR> :syntax sync fromstart <CR>
nmap <silent> <leader>sf  :set syn=conf   <CR> :syntax sync fromstart <CR>

" Make writing and quitting faster
cmap W w
cmap qq qa!
nmap <leader>w :w!<CR>

" I prefer to jump to the exact same spot as where the cursor was when I created
" the mark

nnoremap ' `
nnoremap ` '

" jump to the position before the latest jump, or where the
" last "m'" or "m`" command was given.  Not set when the
" |:keepjumps| command modifier was used.

nnoremap `` ''
nnoremap '' ``

" Easier window management
map <C-h> <C-w><Left>
map <C-j> <C-w><Down>
map <C-J> <C-W>j<C-W>_
map <C-h> <C-w><Left>
map <C-h> <C-w><Left>

map =  <C-W>-
map +  <C-W>+
map \| :vsplit<CR>
map -  :split<CR>


" For following links in the Vim help
nmap <C-9> <C-]>

" quick access to the history buffer
nmap q q:

" silly experiment :-)
map ö <C-E><C-E><C-E><C-E><C-E><C-E><C-E><C-E><C-E><C-E><C-E>
map Ö <C-Y><C-Y><C-Y><C-Y><C-Y><C-Y><C-Y><C-Y><C-Y><C-Y><C-Y>

" Y should do what it's expected to do (d$, D, c$, C)
nmap Y y$


nmap <silent> <leader>d "_d
vmap <silent> <leader>d "_d

" align text
nmap <leader>cl :left<CR>
nmap <leader>cr :right<CR>
nmap <leader>cc :center<CR>

" Titlecase And Center
nnoremap <leader>t :call TitleCaseCenter()<CR>

" XXX this is so simple and so useful
vnoremap S :sort<CR>

" Titlecase The Current Line, thank you
nnoremap U :s/\v[a-zåäö]+/\u&/g<CR>

" allow the use of TAB for jumping between matching pairs
" note https://github.com/trapd00r/configs/commit/d7dc036e#L0R74
nnoremap <TAB> %

" make those behave like ci' , ci"
nnoremap ci( f(ci(
nnoremap ci{ f{ci{
nnoremap ci[ f[ci[

vnoremap ci( f(ci(
vnoremap ci{ f{ci{
vnoremap ci[ f[ci[

" pod stuff
nnoremap dad /\v^\=head/<CR> W d$xa
nnoremap d= f=d$a=
nnoremap d> f>d$a>

inoremap £1 ()<ESC>i
inoremap £2 []<ESC>i
inoremap £3 {<ESC>o}<ESC>O

inoremap £4 {}<ESC>i
inoremap £q ''<ESC>i
inoremap £Q ""<ESC>i

inoremap jj <ESC>
inoremap jk <ESC>

nnoremap [7~ :source %<CR>
nnoremap [2~ :source %<CR>

" jumping to sub definition
nnoremap <buffer> ]]    :<C-u>call search('^\s*sub .* {$', 'sW')<CR>
nnoremap <buffer> [[    :<C-u>call search('^\s*sub .* {$', 'bsW')<CR>
nnoremap <buffer> ][    :<C-u>call search('^}$', 'sW')<CR>
nnoremap <buffer> []    :<C-u>call search('^}$', 'bsW')<CR>

" buffer shortcuts
nnoremap <C-n> :bnext<CR>
nnoremap <C-p> :bprev<CR>
nnoremap <leader>b :buffers<CR>:buffer<space>
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

"nnoremap <leader>a :bdelete!<CR>

nnoremap <leader>f :set paste<CR>

nnoremap <leader>s :call RemoveTrailingCrap()

nnoremap <leader>v V`]

" spell
map [29~ z=
nnoremap za zg
nnoremap <leader><TAB> :call ToggleSpell()<CR>

nnoremap <leader>p :set paste<CR>

nnoremap <silent> <C-l> :nohl<CR>
nnoremap <silent> ,,    :nohl<CR>

nnoremap <C-D> <C-W>

" sane regex

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

" directory shortcuts
cnoremap $h e ~/
cnoremap $d e ~/devel
cnoremap $. e .

" emacs keymap in the commandline
cnoremap  <c-a>   <home>
cnoremap  <c-e>   <end>
cnoremap  <c-b>   <left>
cnoremap  <c-d>   <del>
cnoremap  <c-f>   <right>
cnoremap  <C-_>   <c-f>

cnoremap  <c-n>   <down>
cnoremap  <c-p>   <up>
cnoremap  <C-*>   <c-a>

map [3~ xx

" cd to the directory of the open buffer, if possible
map <leader>cd :cd %:p:h<CR>


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
