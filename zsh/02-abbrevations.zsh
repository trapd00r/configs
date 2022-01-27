###< vim: set ft=zsh:fdm=marker:fmr=#<,#>:fdl=0:fen:et:sw=2:fcl=all:
###
#      ${HOME}/etc/zsh/02-abbrevations.zsh
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗
#         owner  Magnus Woldrich <magnus.woldrich@gmail.com>
#         btime  2009-04-24
#         mtime  2016-09-05 14:56:04
#   permissions  You are free to use things you may find useful here.
#                Would my tweaks happen to give you a raise or fetch you a
#                girlfriend, it goes without saying I'm counting on you
#                to share with me as I've shared with you.
#           git  http://github.com/trapd00r/configs/zsh  (up-to-date)
#           url  http://devel.japh.se/configs/zsh        (sync 1/24h)
#           irc  japh@freenode #zsh #vim #perl
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗ ‗‗‗‗ ‗‗‗‗
###
###>

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
  "bb"          "/mnt/music8/+TAGGED/"
  "ee"          "/mnt/music8/+TAGGED/E/Eminem"
  "ss"          "/mnt/music8/_soulseek"
  "sqlk"        "${HOME}/dev/askas/air8/cgi-bin/ibutik/_DATABAS/_Nytt_SQLkoder.sql"

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
#  LBUFFER+=''
}

zle -N magic-abbrev-expand
zle -N no-magic-abbrev-expand

bindkey " "   magic-abbrev-expand
bindkey "^x " no-magic-abbrev-expand
