#ifndef STATS_H
#define STATS_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "fasta.h"
#include "fastq.h"
#include "filetype.h"

using namespace std;

const short FORMAT_HUMAN = 0;
const short FORMAT_TAB = 1;
const short FORMAT_TAB_NO_HEAD = 2;
const short FORMAT_GREPPY = 3;


class Stats
{
public:
    Stats();
    Stats(string filename, unsigned long minimumLength=1);

    // return a string containing the stats. format must be one
    // of: FORMAT_{HUMAN, TAB, TAB_NO_HEAD, GREPPY}
    string toString(short format) const;

private:
    void init();
    string toString_human_readable() const;
    string toString_tab_delimited(bool header) const;
    string toString_greppy() const;
    double mean_;
    unsigned long n50_[9];
    unsigned long n50n_[9];
    unsigned long longest_;
    unsigned long shortest_;
    unsigned long number_;
    unsigned long totalLength_;
    unsigned long nCount_;
    unsigned long gapCount_;
    string filename_;
};

#endif // STATS_H
