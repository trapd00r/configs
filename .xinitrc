#!/bin/bash

declare -A host_wm
host_wm[shiva]="$(which stumpwm   2> /dev/null)"
 host_wm[dvdc]="$(which ratpoison 2> /dev/null)"

declare -A wm_cmd
wm_cmd[dwm]=$(      which dwm       2> /dev/null)
wm_cmd[subtle]=$(   which subtle    2> /dev/null)
wm_cmd[windowlab]=$(which windowlab 2> /dev/null)
wm_cmd[ratpoison]=$(which ratpoison 2> /dev/null)
wm_cmd[stumpwm]=$(  which stumpwm   2> /dev/null)


wm_cmd[wmii]="     wmii -r $HOME/.wmii-hg/wmiirc.sh"
wm_cmd[stumpwm_c]="ck-launch-session $(which stumpwm 2> /dev/null)"
wm_cmd[stumpwm_s]="ck-launch-session sbcl --load $HOME/bin/startstump"

declare -A host_resolution
host_resolution[shiva]="1680x1050"
host_resolution[india]="1366x768"


if [ "$HOSTNAME" == 'shiva' ]; then
  xrdb $HOME/configs/.Xresources
  unclutter -idle 4 &
  xset m 1 1        &

  xsetroot -cursor_name left_ptr
  setxkbmap -option terminate:ctrl_alt_bksp
  nitrogen --restore &

  urxvtd -q -f -o                     &
  (sleep 1; urxvtc -name URxvt.shiva) &

elif [ "$HOSTNAME" == 'india' ]; then
  xrdb $HOME/.Xresources
  xsetroot -bg \#121212 -mod 3 3 &

else
  printf "\n-\n> Can not find a suitable WM for %s\n" $HOSTNAME
  exit
fi

sh $HOME/devel/dzen-scripts/dzen_${HOSTNAME}_right.sh &
sh $HOME/devel/dzen-scripts/dzen_${HOSTNAME}_left.sh  &

setxkbmap se -variant nodeadkeys
xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape'

exec ${host_wm[$HOSTNAME]}

##xrandr --addmode DVI-I-1 1680x1050
##xrandr --output DVI-I-1 --auto --mode 1680x1050
##xrandr --output DVI-I-1 --right-of DVI-I-2

# vim: set ft=sh:
