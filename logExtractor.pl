#!/usr/bin/perl -w

use Getopt::Std;
my $logFile = "none";
my $inputColumns = "none";
my $printColumnNames = 0;
my @columns = ();
my @columnNames = ();
my $cNames = "none";

# Vasu: Code for Log Extraction 
# Usage Details:
print "Usage of Log Extractor : ./logExtractor.pl -f app-delay-tracer.log -c 1,2,3/all !!!\n";
print "Usage of Log Extractor : ./logExtractor.pl -f app-delay-tracer.log -p !!!\n";
print "Usage of Log Extractor : ./logExtractor.pl -f app-delay-tracer.log -e DelayUS,AppId !!!\n";

getopts('f:c:e:p', \%options);

# Validate the option f
if ($options{f}) {
    $logFile = $options{f};
    print "Input Log file: $logFile\n";
}
elsif (! $options{f}) {
    print "\nERROR: Specify the the Log file with -f option \n";
    print_usage ();
    exit;
}

# Validate the options c, e & p
if ($options{c}) {
    $inputColumns = $options{c};
    @columns = split (/,/,$inputColumns);
    print "Columns of the LogFile for extraction are: $inputColumns\n";
}
elsif ($options{e}) {
    $cNames = $options{e};
    @columnNames = split (/,/,$cNames);
    print "Columns of the LogFile for extraction are: $cNames\n";
}
elsif ($options{p}) {
    $printColumnNames = 1;
} 
elsif (! $options{c}) {
    print "ERROR: Specify the columns to be extracted from the Log file: $options{f}\n";
    print_usage ();
    exit;
}
elsif (! $options{e}) {
    print "ERROR: Specify the columns to be extracted from the Log file: $options{f}\n";
    print_usage ();
    exit;
}

# Subroutine for printing the usage of this script file
sub print_usage {
    print "\n!!! Usage of Log Extractor : ./logExtractor.pl -f app-delay-tracer.log -c 1,2,3 !!!\n";
    print "!!! Usage of Log Extractor : ./logExtractor.pl -f app-delay-tracer.log -p !!!\n";
    print "!!! Usage of Log Extractor : ./logExtractor.pl -f app-delay-tracer.log -e DelayUS,AppId !!!\n";
    print "!!! -f: -> Log file to extract the contents. !!!\n";
    print "!!! -c: -> Columns to be extracted from Log file (all for all entries) !!!\n";
    print "!!! -p: -> print the number of columns in the file and the column details !!!\n";
    print "!!! -e: -> Columns to be extraced if the column names is specified !!!\n";
}

my $logcount = 0;
open (LOG, "$logFile");
while (<LOG>) {
    chomp ($_);
    my $line = "$_";
    if ($inputColumns eq "all") {
    	print "$line\n";
    }
    elsif ($printColumnNames == 1) {
    	print "$line\n";
	exit;
    }
    else {
	if ($line =~ s/\s+/ /g) {
    	    #print "Actual Log entry is: $line\n";
	    my @logSplits = split (/\s/, $line);
	    my $logForDisplay = "";
	    if ($inputColumns) {
		foreach my $column (@columns) {
		    if (($column <= $#logSplits) && ($column > 0)) {
		        $logForDisplay = "$logForDisplay". "$logSplits[$column-1]\t\t";
		    }
	        }
	    }
		print "Input Columns: $inputColumns\n";
	    print "$logForDisplay\n";
	}
	if (! /^Time/) {
	    $logcount++;	
	}
    }
}

close (LOG);
print ("Total Number of Log enries: $logcount\n");
