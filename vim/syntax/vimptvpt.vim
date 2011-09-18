" Vim syntax file
" Language:     VPT source files
" Written By:   Damian Conway
" Last Change:  Tue Apr 22 08:32:54 EST 2008

" For version 5.x: Clear all syntax items
" For version 6.x: Quit when a syntax file was already loaded
if version < 600
  syntax clear
elseif exists("b:current_syntax")
  finish
endif


syntax case ignore
syntax sync fromstart
set nowrap


highlight   VPTBulletPoint       ctermfg=yellow   cterm=bold
highlight   VPTSlidesOnly        ctermfg=black    ctermbg=green    cterm=bold
highlight   VPTNotesOnly         ctermfg=black    ctermbg=magenta  cterm=bold
highlight   VPTDirective         ctermfg=red      cterm=bold
highlight   VPTDirectiveText     ctermfg=darkblue     cterm=bold
highlight   VPTBadDirective      ctermfg=yellow   ctermbg=red   cterm=bold
highlight   VPTSectionDirective  ctermfg=red      ctermbg=darkblue cterm=bold
highlight   VPTSection           ctermfg=white    ctermbg=darkblue cterm=bold
highlight   VPTHeading           ctermfg=white              cterm=underline,bold
highlight   VPTCodeBlock         ctermfg=cyan     cterm=bold
highlight   VPTCode              ctermfg=cyan     cterm=bold
highlight   VPTCodeDelim         ctermfg=cyan
highlight   VPTEmph              ctermfg=white    cterm=bold
highlight   VPTEmphDelim         ctermfg=white
highlight   VPTEscape            ctermfg=red
highlight   VPTComment           ctermfg=red

highlight   VPTEdgeScreen        ctermfg=darkblue                  cterm=bold
highlight   VPTOffScreen         ctermfg=darkblue     ctermbg=red  cterm=bold

highlight! link  VPTFoldedHeadings  VPTHeading
highlight! link  VPTFoldedSections  VPTSection

syn region  VPTSection
    \ matchgroup=VPTSectionDirective
    \    start=/^=section\s\+/
    \      end=/\_^\s*\_$/
    \ contains=VPTCode,VPTEscape,VPTEmph


syn region  VPTBulletPoint
    \    start=/^\*\s/
    \      end=/\_^\s*\_$/
    \ contains=VPTNotesOnly,VPTSlidesOnly,VPTCode,VPTEmph,VPTEscape,VPTDirectiveText

syn match  VPTNotesOnly    /^+\s/

syn match  VPTSlidesOnly  /^-\s/

syn region  VPTHeading
    \    start=/^\ze\([^-+=* \t]\|\*\*\)/
    \      end=/\_^\s*\_$/
    \ contains=VPTCode,VPTEscape,VPTEmph

syn match   VPTCodeBlock
    \ /^\s.*$/
    \ contains=VPTEmph,VPTEscape

syn region  VPTCode
    \ matchgroup=VPTCodeDelim
    \      start=/{{/
    \        end=/}}\|\_^\s*\_$/
    \   contains=VPTEmph,VPTCode,VPTEscape
    \ contained

syn region  VPTEmph
    \ matchgroup=VPTEmphDelim
    \      start=/\*\*/
    \        end=/\*\*\|\_^\s*\_$/
    \   contains=VPTCode,VPTEscape
    \ contained

syn match   VPTEscape
    \ /\\\@<!\(\\\\\)*\\[\\{}*]/
    \ contained

syn match   VPTComment
    \ /^!.*/
    \ containedin=ALL

let block_directives = join( split('
    \   title  presenter  info
    \
    \'),'\|')

let line_directives = join( split('
    \   duration
    \   pause
    \   autopause
    \   autoslidepause
    \   break
    \   animation
    \   target\ze\%(\%d32\|\t\)\+\S
    \   link\ze\%(\%d32\|\t\)\+\S
    \   selector\ze\%(\%d32\|\t\)\+\S
    \   example
    \   active
    \   intermission
    \'),'\|')

syn match   VPTBadDirective    /^=\S*/

exe 'syn region  VPTDirectiveText
    \ matchgroup=VPTDirective
    \      start=/^=\(' . block_directives . '\)/
    \        end=/\(\_^=\(' . block_directives . '\|' .  line_directives . '\)\|\_^\s*\_$\)\@=/'

exe 'syn region  VPTDirectiveText
    \ matchgroup=VPTDirective
    \      start=/^=\(' . line_directives . '\)/
    \        end=/$/
    \    oneline'

exe 'syn region  VPTDirectiveText
    \ matchgroup=VPTDirective
    \      start=/^=\(selector\)[ \t]\+/
    \        end=/[ \t]\@=/
    \    oneline'

let b:current_syntax = "vpt"
