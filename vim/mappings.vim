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

" Make ^Z behave in insert mode as well
map! <C-Z> <C-O><C-Z>

nmap <silent> <leader>sp :set syn=perl<CR>:syntax sync fromstart<CR>
nmap <space> 10j
nmap Y y$

inoremap <Down> <NOP>
inoremap <Left> <NOP>
inoremap <Up>   <NOP>

nnoremap ; :

nnoremap <C-h> :!perl -MVi::QuickFix="/mnt/Docs/Backup/vim_quickfix_err/%.err" -c %<CR>:cf<CR>
nnoremap <C-j> :cn<CR>
nnoremap <C-m> :cwindow 5<CR>


nnoremap <C-n> :bnext<CR>
nnoremap <C-p> :bprev<CR>
nnoremap <leader>d :buffers<CR>:buffer<space>
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

map [29~ :help keycodes<CR>



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
