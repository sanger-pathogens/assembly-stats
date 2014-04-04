#include "fastq.h"

Fastq::Fastq() : Fasta(), qual_("") {}


Fastq::Fastq(string id, string seq, string qual)
{
    if (seq.length() != qual.length())
    {
        cerr << "Error constructing Fastq object: mismatch in sequence and qual length." << endl
             << "id: " << id << endl
             << "Seq: " << seq << endl
             << "Qual: " << qual << endl
             << "Aborting" << endl;
        exit(1);
    }

    id_ = id;
    seq_ = seq;
    qual_ = qual;
}


string Fastq::qual() const
{
    return qual_;
}


void Fastq::qual(string s)
{
    qual_ = s;
}


bool Fastq::fillFromFile(istream& inStream)
{
    string line;
    getline(inStream, line);

    // check if we're at the end of the file
    if (inStream.eof())
    {
        id_ = "";
        seq_ = "";
        qual_ = "";
        return false;
    }
    // Expecting a header line.  If not, abort
    else if (line[0] == '@')
    {
        id_ = line.substr(1);
    }
    else
    {
        cerr << "Error reading fastq file!" << endl
             << "Expected line starting with '@', but got this:" << endl
             << line << endl;
        exit(1);
    }

    // Next line is sequence string
    getline(inStream, line);
    seq_ = line;

    // Next line is +... line
    getline(inStream, line);

    if (line[0] != '+')
    {
        cerr << "Error reading fastq file!" << endl
             << "Expected line starting with '+', but got this:" << endl
             << line << endl;
        exit(1);
    }

    // Next line is quality string
    getline(inStream, line);

    if (line.length() != seq_.length())
    {
        cerr << "Mismatch in sequence and quality length." << endl
             << "id: " << id_ << endl
             << "seq: " << seq_ << endl
             << "qual: " << line << endl
             << "Aborting" << endl;
        exit(1);
    }
    qual_ = line;

    return true;
}


void Fastq::toString(ostream& outStream) const
{
    outStream << "@" << id_ << endl << seq_ << '\n'
              << "+" << endl << qual_ << '\n';
}

