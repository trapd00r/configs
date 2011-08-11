#!/usr/bin/zsh

zstyle ':completion:*'                       accept-exact '*(N)'
zstyle ':completion:*'                       separate-sections 'yes'
zstyle ':completion:*'                       list-dirs-first true
zstyle ':completion:*:default'               list-colors ${(s.:.)LS_COLORS}
zstyle ':completion:*'                       menu select=200
zstyle ':completion:*'                       use-perl=1
zstyle ':completion:*'                       my-accounts='m@japh.se'

zstyle ':completion:*'                       squeeze-slashes true
zstyle ':completion:*:cd:*'                  ignore-parents parent pwd
#zstyle ':completion:*:cd:*'                  tag-order 'named-directories'

zstyle ':completion:*:(all-|)files'          ignored-patterns '*.un~'
zstyle ':completion:*:*:kill:*:processes' \
  list-colors '=(#b) #([0-9]#)*=0=01;31'

zstyle ':completion::complete:*'             use-cache on
zstyle ':completion::complete:*'             cache-path ~/etc/cache/$HOST
zstyle ':completion:*:processes'             command 'ps -axw'
zstyle ':completion:*:processes-names'       command 'ps -awxho command'
zstyle ':completion:*'                       matcher-list 'm:{a-z}={A-Z}'
zstyle ':completion:*:functions'             ignored-patterns '_*'

zstyle ':completion:*' group-name            ''
zstyle ':completion:*:*:mplayer:*'           tag-order files
zstyle ':completion:*:*:mplayer:*'           file-patterns   \
       '*.(rmvb|mkv|mpg|wmv|mpeg|avi|flv|mp3|mp4|flac|ogg):video' \
       '*:all-files' '*(-/):directories'

zstyle ':completion:*:*:(vim|rview|vimdiff|xxd):*:*files' \
  ignored-patterns '*~|*.(old|bak|zwc|viminfo|rxvt-*|zcompdump)|pm_to_blib|cover_db|blib' \
  file-sort modification
zstyle ':completion:*:*:(vim|rview|vimdiff|xxd):*' \
  file-sort modification
zstyle ':completion:*:*:(vim|rview|vimdiff|xxd):*' \
  tag-order files
#zstyle ':completion:*:vim:*:directories' ignored-patterns \*

zstyle ':completion:*:*:(scp):*' \
  file-sort modification

zstyle ':completion:*:*:(cd):*:*files' ignored-patterns '*~' file-sort access
zstyle ':completion:*:*:(cd):*'        file-sort access
zstyle ':completion:*:*:(cd):*'        menu select
zstyle ':completion:*:*:(cd):*'        completer _history

zstyle ':completion:*:*:perl:*'        file-patterns '*'


zstyle ':completion:*:descriptions' \
  format $'%{- \e[38;5;137;1m\e[48;5;234m%}%B%d%b%{\e[m%}'
zstyle ':completion:*:warnings' \
  format $'%{No match for \e[38;5;240;1m%}%d%{\e[m%}'

zstyle ':completion:*:*:apvlv:*'             tag-order files
zstyle ':completion:*:*:apvlv:*'             file-patterns '*.pdf'

zstyle ':completion:most-accessed-file:*' match-original both
zstyle ':completion:most-accessed-file:*' file-sort access
zstyle ':completion:most-accessed-file:*' file-patterns '*:all\ files'
zstyle ':completion:most-accessed-file:*' hidden all
zstyle ':completion:most-accessed-file:*' completer _files


zstyle ':completion:*:scp:*' group-order \
      users files all-files hosts-domain hosts-host hosts-ipaddr

zstyle ':completion:*:ssh:*' tag-order \
      users 'hosts:-host hosts:-domain:domain hosts:-ipaddr:IP\ address *'

zstyle ':completion:*:ssh:*' group-order \
      hosts-domain hosts-host users hosts-ipaddr

zstyle ':completion:*:(ssh|scp):*:hosts-host' ignored-patterns \
      '*.*' loopback localhost

zstyle ':completion:*:(ssh|scp):*:hosts-domain' ignored-patterns \
      '<->.<->.<->.<->' '^*.*' '*@*'

zstyle ':completion:*:(ssh|scp):*:hosts-ipaddr' ignored-patterns \
      '^<->.<->.<->.<->' '127.0.0.<->'

zstyle ':completion:*:(ssh|scp):*:users' ignored-patterns \
      adm bin daemon halt lp named shutdown sync

zstyle ':completion:*:(ssh|scp):*:my-accounts' users-hosts \
  'scp1@192.168.1.100' 'scp1@brutus.ethup.se' 'trapd00r@90.225.22.81'


zstyle ':completion:*:*:*:users' ignored-patterns \
        adm amanda apache avahi beaglidx bin cacti canna clamav daemon \
        dbus distcache dovecot fax ftp games gdm gkrellmd gopher \
        hacluster haldaemon halt hsqldb ident junkbust ldap lp mail \
        mailman mailnull mldonkey mysql nagios \
        named netdump news nfsnobody nobody nscd ntp nut nx openvpn \
        operator pcap postfix postgres privoxy pulse pvm quagga radvd \
        rpc rpcuser rpm shutdown squid sshd sync uucp vcsa xfs
zstyle '*' single-ignored show

#zstyle ':completion:*:options'               menu search



go_prefixes=(5 6 8)
for p in $prefixes; do
  compctl -g "*.${p}" ${p}l
  compctl -g "*.go"   ${p}g
done
compctl -g "*.go" gofmt
compctl -g "*.go" gccgo


#zstyle ':completion:*:*:kill:*' menu yes select
#zstyle ':completion:*:kill:*'   force-list always
#zstyle ':completion:*' menu select=10 interactive list-dirs-first


# vim: set ts=2 et sw=2 fdm=marker:
