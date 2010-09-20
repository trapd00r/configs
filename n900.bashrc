alias :q='exit'
alias ls='pilsner'
alias l='\ls --group-directories-first --color=auto'
alias d='cd /home/user/MyDocs'
alias b="cd /home/user/bin"
alias v='cd /home/user/MyDocs/Videos'
alias ..="cd .."
alias .="pwd"
alias ags='apt-cache search'
alias agi='apt-get install' 
alias agr='apt-get remove'
alias shiva='ssh -p 19216 scp1@192.168.1.101'
alias dvdc='ssh -p 19216 scp1@192.168.1.100'
alias india='ssh -p 19216 scp1@192.168.1.102'
alias ss='source $HOME/.bashrc'

export PATH="/home/user/bin:/usr/bin/gnu:$PATH"

export PS1="\[\e[36;1m\]\u\[\e[0m@\[\e[32;1m\]\H\[\e[0m | \[\e[31;1m\w \[\e[0m\n> \]"
set -o vi

LS_COLORS="*.hs=38;5;159:*.ini=38;5;122:*.part=38;5;240:*.pid=38;5;160:*.pod=38;5;106:*.vim=1:*.git=38;5;197:*.urlview=38;5;85:*.dump=38;5;119:*.conf=1:*.md=38;5;184:*.markdown=38;5;184:*.h=38;5;81:*.rb=38;5;192:*.c=38;5;110:*.diff=42;38:*.yml=38;5;208:*.PL=38;5;160:*.csv=38;5;78:tw=33;1;38;5;208:*.chm=38;5;144:*.bin=38;5;249:*.sms=38;5;33:*.pdf=38;5;203:*.cbz=38;5;140:*.cbr=38;5;140:*.nes=38;5;160:*.mpg=38;5;38:*.ts=38;5;39:*.sfv=38;5;191:*.m3u=38;5;172:*.txt=38;5;192:*.log=38;5;190:*.bash=38;5;173:*.swp=38;5;241:*.swo=38;5;236:*.theme=38;5;109:*.zsh=38;5;173:*.nfo=38;5;113:mi=38;5;124:or=38;5;160:ex=33;1;38;5;148:ln=target:pi=38;5;126:ow=33;1;38;5;208:di=38;5;30:*.pm=33;1;38;5;197:*.pl=38;5;214:*.sh=38;5;113:*.patch=45;37:*.tar=38;5;118:*.tar.gz=38;5;119:*.zip=38;5;11:*.rar=38;5;11:*.tgz=38;5;11:*.7z=38;5;11:*.mp3=38;5;191:*.flac=33;1;38;5;166:*.mkv=33;1;38;5;115:*.avi=38;5;114:*.wmv=38;5;113:*.jpg=38;5;66:*.jpeg=38;5;67:*.png=38;5;68:*.pacnew=38;5;33:*.xz=38;5;118:*.iso=38;5;124:*.css=38;5;91:*.php=38;5;93:*.gitignore=38;5;240:*.tmp=38;5;244:*.py=38;5;41"
export LS_COLORS
