## vim:ft=sh:
# {XDG_CONFIG_HOME}/xinitrc
# host: elite
# 2016-09-13 12:19:19

setxkbmap -option      terminate:ctrl_alt_bksp &
setxkbmap se -variant  nodeadkeys &
xsetroot  -cursor_name left_ptr &
#feh       --bg-center  ~/img/dylan.jpg &
xsetroot               &
xmodmap                ${XDG_CONFIG_HOME}/xmodmaprc   &
setxkbmap se -variant  nodeadkeys &
motion    -c           ${XDG_CONFIG_HOME}/motion.conf &
xrdb                   ${XDG_CONFIG_HOME}/Xresources  &
xset      +fp          /usr/share/fonts
xset                   fp rehash
dhcpcd &
xbanish &
xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape'

sh $HOME/dev/dzen-scripts/dzen_elite.sh &

catpoison
#ratpoison
