
if v:version < 600
    syntax clear
elseif exists('b:current_syntax')
    finish
endif



syn case match



if v:version >= 508 || !exists("did_<%eval: expand('%:t:r') %>_syn_inits")
    if v:version < 508
        let did_<%eval: expand('%:t:r') %>_syn_inits = 1
        command -nargs=+ HiLink hi link <args>
    else
        command -nargs=+ HiLink hi def link <args>
    endif
    delcommand HiLink
endif



let b:current_syntax = '<%eval: expand("%:t:r") %>'
