#!/bin/sh
# vim:ft=sh:
# $XDG_CONFIG_HOME/xinitrc
# host: sid 2021-03-21

xset         +fp      /usr/share/fonts/jmk
xrdb         -merge   $XDG_CONFIG_HOME/Xresources
#xbindkeys    -f       $XDG_CONFIG_HOME/xbindkeysrc
setxkbmap se -variant nodeadkeys \
             -option  terminate:ctrl_alt_bksp
xbindkeys &

xmodmap               ~/etc/xmodmaprc
xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape'

#[ ] [][ ][] monitor setup
xrandr --output DP-4 --primary \
       --output HDMI-0 --rotate left  --right-of DP-4 \
       --output DP-2   --rotate right --left-of DP-4  \
       --output DVI-D-0 --left-of DP-2 # TV

# https://forums.developer.nvidia.com/t/440-36-with-bumblebee-drops-to-1-fps-after-running-for-10-minutes/108431/4
xset s off -dpms &

xset r rate 280 30
xkbset bouncekeys 50
xbanish &
$HOME/dev/sdorfehs-config/sdorfehs-feedbar &

# https://www.japh.se/2021/03/21/ratpoison-urxvt-and-borders.html
xsetroot -solid '#121212'

xscreensaver -no-splash &
dunst &
#mullvad connect &

# start mpd unless it's already started
[ ! -s ~/var/mpd/pid ] && (mpd ~/etc/mpd.conf && mpdas)&

/usr/lib/kdeconnectd &

#exec sdorfehs -f $HOME/dev/sdorfehs-config/sdorfehsrc
exec sdorfehs-2022 -f $HOME/dev/sdorfehs-config/sdorfehsrc
#exec catpoison -f $XDG_CONFIG_HOME/ratpoisonrc
#exec openbox
