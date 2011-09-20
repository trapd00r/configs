#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';
use vars qw($VERSION);

my $APP  = '';
$VERSION = '0.001';

use Devel::Comments;
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
or directly to L<m@japh.se>

=head1 AUTHOR

  Magnus Woldrich
  CPAN ID: WOLDRICH
  m@japh.se
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

L<stuff|http://japh.se>

=cut
