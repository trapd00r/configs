###< vim: set ft=zsh:fdm=marker:fmr=#<,#>:fdl=0:fen:et:sw=2:fcl=all:
###
#      ${HOME}/etc/zsh/02-exports.zsh
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗
#         owner  Magnus Woldrich <magnus.woldrich@gmail.com>
#         btime  2009-04-24
#         mtime  2016-09-05 14:23:34
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

export JEKYLL_ENV='production'
#< LD_PRELOAD
# https://github.com/trapd00r/stderred
[[ -f ${HOME}/lib/stderred.so ]] && export LD_PRELOAD=${HOME}/lib/stderred.so:${LD_PRELOAD}
#>
#< xdg
export       XDG_DATA_HOME=${HOME}/var
export       XDG_MUSIC_DIR=${HOME}/mp3
export      XDG_CACHE_HOME=${HOME}/var/cache
export      XDG_VIDEOS_DIR=${HOME}/vid
export     XDG_CONFIG_HOME=${HOME}/etc
export     XDG_DESKTOP_DIR=${HOME}/tmp
export    XDG_DOWNLOAD_DIR=${HOME}/tmp
export    XDG_PICTURES_DIR=${HOME}/img
export   XDG_DOCUMENTS_DIR=${HOME}/usr/share/doc
export   XDG_TEMPLATES_DIR=${HOME}/tmp
export XDG_PUBLICSHARE_DIR=${HOME}/usr/share
#>
#< various applications
export              ACKRC=${HOME}/etc/ackrc
export       CLIVE_CONFIG=${XDG_CONFIG_HOME}/cliverc
export      GENISOIMAGERC=${XDG_CONFIG_HOME}/genisoimagerc
export    GIMP2_DIRECTORY=${XDG_CONFIG_HOME}/gimp
export PULSE_CLIENTCONFIG=${XDG_CONFIG_HOME}/pulse/client.conf
export           SCREENRC=${XDG_CONFIG_HOME}/screenrc
export        X_OSD_COLOR='#a8ff00'
export            BROWSER=firefox
#>
#< locale
export            LC_ALL=""

export              LANG=en_US
export        LC_ADDRESS=en_US.UTF-8
export        LC_COLLATE=en_US.UTF-8
export          LC_CTYPE=en_US.UTF-8
export LC_IDENTIFICATION=en_US.UTF-8
export    LC_MEASUREMENT=en_US.UTF-8
export       LC_MESSAGES=en_US.UTF-8
export       LC_MONETARY=en_US.UTF-8
export           LC_NAME=en_US.UTF-8
export        LC_NUMERIC=en_US.UTF-8
export          LC_PAPER=en_US.UTF-8
export      LC_TELEPHONE=en_US.UTF-8
export           LC_TIME=en_US.UTF-8
#>
#< path
unset PATH
export          PATH=${HOME}/dev/utils:${HOME}/bin:/bin:/usr/local/bin:/usr/bin/core_perl:/usr/bin/core_perl/bin/:/usr/bin:${HOME}/bin/site_perl:/usr/bin/vendor_perl:/sbin:/usr/sbin:/usr/games:/usr/local/games:$HOME/lib/go/bin:$HOME/perl6/bin:$HOME/.gem/ruby/2.5.0/bin
export        GOPATH=${HOME}/lib/go
export       AWKPATH=${HOME}/dev/lib/awk/
export       MANPATH=${HOME}/usr/share/man:/usr/local/man:/usr/share/man
export      PERL5LIB=${HOME}/lib/perl5:${HOME}/lib/perl/5.14.2/auto:${HOME}/lib/perl/5.14/auto:${HOME}/lib/perl5/:${HOME}/lib:/usr/share/perl5/site_perl:/usr/share/perl5/core_perl:/usr/share/perl5/vendor_perl:/usr/share/perl5/site_perl:/usr/lib/perl5/core_perl/auto:/usr/lib/perl5/vendor_perl/auto:/usr/lib/perl5/site_perl/auto
export PERLBREW_ROOT=${HOME}/usr/share/perl5
export      TERMINFO=${HOME}/usr/share/terminfo:/usr/share/terminfo
#>
#< vifm
export     VIFM=${XDG_CONFIG_HOME}/vifm
export MYVIFMRC=${XDG_CONFIG_HOME}/vifm/vifmrc
#>
#< perl
export           PERL_CPANM_OPT='-nql~/ --reinstall --prompt --auto-cleanup 365 --mirror-only'
export      PERL_MM_USE_DEFAULT=0
export  HARNESS_SUMMARY_COL_SUC=green
export HARNESS_SUMMARY_COL_FAIL=red
#>
#< mplayer
export    DVDCSS_CACHE=/dev/shm/dvdcss
export   DVDCSS_METHOD=title
export  DVDCSS_VERBOSE=0
export  DVDREAD_NOKEYS=1

