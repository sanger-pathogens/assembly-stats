#include "stats.h"

#include "bxzstr.hpp"

void Stats::init()
{
    mean_ = 0;
    for (int i = 0; i < 9; i++)
    {
        n50_[i] = 0;
        n50n_[i] = 0;
    }

    longest_ = 0;
    shortest_ = 0;
    number_ = 0;
    totalLength_ = 0;
    nCount_ = 0;
    gapCount_ = 0;
    filename_ = "";
}


Stats::Stats()
{
    init();
}


Stats::Stats(string filename, unsigned long minimumLength)
{
    init();
    vector<int> seqLengths;
    bxz::ifstream inStream;
    unsigned long cumulativeLength = 0;

    inStream.open(filename.c_str());

    if (! inStream.is_open())
    {
        cerr << "Error opening file '" << filename << "'" << endl;
        exit(1);
    }

    filename_ = filename;

    short filetype = fastaOrFastq(inStream);
    while(inStream.good())
    {
        Fasta* seq;

        if (filetype == FASTQ_FILE)
        {
            Fastq* p;
            p = new Fastq;
            seq = (Fastq*) p;
        }
        else if (filetype == FASTA_FILE)
        {
            seq = new Fasta();
        }
        else
        {
            cerr << "Input file type not recognised as fasta or fastq.  Aborting" << endl;
            exit(1);
        }

        if ( !(seq->fillFromFile(inStream)) )
        {
            break;
        }
        else if (seq->length() >= minimumLength)
        {
            int l = seq->length();
            seqLengths.push_back(l);
            totalLength_ += l;
            vector< pair<unsigned long, unsigned long> > gaps = seq->gaps();
            gapCount_ += gaps.size();
            for (vector< pair<unsigned long, unsigned long> >::iterator p = gaps.begin(); p != gaps.end(); ++p)
            {
                nCount_ += p->second - p->first + 1;
            }
        }

        delete seq;
    }

    inStream.close();

    if (seqLengths.size() == 0)
    {
        return;
    }

    sort(seqLengths.begin(), seqLengths.end());
    longest_ = seqLengths.back();
    shortest_ = seqLengths.front();
    number_ = seqLengths.size();
    mean_ = 1.0 * totalLength_ / number_;

    int k = 0;

    for (int i = seqLengths.size() - 1; 0 <= i; i--)
    {
        cumulativeLength += seqLengths[i];

        while (k < 9 && cumulativeLength >= totalLength_ * (k + 1) / 10.0)
        {
            n50_[k] = seqLengths[i];
            n50n_[k] = seqLengths.size() - i;
            k++;
        }
    }
}


string Stats::toString(short format) const
{
    switch (format)
    {
        case FORMAT_HUMAN:
            return toString_human_readable();
        case FORMAT_TAB:
            return toString_tab_delimited(true);
        case FORMAT_TAB_NO_HEAD:
            return toString_tab_delimited(false);
        case FORMAT_GREPPY:
            return toString_greppy();
        default:
            cerr << "Wrong format supplied to Stats::toString(). Cannot continue" << endl;
            exit(1);
    }
}


string Stats::toString_greppy() const
{
    stringstream ss;
    ss.precision(2);

    ss << filename_ << "\t" << "total_length\t" << totalLength_ << endl
       << filename_ << "\t" << "number\t" << number_ << endl
       << filename_ << "\t" << "mean_length\t" << fixed << mean_ << endl
       << filename_ << "\t" << "longest\t" << longest_ << endl
       << filename_ << "\t" << "shortest\t" << shortest_ << endl
       << filename_ << "\t" << "N_count\t" << nCount_ << endl
       << filename_ << "\t" << "Gaps\t" << gapCount_ << endl;

    for (int j = 0; j < 9; j++)
    {
        ss << filename_ << "\t" << "n" << j + 1 << "0\t" << n50_[j] << endl
           << filename_ << "\t" << "n" << j + 1 << "0n\t" << n50n_[j] << endl;
    }

    return ss.str();
}


string Stats::toString_tab_delimited(bool header) const
{
    stringstream ss;
    ss.precision(2);

    if (header)
    {
        ss << "filename"
           << '\t' << "total_length"
           << '\t' << "number"
           << '\t' << "mean_length"
           << '\t' << "longest"
           << '\t' << "shortest"
           << '\t' << "N_count"
           << '\t' << "Gaps"
           << '\t' << "N50"
           << '\t' << "N50n"
           << '\t' << "N70"
           << '\t' << "N70n"
           << '\t' << "N90"
           << '\t' << "N90n" << endl;
    }

    ss << filename_ << '\t'
       << totalLength_ << '\t'
       << number_ << '\t'
       << fixed << mean_ << '\t'
       << longest_ << '\t'
       << shortest_ << '\t'
       << nCount_ << '\t'
       << gapCount_;

    for (int j = 4; j < 9; j+=2)
    {
        ss << '\t' << n50_[j] << '\t' << n50n_[j];
    }

    ss << endl;
    return ss.str();
}


string Stats::toString_human_readable() const
{
    stringstream ss;
    ss.precision(2);

    ss << "stats for " << filename_ << endl
       << "sum = " << totalLength_
       << ", n = " << number_
       << ", ave = " << fixed << mean_
       << ", largest = " << longest_ << endl
       << "N50 = " << n50_[4] << ", n = " << n50n_[4] << endl
       << "N60 = " << n50_[5] << ", n = " << n50n_[5] << endl
       << "N70 = " << n50_[6] << ", n = " << n50n_[6] << endl
       << "N80 = " << n50_[7] << ", n = " << n50n_[7] << endl
       << "N90 = " << n50_[8] << ", n = " << n50n_[8] << endl
       << "N100 = " << shortest_ << ", n = " << number_ << endl
       << "N_count = " << nCount_ << endl
       << "Gaps = " << gapCount_ << endl;

    return ss.str();
}
