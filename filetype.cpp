#include "filetype.h"

short fastaOrFastq(bxz::ifstream &inStream)
{
    char firstChar = inStream.peek();
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

short fastaOrFastq(string filename)
{
    bxz::ifstream ifs;
    ifs.open(filename);

    if (! ifs.is_open())
    {
        cerr << "Error opening file " << filename << endl;
        exit(1);
    }

    short result = fastaOrFastq(ifs);
    ifs.close();
    return result;
}
