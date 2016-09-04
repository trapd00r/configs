## vim:ft=sh:
# {XDG_CONFIG_HOME}/xinitrc
# host: elite
# 2016-09-03 10:50:23

setxkbmap -option      terminate:ctrl_alt_bksp &
setxkbmap se -variant  nodeadkeys &
xsetroot  -cursor_name left_ptr &
feh       --bg-center  ~/img/dylan.jpg &
xmodmap                ${XDG_CONFIG_HOME}/xmodmaprc   &
motion    -c           ${XDG_CONFIG_HOME}/motion.conf &
xrdb                   ${XDG_CONFIG_HOME}/Xresources  &
xset      +fp          /usr/share/fonts
xset                   fp rehash
dhcpcd &

ratpoison
