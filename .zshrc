#######################################################
#						
# .zshrc		
# Massive tabcomplete support
# Nice ls colors :)
# Auto-ls-on-cd
# Predefined prompt variables 
# trapd00r@trapd00r.se
#########################################################

# auth with every newspawn shell
eval `keychain -q --eval id_dsa`

. $HOME/.zsh/zsh-alias

# autocomplete /mnt/*
export CDPATH='.:~:/mnt'

# FUCKING STUPID PIECE OF SHIT GNOMEBUG
export GCONF_LOCAL_LOCKS=1


# ln = link
# pi = pipe
# so = socket
# do = door
# bd = block device driver
# or = orphan
# ex = +x

#eval $(dircolors -b $HOME/.dircolors)
LS_COLORS='ow=01;30:ex=01;31:ln=01;32:*.pl=01;36:*.sh=01;31\
           :*.tar=01;33:*.tgz=01;33:*.zip=01;33:*.rar=01;33:*.gz=01;33\
           :*.png=01;34:*.jpg=01;34:di=01;34;1'
#LS_COLORS='no=00:fi=00:di=01;34:ln=01;36:pi=40;33:so=01;35:do=01;35:bd=40;33;01\
#           :cd=33;01:or=40;31;01:ex=01;32:*.tar=01;31:*.tgz=01;31\
#           :*.arj=01;31:*.taz=01;31:*.lzh=01;31:*.zip=01;31:*.z=01;31\
#           :*.Z=01;31:*.gz=01;31:*.bz2=01;31:*.deb=01;31:*.rpm=01;31\
#           :*.jar=01;31:*.jpg=01;35:*.jpeg=01;35:*.gif=01;35:*.bmp=01;35\
#           :*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35\
#           :*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.mpg=01;35\
#           :*.mpeg=01;35:*.avi=01;35:*.fli=01;35:*.gl=01;35:*.dl=01;35\
#           :*.xcf=01;35:*.xwd=01;35:*.ogg=01;35:*.mp3=01;35:*.wav=01;35\
#           :*.pl=01;31'
export LS_COLORS
TZ='Europe/Stockholm'; export TZ

# bindings
bindkey -v
bindkey "^?"    backward-delete-char
bindkey "^H"    backward-delete-char
bindkey "^[[3~" delete-char
bindkey "^[[1~" beginning-of-line
bindkey "^[[4~" end-of-line
bindkey '^r'    history-incremental-search-backward
bindkey "^[[5~" up-line-or-history
bindkey "^[[6~" down-line-or-history
bindkey "^A"    beginning-of-line
bindkey "^E"    end-of-line
bindkey "^W"    backward-delete-word
bindkey "^b"    backward-word
bindkey "^f"    forward-word
bindkey "^d"    delete-word
bindkey "^k"    kill-line
bindkey ' '     magic-space   
bindkey '^I'    complete-word 

# history
HISTFILE=$HOME/.zsh-history
HISTSIZE=5000
SAVEHIST=1000 
setopt   extended_history
setopt   share_history
function history-all { history -E 1 }

export TERM='rxvt-256color'
export PATH=~/bin:/bin:/usr/bin:/sbin:/usr/sbin:/usr/bin/perlbin/site:/usr/bin/perlbin/vendor:/usr/bin/perlbin/core
export MANPATH=$MANPATH:/usr/local/man:/opt/local/share/man
export EDITOR=vim
export PAGER=vimpager


# find bloat
du1 () { du -h --max-depth=1 "$@" | sort -k 1,1hr -k 2,2f; }

# ls-on-cd
cd() {builtin cd $@; ls }

# n/p pwd cd
xp () {
    echo $PWD | xclip -i
    xclip -o
}

xcd () {
    cd `xclip -o`
}

# PCRE regcheck
regcheck() {
    emulate -L zsh
    zmodload -i zsh/pcre
    pcre_compile $1 && \
    pcre_match $2 && echo "regex matches" || echo "regex does not match"
}


setopt PROMPT_SUBST
#setopt autopushd
#setopt NOTIFY
#setopt NO_FLOW_CONTROL
#setopt APPEND_HISTORY
# setopt AUTO_LIST
# setopt AUTO_REMOVE_SLASH
# setopt AUTO_RESUME		# tries to resume command of same name
unsetopt BG_NICE		# do NOT nice bg commands
##setopt EXTENDED_HISTORY		# puts timestamps in the history
##setopt HASH_CMDS		# turns on hashing
##setopt HIST_ALLOW_CLOBBER
##setopt HIST_REDUCE_BLANKS
#setopt INC_APPEND_HISTORY SHARE_HISTORY
setopt ALL_EXPORT
setopt   notify globdots pushdtohome cdablevars autolist
setopt   autocd recexact longlistjobs
setopt   autoresume histignoredups pushdsilent
setopt   autopushd pushdminus extendedglob rcquotes mailwarning
unsetopt bgnice autoparamslash
##zmodload -a zsh/stat stat
##zmodload -a zsh/zpty zpty
##zmodload -a zsh/zprof zprof
autoload -U compinit
compinit


##
## Time for the mess! Completion rules.
##

zstyle ':completion::complete:*' use-cache on
zstyle ':completion::complete:*' cache-path ~/.zsh/cache/$HOST
zstyle ':completion:*' list-colors ${(s.:.)LS_COLORS}
zstyle ':completion:*:processes' command 'ps -axw'
zstyle ':completion:*:processes-names' command 'ps -awxho command'
zstyle ':completion:*:*:kill:*:processes' list-colors '=(#b) #([0-9]#)*=0=01;31'
zstyle ':completion:*' hosts $(awk '/^[^#]/ {print $2 $3" "$4" "$5}' /etc/hosts | grep -v ip6- && grep "^#%" /etc/hosts | awk -F% '{print $2}') 
zstyle ':completion:*' matcher-list 'm:{a-z}={A-Z}'
zstyle ':completion:*:functions' ignored-patterns '_*'
zstyle ':completion:*:scp:*' tag-order \
   files users 'hosts:-host hosts:-domain:domain hosts:-ipaddr"IP\ Address *'
zstyle ':completion:*:scp:*' group-order \
   files all-files users hosts-domain hosts-host hosts-ipaddr
zstyle ':completion:*:ssh:*' tag-order \
   users 'hosts:-host hosts:-domain:domain hosts:-ipaddr"IP\ Address *'
zstyle ':completion:*:ssh:*' group-order \
   hosts-domain hosts-host users hosts-ipaddr

if [ -z "$LINES" ] || ! ( echo $LINES | grep -q '^[0-9]\+$' ) ; then
      LINES=20
fi

function maxhead() { head -n `echo $LINES - 5|bc` ; }
function maxtail() { tail -n `echo $LINES - 5|bc` ; }


##
## Messing around with prompts
##

#autoload -U promptinit
#promptinit
#prompt adam2


##
## Predefined prompt variables (there's more, but they didn't interest me)
##

local curdir="%d"
local hostname="%M"
local username="%n" 
local bold="%B"
local unbold="%b"
local standout="%S"
local unstandout="%s"
local colorfg="%F"
local uncolorfg="%f"
local colorbg="%K"
local uncolorbg="%k"
local mytime="%*"
local mydate="%D"
local line_tty="%y"
local rootorwhat="%#"
local return_status="%?"


#PROMPT="$username$bold$colorfg{blue}:${uncolorfg}$unbold$colorfg{cyan}$hostname${uncolorfg} : $colorfg{red}$curdir$uncolorfg$colorfg{yellow} »$uncolorfg "  

PROMPT="$bold$username$unbold$uncolorfg$bold$colorfg{red}@$unbold$uncolorfg$hostname | $colorfg{blue}$bold$curdir$unbold$uncolorfg
$colorfg{red}$bold»$unbold$uncolorfg "




#PROMPT="$colorfg{blue}$bold$curdir$unbold$uncolorfg
#$username$bold@$unbold$colorfg{grey}$hostname$uncolorfg$colorfg{yellow}$bold»$unbold$uncolorfg "

#PROMPT="$colorfg{green}┌───$uncolorfg$bold$curdir$unbold$colorfg{green}──────────────────┐$uncolorfg
#$username$bold$colorfg{blue}:${uncolorfg}$unbold$colorfg{cyan}$hostname${uncolorfg} $colorfg{yellow}»$uncolorfg "  

##
## Fucking bug with yaourt, this seems to somewhat solve the problem
##

#export color=