export    MPLAYER_HOME=${XDG_CONFIG_HOME}/mplayer
export  MPLAYER_CONFIG=${XDG_CONFIG_HOME}/mplayer/config
export MPLAYER_CHARSET=UTF-8
export MPLAYER_VERBOSE=1
#>
#< mozilla
export             FIREFOX_DSP=aoss
export         MOZPLUGGER_HOME=${XDG_CONFIG_HOME}/mozplugger
#export       MOZ_DISABLE_PANGO=1
#export VDPAU_NVIDIA_NO_OVERLAY=1
#>
#< terminal
export                  LESSKEY="${XDG_CONFIG_HOME}/lesskey"
export                 ESCDELAY=1
export         RLWRAP_FILTERDIR="${HOME}/dev/_upstream/rlwrap/filters"
export       NCURSES_NO_PADDING=1
export   NCURSES_ASSUMED_COLORS=3,0
export NCURSES_NO_MAGIC_COOKIES=1
#>
#< fonts
#export FONTCONFIG_PATH=''
#export FC_DEBUG=1
export    FONT='-windows-montecarlo-medium-r-normal--0-0-72-72-c-0-microsoft-cp1252'
export  FONT_B='-windows-montecarlo-bold-r-normal--0-0-72-72-c-0-microsoft-cp1252'
export  FONT_I='-nil-profont-medium-r-normal--10-100-72-72-c-50-iso8859-1'
#>
#< mail
export      MAIL=${HOME}/mail
export   MAILDIR=${HOME}/mail
export  SENDMAIL='msmtp -C ~/.msmtprc -a gmail m@japh.se'
export DELIVERED=yes
#>
#< mpd
#export MPD_HOST=0.0.0.0
#export MPD_PORT=64593
#export MPD_USER=scp1
#>
#< printer, scanner
#export          PRINTER="Canon_MP150"
#export SANE_DEBUG_PIXMA=11
export PIXMA_EXPERIMENT=
export SANE_DEBUG_PIXMA=0
#>
#< clipbored
export      CLIPBORED_DMENU_FONT=${FONT}
export     CLIPBORED_DMENU_LINES=30
export  CLIPBORED_DMENU_LISTMODE=vertical
export CLIPBORED_DMENU_NORMAL_BG='#1c1c1c'
export CLIPBORED_DMENU_NORMAL_FG='#484848'
export CLIPBORED_DMENU_SELECT_BG='#292929'
export CLIPBORED_DMENU_SELECT_FG='#1c78ef'
#>
#< gui
export             QT_XFT=1
export        GDK_USE_XFT=1
export DESKTOP_STARTUP_ID=42
#export GDK_NATIVE_WINDOWS=0
#>
#< rtorrent
export RT_HOME=${XDG_DATA_HOME}/var/rtorrent
#>
#< various
export TTC_REPOS=${HOME}/dev
export TTC_APIKEYS=''
export TTC_BOTS='tinycarebot,selfcare_bot,magicrealismbot'
export TTC_WEATHER='Karlstad'
export TTC_CELSIUS=true
export TTC_APIKEYS=false
export TTC_UPDATE_INTERVAL=20
## Twitter api keys
#export TTC_CONSUMER_KEY='...'
#export TTC_CONSUMER_SECRET='...'
#export TTC_ACCESS_TOKEN='...'
#export TTC_ACCESS_TOKEN_SECRET='...'
#>
#< dmenu
export       DMENU_FONT=${FONT}
export      DMENU_LINES='-l 30'
export  DMENU_NORMAL_BG='#ff0000'
export  DMENU_NORMAL_FG='#484848'
export  DMENU_SELECT_BG='#292929'
export  DMENU_SELECT_FG='#1c78ef'
#>
#< dzen2
export  DZEN_ALIGNMENT='c'
export         DZEN_BG='#1c1c1c'
export         DZEN_FG='#ffffff'
export       DZEN_FONT=${FONT}
export      DZEN_WIDTH=1600
export      DZEN_X_POS=0
export      DZEN_Y_POS=900
#>
#< zsh
export               HISTFILE=${XDG_DATA_HOME}/zsh/history
export             HISTIGNORE="&:ls:[bf]g:exit:reset:clear:cd*:gs:gd:calc:du1:l:make"
export               HISTSIZE=256000
export          KEYBOARD_HACK=' '
export             KEYTIMEOUT=100
export                LISTMAX=500
export          LISTROWSFIRST=1
export               SAVEHIST=250000
export              WORDCHARS='*?_.[]~&;!#$%^(){}<>'
export ZSH_ACTIVE_COMPLETIONS="$( echo ${(kv)_comps[@]} )"
export              ZSH_THEME="japhprompt"
# zurl
export            IMAGEOPENER=feh
export              IMAGEARGS=' -F -Z -x -d -B black -g 1080x1920 -k -j ~/dump --draw-tinted '
#>
#< editor
export  LESS=''
export PAGER=vimpager

#if [[ -x =wim ]] # https://github.com/trapd00r/vim
#then
#  export            EDITOR=wim
#  export        GIT_EDITOR="${EDITOR} -X"
#  export      VIDIR_EDITOR=${EDITOR}
#  export VIDIR_EDITOR_ARGS='-c :set nolist | :set cc=0 | set ft=vidir-ls'
#  export        VIMRUNTIME=${HOME}/etc/vim
#  export    VIMRUNTIME_DEV=${HOME}/dev/vim/runtime
#else
#  perl -e 'print STDERR "wim not found! Resort to vim...\n"'
  export            EDITOR=vim
  export        GIT_EDITOR="${EDITOR} -X"
  export      VIDIR_EDITOR=${EDITOR}
#export VIDIR_EDITOR_ARGS='-c :set nolist | :set cc=0 | set ft=vidir | so ~/dev/vidir/vidir.vimrc'
  export VIDIR_EDITOR_ARGS='-c :set nolist | :set cc=0 | set ft=vidir'
  export        VIMRUNTIME=${HOME}/etc/vim
  export    VIMRUNTIME_DEV=${HOME}/dev/vim/runtime
#fi
#>

export GITHUB_USER='trapd00r'
export ACCESS_LOG="$HOME/pi/var/log/access.log"
