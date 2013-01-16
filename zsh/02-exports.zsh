#!/bin/zsh
### vim: set ft=sh:fdm=marker:et:sw=2:fcl=3
###
#      ${HOME}/etc/zsh/02-exports.zsh
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗
#         owner  Magnus Woldrich <m@japh.se>
#         btime  2009-04-24
#         mtime  2013-01-16 09:17:11
#   permissions  You are free to use things you may find useful here.
#                Would my tweaks happen to give you a raise or fetch you a
#                girlfriend, it goes without saying I'm counting on you
#                to share with me as I've shared with you.
#           git  http://github.com/trapd00r/configs/zsh  (up-to-date)
#           url  http://devel.japh.se/configs/zsh        (sync 1/24h)
#           irc  japh@freenode #zsh #vim #perl
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗ ‗‗‗‗ ‗‗‗‗
###
###

# don't worry, her scope ends at EOF
#setopt allexport
#setopt noallexport

[[ -f ${HOME}/lib/stderred.so ]] && LD_PRELOAD=${HOME}/lib/stderred.so:${LD_PRELOAD}

export LC_CTYPE=en_US.UTF-8
export RT_HOME=${HOME}/var/rtorrent
#mkdir -p ${RT_HOME}/{session,log}


#export LC_ALL=""
#export LANG=en_US
#export LC_CTYPE="en_US.UTF-8"
#export LC_NUMERIC="en_US.UTF-8"
#export LC_TIME="en_US.UTF-8"
#export LC_COLLATE="en_US.UTF-8"
#export LC_MONETARY="en_US.UTF-8"
#export LC_MESSAGES="en_US.UTF-8"
#export LC_PAPER="en_US.UTF-8"
#export LC_NAME="en_US.UTF-8"
#export LC_ADDRESS="en_US.UTF-8"
#export LC_TELEPHONE="en_US.UTF-8"
#export LC_MEASUREMENT="en_US.UTF-8"
#export LC_IDENTIFICATION="en_US.UTF-8"

#export INFINALITY_FT_CHROMEOS_STYLE_SHARPENING_STRENGTH=0
export INFINALITY_FT_WINDOWS_STYLE_SHARPENING_STRENGTH=80
export INFINALITY_FT_AUTOHINT_HORIZONTAL_STEM_DARKEN_STRENGTH=95
export INFINALITY_FT_AUTOHINT_INCREASE_GLYPH_HEIGHTS=false
export INFINALITY_FT_AUTOHINT_SNAP_STEM_HEIGHT=100
export INFINALITY_FT_AUTOHINT_VERTICAL_STEM_DARKEN_STRENGTH=95
export INFINALITY_FT_BOLD_EMBOLDEN_X_VALUE=0.1
export INFINALITY_FT_BOLD_EMBOLDEN_Y_VALUE=0
export INFINALITY_FT_BRIGHTNESS=100
export INFINALITY_FT_CONTRAST=100
#export INFINALITY_FT_FILTER_PARAMS="00 35 35 35 00"
export INFINALITY_FT_FRINGE_FILTER_STRENGTH=0
export INFINALITY_FT_GAMMA_CORRECTION="0 100"
export INFINALITY_FT_GLOBAL_EMBOLDEN_X_VALUE=0
export INFINALITY_FT_GLOBAL_EMBOLDEN_Y_VALUE=0
export INFINALITY_FT_GRAYSCALE_FILTER_STRENGTH=0
export INFINALITY_FT_STEM_ALIGNMENT_STRENGTH=25
export INFINALITY_FT_STEM_FITTING_STRENGTH=25
export INFINALITY_FT_STEM_SNAPPING_SLIDING_SCALE=40
export INFINALITY_FT_USE_KNOWN_SETTINGS_ON_SELECTED_FONTS=false
export INFINALITY_FT_USE_VARIOUS_TWEAKS=false
#

#{{{ PATH
# unset PATH
export PATH=/home/scp1/dev/utils:/home/scp1/bin:/bin:/usr/local/bin:/usr/bin/core_perl:/usr/bin/core_perl/bin/:/usr/bin:${HOME}/bin/site_perl:/usr/bin/vendor_perl:/sbin:/usr/sbin
# export PATH=$''${BIN_LOC}:${BIN_STD}${BIN_PL}
    # not using ${HOME} here because UID 0 should be able to use my utils that's
    # 'in the works'

