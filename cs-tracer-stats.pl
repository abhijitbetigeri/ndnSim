#!/usr/bin/perl -w

my $count_args = $#ARGV;

# Script to extract the cache hits from the app-delay-tracer and cs-trace log files

print "Usage: ./cs-tracer-stats.pl cs-trace.txt app-delays-trace.txt \n";

#print "Number of ars to this script is: $count_args\n";
#foreach my $num (0 .. $count_args) {
#    print "$ARGV[$num]\n";
#}

my $hitcount = 0;
my $misscount = 0;
my $cachehits = 0;
my $cachehits_core = 0;
my $cachehits_edge = 0;
my $lineNo = 1;

my $file_cslog = "$ARGV[0]";
my $file_applog = "$ARGV[1]";
#my $nodes = "$ARGV[2]";

#if ($nodes =~ m/\d+\-\d+/) {
#    print " Found Matching";
#}


if (-e $file_cslog) {
   print "Input CS-LOG-Tracer File: $file_cslog\n";
}
if (-e $file_applog) {
   print "Input APP-LOG-Tracer File: $file_applog\n";
}

open CS_LOGTRACER, "$file_cslog" or die $!;
print "\nProcessing cs-trace.txt log..................\n";
while (<CS_LOGTRACER>) {
    my $line = $_;
    $line =~ s/\s+/ /g;
    #print "$line\n";
    my @splits = split (/\s/, $line);
    my $node = $splits[1];
    chomp ($node);
    #print "Node: $node\n";
    if ($line =~ m/(.*)CacheHits (.*)/) {
	my $line_hits = $2;
	chomp ($line_hits);
	$hitcount = $hitcount + $line_hits;
	if ($node <= 7) {
	    $cachehits_edge = $cachehits_edge + $line_hits;
	}
	elsif ($node > 8) {
	    $cachehits_core = $cachehits_core + $line_hits;
	}	
    }
    if ($line =~ m/(.*)CacheMisses (.*)/) {
	my $line_misses = $2;
	chomp ($line_misses);
	$misscount = $misscount + $line_misses;
    }
}
close (CS_LOGTRACER);


open APP_LOGTRACER, "$file_applog" or die $!;
print "\nProcessing app-delay-trace.txt log..................\n";
while (<APP_LOGTRACER>) {
    my $is_even = $lineNo % 2;
    # Process only the even line numbers as the app log tracer file will have duplicate entries.
    if ($is_even == 0) {
    	my $line = $_;
	$line =~ s/\s+/ /g;
    	#print "$line\n";
    	my @logsplits = split (/\s/, $line);
    	#print "$logsplits[9] \n";
    	my $temp_cachehit = $logsplits[9];
	chomp ($temp_cachehit);
	$temp_cachehit =~ s/\s+//g;
    	if ($temp_cachehit > 0 )  {
    	    $cachehits = $cachehits + $temp_cachehit;
    	}
    }
    $lineNo ++;
}
close (APP_LOGTRACER);

print "\n##############  Hits/Misses Counts Statistics ##############\n";
print "Total Aggregates Cache Hits(cs-trace count) All Nodes  : $hitcount \n";
print "Total Aggregates Cache Miss(cs-trace count) All Nodes  : $misscount \n";
print "Total Aggregates Cache Hits(cs-trace count) Core Nodes : $cachehits_core \n";
print "Total Aggregates Hits(cs-trace count) Edges Nodes      : $cachehits_edge \n";
print "Total Cache Hits From App delay Tracer	              : $cachehits \n";
