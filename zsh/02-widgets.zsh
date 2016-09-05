###< vim: set ft=zsh:fdm=marker:fmr=#<,#>:fdl=0:fen:et:sw=2:fcl=all:
###
#      ${HOME}/etc/zsh/02-widgets.zsh
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

prepend-vim() {
  if [[ $BUFFER != "vim "* ]]; then
    BUFFER="vim $BUFFER"; CURSOR+=5
  fi
}
zle -N prepend-vim

# deletes a block between two characters
delete-in() {
  local CHAR LCHAR RCHAR LSEARCH RSEARCH COUNT
  read -k CHAR
  if [[ $CHAR == "w" ]];then
    zle vi-backward-word
    LSEARCH=$CURSOR
    zle vi-forward-word
    RSEARCH=$CURSOR
    RBUFFER="$BUFFER[$RSEARCH+1,${#BUFFER}]"
    LBUFFER="$LBUFFER[1,$LSEARCH]"
    return
  elif [[ $CHAR == "(" ]] || [[ $CHAR == ")" ]];then
    LCHAR="("
    RCHAR=")"
  elif [[ $CHAR == "[" ]] || [[ $CHAR == "]" ]];then
    LCHAR="["
    RCHAR="]"
  elif [[ $CHAR == "{" ]] || [[ $CHAR == "}" ]];then
    LCHAR="{"
    RCHAR="}"
  else
    LSEARCH=${#LBUFFER}
    while [[ $LSEARCH -gt 0 ]] && [[ "$LBUFFER[$LSEARCH]" != "$CHAR" ]]; do
      (( LSEARCH = $LSEARCH - 1 ))
    done
    RSEARCH=0
    while [[ $RSEARCH -lt (( ${#RBUFFER} + 1 )) ]] && [[ "$RBUFFER[$RSEARCH]" != "$CHAR" ]]; do
      (( RSEARCH = $RSEARCH + 1 ))
    done
    RBUFFER="$RBUFFER[$RSEARCH,${#RBUFFER}]"
    LBUFFER="$LBUFFER[1,$LSEARCH]"
    return
  fi
  COUNT=1
  LSEARCH=${#LBUFFER}
  while [[ $LSEARCH -gt 0 ]] && [[ $COUNT -gt 0 ]]; do
    (( LSEARCH = $LSEARCH - 1 ))
    if [[ $LBUFFER[$LSEARCH] == "$RCHAR" ]];then
      (( COUNT = $COUNT + 1 ))
    fi
    if [[ $LBUFFER[$LSEARCH] == "$LCHAR" ]];then
      (( COUNT = $COUNT - 1 ))
    fi
  done
  COUNT=1
  RSEARCH=0
  while [[ $RSEARCH -lt (( ${#RBUFFER} + 1 )) ]] && [[ $COUNT -gt 0 ]]; do
    (( RSEARCH = $RSEARCH + 1 ))
    if [[ $RBUFFER[$RSEARCH] == "$LCHAR" ]];then
      (( COUNT = $COUNT + 1 ))
    fi
    if [[ $RBUFFER[$RSEARCH] == "$RCHAR" ]];then
      (( COUNT = $COUNT - 1 ))
    fi
  done
  RBUFFER="$RBUFFER[$RSEARCH,${#RBUFFER}]"
  LBUFFER="$LBUFFER[1,$LSEARCH]"
}
zle -N delete-in

change-in() {
  zle delete-in
  zle vi-insert
}
zle -N change-in

delete-around() {
  zle delete-in
  zle vi-backward-char
  zle vi-delete-char
  zle vi-delete-char
}
zle -N delete-around

change-around() {
  zle delete-in
  zle vi-backward-char
  zle vi-delete-char
  zle vi-delete-char
  zle vi-insert
}
zle -N change-around