export MANPATH=${HOME}/usr/share/man:/usr/local/man:/usr/share/man
export AWKPATH=${HOME}/dev/lib/awk/
#export TERMINFO=${HOME}/usr/share/terminfo:/usr/share/terminfo
export PERLBREW_ROOT=${HOME}/usr/share/perl5
export PERL5LIB=/home/scp1/lib/perl5/:/home/scp1/lib:/usr/share/perl5/site_perl:/usr/share/perl5/core_perl:/usr/share/perl5/vendor_perl:/usr/share/perl5/site_perl:/usr/lib/perl5/core_perl/auto:/usr/lib/perl5/vendor_perl/auto:/usr/lib/perl5/site_perl/auto
#PERL5LIB=/home/scp1/lib/perl5/
#PERL_HACK_LIB=/tmp
#}}}

if [[ -x =wim ]]
then
# setopt allexport
  export EDITOR=wim
  export GIT_EDITOR="${EDITOR} -X"
  export VIDIR_EDITOR=${EDITOR}
  export VIDIR_EDITOR_ARGS='-c :set nolist | :set cc=0 | set ft=vidir-ls'
  export     VIMRUNTIME=${HOME}/etc/vim
  export VIMRUNTIME_DEV=${HOME}/dev/vim/runtime
  export VIFM=${HOME}/etc/vifm
  export MYVIFMRC=${HOME}/etc/vifm/vifmrc
#  export PAGER='fmt -s'
#  export LESS=''
else
  perl -e 'warn "wim not found! Resort to vim...\n"';
  export EDITOR=vim
  export GIT_EDITOR="${EDITOR} -X"
  export VIDIR_EDITOR=${EDITOR}
  export VIDIR_EDITOR_ARGS='-c :set nolist | :set cc=0 | set ft=vidir-ls'
  export     VIMRUNTIME=${HOME}/etc/vim
  export VIMRUNTIME_DEV=${HOME}/dev/vim/runtime
  export VIFM=${HOME}/etc/vifm
  export MYVIFMRC=${HOME}/etc/vifm/vifmrc
  export PAGER='vimpager'
  export LESS=''
fi

#PERL_MM_USE_DEFAULT=1
export PERL_CPANM_OPT='-nql~/ --reinstall --prompt --auto-cleanup 365 --mirror http://cpan.se  --mirror-only'
#export MPLAYER_VERBOSE=1
export MPLAYER_HOME=${HOME}/etc/mplayer
#export MPLAYER_CHARSET=en_US.UTF-8
export DVDCSS_CACHE=/dev/shm/dvdcss
export DVDCSS_METHOD=title
export DVDCSS_VERBOSE=0
export DVDREAD_NOKEYS=1

# XXX fix packer so we can add -P here
export GREP_OPTIONS='-I --exclude-dir=".git" --color=auto'

export HARNESS_SUMMARY_COL_FAIL=red
export HARNESS_SUMMARY_COL_SUC=green

export ESCDELAY=1
export NCURSES_ASSUMED_COLORS=3,0
export NCURSES_NO_MAGIC_COOKIES=1
export NCURSES_NO_PADDING=1
GIST_DIR="${HOME}/dev/_gists/"
OREILLY_BOOKS_DATABASE=${HOME}/usr/share/doc/oreilly.db

export LESSKEY="${HOME}/etc/lesskey"
#export FONTCONFIG_PATH=''
#export FC_DEBUG=1
export X_OSD_COLOR='#a8ff00'
export CLIVE_CONFIG="${HOME}/etc/cliverc"
export MAIL=/mnt/mail/inbox
export MAILDIR=/mnt/mail/inbox
#export SENDMAIL='msmtp -C ~/.msmtprc -a gmail m@japh.se'
export ACKRC="${HOME}/etc/ackrc"
export GIMP2_DIRECTORY=${HOME}/etc/gimp
export GENISOIMAGERC=${HOME}/etc/genisoimagerc
#export MOZ_DISABLE_PANGO="1"
export BROWSER="/usr/bin/w3m"

