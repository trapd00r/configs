#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';
use vars qw($VERSION);
my $APP  = '';
$VERSION = '0.001';

use Data::Dumper;

{
  package Data::Dumper;
  no strict 'vars';
  $Terse = $Indent = $Useqq = $Deparse = $Sortkeys = 1;
  $Quotekeys = 0;
}





__END__


=pod

=head1 NAME

=head1 USAGE

=head1 DESCRIPTION

=head1 OPTIONS

=head1 REPORTING BUGS

Report bugs and/or feature requests on rt.cpan.org, the repository issue tracker
or directly to L<magnus@trapd00r.se>

=head1 AUTHOR

  Magnus Woldrich
  CPAN ID: WOLDRICH
  magnus@trapd00r.se
  http://japh.se

=head1 CONTRIBUTORS

None required yet.

=head1 COPYRIGHT

Copyright 2011 B<THIS APPLICATION>s L</AUTHOR> and L</CONTRIBUTORS> as listed
above.

=head1 LICENSE

This program is free software; you can redistribute it and/or modify
it under the same terms as Perl itself.

=head1 SEE ALSO

=cut

# vim: set ts=2 et sw=2 fdm=marker:
