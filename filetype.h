#ifndef FILETYPE
#define FILETYPE

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "bxzstr.hpp"

using namespace std;

const short FASTA_FILE = 1;
const short FASTQ_FILE = 2;
const short UNKNOWN = 3;

short fastaOrFastq(bxz::ifstream &inputstream);
short fastaOrFastq(string filename);

#endif // FILETYPE