export XDG_DATA_HOME=${HOME}/var
export XDG_MUSIC_DIR=/mnt/music1/
export XDG_VIDEOS_DIR=/mnt/movie1/
export XDG_CACHE_HOME=${HOME}/etc/cache
export XDG_CONFIG_HOME=${HOME}/etc
export XDG_DESKTOP_DIR=/tmp/.${UID}
export XDG_DOWNLOAD_DIR=${HOME}/dump
export XDG_PICTURES_DIR=/mnt/porn1/.00-pics
export XDG_TEMPLATES_DIR=/tmp/.${UID}
export XDG_DOCUMENTS_DIR=${HOME}/usr/share/doc
export XDG_PUBLICSHARE_DIR=/tmp/.${UID}

export RLWRAP_FILTERDIR="${HOME}/dev/_upstream/rlwrap/filters"

export CLIPBORED_DMENU_FONT=${FONT}
export CLIPBORED_DMENU_LINES=30
export CLIPBORED_DMENU_LISTMODE='vertical'
export CLIPBORED_DMENU_NORMAL_BG='#1c1c1c'
export CLIPBORED_DMENU_NORMAL_FG='#484848'
export CLIPBORED_DMENU_SELECT_BG='#292929'
export CLIPBORED_DMENU_SELECT_FG='#1c78ef'

export MPD_HOST=localhost
export MPD_PORT=6600
export MPD_USER='scp1'
export MPD_PASS=`smokingkills`

#{{{ fonts and colors for essential applications
  # these variables can be used a little here and there
export  FONT='-windows-montecarlo-medium-r-normal--0-0-72-72-c-0-microsoft-cp1252'
export  FONT_B='-windows-montecarlo-bold-r-normal--0-0-72-72-c-0-microsoft-cp1252'
export  FONT_I='-nil-profont-medium-r-normal--10-100-72-72-c-50-iso8859-1'

export  DMENU_FONT=${FONT}
export  DMENU_LINES='-l 30'
export  DMENU_NORMAL_BG='#ff0000'
export  DMENU_NORMAL_FG='#484848'
export  DMENU_SELECT_BG='#292929'
export  DMENU_SELECT_FG='#1c78ef'

export  DZEN_ALIGNMENT='c'
export  DZEN_BG='#1c1c1c'
export  DZEN_FG='#ffffff'
export  DZEN_FONT=${FONT}
export  DZEN_WIDTH=1680
export  DZEN_X_POS=0
export  DZEN_Y_POS=1040
#}}}

#PRINTER="Canon_MP150"
#PIXMA_EXPERIMENT=alice
#SANE_DEBUG_PIXMA=11
export PIXMA_EXPERIMENT=
export SANE_DEBUG_PIXMA=0

export GDK_USE_XFT=1
export QT_XFT=1
#export GDK_NATIVE_WINDOWS=1
#export DESKTOP_STARTUP_ID=42
export SCREENRC=${XDG_CONFIG_HOME}/screenrc
#[[ -z "$IMAGEARGS" && "$IMAGEOPENER" == "feh" ]] && export IMAGEARGS="--scale-down"

# zsh {{{
export WORDCHARS='*?_.[]~&;!#$%^(){}<>'
export ZSH_ACTIVE_COMPLETIONS="$( echo ${(kv)_comps[@]} )"
export ZSH_THEME="ftprompt"
export LISTMAX=500
export LISTROWSFIRST=1
export LISTPROMPT="3D%SAt %p: Hit TAB for more, or the character to insert%s=20"
export KEYBOARD_HACK=' '
export KEYTIMEOUT=100
export HISTFILE=${XDG_DATA_HOME}/zsh/history
export HISTIGNORE="&:ls:[bf]g:exit:reset:clear:cd*"
export HISTSIZE=95000
export SAVEHIST=92000
# zurl {{{
#}}}
export IMAGEOPENER=feh
export IMAGEARGS='-ZxdBblack -g 1080x1920 --keep-http'
#}}}
