#!/usr/bin/zsh

bindkey -v
# main                                                                       {{{
bindkey "^J"    accept-line
bindkey "^M"    accept-line
bindkey "^X^A"  all-matches
bindkey "^?"    backward-delete-char
bindkey "^H"    backward-delete-char
bindkey "^W"    backward-delete-word
bindkey "^B"    backward-word
bindkey "^[~"   _bash_complete-word
bindkey "^X~"   _bash_list-choices
bindkey "^A"    beginning-of-line
bindkey "^[[1~" beginning-of-line
bindkey "^L"    clear-screen
bindkey "^X?"   _complete_debug
bindkey "^Xh"   _complete_help
bindkey "^Xt"   _complete_tag
bindkey "^I"    complete-word
bindkey "^XC"   _correct_filename
bindkey "^Xc"   _correct_word
bindkey "^[[3~" delete-char
bindkey "^D"    delete-word
bindkey "^[[B"  down-line-or-history
bindkey "^[OB"  down-line-or-history
bindkey "^[[6~" down-line-or-history
bindkey "^E"    end-of-line
bindkey "^[[4~" end-of-line
bindkey "^Xa"   _expand_alias
bindkey "^Xe"   _expand_word
bindkey "^F"    forward-word
bindkey "^[,"   _history-complete-newer
bindkey "^[/"   _history-complete-older
bindkey "^R"    history-incremental-search-backward
bindkey "^K"    kill-line
bindkey "^Xd"   _list_expansions
bindkey " "     magic-abbrev-expand
bindkey "^Xm"   _most_recent_file
bindkey "^Xn"   _next_tags
bindkey "^X "   no-magic-abbrev-expand
bindkey "^X^P"  pids
bindkey "^X^R"  _read_comp
bindkey "^C"    self-insert
bindkey "^O"    self-insert
bindkey "^S"    self-insert
bindkey "^X"    self-insert
bindkey "^[[A"  up-line-or-history
bindkey "^[OA"  up-line-or-history
bindkey "^[[5~" up-line-or-history
bindkey "^[[D"  vi-backward-char
bindkey "^[OD"  vi-backward-char
bindkey "^["    vi-cmd-mode
bindkey "^[[C"  vi-forward-char
bindkey "^[OC"  vi-forward-char
bindkey "^U"    vi-kill-line
bindkey "^Q"    vi-quoted-insert
#}}}
# vicmd                                                                      {{{
bindkey -a "^J"    accept-line
bindkey -a "^M"    accept-line
bindkey -a "^L"    clear-screen
bindkey -a "1"-"9" digit-argument
bindkey -a "^N"    down-history
bindkey -a "j"     down-line-or-history
bindkey -a "^[[B"  down-line-or-history
bindkey -a "^[OB"  down-line-or-history
bindkey -a ":"     execute-named-cmd
bindkey -a "="     list-choices
bindkey -a "^D"    list-choices
bindkey -a "^G"    list-expand
bindkey -a "#"     pound-insert
bindkey -a "^R"    redisplay
bindkey -a "^P"    up-history
bindkey -a "k"     up-line-or-history
bindkey -a "^[[A"  up-line-or-history
bindkey -a "^[OA"  up-line-or-history
bindkey -a "A"     vi-add-eol
bindkey -a "a"     vi-add-next
bindkey -a "B"     vi-backward-blank-word
bindkey -a "h"     vi-backward-char
bindkey -a "^H"    vi-backward-char
bindkey -a "^?"    vi-backward-char
bindkey -a "^[[D"  vi-backward-char
bindkey -a "^[OD"  vi-backward-char
bindkey -a "X"     vi-backward-delete-char
bindkey -a "b"     vi-backward-word
bindkey -a "c"     vi-change
bindkey -a "C"     vi-change-eol
bindkey -a "S"     vi-change-whole-line
bindkey -a "d"     vi-delete
bindkey -a "x"     vi-delete-char
bindkey -a "0"     vi-digit-or-beginning-of-line
bindkey -a "+"     vi-down-line-or-history
bindkey -a "\$"    vi-end-of-line
bindkey -a "G"     vi-fetch-history
bindkey -a "f"     vi-find-next-char
bindkey -a "t"     vi-find-next-char-skip
bindkey -a "F"     vi-find-prev-char
bindkey -a "T"     vi-find-prev-char-skip
bindkey -a "\^"    vi-first-non-blank
bindkey -a "W"     vi-forward-blank-word
bindkey -a "E"     vi-forward-blank-word-end
bindkey -a "l"     vi-forward-char
bindkey -a "^[[C"  vi-forward-char
bindkey -a "^[OC"  vi-forward-char
bindkey -a " "     vi-forward-char
bindkey -a "w"     vi-forward-word
bindkey -a "e"     vi-forward-word-end
bindkey -a "|"     vi-goto-column
bindkey -a "\`"    vi-goto-mark
bindkey -a "'"     vi-goto-mark-line
bindkey -a "/"     vi-history-search-backward
bindkey -a "?"     vi-history-search-forward
bindkey -a ">"     vi-indent
bindkey -a "i"     vi-insert
bindkey -a "I"     vi-insert-bol
bindkey -a "J"     vi-join
bindkey -a "D"     vi-kill-eol
bindkey -a "%"     vi-match-bracket
bindkey -a "O"     vi-open-line-above
bindkey -a "o"     vi-open-line-below
bindkey -a "p"     vi-put-after
bindkey -a "P"     vi-put-before
bindkey -a "."     vi-repeat-change
bindkey -a ";"     vi-repeat-find
bindkey -a "n"     vi-repeat-search
bindkey -a "R"     vi-replace
bindkey -a "r"     vi-replace-chars
bindkey -a ","     vi-rev-repeat-find
bindkey -a "N"     vi-rev-repeat-search
bindkey -a "\""    vi-set-buffer
bindkey -a "m"     vi-set-mark
bindkey -a "s"     vi-substitute
bindkey -a "~"     vi-swap-case
bindkey -a "u"     vi-undo-change
bindkey -a "<"     vi-unindent
#bindkey -a "-"     vi-up-line-or-history
bindkey -a "y"     vi-yank
bindkey -a "Y"     vi-yank-whole-line
#}}}
# viins                                                                      {{{
bindkey -s -M viins "^T"  "\\\top\n"

