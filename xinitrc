#!/bin/bash
# vim: ft=sh smc=80 cc= fdm=marker fen fmr=#<,#>:

#< output
#xrandr --output DVI-D-0 --mode 1920x1080 --pos 0x0 --rotate left --output HDMI-0 --mode 1920x1080 --pos 1080x528 --rotate normal
#xrandr --output DVI-D-0 --mode 1920x1080 --pos 0x0 --rotate left --output HDMI-0 --mode 1920x1080 --rotate left --pos 1080x525 &
xrandr --output DVI-D-0 --mode 1920x1080 --pos 1080x0 --rotate left --output HDMI-0 --mode 1920x1080 --rotate left --pos 0x0 &
#>
#< input
#unclutter -idle 4 &
#xset m 2 1 &
xsetroot  -cursor_name right_ptr
setxkbmap -option terminate:ctrl_alt_bksp
setxkbmap se -variant progqwerty \
  || setxkbmap se -variant nodeadkeys
xmodmap $HOME/etc/xmodmaprc &
#>
xrdb $HOME/etc/Xresources &
#< wm
#exec openbox-session
#exec  dwm
#exec  wmiii
#exec  i3
#exec enlightenment_start -no-precache
#exec evilwm
#exec antiwm
exec wrxvt &
exec ratpoison
#>
