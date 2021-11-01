#ifndef FASTA_H
#define FASTA_H

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>

#include "bxzstr.hpp"

using namespace std;

class Fasta
{
public:
    Fasta();
    Fasta(string id, string seq);
    virtual ~Fasta(){}

    string name() const;
    string seq() const;
    virtual string qual() const; // returns "".  Here for compatibility with Fastq

    void name(string s);
    void seq(string s);
    virtual void setQual(string s); // does nothing, here for compatibility with Fastq

    // returns number of bases in sequence
    unsigned long length() const;

    // returns number of Ns (case insensitive)
    unsigned long nCount() const;

    // Return vector with (start, end) positions of each gap in the sequence.
    // Coords zero-based
    vector< pair<unsigned long, unsigned long> > gaps() const;

    // prints the sequence. If lineWidth=0 then no linbreaks in output
    virtual void toString(ostream& outStream, unsigned int lineWidth=60) const;

    // reads next sequence from file, filling contents appropriately
    // Returns true if worked ok, false if at end of file
    virtual bool fillFromFile(bxz::ifstream& inStream);

protected:
    string id_;
    string seq_;
};

#endif // FASTA_H
