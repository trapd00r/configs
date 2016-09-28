###< vim: set ft=zsh:fdm=marker:fmr=#<,#>:fdl=0:fen:et:sw=2:fcl=all:
###
#      ${HOME}/etc/zsh/02-bindkeys.zsh
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗
#         owner  Magnus Woldrich <magnus.woldrich@gmail.com>
#         btime  2009-04-24
#         mtime  2016-09-05 15:44:52
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

#bindkey -v
bindkey "^N"      most-accessed-file
#bindkey "^J"    accept-line
zle -C menu-complete-files menu-complete _generic
zstyle ':completion:menu-complete-files:*' completer _files
bindkey -M viins '^J' menu-complete-files

zle -C all-matches complete-word _generic
bindkey -M viins '^O' all-matches
zstyle ':completion:all-matches:*'   old-matches only
zstyle ':completion:all-matches::::' completer _all_matches

bindkey -M vicmd  ":"  _complete_help 
bindkey -M vicmd   ";" _read_comp

bindkey -M viins "^U" all-matches

#< screen, tmux
#if [[ "$TERM" =~ 'screen' ]]; then
#  bindkey -s '^n' 'tmux next-window\n'
#  bindkey -s '^p' 'tmux previous-window\n'
#fi
#>

#< main
##  remove all key bindings starting with ESC
#bindkey -M vicmd -rp "^["
#bindkey -M viins -rp "^["
## escape as fast as possible from insert mode
#bindkey -M viins -rp '^['
#bindkey -M viins     '^[' vi-cmd-mode


#bindkey "^C"    self-insert
#bindkey "^F"    forward-word
#bindkey "^O"    self-insert
#bindkey "^S"    self-insert
#bindkey "^X "   no-magic-abbrev-expand
#bindkey "^X"    self-insert
#bindkey "^X^P"  pids
#bindkey "^Xa"   _expand_alias
#bindkey "^Xe"   _expand_word
#bindkey "^Xm"   _most_recent_file
#bindkey "^Xn"   _next_tags
#bindkey "^X~"   _bash_list-choices
#bindkey "^[,"   _history-complete-newer
#bindkey "^[/"   _history-complete-older
#bindkey "^[OA"  up-line-or-history
#bindkey "^[[1~" beginning-of-line
#bindkey "^[[5~" up-line-or-history
#bindkey "^[[A"  up-line-or-history
#bindkey "^[~"   _bash_complete-word
#bindkey "^D"    delete-word

bindkey " "     magic-abbrev-expand
bindkey "^A"    beginning-of-line
bindkey "^B"    backward-word
#bindkey "^E"    end-of-line
bindkey "^H"    backward-delete-char
bindkey "^I"    complete-word
bindkey "^L"    clear-screen
bindkey "^M"    accept-line
bindkey "^Q"    vi-quoted-insert
bindkey "^R"    history-incremental-search-backward
bindkey "^U"    vi-kill-line
bindkey "^W"    backward-delete-word
#bindkey "^X^A"  all-matches
#bindkey "^Xd"   _list_expansions
bindkey "^["    vi-cmd-mode
bindkey "^[OB"  down-line-or-history
bindkey "^[OC"  vi-forward-char
bindkey "^[OD"  vi-backward-char
bindkey "^[[3~" delete-char
bindkey "^[[6~" down-line-or-history
bindkey "^[[B"  down-line-or-history
bindkey "^[[C"  vi-forward-char
bindkey "^[[D"  vi-backward-char
#>
#< vicmd
autoload edit-command-line
zle -N edit-command-line
#bindkey -M vicmd "^V"     edit-command-line
#bindkey -M viins "^V"     edit-command-line

bindkey -M vicmd "ga"     what-cursor-position
bindkey -M vicmd "g~"     vi-oper-swap-case
bindkey -M vicmd "di"     delete-in
bindkey -M vicmd "ci"     change-in
bindkey -M vicmd "da"     delete-around
bindkey -M vicmd "ca"     delete-around


bindkey -M vicmd  "^M"    accept-line
bindkey -M vicmd  "1"-"9" digit-argument
#bindkey -M vicmd  "^N"    down-history
bindkey -M vicmd  "^J"     down-line-or-history
bindkey -M vicmd  "^K"     up-line-or-history
#bindkey -M vicmd  "^[[B"  down-line-or-history
#bindkey -M vicmd  "^[OB"  down-line-or-history
#_complete_help -C .complete-word _complete_help

