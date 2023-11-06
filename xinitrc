#!/bin/sh
# $XDG_CONFIG_HOME/xinitrc

xset         +fp      ~/.fonts

if [[ $(hostname) = 'fantomen' ]]; then
  xrdb -merge "$XDG_CONFIG_HOME/Xresources-sid"

  # monitors
  #    [ ]
  #  [][ ][]

  # nvidia-settings --assign "CurrentMetaMode=DPY-1: nvidia-auto-select @1080x1920 +0+0 {ViewPortIn=1080x1920,ViewPortOut=1920x1080+0+0, Rotation=270}, DPY-0: nvidia-auto-select @1080x1920 +3000+0 {ViewPortIn=1080x1920, ViewPortOut=1920x1080+0+0, Rotation=90},DPY-3: nvidia-auto-select @1920x1080 +1080+0 {ViewPortIn=1920x1080, ViewPortOut=1920x1080+0+0}"
  xrandr --output DP-2   --primary \
         --output DP-0   --rotate right  --left-of DP-2 \
         --output DP-5   --above DP-2 \
         --output HDMI-0 --below DP-2

  # https://forums.developer.nvidia.com/t/440-36-with-bumblebee-drops-to-1-fps-after-running-for-10-minutes/108431/4
  xset s off -dpms &

  # https://www.japh.se/2021/03/21/ratpoison-urxvt-and-borders.html
  xsetroot -solid '#161616'

  # https://github.com/trapd00r/hass-mpd-ikea
  webhook -hooks ${HOME}/dev/hass-mpd-ikea/hooks.json &

  perl ${HOME}/dev/sdorfehs-config/sdorfehs-bar.pl &

elif [[ $(hostname) = 'x1' ]]; then
  xrdb -merge   "$XDG_CONFIG_HOME/Xresources-x1"
  xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape'

#  # turn off display after 5 min idle
#  xset s off
#  xset +dpms
#  xset dpms 0 300 350

# disable screen blanking
  xset s off
  xset s noblank
  xset -dpms
  xset dpms 0 0 0
  feh --bg-center ~/img/wp.jpg
fi

setxkbmap se -variant nodeadkeys -option  terminate:ctrl_alt_bksp

# mod4+p = shift-insert
xbindkeys -f $XDG_CONFIG_HOME/xbindkeysrc

xmodmap ~/etc/xmodmaprc

xset r rate 280 30
xkbset bouncekeys 50
xbanish &

xsetroot -cursor_name left_ptr


# gtk applications startup very slow
# https://bbs.archlinux.org/viewtopic.php?id=224787
dbus-update-activation-environment --systemd DBUS_SESSION_BUS_ADDRESS DISPLAY XAUTHORITY

# notifications
dunst &

# disable audit messages spamming dmesg
auditctl -e 0

# sync clipboard TO primary
autocutsel -selection CLIPBOARD -fork
# sync primary TO clipboard 
autocutsel -selection PRIMARY -fork

exec sdorfehs -f $HOME/dev/sdorfehs-config/sdorfehsrc
