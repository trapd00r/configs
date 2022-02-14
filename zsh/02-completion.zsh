### vim: ft=zsh:fdm=marker:fml=1:fdl=0:fmr=<,>:smc&:cc&:
#< ${HOME}/etc/zsh/02-completion.zsh
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗
#         owner  Magnus Woldrich <magnus.woldrich@gmail.com>
#       crafted  2009-04-24
#         mtime  2016-09-05 15:26:36
#   permissions  You are free to use things you may find useful here.
#                Would my tweaks happen to give you a raise or fetch you a
#                girlfriend, it goes without saying I'm counting on you
#                to share with me as I've shared with you.
#           git  git://github.com/trapd00r/configs.git
#           url  http://github.com/trapd00r/configs/zsh
#           irc  japh@freenode #zsh #vim #perl
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗ ‗‗‗‗ ‗‗‗‗
#>
### zstyle :completion:<function>:<completer>:<command>:<argument>:<tag> _settings_

#< LS_COLORS
zstyle ':completion:*:default'               list-colors ${(s.:.)LS_COLORS}
zstyle '*' single-ignored show
#>
#< basics
zstyle ':completion:*'                          accept-exact      '*(N)'
zstyle ':completion:*'                          list-dirs-first   true
zstyle ':completion:*'                          matcher-list      'm:{a-z}={A-Z}'
zstyle ':completion:*'                          menu select       auto
zstyle ':completion:*'                          my-accounts       'm@japh.se'
zstyle ':completion:*'                          separate-sections yes
zstyle ':completion:*'                          squeeze-slashes   false
zstyle ':completion:*'                          use-perl          1
zstyle ':completion:*:(all-|)files'             ignored-patterns  '*.un~'
zstyle ':completion:*:functions'                ignored-patterns  '_*'
zstyle ':completion::complete:*'                cache-path        ${XDG_CONFIG_HOME}/cache/$HOST
zstyle ':completion::complete:*'                use-cache         on
zstyle ':completion:most-accessed-file:*'       completer         _files
zstyle ':completion:most-accessed-file:*'       file-patterns     '*:all\ files'
zstyle ':completion:most-accessed-file:*'       file-sort         access
zstyle ':completion:most-accessed-file:*'       hidden            all
zstyle ':completion:most-accessed-file:*'       match-original    both
zstyle ':completion:*:*:*:users'                ignored-patterns \
  avahi bin daemon dbus ftp http mail nobody

zstyle ':completion:*:cd:*'                     ignored-patterns '(*/)#lost+found'
zstyle ':completion:*:(mv|cp|file|m|mplayer):*' ignored-patterns '(#i)*.(url|mht)'

#zstyle ':completion:*'                       menu select      7 
#zstyle ':completion:*' group-name            ''
#>

###                                                                             ###
## -C will inhibit the check for new completion files, meaning you'll have to    ##
## manually delete .zcompdump or run compinit without -C. The -i flag will skip  ##
## the security check but still check for new completion files. It will ignore   ##
## the insecure files without asking, while -u will use them without asking.     ##
###                                                                             ###

#< compdefs
autoload -U age compinit relative
compinit -u
compdef     _gnu_generic c256 cc256 ln file vnstat vnstati lscpu lsb_release rtcontrol mktorrent plymouth
compdef     _feh         f ff
compdef     _files       mkdir mkdr
compdef     _mkdir       mkdr
compdef     _mplayer     m ms mplayer_redir mplayer_delete_current_file mplayer_headphones mplayer_6ch_headphones mplayer_redir
compdef     _hosts       ping 
compdef  -p _rm          rmc
compdef     _ls          vdir l ls++
compdef     _vim         vidir wim vi
compdef     _xterm       wxterm uxterm
compdef     _urxvt       xvt wrxvt
#compdef  -p _which        'we*' # XXX can be dangerous
#>
#< compinit
() {
  compinit -u
  local -a coreutils
  coreutils=(
    # /bin
    cat chgrp chmod chown cp date dd df dir ln ls mkdir mknod mv readlink
    rm rmdir vdir sleep stty sync touch uname mktemp
    # /usr/bin
    install hostid nice who users pinky stdbuf base64 basename chcon cksum
    comm csplit cut dircolors dirname du env expand factor fmt fold groups
    head id join link logname md5sum mkfifo nl nproc nohup od paste pathchk
    pr printenv ptx runcon seq sha1sum sha224sum sha256sum sha384sum
    sha512sum shred shuf sort split stat sum tac tail tee timeout tr
    truncate tsort tty unexpand uniq unlink wc whoami yes arch touch
  )
  for i in $coreutils; do
    # all which don't already have one
    # at time of this writing, those are:
    # /bin
    # chgrp chmod chown cp date dd df ln ls mkdir rm rmdir stty sync
    # touch uname
    # /usr/bin
    # nice comm cut du env groups id join logname md5sum nohup printenv
    # sort stat unexpand uniq whoami
    (( $+_comps[$i] )) || compdef _gnu_generic $i
  done
}
#>
#< cd
zstyle   ':completion:*:(cd):*'           group-order 'named-directories'
zstyle   ':completion:*:(cd):*'           ignore-parents parent pwd
#zstyle   ':completion:*:*:(cd):*'         completer _correct 
#zstyle ':completion:*' completer _complete _ignored

