#!/bin/bash
# vim: foldmarker=#+,#-:

#+ wm stuff
declare -A host_wm
host_wm[shiva]="$(which stumpwm     2> /dev/null)"
host_wm[laleh]="$(which ratpoison   2> /dev/null)"
host_wm[rambo]="$(which ratpoison   2> /dev/null)"
declare -A wm_cmd
wm_cmd[dwm]=$(      which dwm             2> /dev/null)
wm_cmd[subtle]=$(   which subtle          2> /dev/null)
wm_cmd[windowlab]=$(which windowlab       2> /dev/null)
wm_cmd[ratpoison]=$(which ratpoison       2> /dev/null)
wm_cmd[stumpwm]=$(  which stumpwm         2> /dev/null)
wm_cmd[openbox]=$(  which openbox-session 2> /dev/null)

wm_cmd[wmii]="     wmii -r $HOME/.wmii-hg/wmiirc.sh"
wm_cmd[stumpwm_c]="ck-launch-session $(which stumpwm 2> /dev/null)"
wm_cmd[stumpwm_s]="ck-launch-session sbcl --load $HOME/bin/startstump"
#+ display resolution
declare -A host_resolution
host_resolution[shiva]="1680x1050"
host_resolution[india]="1366x768"
host_resolution[rambo]="1920x1080"

if [ "$HOSTNAME" = 'shiva' ]; then
  xrdb $HOME/etc/Xresources &
  unclutter -idle 4 &
  xset m 1 1        &

  xsetroot -cursor_name center_ptr -fg \#ff0000 -bg \#302400 -rv

  setxkbmap se \
    -variant progqwerty               \
    -model   tm2030USB-102            \  # typematrix 2030
    -option                           \  # clear set opts
    -option caps:escape               \  # caps -> esc
    -option compose:lwin              \  # XXX better use?
    -option grp:led_scroll            \  # indicate layout on leds
    -option keypad:future             \  # fancy arrows and math
    -option keypad:pointerkeys        \  # yeah why not
    -option lv3:ralt_switch_multikey  \  # set RALT as multikey
    -option lv5:lsgt_switch_lock      \  # TODO add 5th lvl in xkb
    -option nbsp:zwnj2nb3nnb4         \  # in 0x20 noone can hear you scream
    -option terminate:ctrl_alt_bksp   \
  ||  setxkbmap se -variant nodeadkeys

 # urxvtd -q -f -o                     &
  twmnd &
 # (sleep 1; urxvtc -name URxvt.shiva) &

elif [ "$HOSTNAME" = 'india' ]; then
  xrdb $HOME/.Xresources
  xsetroot -bg \#121212 -mod 3 3 &
  setxkbmap se -variant nodeadkeys

elif [ "$HOSTNAME" = 'rambo' ]; then
  xrdb $HOME/etc/Xresources
  xset m 1 1        &
  unclutter -idle 4 &
  urxvtd -q -f -o   &
 # (sleep 1; urxvtc -name URxvt.rambo) &
  feh --bg-scale $HOME/wallpapers/pink_floyd_was_here.jpg &
else
  printf "\n-\n> Can not find a suitable WM for %s\n" $HOSTNAME
  exit
fi

#sh $HOME/devel/dzen-scripts/dzen_${HOSTNAME}_right.sh &
#sh $HOME/devel/dzen-scripts/dzen_${HOSTNAME}_left.sh  &

xmodmap $XDG_CONFIG_HOME/xmodmaprc &

#xset fp $(echo "/home/scp1/.fonts,
#  /usr/share/fonts/TTF,
#  /usr/share/fonts/artwiz-fonts,
#  /usr/share/fonts/local,
#  /usr/share/fonts/misc,
#  /usr/share/fonts/scp1" | perl -pe 's/[\n\s]+//g')

#nvidia-settings -a GlyphCache=1
#nvidia-settings -a InitialPixmapPlacement=2

exec ${host_wm[$HOSTNAME]}
