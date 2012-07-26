#!/bin/zsh
### vim: set ft=sh:fdm=marker:et:sw=2:
###
#      ${HOME}/etc/zsh/02-exports.zsh
#   ‗‗‗‗‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗ ‗‗‗‗‗‗‗‗‗‗‗
#         owner  Magnus Woldrich <m@japh.se>
#         btime  2009-04-24
#         mtime  2012-07-26 02:53:32
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
setopt allexport

[[ -f ${HOME}/lib/stderred.so ]] && LD_PRELOAD="${HOME}/lib/stderred.so"


#{{{ PATH
 BIN_STD=/bin:/usr/bin:/usr/local/bin
BIN_PERL=/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl
BIN_SUID=/sbin:/usr/sbin
    PATH=${BIN_STD}:${BIN_HOME}:${BIN_PERL}:${BIN_SUID}
    # not using $HOME here because UID 0 should be able to use my utils as well
    # and "I know what I'm doing"
    PATH=/home/scp1/bin:/home/scp1/dev/utils/:${PATH}:/home/scp1/dev/git-extras/bin

 MANPATH=${HOME}/usr/share/man:/usr/local/man
 AWKPATH=$HOME/dev/lib/awk/
TERMINFO=${HOME}/usr/share/terminfo:/usr/share/terminfo
#}}}

if [[ -x =wim ]]
then
  EDITOR=wim
  GIT_EDITOR="${EDITOR} -X"
  VIDIR_EDITOR=${EDITOR}
  VIDIR_EDITOR_ARGS='-c :set nolist | :set cc=0 | set ft=vidir-ls'
      VIMRUNTIME=${HOME}/etc/vim
  VIMRUNTIME_DEV=${HOME}/dev/vim/runtime
  VIFM=${HOME}/etc/vifm
  MYVIFMRC=$HOME/etc/vifm/vifmrc
  PAGER=''
  LESS=''
else
  perl -e 'warn "wim not found! Resort to vim...\n"';
  EDITOR=vim
  GIT_EDITOR="${EDITOR} -X"
  VIDIR_EDITOR=${EDITOR}
  VIDIR_EDITOR_ARGS='-c :set nolist | :set cc=0 | set ft=vidir-ls'
      VIMRUNTIME=${HOME}/etc/vim
  VIMRUNTIME_DEV=${HOME}/dev/vim/runtime
  VIFM=${HOME}/etc/vifm
  MYVIFMRC=$HOME/etc/vifm/vifmrc
  PAGER=''
  LESS=''
fi

DISPLAY=:0.0
GREP_OPTIONS='-IP --color --line-buffered'

HARNESS_SUMMARY_COL_FAIL="bold red"
HARNESS_SUMMARY_COL_SUC=" bold cyan"
PERLBREW_ROOT=${HOME}/usr/share/perl5
PERL5LIB=${HOME}/lib
PERL_HACK_LIB=/tmp
PERL_MM_USE_DEFAULT=1


ESCDELAY=10
NCURSES_ASSUMED_COLORS=3,0
NCURSES_NO_MAGIC_COOKIES=1
NCURSES_NO_PADDING=1

GIST_DIR="$HOME/dev/_gists/"
PERL_CPANM_OPT="-l ${HOME} -v --interactive --mirror http://cpan.se"
OREILLY_BOOKS_DATABASE=${HOME}/usr/share/doc/oreilly.db


LESSKEY="${HOME}/etc/lesskey"
FONTCONFIG_PATH=''
X_OSD_COLOR='#a8ff00'
CLIVE_CONFIG="$HOME/etc/cliverc"
MAILDIR="/mnt/Mail/inbox/new"
SENDMAIL='msmtp -C ~/.msmtprc -a gmail m@japh.se'
HOSTNAME="shiva"
ACKRC="$HOME/etc/ackrc"
GIMP2_DIRECTORY=${HOME}/etc/gimp
GENISOIMAGERC=${HOME}/etc/genisoimagerc
#export MOZ_DISABLE_PANGO="1"

BROWSER="/usr/bin/w3m"



XDG_CACHE_HOME="$HOME/etc/cache"
XDG_CONFIG_HOME="$HOME/etc"
XDG_DATA_HOME="$HOME/var"
XDG_DESKTOP_DIR="/tmp/.${UID}"
XDG_DOCUMENTS_DIR="${HOME}/usr/share/doc"
XDG_DOWNLOAD_DIR="/tmp/scp1/"
XDG_MUSIC_DIR="/mnt/Music_1/"
XDG_PICTURES_DIR="/mnt/Docs/Photo/"
XDG_PUBLICSHARE_DIR="/tmp/.${UID}"
XDG_TEMPLATES_DIR="/tmp/.${UID}"
XDG_VIDEOS_DIR="/mnt/Movies_1/"

RLWRAP_FILTERDIR="$HOME/dev/_upstream/rlwrap/filters"

WORDCHARS='*?_.[]~&;!#$%^(){}<>'
ZSH_ACTIVE_COMPLETIONS="$( echo ${(kv)_comps[@]} )"
ZSH_THEME="ftprompt"
LISTMAX=0

KEYTIMEOUT="1"

HISTFILE=$XDG_DATA_HOME/zsh/history
HISTIGNORE="&:ls:[bf]g:exit:reset:clear:cd*"
HISTSIZE=10000
SAVEHIST=50000

CLIPBORED_DMENU_FONT=${FONT}
CLIPBORED_DMENU_LINES=30
CLIPBORED_DMENU_LISTMODE='vertical'
CLIPBORED_DMENU_NORMAL_BG='#1c1c1c'
CLIPBORED_DMENU_NORMAL_FG='#484848'
CLIPBORED_DMENU_SELECT_BG='#292929'
CLIPBORED_DMENU_SELECT_FG='#1c78ef'
MPD_HOST=laleh
MPD_PORT=6600
MPD_USER='scp1'
MPD_PASS=`smokingkills`

#{{{ fonts and colors for essential applications
  # these variables can be used a little here and there
  FONT='-windows-montecarlo-medium-r-normal--0-0-72-72-c-0-microsoft-cp1252'
  FONT_B='-windows-montecarlo-bold-r-normal--0-0-72-72-c-0-microsoft-cp1252'
  FONT_I='-nil-profont-medium-r-normal--10-100-72-72-c-50-iso8859-1'

  DMENU_FONT=${FONT}
  DMENU_LINES='-l 30'
  DMENU_NORMAL_BG='#1c1c1c'
  DMENU_NORMAL_FG='#484848'
  DMENU_SELECT_BG='#292929'
  DMENU_SELECT_FG='#1c78ef'

  DZEN_ALIGNMENT='c'
  DZEN_BG='#1c1c1c'
  DZEN_FG='#ffffff'
  DZEN_FONT=${FONT}
  DZEN_WIDTH=1680
  DZEN_X_POS=0
  DZEN_Y_POS=1040
#}}}

PRINTER="Canon_MP150"
setopt allexport
setopt no_allexport
