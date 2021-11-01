# assembly-stats

Get assembly statistics from FASTA and FASTQ files.

[![Build Status](https://travis-ci.org/sanger-pathogens/assembly-stats.svg?branch=master)](https://travis-ci.org/sanger-pathogens/assembly-stats)
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-brightgreen.svg)](https://github.com/sanger-pathogens/assembly-stats/blob/master/LICENSE)

## Contents
* [Installation](#installation)
* [Usage](#usage)
  * [Example](#example)
* [License](#license)
* [Feedback/Issues](#feedbackissues)

## Installation
If you encounter an issue when installing assembly-stats please contact your local system administrator. If you encounter a bug please log it [here](https://github.com/sanger-pathogens/assembly-stats/issues) or email us at path-help@sanger.ac.uk

### Dependencies
- zlib

### Compiling from source
Run the following commands to install the program
`assembly-stats` to `/usr/local/bin/`.

    mkdir build
    cd build
    cmake ..
    make
    make test
    make install

If you do not have root access, you can install to a directory of your choice
by changing the call to cmake. For example:

    cmake -DINSTALL_DIR:PATH=/foo/bar/ ..

would mean you finish up with a copy of `assembly-stats` in the directory
`/foo/bar/`.

## Usage
Get statistics from a list of files:

    assembly-stats file.fasta another_file.fastq

Detection of FASTA or FASTQ format of each file is automatic from the file
contents, so file names and extensions are irrelevant.

The files can be supplied in compressed format (.gz, .bz2 or
.xz). Compression support depends on what libraries are available when
assembly-stats is compiled. Compression type is detected
automatically and does not depend on the file name extensions.

The default output format is human readable.
You can change the output format and ignore sequences shorter than a
given length. Get the full usage by running with no files listed:

    $ assembly-stats
    usage: stats [options] <list of fasta/q files>
    
    Reports sequence length statistics from fasta and/or fastq files
    
    options:
    -l <int>
        Minimum length cutoff for each sequence.
        Sequences shorter than the cutoff will be ignored [1]
    -s
        Print 'grep friendly' output
    -t
        Print tab-delimited output
    -u
        Print tab-delimited output with no header line

### Example
Here is an example on the _Plasmodium falciparum_ reference genome:

    $ assembly-stats Pf3D7_v3.fasta
    stats for Pf3D7_v3.fasta
    sum = 23328019, n = 16, ave = 1458001.19, largest = 3291936
    N50 = 1687656, n = 5
    N60 = 1472805, n = 7
    N70 = 1445207, n = 8
    N80 = 1343557, n = 10
    N90 = 1067971, n = 12
    N100 = 5967, n = 16
    N_count = 0
    Gaps = 0

The numbers should be self-explanatory, except maybe lines like
`N50 = 1687656, n = 5`. The N50 is 1687656, with 50% of the assembly in 5
sequences. A "gap" is any consecutive run of Ns (undetermined nucleotide bases) of any length (it is case-insensitive so
counts any "n" as well).  N_count is the total Ns (undetermined nucleotide bases) across the entire assembly.

## License
assembly-stats is free software, licensed under [GPLv3](https://github.com/sanger-pathogens/assembly-stats/blob/master/LICENSE).

## Feedback/Issues
Please report any issues to the [issues page](https://github.com/sanger-pathogens/assembly-stats/issues) or email path-help@sanger.ac.uk
