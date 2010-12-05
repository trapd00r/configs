#vim: textwidth=0 nowrap ts=2:
alias -s {pl,pm,c,cpp,h,sh}='vim'
alias -s {mkv,avi}='mplayer'
alias -s PKGBUILD='vim'


alias com="cd $HOME/temp &&fetchit http://digest.bayzaar.com/ && feh -Z *.jpg"
alias top20="\cat $HOME/.zsh-history|perl -pe 's/^: [0-9]+:[0-9]+;\s*//'|sort|uniq -c|sort -n -k1|tail -20|tac"
alias pf='pickyfont ter7'
alias n900='ssh -p 19216 user@192.168.1.112'
alias rampeak='dd if=/dev/mem|\cat|strings'

alias lso='ls|pv -qL 10'

# Sane defaults
#alias make='make && su -c "make install"'
alias make='/home/scp1/devel/utils/make'
alias ,='cd -'
alias .='pwd'
alias ..='cd ..'
alias cp='cp -v'
#alias cp='ecp -th'
alias mv='mv -v'
alias rm='rm -v'
alias prename='prename -v'
alias grep='grep -Pi --color=auto'
alias grepp="grep -Pi --color=auto '^|pimpd'"
alias less='vimpager'
#alias make='make -j3'
alias :q='exit'
alias cat='v'
alias scat='source-highlight -o STDOUT -f esc -i'
alias npd='srinfo -np'
alias ptop='watch -n1 ps aux --sort=+%cpu'
alias wget='wget --no-check-certificate -U=Mozilla'
#alias vim="time vim -p $@ >> $HOME/vimtimes"
alias mproot="mplayer -wid $( xwininfo -root|perl -lne '@c=<>;$c[$.-47] =~ s/^xwin.+id: ([0-9A-Za-z]+)\s\(.+/$1/;print $c[$.-47]')"

#alias vimp="/home/scp1/devel/utils/vim $(find . |grep -Pi '.+(?:pl|pm)$'|perl -pe 's/\n/ /')"

alias a='cd $HOME/devel/trunk'
alias b='cd $HOME/bin'
alias c='cd $HOME/configs'
alias d='cd $HOME/devel'
alias dl='cd $HOME/devel/lib/Term::ExtendedColor/lib/Term'
alias e='cd $HOME/devel/exercises'
alias f="pickyfont monte1 normal && pickyfont monte2 bold && pickyfont pro1 italic"
alias g="cd $HOME/Git"
alias h='cd $HOME/devel/trapd00r.se'
alias i='cd $HOME/devel/fetchit'
alias l='cd $HOME/devel/lib'
alias m='cd $HOME/devel/pimpd/pimpd-ng'
#alias n='fc'
alias n='cd $HOME/httpd/NEWtrapd00r.se/all'
alias o='cd $HOME/devel/radiod'
alias p='cd $HOME/devel/pimpd'
alias pp='cd $HOME/devel/pimpd-ng2'
alias q='cd $HOME/devel/pickyfont'
alias r='cd $HOME/devel/rel'
#alias s="stumpish restore /home/scp1/configs/stump.group.dump"
alias t='mkdir -p /tmp/scp1 ; cd /tmp/scp1'
alias u='cd $HOME/devel/utils'
alias x='cd $XDG_CONFIG_HOME'
alias z='cd $HOME/.zsh'
alias sf='chmod +t,o+w "$@"'
 
# quick fontswitch / deprecated - http://github.com/trapd00r/pickyfont
alias 1="printf '\e]710;%s\007' "9x15bold,xft:Kochi Gothic""
alias 2='pickyfont -f speedy2'
alias 3='pickyfont -f progsole'
alias j='pickyfont -f terminus1'
alias jj='pickyfont -f terminus2'
#alias h='pickyfont -f fixed6'
alias hh='pickyfont -f fixed7'
alias k='pickyfont -f proggy1'
alias kk='pickyfont -f clea3'
#alias l='pickyfont -f profont2'
alias ll='pickyfont -f profont2'
alias lll='pickyfont -f profont4'

# git
alias gs='git status'
alias gl="PAGER=less;git log --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%an %cr)%Creset' --abbrev-commit --date=relative"
alias glp='gl -p'

#alias gl='git --no-pager log --pretty=oneline|tac'
alias gp='git push'
alias gd='git diff'
alias gc='git commit'

