## vim:ft=sh:
# {XDG_CONFIG_HOME}/xinitrc
# host: elite
# 2016-09-20 11:49:31

setxkbmap -option      terminate:ctrl_alt_bksp &
setxkbmap se -variant  nodeadkeys &
xsetroot  -cursor_name left_ptr &
#feh       --bg-center  ~/img/dylan.jpg &
xsetroot               &
xmodmap                ${XDG_CONFIG_HOME}/xmodmaprc   &
setxkbmap se -variant  nodeadkeys &
#motion    -c           ${XDG_CONFIG_HOME}/motion.conf &
xrdb                   ${XDG_CONFIG_HOME}/Xresources  &
#xset      +fp          /usr/share/fonts
#xset                   fp rehash
dhcpcd &
xbanish &
sshfs laleh:/var/log      ${HOME}/var/log &
sshfs laleh:http/japh.se  ${HOME}/japh.se &

## desktop
#xmodmap -e 'clear Lock' -e 'keycode 0x42 = Escape'
# laptop
xmodmap -e 'clear Lock' -e 'keycode 66 = Escape'

sh $HOME/dev/dzen-scripts/dzen_elite.sh &
perl $HOME/perl5/bin/knradio -l         &

#catpoison
ratpoison
