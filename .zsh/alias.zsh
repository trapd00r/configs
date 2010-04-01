# vim: textwidth=0 nowrap ts=2
alias -s {pl,pm,c,cpp,h,sh}='vim'
alias -s {mkv,avi}='mplayer'
alias -s PKGBUILD='vim'

# Sane defaults
alias .='pwd'
alias ..='cd ..'
alias cp='cp -v'
alias mv='mv -v'
alias rm='rm -v'
alias prename='prename -v'
alias grep='grep -Pi --color=auto'
alias less='vimpager'
alias make='make -j3'
alias :q='exit'
alias cat='vimpager'

alias c256='printf "\033[38;5;11m foobar"'
# shortcuts
alias a='cd $HOME/devel/trunk'
alias b='cd $HOME/bin'
alias c='cd $HOME/configs'
alias d='cd $HOME/devel'
alias g='cd $HOME/devel/golf'
alias p='cd $HOME/devel/pimpd'
alias t='cd $HOME/temp'
alias q='cd $HOME/devel/begperl'
alias x='cd $XDG_CONFIG_HOME'
alias z='cd $HOME/.zsh'

# documentation
#alias man="pickyfont -f profont4 && man"
#alias perldoc="pickyfont -f profont4 && perldoc"

 
# quick fontswitch / deprecated - http://github.com/trapd00r/pickyfont
alias 1="printf '\e]710;%s\007' "9x15bold,xft:Kochi Gothic""
alias 2='pickyfont -f speedy2'
alias 3='pickyfont -f progsole'
alias j='pickyfont -f terminus1'
alias jj='pickyfont -f terminus2'
alias h='pickyfont -f fixed6'
alias hh='pickyfont -f fixed7'
alias k='pickyfont -f proggy1'
alias kk='pickyfont -f clea3'
alias l='pickyfont -f profont2'
alias ll='pickyfont -f profont3'
alias lll='pickyfont -f profont4'




# git
alias gp='git push origin master'

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
alias ls='$HOME/bin/cope/ls -hovA --indicator-style=file-type \
          --color=always --group-directories-first --time=ctime \
          --time-style=full-iso'
alias ls1='\ls -1 --color=auto --time-style=full-iso'
alias lsa='\ls --color=auto --time-style=full-iso'
alias lsd='find . -maxdepth 2 -type d | sort'
alias lsl='ls -L --time-style=full-iso'
alias lss="\ls -1 --color=auto|grep '(^\w*[^_-])'"
alias lsq='ls -AlQ --color=always --time-style=full-iso'

# application sane defaults
alias iostat='iostat -mtx'
alias mplayer='mplayer -slave -input file=$HOME/.mplayer/fifo'
alias dmesg='dmesg|matchline -dmesg'
alias lsusb='lsusb|matchline -random'
alias lspci='lspci|matchline -lspci'
alias feh='feh -Fzrd'
alias memusage='ps -e -orss=,args= | sort -b -k1,1n|pr -TW$COLUMNS'
alias pacman='pacman-color'
alias scp='scp -P 19216'
alias urxvt='urxvt -name URxvt.shiva'
alias tree='tree -dA'

# other useful stuff
alias shiva="ps -eo pcpu,pid,user,args|sort -k 1 -r|head -10 && iostat -mtx && mpstat -P 'ALL' && sar"
alias cpuu='ps -eo pcpu,pid,user,args | sort -k 1 -r | head -10'
alias ss='source $HOME/.zshrc'
alias ssa='mpc search artist'
alias paste='curlpaste -l perl -s codepad -X'
alias s='stumpish restore-from-file code'
alias v+='ossmix vmix0.pcm8 -- +2'
alias v-='ossmix vmix0.pcm8 -- -2'
alias rec='ffmpeg -f x11grab -s 3360x1050 -r 150 -i :0.0 -sameq /tmp/foo.mpg'
alias dvdc='ssh scp1@192.168.1.33 -p 19216'
alias fevil='find . -regextype posix-extended -regex'
alias mountfixbug='echo 64 > /sys/block/sdn/device/max_sectors && mount -a'
alias np='pimpd -i'
alias pdb='perl -d -e 1'
alias qi='qemu -cdrom iso -boot d hd'
alias rmvi='rm *.sw*'
alias R='rehash'
alias reset='printf "\033c\033(K\033[J\033[0m\033[?25h"'
alias scx='screen -x'
alias share='python -c "import SimpleHTTPServer;SimpleHTTPServer.test()"'
alias sortbycolumn='sort -n -k3'
