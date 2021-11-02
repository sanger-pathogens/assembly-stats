#include "fasta.h"

Fasta::Fasta() : id_(""), seq_("") {}


Fasta::Fasta(string id, string seq) : id_(id), seq_(seq) {}


void Fasta::toString(ostream& outStream, unsigned int lineWidth) const
{
    outStream << ">" << id_ << '\n';
    if (lineWidth)
    {
        for (unsigned long i = 0; i < length(); i += lineWidth)
        {
            outStream << seq_.substr(i, lineWidth) << '\n';
        }
    }
    else
    {
        outStream << seq_ << '\n';
    }
}


string Fasta::name() const
{
    return id_;
}

string Fasta::qual() const
{
    return "";
}

void Fasta::seq(string s)
{
    seq_ = s;
}

void Fasta::setQual(string s)
{
}


string Fasta::seq() const
{
    return seq_;
}


void Fasta::name(string s)
{
    id_ = s;
}


unsigned long Fasta::length() const
{
    return seq_.length();
}



unsigned long Fasta::nCount() const
{
    return count(seq_.begin(), seq_.end(), 'n') + count(seq_.begin(), seq_.end(), 'N');
}



vector< pair<unsigned long, unsigned long> > Fasta::gaps() const
{
    vector< pair<unsigned long, unsigned long> > gaps;
    string seq = seq_;
    transform(seq.begin(), seq.end(), seq.begin(), ::toupper);

    unsigned long pos = seq.find('N');

    while (pos != string::npos)
    {
        unsigned long start = pos;
        pos = seq.find_first_not_of('N', pos);
        if (pos == string::npos)
        {
            gaps.push_back(make_pair(start, seq_.length() - 1));
        }
        else
        {
            gaps.push_back(make_pair(start, pos - 1));
            pos = seq.find('N', pos);
        }
    }
    return gaps;
}


bool Fasta::fillFromFile(bxz::ifstream& inStream)
{
    string line;
    seq_ = "";
    id_ = "";
    getline(inStream, line);

    if (inStream.eof())
    {
        return false;
    }
    // Expecting a header line.  If not, abort
    else if (line[0] == '>')
    {
        id_ = line.substr(1);
    }
    else
    {
        cerr << "Error reading fasta file!" << endl
             << "Expected line starting with '>', but got this:" << endl
             << line << endl;
         exit(1);
    }

    // Next lines should be sequence, up to next header, or end of file
    while ((inStream.peek() != '>') && (!inStream.eof()))
    {
        getline(inStream, line);
        seq_ += line;
    }

    return true;
}


