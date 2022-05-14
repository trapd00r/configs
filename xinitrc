#!/bin/sh
# $XDG_CONFIG_HOME/xinitrc
#
xset         +fp      /usr/share/fonts/jmk
if [[ $(hostname) = 'sid' ]]; then
  xrdb         -merge   "$XDG_CONFIG_HOME/Xresources-sid"
elif [[ $(hostname) = 'tp' ]]; then
  xrdb         -merge   $XDG_CONFIG_HOME/Xresources
fi
#xbindkeys    -f       $XDG_CONFIG_HOME/xbindkeysrc
setxkbmap se -variant nodeadkeys \
             -option  terminate:ctrl_alt_bksp
xbindkeys &

xmodmap               ~/etc/xmodmaprc
xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape'

# monitors
# [][][ ][]
if [[ $(hostname) = 'sid' ]]; then
  xrandr --output DP-4    --primary \
         --output HDMI-0  --rotate left  --right-of DP-4 \
         --output DP-2    --rotate right --left-of DP-4  \
         --output DVI-D-0 --left-of DP-2 --rotate left
# [][ ][ ]
elif [[ $(hostname) = 'tp' ]]; then
  xrandr --output HDMI-1 --primary      --left-of eDP-1 \
         --output DP-2   --rotate right --left-of HDMI-1
  kbdlight&
fi

# https://forums.developer.nvidia.com/t/440-36-with-bumblebee-drops-to-1-fps-after-running-for-10-minutes/108431/4
xset s off -dpms &

xset r rate 280 30
xkbset bouncekeys 50
xbanish &

# https://www.japh.se/2021/03/21/ratpoison-urxvt-and-borders.html
xsetroot -solid '#242424'
xsetroot -cursor_name left_ptr

xscreensaver -no-splash &

# notifications
dunst &

# for controlling phone or the other way around
/usr/lib/kdeconnectd &

#mullvad connect &


# gtk applications startup very slow
# https://bbs.archlinux.org/viewtopic.php?id=224787
dbus-update-activation-environment --systemd DBUS_SESSION_BUS_ADDRESS DISPLAY XAUTHORITY

## perhaps do this?
for f in /etc/X11/xinit/xinitrc.d/*.sh; do
  source "$f"
done

lxsession &

#exec catpoison -f $XDG_CONFIG_HOME/ratpoisonrc
exec sdorfehs-20220514 -f $HOME/dev/sdorfehs-config/sdorfehsrc
