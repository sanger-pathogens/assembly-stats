#include "filetype.h"

short fastaOrFastq(string filename)
{
    ifstream ifs;
    ifs.open(filename.c_str());
    char firstChar;

    if (! ifs.is_open())
    {
        cerr << "Error opening file " << filename << endl;
        exit(1);
    }

    firstChar = ifs.get();
    ifs.close();

    switch (firstChar)
    {
        case '>':
            return FASTA_FILE;
        case '@':
            return FASTQ_FILE;
        default:
            return UNKNOWN;
    }
}

