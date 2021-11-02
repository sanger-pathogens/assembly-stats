#ifndef FASTQ_H
#define FASTQ_H

#include <iostream>
#include <string>
#include <fstream>

#include "bxzstr.hpp"

#include "fasta.h"

using namespace std;

class Fastq : public Fasta
{


public:
    Fastq();
    Fastq(string id, string seq, string qual);
    ~Fastq(){};

    virtual string qual() const;
    virtual void qual(string s);

    virtual void toString(ostream & outStream) const;

    // reads next sequence from file, filling contents appropriately
    // Returns true if worked ok, false if at end of file
    bool fillFromFile(bxz::ifstream& inStream);

private:
    string qual_;
};


#endif // FASTQ_H
