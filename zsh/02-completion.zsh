#!/usr/bin/zsh
# File: $HOME/etc/zsh/02-completion.zsh
#  URL: https://github.com/trapd00r/configs/blob/master/zsh/02-completion.zsh

# make use of LS_COLORS                                                      {{{
zstyle ':completion:*:default'               list-colors ${(s.:.)LS_COLORS}
#}}}
# for everything                                                             {{{
zstyle ':completion:*'                       accept-exact      '*(N)'
zstyle ':completion:*'                       list-dirs-first   true
zstyle ':completion:*'                       matcher-list      'm:{a-z}={A-Z}'
zstyle ':completion:*'                       menu select       200
zstyle ':completion:*'                       my-accounts       'm@japh.se'
zstyle ':completion:*'                       separate-sections 'yes'
zstyle ':completion:*'                       squeeze-slashes   true
zstyle ':completion:*'                       use-perl          1
zstyle ':completion:*' group-name            ''
zstyle ':completion:*:(all-|)files'          ignored-patterns '*.un~'
zstyle ':completion:*:functions'             ignored-patterns '_*'
zstyle ':completion::complete:*'             cache-path       ~/etc/cache/$HOST
zstyle ':completion::complete:*'             use-cache        on
zstyle ':completion:most-accessed-file:*'    completer        _files
zstyle ':completion:most-accessed-file:*'    file-patterns    '*:all\ files'
zstyle ':completion:most-accessed-file:*'    file-sort        access
zstyle ':completion:most-accessed-file:*'    hidden           all
zstyle ':completion:most-accessed-file:*'    match-original   both
zstyle ':completion:*:*:*:users'             ignored-patterns \
  avahi bin daemon dbus ftp http mail nobody
#}}}
# cd                                                                         {{{
zstyle ':completion:*:(cd):*'           group-order 'named-directories'
zstyle ':completion:*:(cd):*'           ignore-parents parent pwd
zstyle ':completion:*:*:(cd):*'         completer _history
zstyle ':completion:*:*:(cd):*'         menu select
#zstyle ':completion:*:*:(cd):*:*files' ignored-patterns '*~' file-sort access
#zstyle ':completion:*:*:(cd):*'        file-sort access
#}}}
# vim                                                                        {{{
zstyle ':completion:*:*:(vim|rview|vimdiff|xxd):*' file-sort name
zstyle ':completion:*:*:(vim|rview|vimdiff|xxd):*' tag-order files
zstyle ':completion:*:*:(vim|rview|vimdiff|xxd):*:*files' \
  ignored-patterns '*~|*.(old|bak|zwc|viminfo|rxvt-*|zcompdump)|pm_to_blib|cover_db|blib' \
  file-sort modification
#zstyle ':completion:*:vim:*:directories'           ignored-patterns \*
#}}}
# mplayer                                                                    {{{
zstyle ':completion:*:*:mplayer:*'           tag-order files
zstyle ':completion:*:*:mplayer:*'           file-patterns   \
       '*.(rmvb|mkv|mpg|wmv|mpeg|avi|flv|mp3|mp4|flac|ogg|webm|iso|img):video' \
       '*:all-files' '*(-/):directories'
#}}}
# ssh                                                                        {{{
zstyle ':completion:*:*:(scp):*' file-list true
zstyle ':completion:*:*:(scp):*' file-sort name
zstyle ':completion:*:scp:*'     group-order \
  files all-files users hosts-host hosts-ipaddr

zstyle ':completion:*:ssh:*'     tag-order \
  users 'hosts:-host hosts:-ipaddr:IP\ address hosts:-domain:domain *'
zstyle ':completion:*:ssh:*'     group-order hosts-host users hosts-ipaddr

zstyle ':completion:*:(ssh|scp):*:hosts-host' ignored-patterns \
  '*.*' loopback localhost

zstyle ':completion:*:(ssh|scp):*:hosts-ipaddr' ignored-patterns \
  '^<->.<->.<->.<->' '127.0.0.<->'

zstyle ':completion:*:(ssh|scp):*:my-accounts' users-hosts \
  'scp1@laleh' \
  'scp1@rambo' \
  'scp1@india' \
  'user@n900'  \
  'root@wrt54gl'
#zstyle ':completion:*:(ssh|scp):*:hosts-domain' ignored-patterns \
#  '<->.<->.<->.<->' '^*.*' '*@*'
#zstyle ':completion:*:(ssh|scp):*:users' ignored-patterns \
#      adm bin daemon halt lp named shutdown sync
#}}}
# Go                                                                         {{{
go_prefixes=(5 6 8)
for p in $prefixes; do
  compctl -g "*.${p}" ${p}l
  compctl -g "*.go"   ${p}g
done
compctl -g "*.go" gofmt
compctl -g "*.go" gccgo
#}}}
# processes                                                                  {{{
zstyle ':completion:*:*:kill:*:processes' list-colors '=(#b) #([0-9]#)*=0=01;31'
zstyle ':completion:*:processes'             command 'ps -axw'
zstyle ':completion:*:processes-names'       command 'ps -awxho command'
#zstyle ':completion:*:*:kill:*' menu yes select
#zstyle ':completion:*:kill:*'   force-list always
#zstyle ':completion:*' menu select=10 interactive list-dirs-first
#}}}
# formats                                                                    {{{
zstyle ':completion:*:descriptions' \
  format $'%{- \e[38;5;137;1m\e[48;5;234m%}%B%d%b%{\e[m%}'
#zstyle ':completion:*:warnings' \
#  format $'%{\e[38;5;240;1m%}%d%{\e[m%}'
#}}}

zstyle ':completion:*:*:perl:*'        file-patterns '*'
zstyle ':completion:*:*:apvlv:*'       tag-order files
zstyle ':completion:*:*:apvlv:*'       file-patterns '*.pdf'

zstyle '*' single-ignored show

# vim: set ts=2 et sw=2 fdm=marker:
