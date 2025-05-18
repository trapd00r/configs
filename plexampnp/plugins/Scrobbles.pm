package Scrobbles;

use strict;
use warnings;
use DBI;
use Time::Piece;

sub new {
    my ($class) = @_;
    my $self = {};
    bless $self, $class;
    return $self;
}

sub get_output {
    my ($class, $now_playing) = @_;
    my $scrobbles = get_scrobbles($now_playing);
    return unless $scrobbles && $scrobbles->{scrobble_count};

    return sprintf("(%d scrobbles, first: %s, last: %s)",
        $scrobbles->{scrobble_count},
        $scrobbles->{first_scrobble},
        $scrobbles->{latest_scrobble}
    );
}

sub get_scrobbles {
    my ($class, $track) = @_;

    # Extract track info from the now_playing hash
    my $artist = $track->{artist};
    my $title = $track->{title};

    # Check if we have all required config values
    my $config = $main::config{db};
    unless ($config && ref($config) eq 'HASH') {
        warn "Database configuration not found or invalid\n";
        return;
    }

    for my $key (qw(host port dbname user pass)) {
        unless (defined $config->{$key}) {
            warn "Missing required database configuration: $key\n";
            return;
        }
    }

    my $dsn = sprintf("DBI:mysql:database=%s;host=%s;port=%s",
        $config->{dbname},
        $config->{host},
        $config->{port}
    );

    my $dbh = DBI->connect(
        $dsn,
        $config->{user},
        $config->{pass},
        { RaiseError => 0, PrintError => 1 }
    ) or return;

    my $sth = $dbh->prepare(q{
        SELECT
          s.artist,
          s.title,
          s.album,
          CAST(s.scrobbled_on AS DATE) as first_scrobble,
          COUNT(*) AS scrobble_count,
          (SELECT CAST(MAX(scrobbled_on) AS DATE) FROM scrobbles WHERE title = s.title) as latest_scrobble
        FROM
          scrobbles s
        WHERE
          s.title = ? AND s.artist = ?
        ORDER BY
          s.scrobbled_on ASC
        LIMIT 1
    });

    $sth->execute($title, $artist);
    my $result = $sth->fetchrow_hashref;
    $sth->finish;
    $dbh->disconnect;

    return $result;
}

1;
