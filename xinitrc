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
#nvidia-settings --assign "CurrentMetaMode=\
#  DPY-1: nvidia-auto-select @2560x2880 +0+1080 {Rotation=0}, \
#  DPY-6: nvidia-auto-select @1920x1080 +2560+0 {Rotation=0}, \
#  DPY-3: nvidia-auto-select @1920x1080 +2560+1080 {Rotation=0}, \
#  DPY-0: nvidia-auto-select @1920x1080 +4480+1080 {Rotation=90}"

  xrandr --output DP-2   --primary \
         --output DP-0   --left-of DP-2 \
         --output DP-5   --above DP-2 \
         --output HDMI-0 --below DP-2 \
         # --output DVI-I-1-1 --left-of DP-0
#         --output DVI-I-1-1 --rotate left --left-of DP-0

  # https://forums.developer.nvidia.com/t/440-36-with-bumblebee-drops-to-1-fps-after-running-for-10-minutes/108431/4
  xset s off -dpms &

  # https://www.japh.se/2021/03/21/ratpoison-urxvt-and-borders.html
  xsetroot -solid '#161616'

  # https://github.com/trapd00r/hass-mpd-ikea
  webhook -hooks ${HOME}/dev/hass-mpd-ikea/hooks.json &

  # NO FONTS IN VIVALDI UI!
  xfsettingsd &

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

  # 3 monitors from dock:
  # - HDMI
  # - HDMI
  # - DP
  # 1 monitor from laptop
  # - usb-c
 autorandr --load docked || autorandr --default default

#xrandr --output eDP-1 --primary --mode 1920x1200 --pos 4480x1254 --rotate normal --output HDMI-1 --off --output DP-1 --off --output DP-2 --off --output DP-3 --mode 2560x2880 --pos 0x0 --rotate normal --output DP-4 --off --output DP-1-1 --off --output DP-1-1-5 --mode 1920x1080 --pos 2560x1254 --rotate normal --output DP-1-1-6 --mode 1920x1080 --pos 2560x174 --rotate normal --output DP-1-2 --off --output DP-1-3 --off
#  xrandr --output eDP-1 --primary --mode 1920x1200 --pos 4480x1080 --rotate normal --output HDMI-1 --off --output DP-1 --off --output DP-2 --off --output DP-3 --mode 2560x2880 --pos 0x0 --rotate normal --output DP-4 --off --output DP-2-1 --off --output DP-2-1-5 --mode 1920x1080 --pos 2560x1080 --rotate normal --output DP-2-1-6 --mode 1920x1080 --pos 2560x0 --rotate normal --output DP-2-2 --off --output DP-2-3 --off
  # xrandr --output eDP-1 --mode 1920x1200 --pos 4480x1680 --output DP-1 --mode 2560x2880 --pos 0x0  --output DP-3-1-5 --primary --mode 1920x1080 --pos 2560x1800 --output DP-3-1-6 --mode 1920x1080 --pos 2560x720
  # xrandr --output eDP-1 --mode 1920x1200 --pos 4480x1680 --output DP-1 --mode 2560x2880 --pos 0x0  --output DP-4-1-5 --primary --mode 1920x1080 --pos 2560x1800 --output DP-4-1-6 --mode 1920x1080 --pos 2560x720
  # xrandr --output eDP-1 --mode 1920x1200 --pos 4480x461 --rotate normal --output HDMI-1 --off --output DP-1 --off --output DP-2 --off --output DP-3 --mode 2560x2880 --pos 0x0 --rotate normal --output DP-4 --off --output DP-2-1 --off --output DP-2-1-5 --primary --mode 1920x1080 --pos 2560x1080 --rotate normal --output DP-2-1-6 --mode 1920x1080 --pos 2560x0 --rotate normal --output DP-2-2 --off --output DP-2-3 --off
  # xrandr --output eDP-1 --mode 1920x1200 --pos 4480x643 --rotate normal --output HDMI-1 --off --output DP-1 --off --output DP-2 --off --output DP-3 --mode 2560x2880 --pos 0x0 --rotate normal --output DP-4 --off --output DP-1-1 --off --output DP-1-1-5 --primary --mode 1920x1080 --pos 2560x1080 --rotate normal --output DP-1-1-6 --mode 1920x1080 --pos 2560x0 --rotate normal --output DP-1-2 --off --output DP-1-3 --off
  # xrandr --output eDP-1 --mode 1920x1200 --pos 4480x840 --rotate normal --output HDMI-1 --off --output DP-1 --mode 2560x2880 --pos 0x0 --rotate normal --output DP-2 --off --output DP-3 --off --output DP-4 --off --output DP-4-1 --off --output DP-4-1-5 --primary --mode 1920x1080 --pos 2560x1362 --rotate normal --output DP-4-1-6 --mode 1920x1080 --pos 2560x282 --rotate normal --output DP-4-2 --off --output DP-4-3 --off

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
# autocutsel -selection CLIPBOARD -fork
# autocutsel -selection PRIMARY -fork
autocutsel -fork
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

# resolves slow pass retrieval
/usr/bin/gnome-keyring-daemon --daemonize --start --components=gpg,pkcs11,secrets,ssh

# polybar --config=$HOME/etc/polybar/config_fantomen.ini &
# exec bspwm


# undocked laptop uses:
# polybar middle --config=config_x1_undocked.ini

# for laptop
setxkbmap -option caps:escape

# set gtk4 theme...
# https://github.com/ALEX11BR/ThemeChanger


# dbus-launch --exit-with-session dconf write /org/gnome/desktop/interface/gtk-theme "'japh'"
# gsettings set org.gnome.desktop.interface gtk-theme "japh"



if [[ $(hostname) = 'fantomen' ]]; then
  exec i3-workspace-fix
  # exec sdorfehs -f $HOME/dev/sdorfehs-config/sdorfehsrc
elif [[ $(hostname) = 'x1' ]]; then
  exec i3-workspace-fix -c ~/etc/i3/config-x1
  # exec sdorfehs -f $HOME/dev/sdorfehs-config/sdorfehsrc-x1
fi

#exec bspwm




# for browsers (vivaldi) to use the gtk theme we must do a few things: 
# echo "[Settings]
# gtk-theme-name=japh
# " > ~/.config/gtk-3.0/settings.ini

# gsettings set org.gnome.desktop.interface gtk-theme "japh"
# killall xdg-desktop-portal xdg-desktop-portal-gtk
# /usr/lib/xdg-desktop-portal-gtk &
# /usr/lib/xdg-desktop-portal &

# NOTE. The look and settings of the file save dialog can be changed using dconf-editor.
# BUT due to a bug in dconf-editor the changes are not saved unless dconf-editor is started like this
# unset XDG_CONFIG_HOME && dconf-editor