# cope
alias df='$HOME/bin/cope/df'
alias fdisk='$HOME/bin/cope/fdisk'
alias free='$HOME/bin/cope/free'
alias g++='$HOME/bin/cope/g++'
alias ifconfig='$HOME/bin/cope/ifconfig'
alias netstat='$HOME/bin/cope/netstat'
alias nmap='$HOME/bin/cope/nmap'
alias ps='$HOME/bin/cope/ps'

# file management
#alias ls='ls2'
#alias ls='pilsner'
alias ls='ls++'
#alias ls='colorls'
#alias ls='\ls -hovA --indicator-style=file-type --color=always --group-directories-first --time=ctime --time-style=full-iso' 
alias ls1='\ls -1 --color=auto --time-style=full-iso'
alias lsa='\ls --color=auto --time-style=full-iso'
alias lsd='find . -maxdepth 2 -type d | sort'
alias lsl='\ls -Ah --time-style=full-iso --color=auto --group-directories-first'
alias lss="\ls -1 --color=auto|grep '(^\w*[^_-])'"
alias lsq='ls -AlQ --color=always --time-style=full-iso'

# application sane defaults
alias iostat='iostat -mtx'
alias mp='mplayer -slave -input file=$HOME/.mplayer/fifo -msgcolor'
#alias dmesg='dmesg|matchline -dmesg'
alias dmesg='dmesgc|grep -v "TCP"'
alias lsusb='lsusb|matchline -random'
alias lspci='lspci|matchline -lspci'
alias feh='feh -Fzrd'
alias memusage='ps -e -orss=,args= | sort -b -k1,1n|pr -TW$COLUMNS'
#alias pacman='pacman-color'
alias pacman='packer'
alias scp='scp -P 19216'
alias urxvt='urxvt -name URxvt.shiva'
alias tree='tree -dA'

# other useful stuff
alias getmail='getmail --rcfile /home/scp1/.getmail/magnus_at_trapd00r.se && getmail --rcfile /home/scp1/.getmail/trapd00r_at_trapd00r.se'
alias shiva="ps -eo pcpu,pid,user,args|sort -k 1 -r|head -10 && iostat -mtx && mpstat -P 'ALL' && sar"
alias cpuu='ps -eo pcpu,pid,user,args | sort -k 1 -r | head -10'
alias ss='source $HOME/.zshrc'
alias ssa='mpc search artist'
alias v+='ossmix vmix0.pcm8 -- +2'
alias v-='ossmix vmix0.pcm8 -- -2'
alias vv+='ossmix vmix0.pcm9 -- +2'
alias vv-='ossmix vmix0.pcm9 -- -2'
alias vvv+='ossmix vmix0.pcm10 -- +2'
alias vvv+='ossmix vmix0.pcm10 -- -2'

alias trapd00r="printf '\t\033#3trapd00r\n\t\033#4trapd00r\n\tA simple, lightweight Perl hacker\n'"
alias trapd00rc="printf '\t\033#3\e[38;5;25mt\e[38;5;26mr\e[38;5;27ma\e[38;5;31mp\e[38;5;32md\e[38;5;33m0\e[38;5;33m0\e[38;5;37mr\n\t\033#4\e[38;5;133mt\e[38;5;134mr\e[38;5;135ma\e[38;5;139mp\e[38;5;140md\e[38;5;141m00\e[38;5;145mr\n\t\e[38;5;240mA simple, lightweight Perl hacker\n'"
alias rec='ffmpeg -f x11grab -s 3360x1050 -r 150 -i :0.0 -sameq /tmp/foo.mpg'
alias dvdc='ssh scp1@192.168.1.100 -p 19216'
alias india='ssh scp1@192.168.1.102 -p 19216'
alias fevil='find . -regextype posix-extended -regex'
alias mountfixbug='echo 64 > /sys/block/sdn/device/max_sectors && mount -a'
alias np='pimpd -i'
alias pdb='perl -d -e 1'
alias qi='qemu -cdrom iso -boot d hd'
alias rmvi='rm *.sw*'
alias R='rehash'
alias reset='printf "\033c\033(K\033[J\033[0m\033[?25h"'
alias scx='TERM=xterm;screen -x'
alias share='python -c "import SimpleHTTPServer;SimpleHTTPServer.test()"'
alias sortbycolumn='sort -n -k3'

alias win='wminput -c ir_ptr -w -c neverball&'
alias wim='wminput -c ir_ptr -w -c buttons-mame&'
alias wmp='wminput -c mplayer&'
alias wig='wminput -c gamepad&'
alias wit='wminput -c buttons-term&'
alias wir='wminput -c ir_ptr -w -c ir_ptr&'
alias wimp='(wminput -c mplayer&); mplayer'
alias wmp='wminput -c mplayer&'
