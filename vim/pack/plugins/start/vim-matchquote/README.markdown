# vim-matchquote

A Vim plugin to provide `%`-style motion for `'` (single quotation mark), `"` (double quotation mark), `` ` `` (backtick), and `|` (pipe).

Given these constraints:

- only the current line is considered;
- the quotation mark under the cursor must occur an even number of times in the line.

Let's say the cursor is on the nth occurrence of the quotation mark.  Then:

- if n is odd, the cursor moves forward to the next occurrence;
- otherwise the cursor moves backward to the previous occurrence.

The plugin also adds a text object for inner pipe (`i|`) and around pipe (`a|`).

Please note the matchit plugin (if you use it) should be loaded before this plugin.


## Licence

Copyright Andrew Stewart.  Distributed under the MIT licence.
