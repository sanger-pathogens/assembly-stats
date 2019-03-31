#include "filetype.h"
#include <gtest/gtest.h>


TEST(filetype, FastaType)
{
    EXPECT_EQ(FASTA_FILE, fastaOrFastq("test_files/filetype_unittest.fasta"));
}

TEST(filetype, FastqType)
{
    EXPECT_EQ(FASTQ_FILE, fastaOrFastq("test_files/filetype_unittest.fastq"));
}

TEST(filetype, UnknownType)
{
    EXPECT_EQ(UNKNOWN, fastaOrFastq("test_files/filetype_unittest.unknown"));
}
