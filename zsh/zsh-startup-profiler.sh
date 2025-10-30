#!/bin/zsh
# Zsh startup time profiler
# Usage: ./zsh-startup-profiler.sh

echo "=== Zsh Startup Profiling ==="
echo ""

# Method 1: Using zprof (already loaded in zshrc)
echo "Method 1: Using zprof"
echo "Uncomment '#zprof' at the end of your zshrc, then run:"
echo "  zsh -ic 'zprof | head -20'"
echo ""

# Method 2: Time measurement
echo "Method 2: Simple timing"
time zsh -ic 'exit'
echo ""

# Method 3: Trace mode (verbose)
echo "Method 3: Trace mode (shows every command)"
echo "Run: zsh -x 2>&1 | tee /tmp/zsh-trace.log"
echo ""

# Method 4: Profile specific sections
echo "Method 4: Profile specific sections"
echo "Add 'zprof' calls before/after sections in zshrc"
echo ""

# Method 5: Which files take longest
echo "Method 5: Time individual file sources"
echo "For each 'source' in zshrc, wrap with:"
echo "  time ( source ~/etc/zsh/filename.zsh )"
echo ""

