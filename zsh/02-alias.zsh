###< vim: set ft=zsh:fdm=marker:fmr=#<,#>:fdl=0:fen:et:sw=2:fcl=all:
###
#      ${HOME}/etc/zsh/02-alias.zsh
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗
#         owner  Magnus Woldrich <magnus.woldrich@gmail.com>
#         btime  2009-04-24
#         mtime  2019-01-13 09:31:39
#   permissions  You are free to use things you may find useful here.
#                Would my tweaks happen to give you a raise or fetch you a
#                girlfriend, it goes without saying I'm counting on you
#                to share with me as I've shared with you.
#           git  http://github.com/trapd00r/configs/zsh  (up-to-date)
#           url  http://devel.japh.se/configs/zsh        (sync 1/24h)
#           irc  japh@freenode #zsh #vim #perl
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗ ‗‗‗‗ ‗‗‗‗
###
###>

alias rg="rg -T sql -T css -T html --colors 'match:bg:255' --colors 'match:fg:196' --colors 'line:fg:32' --colors 'path:fg:208'"
alias beet="~/dev/beets/beet"
#alias beet="~/dev/_upstream/beets-ui/beet"

#alias lltag="lltag --id3v2 --config $XDG_CONFIG_HOME/lltag.conf"
alias lltag="lltag --config $XDG_CONFIG_HOME/lltag.conf"
alias plexamp='Plexamp.appimage --no-sandbox'
alias evernote='tusk'
#< basics
alias      cp='cp -v'
alias      mv='mv -v'
alias      rm='rmc -v'
#alias      rm='/bin/rm -v'
#alias     grep=ack
alias    grep='grep -iI -P --exclude-dir=".git" --color=auto'
alias     cat="$HOME/dev/vimcat/vimcat"
alias yaourt='trizen'

alias      ls='perl /home/scp1/dev/ls--/ls++' 
alias     lsl='perl /home/scp1/dev/ls--/ls++' 
alias     lls='perl /home/scp1/dev/ls--/ls++' 
alias     lss='perl /home/scp1/dev/ls--/ls++ -Sr'
alias     lst='perl /home/scp1/dev/ls--/ls++ -tr'
alias     lsr='perl /home/scp1/dev/ls--/ls++ --sort=time -r'
alias  pacman='pacman --color=auto'
alias prename='prename -v'
alias     vim='time-spent-in-vim'
alias    cpan='cpanm'
alias     top='xcolor woldrich 2>/dev/null; htop'
alias     :q!='kill -9 $$'
alias      :q='exit'
alias     die='kill -9 $$'
alias   dmesg='/home/scp1/dev/Term-ExtendedColor/bin/colored_dmesg|/bin/grep -viP "TCP|ipv6|audit"'
alias      gd='GIT_PAGER="" git diff'
alias     scd='/bin/screen -d'
alias   share='perl $HOME/dev/cpan-mirror-server-http/bin/cpanmirrorhttpd --verbose --root . --port 8080'
alias    wget='wget --no-check-certificate -U=Mozilla'