# completers in order of usefulness
zstyle ':completion:*' completer _expand _list _complete _match _ignored _prefix _approximate
zstyle ':completion:*' completer _expand _complete _ignored _approximate
#zstyle ':completion:*' completer _complete _history
zstyle ':completion:*' completer _complete 
#####
###### use caching for all completions
#####zstyle ':completion:*' use-cache on
#####zstyle ':completion:*' cache-path ${HOME}/var/zsh/
#####
###### add '..' dirs to completions
######zstyle ':completion:*' special-dirs ..
#####
###### use perl
zstyle ':completion:*' use-perl on
#####
###### XXX _urls setup
zstyle ':completion:*' urls ~/etc/zsh/urls
#####
########zstyle ':completion:*' accept-exact '*(N)'
#####zstyle ':completion:*' group-name ''
#####zstyle ':completion:*' list-dirs-first true
#####zstyle ':completion:*' matcher-list 'm:{a-z}={A-Z}'
#####
#####
###### '-e' is needed to get the argument evaluated each time this is called
###### this argument to max-errors allows one error in 10 characters.
######zstyle -e ':completion:*:approximate:*' max-errors \
######  'reply=( $(( ($#PREFIX + $#SUFFIX) / 10 )) )'
#####
######< reducing matches
######## functions starting with '_' are completion functions by convention
######## these are not supposed to be called by hand. no completion needed.
#####zstyle ':completion:*:(functions|parameters|association-keys)' ignored-patterns '_*'
#####
###### normally I don't want to complete *.o and *~, so, I'll ignore them, except
###### for rm, for obvious reasons
#####zstyle ':completion:*:(^rm):*:(all-|)files' ignored-patterns '*?.o' '*?\~'
#####
######## in my $HOME/bin dir there are often vim backups *~,
######## these are not to be completed...
######## i've got ${HOME}/bin/html/ which is no command, _do_not_complete_it!
######zstyle ':completion:*:complete:-command-::commands' ignored-patterns '(aptitude-*|html|*\~|haskell_count)'
#####
######## don't complete lost+found dirs for 'cd'
zstyle ':completion:*:cd:*' ignored-patterns '(*/)#lost+found'
#####
######## special completions for (mpg|ogg)123
#####zstyle ':completion:*:*:mpg123:*'  file-patterns '(#i)*.mp3:files:mp3\ files *(-/):directories:directories'
#####zstyle ':completion:*:*:ogg123:*'  file-patterns '(#i)*.ogg:files:ogg\ files *(-/):directories:directories'
#####zstyle ':completion:*:*:(mplayer|m|ms):*' file-patterns '(#i)*.(mkv|mp4|m4a|iso|wmv|webm|ogv|avi|mpg|mpeg|rmvb|iso|nrg):files:mplayer\ eats *(-/):directories:directories'
#####
######## weed out uninteresting users when completing '(command) ~<TAB>'
#####zstyle ':completion:*:*:*:*:users' ignored-patterns \
#####  bin daemon mail ftp http nobody dbus avahi ntp git usbmux mysql uuid kwakd
######>
######< formats
#zstyle ':completion:*:descriptions' format "- %{${fg[yellow]}%}%d%{${reset_color}%} -"
#zstyle ':completion:*:messages'     format "- %{${fg[cyan]}%}%d%{${reset_color}%} -"
#zstyle ':completion:*:corrections'  format "- %{${fg[yellow]}%}%d%{${reset_color}%} - (%{${fg[cyan]}%}errors %e%{${reset_color}%})"
#zstyle ':completion:*:default'      \
#  select-prompt \
#  "%{${fg[yellow]}%}Match %{${fg_bold[cyan]}%}%m%{${fg_no_bold[yellow]}%}  Line %{${fg_bold[cyan]}%}%l%{${fg_no_bold[red]}%}  %p%{${reset_color}%}"
#zstyle ':completion:*:default'      \
#  list-prompt   \
#  "%{${fg[yellow]}%}Line %{${fg_bold[cyan]}%}%l%{${fg_no_bold[yellow]}%}  Continue?%{${reset_color}%}"
#zstyle ':completion:*:warnings'     \
#  format        \
#  "- %{${fg_no_bold[red]}%}no match%{${reset_color}%} - %{${fg_no_bold[yellow]}%}%d%{${reset_color}%}"
zstyle ':completion:*' group-name ''

