#!/bin/sh
# $XDG_CONFIG_HOME/xinitrc

#----------------------------------------
# create a font path
#----------------------------------------
xset +fp /usr/share/fonts/misc/
xset +fp      ~/.fonts
fc-cache -f &

if [[ $(hostname) = 'fantomen' ]]; then
  xrdb -merge "$XDG_CONFIG_HOME/Xresources-sid"

  # monitors
  #    [ ]
  #  [][ ][]

  # nvidia-settings --assign "CurrentMetaMode=DPY-1: nvidia-auto-select @1080x1920 +0+0 {ViewPortIn=1080x1920,ViewPortOut=1920x1080+0+0, Rotation=270}, DPY-0: nvidia-auto-select @1080x1920 +3000+0 {ViewPortIn=1080x1920, ViewPortOut=1920x1080+0+0, Rotation=90},DPY-3: nvidia-auto-select @1920x1080 +1080+0 {ViewPortIn=1920x1080, ViewPortOut=1920x1080+0+0}"
  xrandr --output DP-2   --primary \
         --output DP-0   --rotate right  --left-of DP-2 \
         --output DP-5   --above DP-2 \
         --output HDMI-0 --below DP-2 \
         --output DVI-I-1-1 --left-of DP-0
#         --output DVI-I-1-1 --rotate left --left-of DP-0

  # https://forums.developer.nvidia.com/t/440-36-with-bumblebee-drops-to-1-fps-after-running-for-10-minutes/108431/4
  xset s off -dpms &

  # https://www.japh.se/2021/03/21/ratpoison-urxvt-and-borders.html
  xsetroot -solid '#161616'

  # https://github.com/trapd00r/hass-mpd-ikea
  webhook -hooks ${HOME}/dev/hass-mpd-ikea/hooks.json &

#  perl ${HOME}/dev/sdorfehs-config/sdorfehs-bar.pl &

elif [[ $(hostname) = 'x1' ]]; then
  xrdb -merge   "$XDG_CONFIG_HOME/Xresources-x1"
  #----------------------------------------
  # only needed on laptop keyboard
  #----------------------------------------
  xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape'

  #----------------------------------------
  # disable screen blanking
  #----------------------------------------
  xset s off
  xset s noblank
  xset -dpms
  xset dpms 0 0 0


  xsetroot -solid '#161616'

  # kontor
  # xrandr --output HDMI-1 --primary --output eDP-1 --right-of HDMI-1

  # docked at home
  xrandr --output eDP-1 --mode 1920x1200 --pos 3000x720 --rotate normal --output DP-3-1-5 --primary --mode 1920x1080 --pos 1080x1080 --rotate normal --output DP-3-1-6 --mode 1920x1080 --pos 0x318 --rotate right --output DP-3-2 --mode 1920x1080 --pos 1080x0 --rotate normal --output DP-3-3 --off
  # xrandr --output eDP-1 --mode 1920x1200 --pos 3000x720 --rotate normal --output DP-4-1-5 --primary --mode 1920x1080 --pos 1080x1080 --rotate normal --output DP-4-1-6 --mode 1920x1080 --pos 0x318 --rotate right --output DP-4-2 --mode 1920x1080 --pos 1080x0 --rotate normal --output DP-4-3 --off
fi

#----------------------------------------
# set keyboard layout and options
#----------------------------------------
setxkbmap se -variant nodeadkeys -option terminate:ctrl_alt_bksp
#setxkbmap se -variant us -option terminate:ctrl_alt_bksp
xset r rate 280 30
xkbset bouncekeys 50

# mpd4+p = shift-insert
# xbindkeys -f $XDG_CONFIG_HOME/xbindkeysrc

#----------------------------------------
# set mouse cursor and options
#----------------------------------------
#xbanish &
xsetroot -cursor_name left_ptr

#----------------------------------------
# setup clipboard sync
#   clipboard -> primary
#   primary   -> clipboard
#----------------------------------------
autocutsel -selection CLIPBOARD -fork
autocutsel -selection PRIMARY -fork

#----------------------------------------
# things needed when not using a DE
#----------------------------------------
dunst &

# for graphical authentication popups
lxpolkit &

# gtk applications startup very slow
# https://bbs.archlinux.org/viewtopic.php?id=224787
dbus-update-activation-environment --systemd DBUS_SESSION_BUS_ADDRESS DISPLAY XAUTHORITY


if [[ $(hostname) = 'fantomen' ]]; then
  polybar --config=$HOME/etc/polybar/config_fantomen.ini &
#  openbox-session
  exec sdorfehs -f $HOME/dev/sdorfehs-config/sdorfehsrc
elif [[ $(hostname) = 'x1' ]]; then
  polybar --config=$HOME/etc/polybar/config_x1.ini &
  exec sdorfehs -f $HOME/dev/sdorfehs-config/sdorfehsrc-x1
fi
