#!/bin/sh
# vim:ft=sh:
# $XDG_CONFIG_HOME/xinitrc
# host: sid 2021-03-21

xset         +fp      /usr/share/fonts/jmk
xrdb         -merge   $XDG_CONFIG_HOME/Xresources
xbindkeys    -f       $XDG_CONFIG_HOME/xbindkeysrc
xmodmap               ~/etc/xmodmaprc
setxkbmap se -variant nodeadkeys
setxkbmap    -option  terminate:ctrl_alt_bksp

# capslock -> esc
xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape'

# [][ ][] monitor setup
xrandr --output HDMI-0 --rotate left  --right-of DP-4 \
       --output DP-2   --rotate right --left-of DP-4

# https://forums.developer.nvidia.com/t/440-36-with-bumblebee-drops-to-1-fps-after-running-for-10-minutes/108431/4
xset s off -dpms &

# https://www.japh.se/2021/03/21/ratpoison-urxvt-and-borders.html
xsetroot -solid '#292929'

xscreensaver -no-splash &

# start mpd unless it's already started
#[ ! -s ~/var/mpd/pid ] && (mpd ~/etc/mpd.conf && mpdas && beets mpdstats)&
[ ! -s ~/var/mpd/pid ] && (mpd ~/etc/mpd.conf && mpdas)&
#exec pgrep -l cantata || cantata

/usr/lib/kdeconnectd &

exec catpoison -f $XDG_CONFIG_HOME/ratpoisonrc
