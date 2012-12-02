#!/usr/bin/zsh
### vim: ft=zsh et sw=2 fen fdm=marker fml=2 fmr=#<,#> smc=140 tw=100 cc=:
#< ${HOME}/etc/zsh/020-completion.zsh
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗
#         owner  Magnus Woldrich <m@japh.se>
#       crafted  2009-04-24
#         mtime  2012-12-02 02:03:28
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

zstyle ':completion:*' file-patterns \
  '%p:globbed-files' \
  '*(-/):directories'\
  '*:all-files'

# completers in order of usefulness
zstyle ':completion:*' completer _expand _complete _ignored _approximate

# use caching for all completions
zstyle ':completion:*' use-cache on
zstyle ':completion:*' cache-path ${HOME}/var/zsh/

# add '..' dirs to completions
zstyle ':completion:*' special-dirs ..

# use perl
zstyle ':completion:*' use-perl on

# XXX _urls setup
zstyle ':completion:*' urls ~/etc/zsh/urls

zstyle ':completion:*' accept-exact '*(N)'
zstyle ':completion:*' group-name ''
zstyle ':completion:*' list-dirs-first true
zstyle ':completion:*' matcher-list 'm:{a-z}={A-Z}'


# '-e' is needed to get the argument evaluated each time this is called
# this argument to max-errors allows one error in 10 characters.
zstyle -e ':completion:*:approximate:*' max-errors \
  'reply=( $(( ($#PREFIX + $#SUFFIX) / 10 )) )'

#< reducing matches
### functions starting with '_' are completion functions by convention
### these are not supposed to be called by hand. no completion needed.
zstyle ':completion:*:(functions|parameters|association-keys)' ignored-patterns '_*'

# normally I don't want to complete *.o and *~, so, I'll ignore them, except
# for rm, for obvious reasons
zstyle ':completion:*:(^rm):*:(all-|)files' ignored-patterns '*?.o' '*?\~'

### in my $HOME/bin dir there are often vim backups *~,
### these are not to be completed...
### i've got ${HOME}/bin/html/ which is no command, _do_not_complete_it!
#zstyle ':completion:*:complete:-command-::commands' ignored-patterns '(aptitude-*|html|*\~|haskell_count)'

### don't complete lost+found dirs for 'cd'
zstyle ':completion:*:cd:*' ignored-patterns '(*/)#lost+found'

### special completions for (mpg|ogg)123
zstyle ':completion:*:*:mpg123:*' file-patterns '(#i)*.mp3:files:mp3\ files *(-/):directories:directories'
zstyle ':completion:*:*:ogg123:*' file-patterns '(#i)*.ogg:files:ogg\ files *(-/):directories:directories'

### weed out uninteresting users when completing '(command) ~<TAB>'
zstyle ':completion:*:*:*:*:users' ignored-patterns \
  bin daemon mail ftp http nobody dbus avahi ntp git usbmux mysql uuid kwakd
#>
#< formats
zstyle ':completion:*:descriptions' format "- %{${fg[yellow]}%}%d%{${reset_color}%} -"
zstyle ':completion:*:messages'     format "- %{${fg[cyan]}%}%d%{${reset_color}%} -"
zstyle ':completion:*:corrections'  format "- %{${fg[yellow]}%}%d%{${reset_color}%} - (%{${fg[cyan]}%}errors %e%{${reset_color}%})"
zstyle ':completion:*:default'      \
  select-prompt \
  "%{${fg[yellow]}%}Match %{${fg_bold[cyan]}%}%m%{${fg_no_bold[yellow]}%}  Line %{${fg_bold[cyan]}%}%l%{${fg_no_bold[red]}%}  %p%{${reset_color}%}"
zstyle ':completion:*:default'      \
  list-prompt   \
  "%{${fg[yellow]}%}Line %{${fg_bold[cyan]}%}%l%{${fg_no_bold[yellow]}%}  Continue?%{${reset_color}%}"
zstyle ':completion:*:warnings'     \
  format        \
  "- %{${fg_no_bold[red]}%}no match%{${reset_color}%} - %{${fg_no_bold[yellow]}%}%d%{${reset_color}%}"
zstyle ':completion:*' group-name ''

# zstyle ':completion:*:descriptions' format "- %d -"
# zstyle ':completion:*:messages'     format "- %d -"
# zstyle ':completion:*:corrections'  format "- %d - (errors %e)"
# zstyle ':completion:*:default'      select-prompt "Match %m  Line %l  %p"
# zstyle ':completion:*:default'      list-prompt "Line %l  Continue?"
# zstyle ':completion:*:warnings'     format "- no match - %d"
# zstyle ':completion:*'              group-name ''
#
#< list colorization
### use $LS_COLORS for general completion
###   Note: (s.:.) splits ${LS_COLORS} into an array
zstyle ':completion:*' list-colors ${(s.:.)LS_COLORS}

### highlight parameters with uncommon names
zstyle ':completion:*:parameters' list-colors "=[^a-zA-Z]*=$color[red]"

### highlight aliases
zstyle ':completion:*:aliases' list-colors "=*=$color[green]"

### show that _* functions are not for normal use
### (not needed, since I don't complete _* functions at all)
#zstyle ':completion:*:functions' list-colors "=_*=$color[red]"

### highlight the original input.
zstyle ':completion:*:original' list-colors "=*=$color[red];$color[bold]"

### highlight words like 'esac' or 'end'
zstyle ':completion:*:reserved-words' list-colors "=*=$color[red]"

### colorize hostname completion
zstyle ':completion:*:*:*:*:hosts' \
  list-colors "=*=$color[cyan];$color[bg-black]"

### colorize username completion
zstyle ':completion:*:*:*:*:users' \
  list-colors "=*=$color[red];$color[bg-black]"

### colorize processlist for 'kill'
zstyle ':completion:*:*:kill:*:processes' \
  list-colors "=(#b) #([0-9]#) #([^ ]#)*=$color[cyan]=$color[yellow]=$color[green]"
#>
#>
#< documentation
zstyle ':completion:*:manuals'       separate-sections true
zstyle ':completion:*:manuals.(^1*)' insert-sections   true
#>
#< menu completion/selection setup

# enable menu completion
zstyle ':completion:*' menu select

# enable verbose completion
zstyle ':completion:*'              verbose yes
zstyle ':completion:*:-command-:*:' verbose no

# default menu selection for a few commands
zstyle ':completion:*:*:(kill*|man):*' menu yes
#

# if i have 'rm file0' on the commandline
# i don't need "file0" in possible completions
zstyle ':completion:*:(rm|kill|mplayer|m|ms|f|feh):*' ignore-line yes

### $hosts for <tab> completing hostnames
zstyle ':completion:*:(nc|ping|ssh|nmap|*ftp|telnet|finger|mtr):*' hosts $hosts

### i like kill <tab>, but i want more processes...
zstyle ':completion:*:processes' command 'ps --forest -A -o pid,user,cmd'
zstyle ':completion:*:*:kill:*:processes' sort false
zstyle ':completion:*:processes-names' command 'ps c -u ${USER} -o command | uniq'
#>
#< sorting
zstyle ':completion:*:*:(mplayer|vim|feh|cd|ls|du|file):*' file-sort time
#>

#< init!
for i in computil complist ; do
    zrcmodload zsh/$i
done
#>

#< compressed files
zstyle ':completion:*:*:unrar:*'        ignored-patterns 'Sample|Subs'
zstyle ':completion:*:*:unrar:*'        file-patterns '*.rar|*(-/):directories'
zstyle ':completion:*:*:unrarec:*'     '*(-/):directories'
#>
#< $ perl <anything>
zstyle ':completion:*:*:perl:*'         file-patterns '*'
#>
#< comics and pdfs
zstyle ':completion:*:*:(apvlv|xpdf):*' tag-order     files
zstyle ':completion:*:*:(apvlv|xpdf):*' file-patterns '(#i)*.pdf'
zstyle ':completion:*:*:(mcomix):*'     file-patterns '(#i)*.cb[rzt]'
#>
#< burning
zstyle ':completion:*:*:(wodim|xfburn):*'     file-patterns '(#i)*.{iso,img}'
#>
#< ssh
zstyle ':completion:*:*:scp:*'  ignored-patterns '*.(nfo|sfv|rar|r[0-9]|idx|srt|zip)'
zstyle ':completion:*:*:scp:*'  ignored-patterns '[Ss](ubs|ample|creens)[.]*'
zstyle ':completion:*:*:(scp):*' file-list true
zstyle ':completion:*:*:(scp):*' file-sort name
#>
#< chmod
zstyle ':completion:*:*:(chmod):*' extra-verbose true
#>
#< cd
zstyle ':completion:*:*:(cd):*' accept-exact-dirs true
zstyle ':completion:*:*:(cd):*' add-space         true
zstyle ':completion:*:*:(cd):*' ambiguous         true
zstyle ':completion:*:*:(cd):*' extra-verbose     false
zstyle ':completion:*:*:(cd):*' force-list
zstyle ':completion:*:*:(cd):*' format            ''
zstyle ':completion:*:*:(cd):*' group-order       paths path-directories  directories  directory-stack bookmarks
#zstyle ':completion:*:*:(cd):*' completer         _list _complete _expand _match
#>
#< git
zstyle ':completion:*:*:git:*' user-commands ${${(M)${(k)commands}:#git-*}/git-/}
#>
#< vim
##zstyle ':completion:*:*:([vw]im|rview|vimdiff|xxd):*' file-sort modification
zstyle ':completion:*:*:([vw]im|rview|vimdiff|xxd):*' tag-order files
zstyle ':completion:*:*:([vw]im|rview|vimdiff|xxd):*:*files' ignored-patterns \
  '*~|*.(old|bak|zwc|viminfo|rxvt-*|zcompdump)|pm_to_blib|cover_db|blib' \
  file-sort modification
zstyle ':completion:*:vim:*:directories'           ignored-patterns \*
#>
#< mplayer/ffmpeg
zstyle ':completion:*:*:mplayer:*'  tag-order files
zstyle ':completion:*:*:mplayer:*'  ignored-patterns '*.(nfo|sfv|rar|r[0-9]|idx|srt|zip)'
zstyle ':completion:*:*:mplayer:*'  ignored-patterns '[Ss](ubs|ample|creens)[.]*'
zstyle ':completion:*:*:mplayer:*'  file-patterns \
  '*.(rmvb|mkv|mpe|mpg|mpeg|wmv|avi|flv|mp3|mp4|flac|ogg|webm|iso|img|mov|ts|vob|mov|m2v|asf|ogv):video' \
  '*:all-files' '*(-/):directories'
zstyle ':completion:*:*:ffprobe:*'           file-patterns   \
       '*.(rmvb|mkv|mpe|mpg|mpeg|wmv|avi|flv|mp3|mp4|flac|ogg|webm|iso|img|mov|ts|vob|mov|m2v|asf|ogv):video' \
       '*:all-files' '*(-/):directories'
zstyle ':completion:*:*:seen:*'           file-patterns   \
  '*.(rmvb|mkv|mpe|mpg|mpeg|wmv|avi|flv|mp4|webm|iso|img|mov|ts|vob|m2v|ogv):video' \
       '*:all-files' '*(-/):directories'
zstyle ':completion:*:*:mplayer_6ch_headphones:*' file-patterns '*.(dts|ac3|flac|mkv|mp4)(#i)' '*(-/):directories'
#>

#< insert all matches
zstyle ':completion:all-matches:*' old-matches true
zstyle ':completion:all-matches:*' insert      true
zle -C all-matches complete-word _generic
bindkey '^O' all-matches
#>

#< XXX
#zstyle ':completion:*' ambiguous         true
#zstyle ':completion:*:*:(ls):*' file-sort         modification
#
##zstyle ':completion:*' completer _expand _list _complete _match _ignored _prefix _approximate
##zstyle ':completion:*' menu 60
#zstyle ':completion:*'  squeeze-slashes false
##zstyle ':completion:*' fake-always /mnt/porn[123456]
##zstyle ':completion:*:(cd|file|mv):*'  fake-always '/mnt/porn5/pix/%models'
#
#zstyle ':completion:*:*:*'   ignore-line yes
#zstyle ':completion:*:*:*:*' file-sort   reverse size

#zstyle ':completion:*:(all-|)files'           ignored-patterns '*.un~'
#zstyle ':completion:*:(^rmc?):*:(all-|)files' ignored-patterns '*?.o' '*?\~'

##zstyle ':completion:*:(cd):*' group-order 'named-directories'
##zstyle ':completion:*:(cd):*' ignore-parents parent pwd
#zstyle ':completion:*:*:(cd):*' completer _history
#zstyle ':completion:*:*:(cd):*' file-sort time
#zstyle ':completion:*:*:(cd):*' menu select
##zstyle ':completion:*:*:(cd):*:*files' ignored-patterns '*~' file-sort access
#
#zstyle '*' single-ignored show
#
#zstyle ':completion:*'  menu yes select
#zstyle ':completion:*'  force-list always
#>
#< most-accessed-file
##zstyle ':completion:most-accessed-file:*' completer _files
##zstyle ':completion:most-accessed-file:*' file-patterns '*:all\ files'
##zstyle ':completion:most-accessed-file:*' file-sort access
##zstyle ':completion:most-accessed-file:*' hidden all
##zstyle ':completion:most-accessed-file:*' match-original both
#>
