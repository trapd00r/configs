#!/usr/bin/zsh
# File: $HOME/etc/zsh/02-completion.zsh
#  URL: https://github.com/trapd00r/configs/blob/master/zsh/02-completion.zsh
#
zstyle ':completion:*' verbose yes
zstyle ':completion:*:descriptions' format '%B%d%b'
zstyle ':completion:*:messages' format '%d'
zstyle ':completion:*:warnings' format 'No matches for: %d'
zstyle ':completion:*' group-name

### what completers to use?
#zstyle ':completion:*' completer _expand _complete _ignored _approximate _prefix

#zstyle ':completion:*:descriptions' format "- %{${fg[106]}%}%d%{${reset_color}%} -"
#zstyle ':completion:*:messages'     format "- %{${fg[cyan]}%}%d%{${reset_color}%} -"
#zstyle ':completion:*:default'      \
#  select-prompt \
#  "%{${fg[106]}%}Match %{${fg_bold[cyan]}%}%m%{${fg_no_bold[106]}%}  Line %{${fg_bold[cyan]}%}%l%{${fg_no_bold[red]}%}  %p%{${reset_color}%}"
#zstyle ':completion:*:default'      \
#  list-prompt   \
#  "%{${fg[106]}%}Line %{${fg_bold[cyan]}%}%l%{${fg_no_bold[106]}%}  Continue?%{${reset_color}%}"
#zstyle ':completion:*:warnings'     \
#  format        \
#  "- %{${fg_no_bold[red]}%}no match%{${reset_color}%} - %{${fg_no_bold[106]}%}%d%{${reset_color}%}"
#    zstyle ':completion:*' group-name ''
#    zstyle ':completion:*:descriptions' format "- %d -"
#    zstyle ':completion:*:messages'     format "- %d -"
#    zstyle ':completion:*:corrections'  format "- %d - (errors %e)"
#    zstyle ':completion:*:default'      select-prompt "Match %m  Line %l  %p"
#    zstyle ':completion:*:default'      list-prompt "Line %l  Continue?"
#    zstyle ':completion:*:warnings'     format "- no match - %d"
#    zstyle ':completion:*'              group-name ''

### manual pages are sorted into sections
zstyle ':completion:*:manuals'       separate-sections true
zstyle ':completion:*:manuals.(^1*)' insert-sections   true



zstyle ':completion:*:(^rmc?):*:(all-|)files' ignored-patterns '*?.o' '*?\~'


zstyle -e ':completion:*:approximate:*' max-errors 'reply=( $(( ($#PREFIX + $#SUFFIX) / 3 )) )'
### use caching for all completions
zstyle ':completion:*' use-cache on
zstyle ':completion:*' cache-path ${HOME}/var/zsh/
### add '..' dirs to completions
zstyle ':completion:*' special-dirs ..
### use perl
zstyle ':completion:*' use-perl on
### _urls setup
zstyle ':completion:*' urls ~/etc/zsh/urls

# make use of LS_COLORS                                                      {{{
zstyle ':completion:*:default'               list-colors ${(s.:.)LS_COLORS}
#}}}
zstyle ':completion:*'                       accept-exact      '*(N)'
zstyle ':completion:*'                       list-dirs-first   true
zstyle ':completion:*'                       matcher-list      'm:{a-z}={A-Z}'
#zstyle ':completion:*'                       menu select       200
zstyle ':completion:*'                       my-accounts       'm@japh.se'
zstyle ':completion:*'                       separate-sections 'yes'
zstyle ':completion:*'                       squeeze-slashes   true
zstyle ':completion:*'                       use-perl          1
zstyle ':completion:*' group-name            ''
zstyle ':completion:*:(all-|)files'          ignored-patterns '*.un~'
zstyle ':completion:*:functions'             ignored-patterns '_*'
#zstyle ':completion:most-accessed-file:*'    completer        _files
#zstyle ':completion:most-accessed-file:*'    file-patterns    '*:all\ files'
#zstyle ':completion:most-accessed-file:*'    file-sort        access
#zstyle ':completion:most-accessed-file:*'    hidden           all
#zstyle ':completion:most-accessed-file:*'    match-original   both
zstyle ':completion:*:*:*:users'             ignored-patterns \
  avahi bin daemon dbus ftp http mail nobody freenet
