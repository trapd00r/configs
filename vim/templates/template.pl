#!/usr/bin/perl
# vim: ft=perl:fdm=marker:fmr=#<,#>:fen:et:sw=2:
use strict;
use warnings FATAL => 'all';
use vars     qw($VERSION);
use autodie  qw(:all);

my $APP  = '';
$VERSION = '0.001';

use Data::Dumper;

{
  package Data::Dumper;
  no strict 'vars';
  $Terse = $Indent = $Useqq = $Deparse = $Sortkeys = 1;
  $Quotekeys = 0;
}


=begin comment


Here goes inline comments that won't show up in pod doc

=end comment


=cut




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
  L<~/|http://japh.se>
  L<git|http://github.com/trapd00r>

=head1 CONTRIBUTORS

None required yet.

=head1 COPYRIGHT

Copyright 2019- B<THIS APPLICATION>s L</AUTHOR> and L</CONTRIBUTORS> as listed
above.

=head1 LICENSE

This program is free software; you can redistribute it and/or modify
it under the same terms as Perl itself.

=head1 SEE ALSO

L<~/|http://japh.se>

=cut