bindkey -M vicmd  "="     list-choices
bindkey -M vicmd  "^D"    list-choices
#bindkey -M vicmd  "^G"    list-expand
bindkey -M vicmd  "#"     pound-insert
bindkey -M vicmd  "^R"    history-incremental-search-backward
#bindkey -M vicmd  "^P"    up-history
bindkey -M vicmd  "k"     up-line-or-history
#bindkey -M vicmd  "^[[A"  up-line-or-history
#bindkey -M vicmd  "^[[B"  down-line-or-history
bindkey -M vicmd  "A"     vi-add-eol
bindkey -M vicmd  "a"     vi-add-next
bindkey -M vicmd  "B"     vi-backward-blank-word
bindkey -M vicmd  "h"     vi-backward-char
#bindkey -M vicmd  "^H"    vi-backward-char
bindkey -M vicmd  "^?"    vi-backward-char
#bindkey -M vicmd  "^[[D"  vi-backward-char
#bindkey -M vicmd  "^[OD"  vi-backward-char
bindkey -M vicmd  "X"     vi-backward-delete-char
bindkey -M vicmd  "b"     vi-backward-word
bindkey -M vicmd  "c"     vi-change
bindkey -M vicmd  "C"     vi-change-eol
bindkey -M vicmd  "S"     vi-change-whole-line
bindkey -M vicmd  "d"     vi-delete
bindkey -M vicmd  "x"     vi-delete-char
bindkey -M vicmd  "0"     vi-digit-or-beginning-of-line
bindkey -M vicmd  "9"     vi-digit-or-beginning-of-line
bindkey -M vicmd  "="     vi-digit-or-beginning-of-line
bindkey -M vicmd  "+"     vi-down-line-or-history
bindkey -M vicmd  "\$"    vi-end-of-line
bindkey -M vicmd  "G"     vi-fetch-history
bindkey -M vicmd  "f"     vi-find-next-char
bindkey -M vicmd  "t"     vi-find-next-char-skip
bindkey -M vicmd  "F"     vi-find-prev-char
bindkey -M vicmd  "T"     vi-find-prev-char-skip
bindkey -M vicmd  "\^"    vi-first-non-blank
bindkey -M vicmd  "W"     vi-forward-blank-word
bindkey -M vicmd  "E"     vi-forward-blank-word-end
bindkey -M vicmd  "l"     vi-forward-char
bindkey -M vicmd  "^[[C"  vi-forward-char
bindkey -M vicmd  "^[OC"  vi-forward-char
bindkey -M vicmd  " "     vi-forward-char
bindkey -M vicmd  "w"     vi-forward-word
bindkey -M vicmd  "e"     vi-forward-word-end
bindkey -M vicmd  "|"     vi-goto-column
bindkey -M vicmd  "\`"    vi-goto-mark
bindkey -M vicmd  "'"     vi-goto-mark-line
bindkey -M vicmd  "/"     history-incremental-pattern-search-backward
#bindkey -M vicmd  "/"     vi-history-search-backward
bindkey -M vicmd  "?"     vi-history-search-forward
bindkey -M vicmd  ">"     vi-indent
bindkey -M vicmd  "i"     vi-insert
bindkey -M vicmd  "I"     vi-insert-bol
#bindkey -M vicmd  "J"     vi-join
bindkey -M vicmd  "D"     vi-kill-eol
bindkey -M vicmd  "%"     vi-match-bracket
bindkey -M vicmd  "O"     vi-open-line-above
bindkey -M vicmd  "o"     vi-open-line-below
bindkey -M vicmd  "p"     vi-put-after
bindkey -M vicmd  "P"     vi-put-before
bindkey -M vicmd  "."     vi-repeat-change
bindkey -M vicmd  ";"     vi-repeat-find
bindkey -M vicmd  "n"     vi-repeat-search
bindkey -M vicmd  "R"     vi-replace
bindkey -M vicmd  "r"     vi-replace-chars
bindkey -M vicmd  ","     vi-rev-repeat-find
bindkey -M vicmd  "N"     vi-rev-repeat-search
bindkey -M vicmd  "\""    vi-set-buffer
bindkey -M vicmd  "m"     vi-set-mark
bindkey -M vicmd  "s"     vi-substitute
bindkey -M vicmd  "~"     vi-swap-case
bindkey -M vicmd  "u"     vi-undo-change
bindkey -M vicmd  "<"     vi-unindent
#bindkey -M vicmd  "-"     vi-up-line-or-history
bindkey -M vicmd  "y"     vi-yank
bindkey -M vicmd  "Y"     vi-yank-whole-line
#>
#< viins
#bindkey -s -M viins "^T"  "\\\top\n"
bindkey -M viins "^K" up-line-or-history
bindkey -M viins "^J" down-line-or-history

bindkey -M viins '^G' xterm-set-bg
bindkey -M vicmd '^G' xterm-set-bg
#bindkey -M vicmd '^S' font-711-710-rev
#bindkey -M viins '^S' font-711-710-rev
bindkey -M vicmd '^S' wrxvt_spawn_in_cwd
bindkey -M viins '^S' wrxvt_spawn_in_cwd


autoload edit-command-line
#bindkey -s -M viins '^V0' edit-command-line

bindkey -s -M viins "^X0" " &> /dev/null "
bindkey -s -M viins "^X1" "  > /dev/null "
bindkey -s -M viins "^X2" " 2> /dev/null "
bindkey -s -M viins "^X3" " 2>&1 "

#bindkey "^V"             prepend-vim
#bindkey -M viins "^J"    insert-last-word
bindkey -M viins "^M"    accept-line
#bindkey -M viins "^X^A"  all-matches
bindkey -M viins "^?"    backward-delete-char
bindkey -M viins "^H"    backward-delete-char
bindkey -M viins "^W"    backward-delete-word
bindkey -M viins "^B"    backward-word
bindkey -M viins "^[~"   _bash_complete-word
bindkey -M viins "^E"   _bash_list-choices
bindkey -M viins "^[[1~" beginning-of-line
bindkey -M viins "^A"    beginning-of-line
bindkey -M viins "^L"    clear-screen
bindkey -M viins "^X?"   _complete_debug
bindkey -M viins "^Xh"   _complete_help
bindkey -M viins "^Xt"   _complete_tag
bindkey -M viins "^I"    complete-word
bindkey -M viins "^XC"   _correct_filename
bindkey -M viins "^Xc"   _correct_word
bindkey -M viins "^[[3~" delete-char
bindkey -M viins "^D"    delete-word
bindkey -M viins "^[[6~" down-line-or-history
bindkey -M viins "^[[B"  down-line-or-history
bindkey -M viins "^[OB"  down-line-or-history
bindkey -M viins "^[[4~" end-of-line
#bindkey -M viins "^E"    end-of-line
bindkey -M viins "^Xa"   _expand_alias
bindkey -M viins "^Xe"   _expand_word
bindkey -M viins "^F"    forward-word
bindkey -M viins "^[,"   _history-complete-newer
bindkey -M viins "^[/"   _history-complete-older
bindkey -M viins "^R"    history-incremental-search-backward
bindkey -M viins "^Xd"   _list_expansions
bindkey -M viins " "     magic-abbrev-expand
bindkey -M viins "^Xm"   _most_recent_file
bindkey -M viins "^Xn"   _next_tags
bindkey -M viins "^X "   no-magic-abbrev-expand
bindkey -M viins "^X^P"  pids
bindkey -M viins "^X^R"  _read_comp
bindkey -M viins "^[[5~" up-line-or-history
bindkey -M viins "^[[A"  up-line-or-history
bindkey -M viins "^[OA"  up-line-or-history
bindkey -M viins "^[[D"  vi-backward-char
bindkey -M viins "^[OD"  vi-backward-char
bindkey -M viins "^["    vi-cmd-mode
bindkey -M viins "^[[C"  vi-forward-char
bindkey -M viins "^[OC"  vi-forward-char
bindkey -M viins "^U"    vi-kill-line
bindkey -M viins "^Q"    vi-quoted-insert
#>
#< command
#bindkey -M command "^G" send-break
bindkey -M command "^C" send-break
#bindkey -M command "^J" send-break
#bindkey -M command "^M" send-break
#>
#< isearch
bindkey -M isearch " " self-insert
bindkey -M isearch "^J" self-insert
#>
#< menuselect
zmodload zsh/complist
#bindkey -M menuselect -rp '^'
#bindkey -M menuselect '^J' down-line-or-search
#bindkey -M menuselect  '^K' up-line-or-search
bindkey -M menuselect '^J' down-line-or-history
bindkey -M menuselect  '^K' up-line-or-history
bindkey -M menuselect  '^E' accept-and-menu-complete
#bindkey -M menuselect  '^M' accept-and-infer-next-history
#bindkey -M menuselect  '^M' accept-line-and-down-history
bindkey -M menuselect  '^M' magic-space
#>
#< emacs
bindkey -M emacs "^[a"  accept-and-hold
bindkey -M emacs "^[A"  accept-and-hold
#bindkey -M emacs "^J"   accept-line
bindkey -M emacs "^M"   accept-line
#bindkey -M emacs "^O"   accept-line-and-down-history
bindkey -M emacs "^B"   backward-char
bindkey -M emacs "^[[D" backward-char
bindkey -M emacs "^[OD" backward-char
bindkey -M emacs "^H"   backward-delete-char
bindkey -M emacs "^W"   backward-kill-word
bindkey -M emacs "^[^?" backward-kill-word
bindkey -M emacs "^[^H" backward-kill-word
bindkey -M emacs "^[b"  backward-word
bindkey -M emacs "^[B"  backward-word
bindkey -M emacs "^[<"  beginning-of-buffer-or-history
bindkey -M emacs "^A"   beginning-of-line
bindkey -M emacs "^[c"  capitalize-word
bindkey -M emacs "^[C"  capitalize-word
bindkey -M emacs "^L"   clear-screen
bindkey -M emacs "^[^L" clear-screen
bindkey -M emacs "^[^_" copy-prev-word
bindkey -M emacs "^[w"  copy-region-as-kill
bindkey -M emacs "^[W"  copy-region-as-kill
bindkey -M emacs "^D"   delete-char-or-list
bindkey -M emacs "^[0"  digit-argument
bindkey -M emacs "^[1"  digit-argument
bindkey -M emacs "^[2"  digit-argument
bindkey -M emacs "^[3"  digit-argument
bindkey -M emacs "^[4"  digit-argument
bindkey -M emacs "^[5"  digit-argument
bindkey -M emacs "^[6"  digit-argument
bindkey -M emacs "^[7"  digit-argument
bindkey -M emacs "^[8"  digit-argument
bindkey -M emacs "^[9"  digit-argument
bindkey -M emacs "^[L"  down-case-word
bindkey -M emacs "^N"   down-line-or-history
bindkey -M emacs "^[[B" down-line-or-history
bindkey -M emacs "^[OB" down-line-or-history
bindkey -M emacs "^[>"  end-of-buffer-or-history
#bindkey -M emacs "^E"   end-of-line
bindkey -M emacs "^X^X" exchange-point-and-mark
bindkey -M emacs "^[z"  execute-last-named-cmd
bindkey -M emacs "^[x"  execute-named-cmd
bindkey -M emacs "^[!"  expand-history
bindkey -M emacs "^[ "  expand-history
bindkey -M emacs "^I"   expand-or-complete
bindkey -M emacs "^X*"  expand-word
bindkey -M emacs "^F"   forward-char
bindkey -M emacs "^[[C" forward-char
bindkey -M emacs "^[OC" forward-char
bindkey -M emacs "^[f"  forward-word
bindkey -M emacs "^[F"  forward-word
bindkey -M emacs "^[g"  get-line
bindkey -M emacs "^[G"  get-line
bindkey -M emacs "^R"   history-incremental-search-backward
bindkey -M emacs "^Xr"  history-incremental-search-backward
bindkey -M emacs "^S"   history-incremental-search-forward
bindkey -M emacs "^Xs"  history-incremental-search-forward
bindkey -M emacs "^[p"  history-search-backward
bindkey -M emacs "^[P"  history-search-backward
bindkey -M emacs "^[n"  history-search-forward
bindkey -M emacs "^[N"  history-search-forward
bindkey -M emacs "^X^N" infer-next-history
bindkey -M emacs "^[_"  insert-last-word
bindkey -M emacs "^[."  insert-last-word
bindkey -M emacs "^X^K" kill-buffer
#bindkey -M emacs "^K"   kill-line
bindkey -M emacs "^U"   kill-whole-line
bindkey -M emacs "^[d"  kill-word
bindkey -M emacs "^[D"  kill-word
bindkey -M emacs "^[^D" list-choices
bindkey -M emacs "^Xg"  list-expand
bindkey -M emacs "^XG"  list-expand
bindkey -M emacs "^[-"  neg-argument
#bindkey -M emacs "^X^O" overwrite-mode
bindkey -M emacs "^Q"   push-line
bindkey -M emacs "^[q"  push-line
bindkey -M emacs "^[Q"  push-line
bindkey -M emacs "^V"   quoted-insert
bindkey -M emacs "^['"  quote-line
bindkey -M emacs "^[\"" quote-region
bindkey -M emacs "^[h"  run-help
bindkey -M emacs "^[H"  run-help
bindkey -M emacs "^[^I" self-insert-unmeta
bindkey -M emacs "^[^J" self-insert-unmeta
bindkey -M emacs "^[^M" self-insert-unmeta
#bindkey -M emacs "^G"   send-break
#bindkey -M emacs "^[^G" send-break
bindkey -M emacs "^@"   set-mark-command
bindkey -M emacs "^[s"  spell-word
bindkey -M emacs "^[S"  spell-word
bindkey -M emacs "^[\$" spell-word
bindkey -M emacs "^T"   transpose-chars
#bindkey -M emacs "^[t"  transpose-words
#bindkey -M emacs "^[T"  transpose-words
bindkey -M emacs "^X^U" undo
bindkey -M emacs "^Xu"  undo
bindkey -M emacs "^_"   undo
bindkey -M emacs "^[u"  up-case-word
bindkey -M emacs "^[U"  up-case-word
bindkey -M emacs "^P"   up-line-or-history
bindkey -M emacs "^[[A" up-line-or-history
bindkey -M emacs "^[OA" up-line-or-history
bindkey -M emacs "^X^V" vi-cmd-mode
bindkey -M emacs "^X^F" vi-find-next-char
bindkey -M emacs "^[|"  vi-goto-column
bindkey -M emacs "^X^J" vi-join
bindkey -M emacs "^X^B" vi-match-bracket
bindkey -M emacs "^X="  what-cursor-position
bindkey -M emacs "^[?"  which-command
bindkey -M emacs "^Y"   yank
bindkey -M emacs "^[y"  yank-pop

bindkey -R -M emacs " "-"~" self-insert
bindkey -M emacs "^?" backward-delete-char
bindkey -R -M emacs "\M-^@"-"\M-^?" self-insert
#>
#< redirection
bindkey -s "^X0" " &> /dev/null "
bindkey -s "^X1" "  > /dev/null "
bindkey -s "^X2" " 2> /dev/null "
bindkey -s "^X3" " 2>&1 "
#>
#< ranges
bindkey -R "!"-"~"         self-insert
bindkey -R "^Y"-"^Z"       self-insert
bindkey -R "^\\\\"-"^_"    self-insert
bindkey -R "\M-^@"-"\M-^?" self-insert
#>
#< applications
#bindkey -s "^T" "top\n"
#bindkey -s "^V" "^Rvim\n"
#bindkey -s "^Z" "urxvt -name shiva\n"
#>
#< escape FAST
#  remove all key bindings starting with ESC
bindkey -M vicmd -rp "^["
bindkey -M viins -rp "^["
# escape as fast as possible from insert mode
bindkey -M viins -rp '^['
bindkey -M viins     '^[' vi-cmd-mode
#>
#< terminfo madness
# create a zkbd compatible hash;
# to add other keys to this hash, see: man 5 terminfo
#typeset -A key
#
#key[Home]=${terminfo[khome]}
#key[End]=${terminfo[kend]}
#key[Insert]=${terminfo[kich1]}
#key[Delete]=${terminfo[kdch1]}
#key[Up]=${terminfo[kcuu1]}
#key[Down]=${terminfo[kcud1]}
#key[Left]=${terminfo[kcub1]}
#key[Right]=${terminfo[kcuf1]}
#key[PageUp]=${terminfo[kpp]}
#key[PageDown]=${terminfo[knp]}
#
## setup key accordingly
#[[ -n "${key[Home]}"    ]]  && bindkey  "${key[Home]}"    beginning-of-line
#[[ -n "${key[End]}"     ]]  && bindkey  "${key[End]}"     end-of-line
#[[ -n "${key[Insert]}"  ]]  && bindkey  "${key[Insert]}"  overwrite-mode
#[[ -n "${key[Delete]}"  ]]  && bindkey  "${key[Delete]}"  delete-char
#[[ -n "${key[Up]}"      ]]  && bindkey  "${key[Up]}"      up-line-or-history
#[[ -n "${key[Down]}"    ]]  && bindkey  "${key[Down]}"    down-line-or-history
#[[ -n "${key[Left]}"    ]]  && bindkey  "${key[Left]}"    backward-char
#[[ -n "${key[Right]}"   ]]  && bindkey  "${key[Right]}"   forward-char

# Finally, make sure the terminal is in application mode, when zle is
# active. Only then are the values from $terminfo valid.
#function zle-line-init () {
##    echoti smkx
#}
#function zle-line-finish () {
##    echoti rmkx
#}
#zle -N zle-line-init
#zle -N zle-line-finish  
#>