alias       R='rehash'
alias      ss='source $XDG_CONFIG_HOME/zsh/zshrc'
alias  ranger="ranger -r ~/.config/ranger"
#>
#< ls
alias ls1='=ls -1'
alias lsa='=ls --color=auto --time-style=full-iso'
alias lsd='/bin/ls -FAv | grep /$ | column'
alias lsl='=ls --color=auto   --group-directories-first -Ah'
alias lso='=ls | pv -qL 10'
alias lsq='=ls --color=always --time-style=full-iso -AlQ'
#alias lss='=ls --color=auto -1 | grep "(^\w*[^_-])"'
#>
#< directories
alias --  -='builtin cd -'
alias     b='builtin cd $HOME/bin'
alias     c='builtin cd $XDG_CONFIG_HOME/'
alias     d='builtin cd $HOME/dev'
alias     g='builtin cd $HOME/dev/_upstream'
alias     h='builtin cd $HOME/http/japh.se'
alias     q='builtin cd $HOME/dev/pickyfont'
alias     u='builtin cd $HOME/dev/utils'
alias     z='builtin cd $HOME/etc/zsh'
alias    aa='builtin cd $HOME/dev/App-Autotest'
alias    ap='builtin cd $HOME/dev/pimpd2'
alias    at='builtin cd $HOME/dev/ttycolor'
alias    dm='builtin cd $HOME/dev/Daemon-Mplayer'
alias    pp='builtin cd $HOME/dev/pimpd'
alias   RPD='builtin cd $HOME/dev/RPD'
alias   flc='builtin cd $HOME/dev/File-LsColor'
alias   mll='builtin cd $HOME/dev/Module-LocalLoad'
alias   mnp='builtin cd $HOME/dev/Mplayer-NowPlaying-CPAN'
alias   mp3='builtin cd $XDG_MUSIC_DIR'
alias   tec='builtin cd $HOME/dev/Term-ExtendedColor'
alias   tet='builtin cd $HOME/dev/Term-ExtendedColor-TTY'
alias   tex='builtin cd $HOME/dev/Term-ExtendedColor-Xresources'
alias     t='builtin cd $HOME/tmp'
#alias     t='mkdir -p /dev/shm/⚑; builtin cd /dev/shm/⚑'
#>
#< ssh hosts
# https://github.com/trapd00r/utils/blob/master/ssh
if [[ $UID != 0 ]]
then
  if [ -f "$HOME/.ssh/config" ]
  then
    for host in $(
      perl -ne 'print "$1\n" if /\A[Hh]ost\s+(.+)$/' $HOME/.ssh/config
      ); do
      alias $host="ssh $host $@"
    done
  fi
fi
#>
#< various applications
alias        get='woof -u -U -i 0.0.0.0 -p 4040'
alias        put='woof -u -i 0.0.0.0 -p 4040'

alias        irb='   rlwrap irb-1.8'
alias      clisp=' rlwrap clisp'
alias     bigloo='rlwrap bigloo'
alias     cclive='cclive --config-file $XDG_CONFIG_HOME/ccliverc -f best'
alias     gource='gource -1280x720 --max-files 0 --file-idle-time 0 --bloom-multiplier 0.5 --bloom-intensity 0.9 -e 0.7 --background 121212 -o - | ffmpeg -y -b 3000K -r 60 -f image2pipe -vcodec ppm -i - -vcodec libx264 -vpre slow -threads 0 gource.mp4'
alias logstalgia='logstalgia  japh_selected_log -s 5 --output-ppm-stream - |  ffmpeg -y -b 3000K -r 60 -f image2pipe -vcodec ppm -i - -vcodec libx264 -vpre slow -threads 0 logstalgia.mp4'
alias    ncmpcpp="ncmpcpp -b $HOME/etc/ncmpcpp/keys"
#>
#< audio
#alias    love='pimpd2 --love; mpd_cp_native /mnt/music8/_fav/_2021/'
alias  unlove='pimpd2 --unlove'
alias   songs='pimpd2 --songs'
alias  albums='pimpd2 --albums'
alias   slove='pimpd2 --slove|ls_color'
alias     mpd="mpd ~/etc/mpd.conf && mpdas"
#>

#<open sound system 4
#if [ -f '/etc/rc.d/oss' ]; then
#  alias        v+='ossmix vmix0.pcm8   -- +2'
#  alias       v++='ossmix vmix0.pcm9   -- +2'
#  alias      v+++='ossmix vmix0.pcm10  -- +2'
#  alias        v-='ossmix vmix0.pcm8   -- -2'
#  alias       v--='ossmix vmix0.pcm9   -- -2'
#  alias      v---='ossmix vmix0.pcm10 -- -2'
#
#  alias      play='ossmix mplayer 18:18 || pimpd2 --play'
#  alias      stop='ossmix mplayer 0  || pimpd2 --kill'
#fi
#>
#< git
alias      gt='git tag|sort --reverse'

