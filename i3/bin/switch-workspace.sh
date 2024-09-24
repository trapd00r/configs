#!/bin/bash

# use mod+1, mod+2 etc to switch to workspaces on different monitors
# there is 5 workspaces on the main monitor, but on the other ones there is only 2
# workspace 6,7 on left monitor is treated like workspace 1,2 so
# we can use the same keybindings to switch to them
# in practice, emulating a more sane workspace setup (ratpoison, sdorfehs)

# Get the name of the active output
focused_output=$(i3-msg -t get_workspaces | jq -r '.[] | select(.focused==true).output')

case "$focused_output" in
    "DP-0")  # Left Monitor
        case "$1" in
            1) i3-msg workspace number 6 ;;  # Mod+1 switches to workspace 6
            2) i3-msg workspace number 7 ;;  # Mod+2 switches to workspace 7
        esac
        ;;
    "DP-5")  # Top Monitor
        case "$1" in
            1) i3-msg workspace number 8 ;;  # Mod+1 switches to workspace 8
            2) i3-msg workspace number 9 ;;  # Mod+2 switches to workspace 9
        esac
        ;;
    "DP-2")  # Middle Monitor
        case "$1" in
            1) i3-msg workspace number 1 ;;  # Mod+1 switches to workspace 1
            2) i3-msg workspace number 2 ;;  # Mod+2 switches to workspace 2
            3) i3-msg workspace number 3 ;;
            4) i3-msg workspace number 4 ;;
            5) i3-msg workspace number 5 ;;
        esac
        ;;
    "HDMI-0")  # Behind Monitor
        echo "HDMI-0 output not configured for specific workspace switches." ;;
    *)
        echo "No matching output for keybinding"
        ;;
esac

# i3 config:

# # define outputs
# set $middle DP-2
# set $left DP-0
# set $top DP-5
# set $behind HDMI-0
#
# set $ws1 1
# set $ws2 2
# set $ws3 3
# set $ws4 4
# set $ws5 5
# set $ws6 6
# set $ws7 7
# set $ws8 8
# set $ws9 9
#
# # lock workspaces to outputs
# workspace $ws1 output $middle
# workspace $ws2 output $middle
# workspace $ws3 output $middle
# workspace $ws4 output $middle
# workspace $ws5 output $middle
# workspace $ws6 output $left
# workspace $ws7 output $left
# workspace $ws8 output $top
# workspace $ws9 output $top
#
#
# # workspace 1 on different monitors
# # in reality we switch to workspace 6,7 etc
# bindsym $mod+1 exec --no-startup-id /bin/bash ~/etc/i3/bin/switch-workspace.sh 1
# bindsym $mod+2 exec --no-startup-id /bin/bash ~/etc/i3/bin/switch-workspace.sh 2
#
# bindsym $mod+3 workspace number $ws3
# bindsym $mod+4 workspace number $ws4
# bindsym $mod+5 workspace number $ws5