autoload edit-command-line
bindkey --s -M viins '^V0' edit-command-line

bindkey -s -M viins "^X0" " &> /dev/null "
bindkey -s -M viins "^X1" "  > /dev/null "
bindkey -s -M viins "^X2" " 2> /dev/null "
bindkey -s -M viins "^X3" " 2>&1 "
bindkey -s -M viins "^G"  'setty background 161917\n'

bindkey -R -M viins "^Y"-"^Z" self-insert
bindkey -R -M viins "\M-^@"-"\M-^?" self-insert
bindkey -R -M viins "^\\\\"-"^_" self-insert
bindkey -R -M viins "!"-"~"      self-insert
bindkey -R -M viins "^N"-"^P"   self-insert
bindkey -M viins "^C"           self-insert
bindkey -M viins "^S"           self-insert
bindkey -M viins "^X"           self-insert

bindkey -M viins "^J"    accept-line
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
bindkey -M viins "^K"    kill-line
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
bindkey -M command "^J" send-break
bindkey -M command "^M" send-break
#}}}
# isearch                                                                    {{{
bindkey -M isearch " " self-insert
#}}}
# emacs                                                                      {{{
bindkey -M emacs "^[a"  accept-and-hold
bindkey -M emacs "^[A"  accept-and-hold
bindkey -M emacs "^J"   accept-line
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
bindkey -s "^V" "^Rvim\n"
bindkey -s "^Z" "urxvt -name shiva\n"

if [[ "$TERM" =~ 'screen' ]]; then
  bindkey -s '^n' 'tmux next-window\n'
  bindkey -s '^p' 'tmux previous-window\n'
fi
#}}}

#bindkey "^N"      most-accessed-file
