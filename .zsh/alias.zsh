#vim: textwidth=0 nowrap ts=2:
alias -s {pl,pm,c,cpp,h,sh}='vim'
alias -s {mkv,avi}='mplayer'
alias -s PKGBUILD='vim'

alias com="cd $HOME/temp &&fetchit http://digest.bayzaar.com/ && feh -Z *.jpg"
alias top20="\cat $HOME/.zsh-history|perl -pe 's/^: [0-9]+:[0-9]+;\s*//'|sort|uniq -c|sort -n -k1|tail -20|tac"

# Sane defaults
alias .='pwd'
alias ..='cd ..'
alias cp='cp -v'
#alias cp='ecp -th'
alias mv='mv -v'
alias rm='rm -v'
alias prename='prename -v'
alias grep='grep -Pi --color=auto'
alias less='vimpager'
alias make='make -j3'
alias :q='exit'
alias cat='v'
alias scat='source-highlight -o STDOUT -f esc -i'
alias npd='srinfo -np'
alias ptop='watch -n1 ps aux --sort=+%cpu'
alias wget='wget -U=Mozilla'
alias vim='vim -p'
alias mproot="mplayer -wid $( xwininfo -root|perl -lne '@c=<>;$c[$.-47] =~ s/^xwin.+id: ([0-9A-Za-z]+)\s\(.+/$1/;print $c[$.-47]')"

alias a='cd $HOME/devel/trunk'
alias b='cd $HOME/bin'
alias c='cd $HOME/configs'
alias d='cd $HOME/devel'
alias e='cd $HOME/devel/exercises'
alias f="pickyfont monte1 normal && pickyfont monte2 bold && pickyfont pro1 italic"
alias g='cd $HOME/devel/golf'
alias h='cd $HOME/httpd/NEWtrapd00r.se'
alias i='cd $HOME/devel/fetchit'
alias l='cd $HOME/devel/lib'
alias m='cd $HOME/devel/pimpd/pimpd-ng'
#alias n='fc'
alias n='cd $HOME/httpd/NEWtrapd00r.se/all'
alias o='cd $HOME/devel/radiod'
alias p='cd $HOME/devel/pimpd'
alias q='cd $HOME/devel/pickyfont'
alias r='cd $HOME/devel/rel'
alias s="stumpish restore /home/scp1/configs/stump.group.dump"
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
alias gp='git push origin master'
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
alias ls='pilsner'
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
alias dmesg='dmesg|matchline -dmesg'
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
alias shiva="ps -eo pcpu,pid,user,args|sort -k 1 -r|head -10 && iostat -mtx && mpstat -P 'ALL' && sar"
alias cpuu='ps -eo pcpu,pid,user,args | sort -k 1 -r | head -10'
alias ss='source $HOME/.zshrc'
alias ssa='mpc search artist'
alias v+='ossmix vmix0.pcm8 -- +2'
alias v-='ossmix vmix0.pcm8 -- -2'
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
alias scx='screen -x'
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
