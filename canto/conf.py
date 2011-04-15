
add("http://reddit.com/r/linux.rss")
add("http://reddit.com/r/perl.rss")
add("http://reddit.com/r/vim.rss")
add("http://reddit.com/r/git.rss")
add("http://kerneltrap.org/node/feed")

link_handler("firefox --no-remote \"%u\"")
link_handler("rmcd -l \"%u\"", ext="mp3")

colors[0] = (250, 233)
colors[1] = (208, 233) # unread
colors[2] = (240, 233) # read
colors[3] = (220, 233) # links
colors[4] = (253, 233) # quotes
colors[5] = (112, 233) # attr
colors[6] = (031, 233) # image links