# zstyle ':completion:*:descriptions' format "- %d -"
# zstyle ':completion:*:messages'     format "- %d -"
# zstyle ':completion:*:corrections'  format "- %d - (errors %e)"
# zstyle ':completion:*:default'      select-prompt "Match %m  Line %l  %p"
# zstyle ':completion:*:default'      list-prompt "Line %l  Continue?"
# zstyle ':completion:*:warnings'     format "- no match - %d"
 zstyle ':completion:*'              group-name ''

######< list colorization
######## use $LS_COLORS for general completion
########   Note: (s.:.) splits ${LS_COLORS} into an array
######zstyle ':completion:*' list-colors ${(s.:.)LS_COLORS}
#####
######## highlight parameters with uncommon names
zstyle ':completion:*:parameters' list-colors "=[^a-zA-Z]*=$color[red]"
#####
######## highlight aliases
zstyle ':completion:*:aliases' list-colors "=*=$color[green]"
#####
######## show that _* functions are not for normal use
######## (not needed, since I don't complete _* functions at all)
######zstyle ':completion:*:functions' list-colors "=_*=$color[red]"
#####
######## highlight the original input.
zstyle ':completion:*:original' list-colors "=*=$color[red];$color[bold]"
#####
######## highlight words like 'esac' or 'end'
zstyle ':completion:*:reserved-words' list-colors "=*=$color[red]"
#####
######## colorize hostname completion
zstyle ':completion:*:*:*:*:hosts' \
list-colors "=*=$color[cyan];$color[bg-black]"
#####
######## colorize username completion
zstyle ':completion:*:*:*:*:users' \
list-colors "=*=$color[red];$color[bg-black]"
#####
######## colorize processlist for 'kill'
zstyle ':completion:*:*:kill:*:processes' \
list-colors "=(#b) #([0-9]#) #([^ ]#)*=$color[cyan]=$color[yellow]=$color[green]"
######>
######>
######< documentation
#####zstyle ':completion:*:manuals'       separate-sections true
#####zstyle ':completion:*:manuals.(^1*)' insert-sections   true
######>
######< menu completion/selection setup
#####
###### enable menu completion
######zstyle ':completion:*' menu auto
#####
###### enable verbose completion
######zstyle ':completion:*'              verbose yes
#####zstyle ':completion:*:-command-:*:' verbose no
#####
###### default menu selection for a few commands
#zstyle ':completion:*:*:(kill*|man):*' menu yes
zstyle ':completion:*:*:(kill*):*' menu yes
######
#####
###### if i have 'rm file0' on the commandline
###### i don't need "file0" in possible completions
zstyle ':completion:*:(rm|kill|mplayer|m|ms|f|feh|vim|file):*' ignore-line yes
#zstyle ':completion:*:*:*'   ignore-line yes
#####
######## $hosts for <tab> completing hostnames
zstyle ':completion:*:(nc|ping|ssh|nmap|*ftp|telnet|finger|mtr):*' hosts sid pi
#####
######## i like kill <tab>, but i want more processes...
zstyle ':completion:*:processes' command 'ps --forest -A -o pid,user,cmd'
zstyle ':completion:*:*:kill:*:processes' sort false
zstyle ':completion:*:processes-names' command 'ps c -u ${USER} -o command | uniq'
######>
######< sorting
zstyle ':completion:*:*:(gd):*' file-sort time
zstyle ':completion:*:*:(mplayer|m|ms|vim|feh|ls|du|file|cd):*' file-sort time
zstyle ':completion:*:*:(mplayer|vim|feh|ls|du|file|cd):*' file-sort time
zstyle ':completion:*:*:(mplayer|vim|feh|cd|ls|du|file):*' file-sort name
#zstyle ':completion:*:*:cd:*' file-sort name
zstyle ':completion:*:*:cd:*' file-sort time
######>
#####
######< init!
#####for i in computil complist ; do
#####    zrcmodload zsh/$i
#####done
######>
#####
######< compressed files
zstyle ':completion:*:*:unrar:*'        ignored-patterns 'Sample|Subs'
zstyle ':completion:*:*:unrar:*'        file-patterns '*.rar|*(-/):directories'
zstyle ':completion:*:*:unrarec:*'     '*(-/):directories'
######>
######< $ perl <anything>
zstyle ':completion:*:*:perl:*'         file-patterns '*'
######>
######< comics and pdfs
zstyle ':completion:*:*:(apvlv|xpdf):*' tag-order     files
zstyle ':completion:*:*:(apvlv|xpdf):*' file-patterns '(#i)*.pdf'
zstyle ':completion:*:*:(evince):*'     file-patterns '(#i)*.cb[rzt]'
######>
######< burning
#####zstyle ':completion:*:*:(wodim|xfburn):*'     file-patterns '(#i)*.{iso,img}'
######>
######< ssh
zstyle ':completion:*:*:scp:*'  ignored-patterns '*.(nfo|sfv|rar|r[0-9]|idx|srt|zip)'
zstyle ':completion:*:*:scp:*'  ignored-patterns '[Ss](ubs|ample|creens)[.]*'
zstyle ':completion:*:*:(scp):*' file-list true
zstyle ':completion:*:*:(scp):*' file-sort name
######>
######< chmod
zstyle ':completion:*:*:(chmod):*' extra-verbose true
######>
######< cd
zstyle ':completion:*:*:(cd):*' accept-exact-dirs false
zstyle ':completion:*:*:(cd):*' add-space         true
zstyle ':completion:*:*:(cd):*' ambiguous         true
zstyle ':completion:*:*:(cd):*' extra-verbose     false
#zstyle ':completion:*:*:(cd):*' extra-verbose     true
zstyle ':completion:*:*:(cd):*' force-list
zstyle ':completion:*:*:(cd):*' format            ''
zstyle ':completion:*:*:(cd):*' group-order       paths path-directories  directories  directory-stack bookmarks
zstyle ':completion:*:*:(cd):*' completer         _list _complete _expand _match
zstyle ':completion::complete:cd:*' tag-order \
'named-directories:-mine:extra\ directories
named-directories:-normal:named\ directories *'
zstyle ':completion::complete:cd:*:named-directories-mine' \
zstyle ':completion::complete:cd:*:named-directories-mine' \
######  ignored-patterns '*'
#####
#####
######>
######< git
zstyle ':completion:*:*:git:*' user-commands ${${(M)${(k)commands}:#git-*}/git-/}
######>
######< vim
zstyle ':completion:*:*:([vw]im|rview|vimdiff|xxd):*' tag-order files
zstyle ':completion:*:*:([vw]im|rview|vimdiff|xxd):*:*files' ignored-patterns \
'*~|*.(old|bak|zwc|viminfo|rxvt-*|zcompdump)|pm_to_blib|cover_db|blib' \
file-sort modification
#####zstyle ':completion:*:vim:*:directories'           ignored-patterns \*
######>
######< mplayer/ffmpeg
zstyle ':completion:*:*:mplayer:*'  tag-order files
zstyle ':completion:*:*:mplayer:*'  ignored-patterns '(#i)*.(nfo|sfv|rar|r[0-9]|idx|srt|zip)'
zstyle ':completion:*:*:mplayer:*'  ignored-patterns '[Ss](ubs|ample|creens)[.]*'
zstyle ':completion:*:*:mplayer:*'  file-patterns \
'*.(rmvb|mkv|mpe|mpg|mpeg|wmv|avi|flv|mp3|mp4|flac|ogg|webm|iso|img|mov|ts|vob|mov|m2v|asf|ogv|vob|VOB):video' \
'*:all-files' '*(-/):directories'
zstyle ':completion:*:*:ffprobe:*'           file-patterns   \
'*.(rmvb|mkv|mpe|mpg|mpeg|wmv|avi|flv|mp3|mp4|flac|ogg|webm|iso|img|mov|ts|vob|mov|m2v|asf|ogv):video' \
'*:all-files' '*(-/):directories'
zstyle ':completion:*:*:seen:*'           file-patterns   \
'*.(rmvb|mkv|mpe|mpg|mpeg|wmv|avi|flv|mp4|webm|iso|img|mov|ts|vob|m2v|ogv):video' \
'*:all-files' '*(-/):directories'
zstyle ':completion:*:*:mplayer_6ch_headphones:*' file-patterns '(#i)*.(dts|ac3|flac|mkv|mp4)' '*(-/):directories'


zstyle ':completion:*:*:xclip:*' file-patterns '(#i)*.(txt|pl|pm|sh|zsh|c|h|cpp|lua|vim|log|nfo)' '*:all-files' '*(-/):directories'
zstyle ':completion:*:*:xclip:*' ignored-patterns '(#i)*.(o||rar|r[0-9]|idx|srt|zip)'
######< insert all matches
#####zstyle ':completion:all-matches:*' old-matches true
#####zstyle ':completion:all-matches:*' insert      true
#####zle -C all-matches complete-word _generic
#####bindkey '^O' all-matches
######>
#####
######< XXX
#####zstyle ':completion:*' ambiguous         true
######zstyle ':completion:*:*:(ls):*' file-sort         modification
######
#######zstyle ':completion:*' completer _expand _list _complete _match _ignored _prefix _approximate
######zstyle ':completion:*' menu select=long
######zstyle ':completion:*' menu select=long-list
#####zstyle ':completion:*' menu auto=15
#####zstyle ':completion:*'  squeeze-slashes true
######
######zstyle ':completion:*:*:*'   ignore-line yes
######zstyle ':completion:*:*:*:*' file-sort   reverse size
#####
######zstyle ':completion:*:(all-|)files'           ignored-patterns '*.un~'
######zstyle ':completion:*:(^rmc?):*:(all-|)files' ignored-patterns '*?.o' '*?\~'
#####
#######zstyle ':completion:*:(cd):*' group-order 'named-directories'
#####zstyle ':completion:*:(cd):*' ignore-parents parent pwd
######zstyle ':completion:*:*:(cd):*' completer _history
######zstyle ':completion:*:*:(cd):*' file-sort time
######zstyle ':completion:*:*:(cd):*' menu select
#######zstyle ':completion:*:*:(cd):*:*files' ignored-patterns '*~' file-sort access
######
######zstyle '*' single-ignored show
######
######zstyle ':completion:*'  menu yes select
######zstyle ':completion:*'  force-list always
######>
######< most-accessed-file
#######zstyle ':completion:most-accessed-file:*' completer _files
#######zstyle ':completion:most-accessed-file:*' file-patterns '*:all\ files'
#######zstyle ':completion:most-accessed-file:*' file-sort access
#######zstyle ':completion:most-accessed-file:*' hidden all
#######zstyle ':completion:most-accessed-file:*' match-original both
######>
#####
#####
#####
######zstyle ':completion:*:*:(cd):*:*files' ignored-patterns '*~' file-sort access
######zstyle ':completion:*:*:(cd):*'        file-sort access
#####zstyle ':completion:*:*:(cd):*'        menu select
#####zstyle ':completion:*:*:(cd):*'        completer _history
#####
#####zstyle ':completion:*' file-patterns '*(-/):directories:directories %p(^-/):globbed-files' '*:all-files'
#####
#####zstyle ':completion:*' group-order globbed-files all-files files directories
#####_my-prev-result() {
#####    local hstring
#####    if [[ $WIDGET = *-all-* ]]; then
#####        compstate[insert]=all
#####    fi
#####    # Run last command again, save output in hstring
#####    hstring=$(eval $(fc -l -n -1))
#####    # Split items on new-line into an array, quote each item
#####    compadd - ${(@f)hstring}
#####}
#####
#####zle -C my-prev-comp menu-complete _my-prev-result
#####bindkey '\E' my-prev-comp
#####
#####zle -C my-all-prev-comp complete-word _my-prev-result
#####bindkey '^E' my-all-prev-comp
#>
#< completion for environment variable values
_comps[-value-,ASKAS_BUTIK,-default-]='compadd magnusw1 magnusw2 partner glitter'
#>
