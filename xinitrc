#!/bin/sh
# $XDG_CONFIG_HOME/xinitrc

xset         +fp      ~/.fonts
if [[ $(hostname) = 'sid' ]]; then
  xrdb         -merge   "$XDG_CONFIG_HOME/Xresources"
elif [[ $(hostname) = 'fantomen' ]]; then
  xrdb         -merge   "$XDG_CONFIG_HOME/Xresources-sid"
elif [[ $(hostname) = 'tp' ]]; then
  xrdb         -merge   $XDG_CONFIG_HOME/Xresources
fi
setxkbmap se -variant nodeadkeys \
             -option  terminate:ctrl_alt_bksp
             
xbindkeys    -f       $XDG_CONFIG_HOME/xbindkeysrc

xmodmap               ~/etc/xmodmaprc
xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape'

# xrandr --output DP-2 --primary --output HDMI-0 --rotate left --right-of DP-2 --output DP-0 --rotate right --left-of DP-2

# monitors
## [][][ ][]
# nvidia-settings --assign "CurrentMetaMode=DPY-1: nvidia-auto-select @1080x1920 +0+0 {ViewPortIn=1080x1920,ViewPortOut=1920x1080+0+0, Rotation=270}, DPY-0: nvidia-auto-select @1080x1920 +3000+0 {ViewPortIn=1080x1920, ViewPortOut=1920x1080+0+0, Rotation=90},DPY-3: nvidia-auto-select @1920x1080 +1080+0 {ViewPortIn=1920x1080, ViewPortOut=1920x1080+0+0}"
if [[ $(hostname) = 'fantomen' ]]; then
  xrandr --output DP-2   --primary \
         --output HDMI-0 --rotate left   --right-of DP-2 \
         --output DP-0   --rotate right  --left-of DP-2 \
         --output DP-5   --same-as DP-2  --right-of DP-0
  xrandr --output DP-2   --primary \
         --output HDMI-0 --rotate left --right-of DP-2 \
         --output DP-0 --rotate right --left-of DP-2
## [][ ][ ]
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
#/usr/lib/kdeconnectd &

#mullvad connect &


# gtk applications startup very slow
# https://bbs.archlinux.org/viewtopic.php?id=224787
dbus-update-activation-environment --systemd DBUS_SESSION_BUS_ADDRESS DISPLAY XAUTHORITY

## perhaps do this?
#for f in /etc/X11/xinit/xinitrc.d/*.sh; do
#  source "$f"
#done
#
#lxsession &

#mpd ~/etc/mpd.conf && [[ -z $(pgrep -xU $UID mpdas) ]] && mpdas &

# disable audit messages spamming dmesg
auditctl -e 0

if [[ $(hostname) = 'sid' ]]; then
  exec sdorfehs-2022 -f $HOME/dev/sdorfehs-config/sdorfehsrc
elif [[ $(hostname) = 'fantomen' ]]; then
  exec sdorfehs -f $HOME/dev/sdorfehs-config/sdorfehsrc
elif [[ $(hostname) = 'tp' ]]; then
  exec sdorfehs -f $HOME/dev/sdorfehs-config/sdorfehsrc
fi
