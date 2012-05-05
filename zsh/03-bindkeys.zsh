#!/usr/bin/zsh

bindkey -v
# main                                                                       {{{
#bindkey "^J"    accept-line


#bindkey "^C"    self-insert
#bindkey "^F"    forward-word
#bindkey "^O"    self-insert
#bindkey "^S"    self-insert
#bindkey "^X "   no-magic-abbrev-expand
#bindkey "^X"    self-insert
#bindkey "^X^P"  pids
#bindkey "^X^R"  _read_comp
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
bindkey "^E"    end-of-line
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
#}}}
# vicmd                                                                      {{{
#bindkey -M vicmd  "^J"    accept-line
bindkey -M vicmd  "^M"    accept-line
bindkey -M vicmd  "^L"    clear-screen
bindkey -M vicmd  "1"-"9" digit-argument
bindkey -M vicmd  "^N"    down-history
bindkey -M vicmd  "^J"     down-line-or-history
bindkey -M vicmd  "^[[B"  down-line-or-history
bindkey -M vicmd  "^[OB"  down-line-or-history
bindkey -M vicmd  ":"     execute-named-cmd
bindkey -M vicmd  "="     list-choices
bindkey -M vicmd  "^D"    list-choices
bindkey -M vicmd  "^G"    list-expand
bindkey -M vicmd  "#"     pound-insert
bindkey -M vicmd  "^R"    redisplay
bindkey -M vicmd  "^P"    up-history
bindkey -M vicmd  "k"     up-line-or-history
bindkey -M vicmd  "^[[A"  up-line-or-history
bindkey -M vicmd  "^[OA"  up-line-or-history
bindkey -M vicmd  "A"     vi-add-eol
bindkey -M vicmd  "a"     vi-add-next
bindkey -M vicmd  "B"     vi-backward-blank-word
bindkey -M vicmd  "h"     vi-backward-char
bindkey -M vicmd  "^H"    vi-backward-char
bindkey -M vicmd  "^?"    vi-backward-char
bindkey -M vicmd  "^[[D"  vi-backward-char
bindkey -M vicmd  "^[OD"  vi-backward-char
bindkey -M vicmd  "X"     vi-backward-delete-char
bindkey -M vicmd  "b"     vi-backward-word
bindkey -M vicmd  "c"     vi-change
bindkey -M vicmd  "C"     vi-change-eol
bindkey -M vicmd  "S"     vi-change-whole-line
bindkey -M vicmd  "d"     vi-delete
bindkey -M vicmd  "x"     vi-delete-char
bindkey -M vicmd  "0"     vi-digit-or-beginning-of-line
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
bindkey -M vicmd  "/"     vi-history-search-backward
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
#}}}
# viins                                                                      {{{
bindkey -s -M viins "^T"  "\\\top\n"
bindkey -M viins "^K" up-line-or-history
bindkey -M viins "^J" down-line-or-history

autoload edit-command-line
bindkey -s -M viins '^V0' edit-command-line

bindkey -s -M viins "^X0" " &> /dev/null "
bindkey -s -M viins "^X1" "  > /dev/null "
bindkey -s -M viins "^X2" " 2> /dev/null "
bindkey -s -M viins "^X3" " 2>&1 "
bindkey -s -M viins "^G"  'setty background 161917\n'

#bindkey -M viins "^J"    accept-line
bindkey -M viins "^M"    accept-line
bindkey -M viins "^X^A"  all-matches
bindkey -M viins "^?"    backward-delete-char
bindkey -M viins "^H"    backward-delete-char
bindkey -M viins "^W"    backward-delete-word
bindkey -M viins "^B"    backward-word
bindkey -M viins "^[~"   _bash_complete-word
bindkey -M viins "^X~"   _bash_list-choices
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
bindkey -M viins "^E"    end-of-line
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
#}}}
# command {{{
bindkey -M command "^G" send-break
bindkey -M command "^C" send-break
#bindkey -M command "^J" send-break
bindkey -M command "^M" send-break
#}}}
# isearch                                                                    {{{
bindkey -M isearch " " self-insert
#}}}
# emacs                                                                      {{{
bindkey -M emacs "^[a"  accept-and-hold
bindkey -M emacs "^[A"  accept-and-hold
#bindkey -M emacs "^J"   accept-line
bindkey -M emacs "^M"   accept-line
bindkey -M emacs "^O"   accept-line-and-down-history
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
bindkey -M emacs "^E"   end-of-line
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
bindkey -M emacs "^K"   kill-line
bindkey -M emacs "^U"   kill-whole-line
bindkey -M emacs "^[d"  kill-word
bindkey -M emacs "^[D"  kill-word
bindkey -M emacs "^[^D" list-choices
bindkey -M emacs "^Xg"  list-expand
bindkey -M emacs "^XG"  list-expand
bindkey -M emacs "^[-"  neg-argument
bindkey -M emacs "^X^O" overwrite-mode
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
bindkey -M emacs "^G"   send-break
bindkey -M emacs "^[^G" send-break
bindkey -M emacs "^@"   set-mark-command
bindkey -M emacs "^[s"  spell-word
bindkey -M emacs "^[S"  spell-word
bindkey -M emacs "^[\$" spell-word
bindkey -M emacs "^T"   transpose-chars
bindkey -M emacs "^[t"  transpose-words
bindkey -M emacs "^[T"  transpose-words
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
#}}}
# redirection                                                                {{{
bindkey -s "^X0" " &> /dev/null "
bindkey -s "^X1" "  > /dev/null "
bindkey -s "^X2" " 2> /dev/null "
bindkey -s "^X3" " 2>&1 "
#}}}
# ranges                                                                     {{{
bindkey -R "!"-"~"         self-insert
bindkey -R "^Y"-"^Z"       self-insert
bindkey -R "^\\\\"-"^_"    self-insert
bindkey -R "\M-^@"-"\M-^?" self-insert
#}}}
# applications                                                               {{{
bindkey -s "^T" "top\n"
#bindkey -s "^V" "^Rvim\n"
bindkey -s "^Z" "urxvt -name shiva\n"

if [[ "$TERM" =~ 'screen' ]]; then
  bindkey -s '^n' 'tmux next-window\n'
  bindkey -s '^p' 'tmux previous-window\n'
fi
#}}}

#  remove all key bindings starting with ESC
bindkey -M vicmd -rp "^["
bindkey -M viins -rp "^["
# escape as fast as possible from insert mode
bindkey -M viins -rp '^['
bindkey -M viins     '^[' vi-cmd-mode

#bindkey "^N"      most-accessed-file
