" Vim color file
" Maintainer: Abhijit Nadgouda (http://ifacethoughts.net/)
" Version: 0.6

set background=dark
hi clear
if exists("syntax_on")
    syntax reset
endi
let g:colors_name="typing"

hi Normal       guifg=#c0c0c0       guibg=#222222
hi Title        guifg=White                         gui=bold
hi Title        ctermfg=White                       cterm=bold
hi LineNr       guifg=DarkGrey                                  
hi LineNr       ctermfg=DarkGrey
hi Comment      guifg=DarkGrey                                  
hi Comment      ctermfg=DarkGrey
hi Identifier	guifg=LightGreen                    gui=NONE                         
hi Identifier   ctermfg=LightGreen                  cterm=none
hi Statement    guifg=#66ccff                       gui=NONE
hi Statement    ctermfg=LightBlue                   
hi Label        guifg=#66ccff                       gui=NONE
hi Label        ctermfg=LightBlue
hi Exception    guifg=#66ccff                       gui=NONE
hi Exception    ctermfg=LightBlue
hi Boolean      guifg=LightGreen                    gui=NONE
hi Boolean      ctermfg=LightGreen
hi String       guibg=Black                 
hi String       ctermbg=Black
hi Type         guifg=LightGreen                    gui=NONE
hi Type         ctermfg=LightGreen                  cterm=NONE
hi TypeDef      guifg=LightGreen                    gui=NONE                      
hi TypeDef      ctermfg=LightGreen                  cterm=NONE
hi Number       guifg=LightGreen                    gui=NONE                                
hi Number       ctermfg=LightGreen                  cterm=NONE
hi Float        guifg=LightGreen                    gui=NONE         
hi Float        ctermfg=LightGreen                  cterm=NONE
hi Constant     guifg=LightGreen                    gui=NONE                 
hi Constant     ctermfg=LightGreen                  cterm=NONE
hi Function     guifg=#cc6633                                   
hi Function     ctermfg=DarkYellow
hi Preproc      guifg=#cc6633                                   
hi Preproc      ctermfg=DarkYellow
hi Keyword      guifg=#cc6633                                   
hi Keyword      ctermfg=DarkYellow
hi Include      guifg=#cc6633                                   
hi Include      ctermfg=DarkYellow 
hi Folded       guifg=DarkGrey      guibg=Black                 
hi Folded       ctermfg=DarkGrey    ctermbg=Black
hi Incsearch    guifg=Yellow        guibg=Black                 
hi Incsearch    ctermfg=Yellow
hi Search       guifg=Yellow        guibg=Black
hi Search       ctermfg=Yellow      ctermbg=Black
hi Ignore       guifg=DarkGrey                                  
hi Ignore       ctermfg=DarkGrey
hi Select       guifg=Black         guibg=Yellow                
hi Select       ctermfg=Black       ctermbg=Yellow
hi Spellbad     guifg=Magenta       guibg=Black                 
hi Spellbad     ctermfg=Magenta     ctermbg=Black
hi Spellcap     guifg=Grey          guibg=Black                 
hi Spellcap     ctermfg=Grey        ctermbg=Black
hi Spellrare    guifg=Grey          guibg=Black                 
hi Spellrare    ctermfg=Grey        ctermbg=Black
hi Spelllocal   guifg=Grey          guibg=Black                 
hi Spelllocal   ctermfg=Grey        ctermbg=Black
hi Specialchar                                      gui=underline
hi Specialchar                                      cterm=underline
hi Tabline      guifg=#ccc          guibg=#333                  
hi Tablinefill  guibg=#333
hi Tablinesel   guifg=#000          guibg=#666
hi Cursor                           guibg=#666
