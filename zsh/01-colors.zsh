GREP_COLORS="38;5;230:sl=38;5;240:cs=38;5;100:mt=38;5;161;1:fn=38;5;197:ln=38;5;212:bn=38;5;44:se=38;5;166"

eval $( dircolors -b $HOME/dev/LS_COLORS/LS_COLORS )

export ACK_COLOR_MATCH="cyan bold"
export ACK_COLOR_FILENAME="cyan bold on_black"
export ACK_COLOR_LINENO="bold green"

export LS_COLORS GREP_COLORS

#if [ "$TERM" = "linux" ]; then
#
## a [8] at the end of the string will store the color
## as a default one
#
#    echo -en "\e]P01c1c1c" #black
#    echo -en "\e]P81c1c1c" #darkgrey
#    echo -en "\e]P1ff4747" #darkred
#    echo -en "\e]P9ff6767" #red
#    echo -en "\e]P24d4c4c" #darkgreen
#    echo -en "\e]PAb03b31" #green
#    echo -en "\e]P3ff8f00" #brown
#    echo -en "\e]PBbdf13d" #yellow
#    echo -en "\e]P41165e9" #darkblue
#    echo -en "\e]PC5496ff" #blue
#    echo -en "\e]P589005a" #darkmagenta
#    echo -en "\e]PDb50077" #magenta
#    echo -en "\e]P6cb1c13" #darkcyan
#    echo -en "\e]PE6be603" #cyan
#    echo -en "\e]P7ffffff" #lightgrey
#    echo -en "\e]PFdedede" #white
#    clear #for background artifacting
#    LS_COLORS="*.pl=01;35:ow=01;34:no=00:fi=00:di=01;33:ln=01;36:pi=40;33:so=01;35:bd=40;33;01:cd=40;33;01:or=01;05;37;41:mi=01;05;37;41:ex=01;32:*.cmd=01;32:*.exe=01;32:*.com=01;32:*.btm=01;32:*.bat=01;32:*.sh=01;32:*.csh=01;32:*.tar=01;31:*.tgz=01;31:*.arj=01;31:*.taz=01;31:*.lzh=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.gz=01;31:*.bz2=01;31:*.bz=01;31:*.tz=01;31:*.rpm=01;31:*.cpio=01;31:*.jpg=01;35:*.gif=01;35:*.bmp=01;35:*.xbm=01;35:*.xpm=01;35:*.png=01;35:*.tif=01;35:"
#    export LS_COLORS
#fi