#}}}
# cd                                                                         {{{
zstyle ':completion:*:(cd):*'           group-order 'named-directories'
#zstyle ':completion:*:(cd):*'           ignore-parents parent pwd
zstyle ':completion:*:*:(cd):*'         completer _history
#zstyle ':completion:*:*:(cd):*'         menu select
#zstyle ':completion:*:*:(cd):*:*files' ignored-patterns '*~' file-sort access
#zstyle ':completion:*:*:(cd):*'        file-sort access
#}}}
zstyle ':completion:*:*:git:*' user-commands ${${(M)${(k)commands}:#git-*}/git-/}


# vim                                                                        {{{
#zstyle ':completion:*:*:(vim|rview|vimdiff|xxd):*' file-sort modification
#zstyle ':completion:*:*:(vim|rview|vimdiff|xxd):*' tag-order files
#zstyle ':completion:*:*:(vim|rview|vimdiff|xxd):*:*files' \
#  ignored-patterns '*~|*.(old|bak|zwc|viminfo|rxvt-*|zcompdump)|pm_to_blib|cover_db|blib' \
#  file-sort modification
#zstyle ':completion:*:vim:*:directories'           ignored-patterns \*
#}}}
# mplayer                                                                    {{{
zstyle ':completion:*:*:mplayer:*'           tag-order files
zstyle ':completion:*:*:mplayer:*'           ignored-patterns '*.(nfo|sfv|rar|r[0-9]|idx|srt)'
zstyle ':completion:*:*:mplayer:*'           ignored-patterns 'Sample|Subs|sample[.]*'
zstyle ':completion:*:*:mplayer:*'           file-patterns   \
  '*.(rmvb|mkv|mpe|mpg|mpeg|wmv|avi|flv|mp3|mp4|flac|ogg|webm|iso|img|mov|ts|vob|mov|m2v|asf|ogv):video' \
       '*:all-files' '*(-/):directories'
zstyle ':completion:*:*:ffprobe:*'           file-patterns   \
       '*.(rmvb|mkv|mpe|mpg|mpeg|wmv|avi|flv|mp3|mp4|flac|ogg|webm|iso|img|mov|ts|vob|mov|m2v|asf|ogv):video' \
       '*:all-files' '*(-/):directories'
zstyle ':completion:*:*:seen:*'           file-patterns   \
  '*.(rmvb|mkv|mpe|mpg|mpeg|wmv|avi|flv|mp4|webm|iso|img|mov|ts|vob|m2v|ogv):video' \
       '*:all-files' '*(-/):directories'
zstyle ':completion:*:*:mplayer_6ch_headphones:*' file-patterns '*.(dts|ac3|flac|mkv|mp4)(#i)' '*(-/):directories'
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
  'user@n950'  \
  'root@wrt54gl'
#zstyle ':completion:*:(ssh|scp):*:hosts-domain' ignored-patterns \
#  '<->.<->.<->.<->' '^*.*' '*@*'
#zstyle ':completion:*:(ssh|scp):*:users' ignored-patterns \
#      adm bin daemon halt lp named shutdown sync
# processes                                                                  {{{
zstyle ':completion:*:*:kill:*:processes' list-colors '=(#b) #([0-9]#)*=0=01;31'
zstyle ':completion:*:processes'             command 'ps -axw'
zstyle ':completion:*:processes-names'       command 'ps -awxho command'
zstyle ':completion:*:*:kill:*' menu yes select
zstyle ':completion:*:kill:*'   force-list always
#zstyle ':completion:*' menu select=10 interactive list-dirs-first
#}}}
# formats                                                                    {{{
zstyle ':completion:*:descriptions' \
  format $'%{- \e[38;5;137;1m\e[48;5;234m%}%B%d%b%{\e[m%}'
#zstyle ':completion:*:warnings' \
#  format $'%{\e[38;5;240;1m%}%d%{\e[m%}'
#}}}
#
zstyle ':completion:*:*:unrar:*'       ignored-patterns 'Sample|Subs'
zstyle ':completion:*:*:unrarec:*'    '*(-/):directories' 
zstyle ':completion:*:*:perl:*'        file-patterns '*'
zstyle ':completion:*:*:apvlv:*'       tag-order files
zstyle ':completion:*:*:apvlv:*'       file-patterns '*.pdf'

zstyle '*' single-ignored show

# vim: set ts=2 et sw=2 fdm=marker cc=:
