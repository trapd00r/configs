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

LS_COLORS='*.pl=01;31:*.sh=01;36:*.mp3=01;32:*.tar=01;33:*.tgz=01;33 \
           :*.zip=01;33:*.rar=01;33:*.gz=01;33:*.png=01;34:*.jpg=01;34'
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

export TERM=xterm
export PATH=~/bin:/bin:/usr/bin:/sbin:/usr/sbin:/usr/bin/perlbin/site:/usr/bin/perlbin/vendor:/usr/bin/perlbin/core
export MANPATH=$MANPATH:/usr/local/man:/opt/local/share/man
export EDITOR=vim
export PAGER=vimpager

alias gp='git push origin master'
# git init
# git add .
# git commit
# git remote add origin git@github.com:trapd00r/foo.git
# git push origin master


alias ..='cd ..'
alias b='cd $HOME/bin'
alias cp='cp -v'
alias d='cd $HOME/devel/'
alias def='echo -e "
          \033]50;-*-terminus-medium-*-normal-*-*-*-72-72-c-*-*-*\007"'
alias df='/home/scp1/bin/cope/df'
alias dmesg='dmesg|matchline -dmesg'
alias dvdc='ssh 192.168.1.33 -p 19216'
alias fdisk='/home/scp1/bin/cope/fdisk'
alias feh='feh -FZrd'
alias fevil='find . -regextype posix-extended -regex'
alias free='/home/scp1/bin/cope/free'
alias g1='cd /mnt/Games'
alias g2='cd /mnt/Games_2'
alias g='cd $HOME/devel/golf'
alias getpics='cp -r /mnt/camera/dcim/100canon /home/scp1/temp && \
               chown -R scp1:users /home/scp1/temp/100canon'
alias g++='/home/scp1/bin/cope/g++'
alias grep='grep -iE --color=auto '
alias hchk='rhash -c'
alias hide='echo -en "\033]50;nil2\007"'
alias horny='feh -FZr /mnt/Porn/01-Pics /mnt/Docs/.pik'
alias huge='echo -en "
           \033]50;-*-terminus-*-*-*-*-32-*-72-72-*-160-*-*\007"'
alias ifconfig='/home/scp1/bin/cope/ifconfig'
alias large='echo -en "
            \033]50;-misc-fixed-medium-r-normal-*-*-150-*-*-c-*-iso8859-15\007"'
alias less='vimpager'
alias ls1='\ls -1 --color=auto'
alias lsa='\ls --color=auto'
alias lsd='find . -maxdepth 2 -type d | sort'
alias ls='\ls -hovA --indicator-style=file-type \
          --color=always --group-directories-first --time=ctime \
          --time-style=long-iso'
alias lspci='lspci|matchline -lspci'
alias lsq='ls -AlQ --color=always'
alias lss="\ls -1|grep '(^\w*[^_-])'"
alias lsusb='lsusb|matchline -random'
alias m1='cd /mnt/Music_1'
alias m2='cd /mnt/Music_2'
alias m3='cd /mnt/Music_3'
alias m4='cd /mnt/Music_4'
alias m5='cd /mnt/Music_5'
alias make='make -j3'
alias man='echo -en "\033]50;-*-terminus-*-*-*-*-14-*-72-72-*-*-*-*\007" && \man'
alias m='cd $HOME/bin/mess'
alias medbold='echo -en "
              \033]50;-*-terminus-*-*-*-*-14-*-72-72-*-*-*-*\007"'
alias medium='echo -en "
              \033]50;-*-terminus-*-*-*-*-12-*-72-72-*-*-*-*\007"'
alias memusage='ps -e -orss=,args= | sort -b -k1,1n | pr -TW$COLUMNS'
alias mntmp3="mount /dev/$(dmesg|\tail -1|awk {'print $3'}| \
              perl -pe 's/[^a-z]//g') /mnt/mp3"
alias mo1='cd /mnt/Movies_1'
alias mo2='cd /mnt/Movies_2'
alias mo3='cd /mnt/Movies_3'
alias mountfixbug='echo 64 > /sys/block/sdn/device/max_sectors && mount -a'
alias mpd='mpd && scmpc && \tail -f $HOME/.scmpc.log'
alias mplayer='mplayer '
alias mv1='cd /mnt/Mvids'
alias mv='mv -v'
alias netstat='/home/scp1/bin/cope/netstat'
alias nmap='/home/scp1/bin/cope/nmap'
alias np='pimpd -i'
alias ob='startx /usr/bin/openbox-session -- /usr/bin/Xnest :2'
alias pacman='pacman-color'
alias pacrem='pacman -Rs $(pacman -Qtdq)'
alias pasta='wgetpaste -l Perl -X -s ca'
alias p='cd $HOME/devel/pimpd'
alias pdb='perl -d -e 1'
alias perldoc='echo -en "\033]50;-*-terminus-*-*-*-*-14-*-72-72-*-*-*-*\007" \
               && perldoc'
alias ping='/home/scp1/bin/cope/ping'
alias prename='prename -v '
alias ps='/home/scp1/bin/cope/ps'
alias :q='exit'
alias qi='qemu -cdrom iso -boot d hd'
alias rm='rm -v'
alias rmvi='rm *.swp'
alias R='rehash'
alias -s cbr=comical
alias -s chm=xchm
alias scp='scp -P 19216'
alias scx='screen -x'
alias share='python -c "import SimpleHTTPServer;SimpleHTTPServer.test()"'
alias small='echo -en "\033]50;6x10\007"'
alias sortbycolumn='sort -n -k3'
alias -s PKGBUILD=vim
alias t='cd $HOME/temp'
alias toy='mencoder -ovc lavc -lavcopts \
           vcodec=mpeg4:vbitrate=1000:vhq:keyint=250:threads=2:vpass=1 \
           -oac mp3lame -lameopts cbr:br=320'
alias tree='tree -dA'
alias tv1='cd /mnt/TV'
alias tv2='cd /mnt/TV_2'
alias urxvt='urxvt -name URxvt.shiva'
alias vol='ossmix mpd|awk ''{print $5,$10,$11}'''
alias vim='echo -en "\033]50;-*-terminus-*-*-*-*-14-*-72-72-*-*-*-*\007" && vim'
#alias wget='aria2c -Z'
alias wgeturlfromfile='wget -r -l1 -H -t1 -nd -N -np -A.jpg -erobots=off -i' 
alias x='cd $XDG_CONFIG_HOME'

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


