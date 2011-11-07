#!/usr/bin/perl -w

# make-gtkrc.pl -- Build gtkrc files from templates
# $Id: make-gtkrc.pl,v 1.1.1.1 2002/01/18 21:39:57 seth Exp $

# make-gtkrc.pl SUBST-FILE... < INPUT > OUTPUT

use Getopt::Std;


# Default parameter values (from Eazel-Teal)

my %substs = (
  focus_color		=> '"#508083"',
  # focus_color gets set in <0>, so use it by default
  menuitem_gradient	=> '{ vertical : <0,0.5> [3] <0> [10] <0> [2] <0,0.6> }',
  insensitive_colors	=> '"#636563", "#cecfce"',
  gradiented_menus	=> 'no',
  prelight_check_buttons => 'yes',
  lists_have_separators	=> 'no',
);


# Read any command line options

if (!getopts ('c:d:')) {
    print "usage: make-gtkrc.pl [-c COLOR] [-d ENGINE-DIR] [SUBST-FILES..] <IN >OUT\n";
    exit 1;
}

if (defined $opt_c) {
    # opt_c sets the focus_color
    $_ = $opt_c;
    if (/^\#/) {
	$_ = '"' . $_ . '"';
    }
    $substs{'focus_color'} = $_;
}

if (defined $opt_d) {
    # opt_d sets the `@enginedir@' substitution
    $substs{'enginedir'} = $opt_d;
}
    
# Read all substitutions into %substs hash

foreach my $subst_file (@ARGV) {

    open (SUBST, $subst_file) or die "Can't open $subst_file for input: $!";

    while (<SUBST>) {
	# skip blank lines and comments
	next if /^#/;
	next if /^\s*$/;
	chop;

	if (! /^(\S+?)\s+(.*)$/) {
	    die "Malformed substitution: $_";
	}

	$substs{$1} = $2;
    }

    close SUBST;
}


# Then run through STDIN applying them..

print "# gtkrc generated automatically by make-gtkrc.pl\n\n";

my $if_state = 1;
my @if_stack = ();

while (<STDIN>) {
    my @tokens = split (/\@/);

    while (@tokens) {
	# this is a verbatim token

	my $text = shift (@tokens);
	my $swallow_nl = 0;

	if ($if_state) {
	    print ($text);
	}

	if (@tokens) {
	    # this is an @foo@ expression

	    my $expr = shift (@tokens);

	    if ($expr =~ /^\s*$/) {
		# `@@' -> `@'

		print '@';

	    } elsif ($expr =~ /^if\s+(\S+)$/) {
		# if statement

		push (@if_stack, $if_state);
		$if_state = $substs{$1} ne 'no';
		$swallow_nl = 1;

	    } elsif ($expr =~ /^\s*else\s*$/) {
		# else statement

		$if_state = ! $if_state;
		$swallow_nl = 1;

	    } elsif ($expr =~ /^\s*endif\s*$/) {
		# endif statement

		$if_state = pop (@if_stack);
		$swallow_nl = 1;

	    } elsif ($expr =~ /^\s*(\S+)\s*$/) {
		# `@foo@' -> <value of foo>

		my $word = $1;
		if (!defined $substs{$word}) {
		    die "Undefined substitution: $word";
		}
		if ($if_state) {
		    print $substs{$word};
		}
	    }

	    if ($swallow_nl && @tokens && $tokens[0] eq "\n") {
		@tokens = ();
	    }
	}
    }
}

# End of make-gtkrc.pl
