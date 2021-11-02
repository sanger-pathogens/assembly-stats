#include <list>
#include <iostream>
#include <sstream>
#include "fastq.h"
#include "gtest/gtest.h"
#include "bxzstr.hpp"

TEST(Fastq, DefaultConstructor)
{
    Fastq fq;
    EXPECT_EQ(0, fq.name().compare(""));
    EXPECT_EQ(0, fq.seq().compare(""));
    EXPECT_EQ(0, fq.qual().compare(""));
}


TEST(Fastq, ConstructorWithValues)
{
    Fastq fq("name", "ACGT", "IIGH");
    EXPECT_EQ(0, fq.name().compare("name"));
    EXPECT_EQ(0, fq.seq().compare("ACGT"));
    EXPECT_EQ(0, fq.qual().compare("IIGH"));
}


TEST(Fastq, setValues)
{
    Fastq fq;
    fq.name("name");
    fq.seq("ACGT");
    fq.qual("IIII");
    EXPECT_EQ(0, fq.name().compare("name"));
    EXPECT_EQ(0, fq.seq().compare("ACGT"));
    EXPECT_EQ(0, fq.qual().compare("IIII"));
}


TEST(Fastq, ReadFromFile)
{
    Fastq fq;
    unsigned int counter = 0;
    bxz::ifstream inStream("test_files/fastq_unittest.fastq");

    if (! inStream.is_open())
    {
        cerr << "Error opening test file test_files/fastq_unittest.fastq" << endl;
        exit(1);
    }

    while (fq.fillFromFile(inStream))
    {
        counter++;
	ostringstream stream;
	stream << counter;
	string expectedName = stream.str();
	EXPECT_EQ(0, fq.name().compare(expectedName));
        EXPECT_EQ(0, fq.seq().compare("ACGT"));
    }
}

TEST(Fastq, ReadFromGzFile)
{
    Fastq fq;
    unsigned int counter = 0;
    bxz::ifstream inStream("test_files/fastq_unittest.fastq.gz");

    if (! inStream.is_open())
    {
        cerr << "Error opening test file test_files/fastq_unittest.fastq.gz" << endl;
        exit(1);
    }

    while (fq.fillFromFile(inStream))
    {
        counter++;
	ostringstream stream;
	stream << counter;
	string expectedName = stream.str();
        EXPECT_EQ(0, fq.name().compare(expectedName));
        EXPECT_EQ(0, fq.seq().compare("ACGT"));
    }
}
