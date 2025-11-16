#!/bin/bash

# Move current window to previous workspace on the same monitor
# Alt+Shift+h will move window to previous workspace on focused monitor

# Get current workspace number and output
current_workspace=$(i3-msg -t get_workspaces | jq -r '.[] | select(.focused==true) | .num')
focused_output=$(i3-msg -t get_workspaces | jq -r '.[] | select(.focused==true).output')

# Define workspace ranges for each monitor
case "$focused_output" in
    "DP-2"|"DP-4-1-5"|"DP-3-1-5"|"eDP-1")  # Middle monitor
        min_ws=1
        max_ws=9
        ;;
    "DP-0"|"DP-3"|"DP-1")  # Left monitor
        min_ws=10
        max_ws=18
        ;;
    "DP-5"|"DP-4-1-6"|"DP-3-1-6")  # Top monitor
        min_ws=19
        max_ws=27
        ;;
    "HDMI-0")  # Behind monitor
        min_ws=28
        max_ws=36
        ;;
    *)
        echo "No matching output for workspace navigation."
        exit 1
        ;;
esac

# Calculate previous workspace (wrap around)
if [ "$current_workspace" -le "$min_ws" ]; then
    prev_workspace=$max_ws
else
    prev_workspace=$((current_workspace - 1))
fi

i3-msg move container to workspace number $prev_workspace
i3-msg workspace number $prev_workspace

