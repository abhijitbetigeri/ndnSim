#!/usr/bin/perl -w

my $count_args = $#ARGV;

# Script to extract the hop counts from the app-delay-tracer log file.

print "Usage: ./cs-tracer-stats.pl cs-trace.txt app-delays-trace.txt \n";

my $hopcount = 0;
my $lineNo = 1;
my $evenLineCount = 0;

my $file_applog = "$ARGV[0]";

open APP_LOGTRACER, "$file_applog" or die $!;
while (<APP_LOGTRACER>) {
    my $is_even = $lineNo % 2 == 0;
    # Process only the even line numbers as the app log tracer file will have duplicate entries.
    if ($is_even == 0) {
        my $line = $_;
        $line =~ s/\s+/ /g;
        #print "$line\n";
        my @logsplits = split (/\s/, $line);
        print "$logsplits[8] \n";
        my $temp_hopcount = $logsplits[8];
        chomp ($temp_hopcount);
        $temp_hopcount =~ s/\s+//g;
        if ($temp_hopcount > 0) {
            $hopcount = $hopcount + $temp_hopcount;
        }
	$evenLineCount++;
    }
    $lineNo ++;
}

close (APP_LOGTRACER);

print "\nTotal Hop Counts\n";
print "\nNumber of Log entries: $evenLineCount\n";
print "Total hop counts From App delay Tracer: $hopcount \n";