# show modified files in the last commit
alias     gdd='git diff --name-only HEAD~1..HEAD | ls_color'
# edit modified files in the last commit
alias   vimlast='vim $(git diff --name-only HEAD~1..HEAD)'
#>
#< feh
alias     feh='/usr/bin/feh -FZ --cache-size 2048 --quiet --verbose -G -d --draw-tinted --action "cp -v '\'%f\'\" "$@"
alias    fehe='feh -Texif'
alias    fehf='feh -Tfs'
alias    fehi='feh .fehindex.jpg'
alias    fehj='feh -Trfs'
alias    feht='feh -Tthumb_s'
alias   feher='feh -Texif --recursive'
alias   fehfr='feh -Tfs --recursive'
alias   fehfx='feh -Tfs --slideshow-delay'
alias   fehjr='feh -Trfs --recursive'
alias   fehjx='feh -Trfs --slideshow-delay'
alias   fehtb='feh -Tthumb_b'
alias   fehtn='feh -Tthumb_s_nt'
alias   fehtr='feh -Tthumb_s --recursive'
alias  fehfrx='feh -Tfs --recursive --slideshow-delay'
alias  fehjrx='feh -Trfs --recursive --slideshow-delay'
alias  fehtbr='feh -Tthumb_b --recursive'
alias  fehtnb='feh -Tthumb_b_nt'
alias  fehtnr='feh -Tthumb_s_nt --recursive'
alias fehtnbr='feh -Tthumb_b_nt --recursive'
#>
#< gcc
#alias     gcc='gcc -ansi -pedantic -Wextra -Wempty-body -Wfloat-equal -Wignored-qualifiers -Wmissing-declarations -Wmissing-parameter-type -Wmissing-prototypes -Wold-style-declaration -Woverride-init -Wsign-compare -Wstrict-prototypes -Wtype-limits -Wuninitialized -fstack-protector-all -D_FORTIFY_SOURCE=2'
#alias    gccc='gcc -ansi -pedantic -Wall'
#>
#< ffmpeg
#case $HOSTNAME in
#  wid)
#    alias rec="ffmpeg -f x11grab -s 5760x1080 -r 25 -i :0.0+840,4 -sameq"
#    ;;
#  elite)
#    alias rec="ffmpeg -f x11grab -s 1600x900 -r 25 -i :0.0 -sameq"
#    ;;
#  n900)
#    alias rec="ffmpeg -f x11grab -s 800x480 -r 25 -i :0.0 -sameq"
#    ;;
#  RM680)
#    alias rec="ffmpeg -f x11grab -s 854x480 -r 25 -i :0.0 -sameq"
#    ;;
#  laleh)
#    ;;
#  *)
#    alias rec="ffmpeg -f x11grab -r 25 -i :0.0+840,4 -sameq"
#esac
#>
#< terminal
alias reset='printf "\033c\033(K\033[J\033[0m\033[?25h"'
#>
#< various
alias author='printf "  %s\n  %s\n  %s\n  %s\n" "Magnus Woldrich" "CPAN ID: WOLDRICH" "m@japh.se" "http://japh.se"'
alias osc3c='printf "\t\033#3\e[38;5;25mt\e[38;5;26mr\e[38;5;27ma\e[38;5;31mp\e[38;5;32md\e[38;5;33m0\e[38;5;33m0\e[38;5;37mr\n\t\033#4\e[38;5;133mt\e[38;5;134mr\e[38;5;135ma\e[38;5;139mp\e[38;5;140md\e[38;5;141m00\e[38;5;145mr\n\t\e[38;5;240mA simple, lightweight Perl hacker\n"'
alias dev_null='rm /dev/null; mknod /dev/null c 1 3'
#>
#< wiimote
#if [ $WANNA_PLAY_WITH_WIIMOTE ] 
#then
#  alias      wmp='wminput -c mplayer&'
#  alias      win='wminput -c ir_ptr -w -c neverball&'
#  alias      wir='wminput -c ir_ptr -w -c ir_ptr&'
#  alias      wig='wminput -c gamepad&'
#  alias      wit='wminput -c buttons-term&'
#fi
#>

alias castnow='castnow --address 192.168.10.160'
alias todo="vim ~/dev/private/TODO.todo"
alias nexuiz=xonotic-sdl
alias jobb='vim ~/dev/private/jobb.tidningsbud'
alias psp="cd ${HOME}/dev/askas/air8/cgi-bin/core/lib/AIR/PSP2"
