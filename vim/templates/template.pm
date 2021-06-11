package Vim::Template;
use strict;
use utf8;
use open qw(:std :utf8);

BEGIN {
  use Exporter;
  use vars qw($VERSION @ISA @EXPORT_OK %EXPORT_TAGS);
  @ISA = qw(Exporter);

  $VERSION = '0.001';

  @EXPORT_OK = qw();
  %EXPORT_TAGS = [ qw() ];
}

use Carp ();
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

=head1 SYNOPSIS

=head1 DESCRIPTION

=head1 EXPORTS

None by default.

=head1 FUNCTIONS

=head2 foo()

=over 4

=item    Arguments: $string

=item Return value: \%hash

=back

Description.

=head1 REPORTING BUGS

Report bugs and/or feature requests on rt.cpan.org, the repository issue tracker
or directly to L<m@japh.se>

=head1 AUTHOR

  Magnus Woldrich
  CPAN ID: WOLDRICH
  m@japh.se
  japh@irc.libera.chat #perl
  L<~/|http://japh.se>
  L<git|http://github.com/trapd00r>

=head1 CONTRIBUTORS

None required yet.

=head1 COPYRIGHT

Copyright 2021- B<THIS MODULE>s L</AUTHOR> and L</CONTRIBUTORS> as listed above.

=head1 LICENSE

This library is free software; you may redistribute it and/or modify it under
the same terms as Perl itself.

=head1 SEE ALSO

L<~/|http://japh.se>

=cut
