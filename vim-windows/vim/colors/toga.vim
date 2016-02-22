set background = dark

hi clear
if exists("syntax_on")
    syntax reset
endif

let g:colors_name = "lokaltog"

hi link htmlTag xmlTag
hi link htmlTagName xmlTagName
hi link htmlEndTag xmlEndTag

hi xmlTag ctermfg=149 cterm=bold
hi xmlTagName ctermfg=250
hi xmlEndTag ctermfg=209 cterm=bold

hi Normal ctermbg=none ctermfg=231

hi LineNr ctermbg=234 ctermfg=242
hi CursorLine ctermbg=52 cterm=bold
hi VertSplit ctermfg=245 ctermbg=235 cterm=none

hi Folded ctermbg=235 ctermfg=246 cterm=bold
hi FoldColumn ctermbg=235 ctermfg=246 cterm=none
hi Visual ctermfg=231 ctermbg=88 cterm=bold

hi Directory ctermfg=143 cterm=bold
hi Underlined ctermfg=130

hi ModeMsg ctermfg=214 cterm=bold
hi MoreMsg ctermfg=216 cterm=bold
hi Question ctermfg=218 cterm=bold
hi WarningMsg ctermfg=160 cterm=bold

hi Comment ctermfg=243 cterm=none
hi vimCommentTitle ctermfg=250
hi vimCommentString ctermfg=245
hi link phpCommentTitle vimCommentTitle
hi link phpDocTags vimCommentString
hi link phpDocParam vimCommentTitle

hi TabLine ctermbg=238 ctermfg=231 cterm=none
hi TabLineSel ctermbg=none ctermfg=255 cterm=bold
hi TabLineFill ctermbg=238 ctermfg=240 cterm=none
hi TabLineNumber ctermbg=238 ctermfg=160 cterm=bold
hi TabLineClose ctermbg=238 ctermfg=245 cterm=bold

hi SpecialKey ctermfg=239 ctermbg=none cterm=none
hi NonText ctermfg=88 ctermbg=none cterm=none
hi MatchParen ctermfg=231 ctermbg=61 cterm=bold

hi Constant ctermfg=137 cterm=bold
hi Special ctermfg=150
hi Identifier ctermfg=66
hi Statement ctermfg=186 cterm=bold
hi PreProc ctermfg=102
hi Type ctermfg=67 cterm=bold
hi String ctermfg=143
hi Number ctermfg=173
hi Define ctermfg=173
hi Error ctermfg=208 ctermbg=124
hi Function ctermfg=221 cterm=none
hi Include ctermfg=173 cterm=none
hi PreCondit ctermfg=173 cterm=none
hi Keyword ctermfg=173 cterm=none
hi Search ctermbg=160 ctermfg=231 cterm=bold,underline
hi Title ctermfg=15

hi TODO ctermfg=228 ctermbg=none cterm=bold

hi Pmenu ctermfg=248 ctermbg=240
hi PmenuSel ctermfg=253 ctermbg=245
hi PmenuSbar ctermfg=253 ctermbg=248

hi phpEOL ctermfg=245
hi phpStringDelim ctermfg=94
hi phpDelimiter ctermfg=160

hi phpFunctions ctermfg=221 cterm=bold
hi phpBoolean ctermfg=172 cterm=bold
hi phpOperator ctermfg=215
hi phpMemberSelector ctermfg=138 cterm=bold
hi phpParent ctermfg=227

hi DiffAdd ctermfg=231 ctermbg=71
hi DiffChange ctermfg=231 ctermbg=130
hi DiffText ctermfg=229 ctermbg=130 cterm=bold
hi DiffDelete ctermfg=231 ctermbg=88

hi StatusLineNC cterm=bold ctermfg=240 ctermbg=234
hi StatusLine cterm=bold ctermfg=231 ctermbg=236
hi User1 cterm=bold ctermfg=244 ctermbg=236
hi User2 cterm=bold ctermfg=196 ctermbg=236
hi User3 cterm=bold ctermfg=244 ctermbg=236
hi User4 cterm=bold ctermfg=202 ctermbg=236
hi User5 cterm=bold ctermfg=178 ctermbg=236
hi User6 cterm=bold ctermfg=242 ctermbg=236 cterm=none
hi User7 cterm=bold ctermfg=242 ctermbg=236

" Highlight problematic whitespace (spaces before tabs)
hi RedundantSpaces ctermfg=214 ctermbg=160 cterm=bold
match RedundantSpaces / \+\ze\t/
