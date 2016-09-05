#!/usr/bin/zsh

typeset -Ag abbreviations
abbreviations=(
  "findf" 'find . -maxdepth 1 -type f -printf "%P\n" | \
    perl -e "@_=<>; print sort grep {! /^[.]/ } @_; print sort grep { /^[.]/ } @_" | \
    ls_color'

  "jj"         "!$"
  "jk"         "!-2$"
  "jjk"        "!-3$"
  "jkk"        "!-4$"
  "kk"         "!-5$"
  "kj"         "!-6$"
)

magic-abbrev-expand() {
  local MATCH
   LBUFFER=${LBUFFER%%(#m)[-:_a-zA-Z0-9]#}
  LBUFFER+=${abbreviations[$MATCH]:-$MATCH}
  zle self-insert
  #printf "\b"
}

no-magic-abbrev-expand() {
  LBUFFER+=' '
}

zle -N magic-abbrev-expand
zle -N no-magic-abbrev-expand

bindkey " "   magic-abbrev-expand
bindkey "^x " no-magic-abbrev-expand


# vim: set et sw=2 tw=90:
