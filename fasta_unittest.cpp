#include <iostream>
#include "fasta.h"
#include "gtest/gtest.h"
#include "bxzstr.hpp"

TEST(Fasta, DefaultConstructor)
{
    Fasta fa;
    EXPECT_EQ(0, fa.name().compare(""));
    EXPECT_EQ(0, fa.seq().compare(""));
}


TEST(Fasta, ConstructorWithValues)
{
    Fasta fa("name", "ACGT");
    EXPECT_EQ(0, fa.name().compare("name"));
    EXPECT_EQ(0, fa.seq().compare("ACGT"));
}


TEST(Fasta, setValues)
{
    Fasta fa;
    fa.name("name");
    fa.seq("ACGT");
    EXPECT_EQ(0, fa.name().compare("name"));
    EXPECT_EQ(0, fa.seq().compare("ACGT"));
}


TEST(Fasta, LengthOfSequence)
{
    Fasta fa("name", "");
    EXPECT_EQ((unsigned)0, fa.length());
    fa = Fasta("name", "A");
    EXPECT_EQ((unsigned)1, fa.length());
    fa = Fasta("name", "AC");
    EXPECT_EQ((unsigned)2, fa.length());
}


TEST(Fasta, N_count)
{
    Fasta fa("name", "");
    EXPECT_EQ((unsigned)0, fa.nCount());
    fa = Fasta("name", "n");
    EXPECT_EQ((unsigned)1, fa.nCount());
    fa = Fasta("name", "N");
    EXPECT_EQ((unsigned)1, fa.nCount());
    fa = Fasta("name", "NnACGTNNNTnnT");
    EXPECT_EQ((unsigned)7, fa.nCount());
}


TEST(Fasta, Gaps)
{
    vector< pair<unsigned long, unsigned long> > gaps, expected;
    Fasta fa("name", "");
    gaps = fa.gaps();
    EXPECT_EQ((unsigned)0, gaps.size());

    fa = Fasta("name", "ACGT");
    gaps = fa.gaps();
    EXPECT_EQ((unsigned)0, gaps.size());

    fa = Fasta("name", "nACGT");
    gaps = fa.gaps();
    expected.push_back(make_pair(0, 0));
    EXPECT_TRUE(expected == gaps);

    fa = Fasta("name", "nACNnNGTN");
    gaps = fa.gaps();
    expected.clear();
    expected.push_back(make_pair(0, 0));
    expected.push_back(make_pair(3, 5));
    expected.push_back(make_pair(8, 8));
    EXPECT_TRUE(expected == gaps);
}


TEST(Fasta, ReadFromFile)
{
    Fasta fa;
    int counter = 0;
    bxz::ifstream inStream("test_files/fasta_unittest.fasta");

    if (! inStream.is_open())
    {
        cerr << "Error opening test file test_files/fasta_unittest.fasta" << endl;
        exit(1);
    }

    while (fa.fillFromFile(inStream))
    {
        counter++;
	ostringstream stream;
	stream << counter;
	string expectedName = stream.str();
        EXPECT_EQ(0, fa.name().compare(expectedName));
        EXPECT_EQ(0, fa.seq().compare("ACGT"));
    }

    EXPECT_EQ(3, counter);
}

TEST(Fasta, ReadFromGzFile)
{
    Fasta fa;
    int counter = 0;
    bxz::ifstream inStream("test_files/fasta_unittest.fasta.gz");

    if (! inStream.is_open())
    {
        cerr << "Error opening test file test_files/fasta_unittest.fasta.gz" << endl;
        exit(1);
    }

    while (fa.fillFromFile(inStream))
    {
        counter++;
	ostringstream stream;
	stream << counter;
	string expectedName = stream.str();
        EXPECT_EQ(0, fa.name().compare(expectedName));
        EXPECT_EQ(0, fa.seq().compare("ACGT"));
    }

    EXPECT_EQ(3, counter);
}
