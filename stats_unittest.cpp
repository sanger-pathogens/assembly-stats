#include "stats.h"
#include "gtest/gtest.h"

TEST(Stats, HumanReadable)
{
    Stats s("test_files/stats_unittest.fasta");
    string expected = "stats for test_files/stats_unittest.fasta\n\
sum = 21, n = 5, ave = 4.20, largest = 8\n\
N50 = 6, n = 2\n\
N60 = 6, n = 2\n\
N70 = 4, n = 3\n\
N80 = 4, n = 3\n\
N90 = 2, n = 4\n\
N100 = 1, n = 5\n\
N_count = 4\n\
Gaps = 2\n\
";

    string got = s.toString(FORMAT_HUMAN);
    EXPECT_EQ(0, expected.compare(got));

    // Test gzipped input
    Stats s2("test_files/stats_unittest.fasta.gz");
    got = s.toString(FORMAT_HUMAN);
    EXPECT_EQ(0, expected.compare(got));
}


TEST(Stats, Greppy)
{
    Stats s("test_files/stats_unittest.fasta");
    string expected = "test_files/stats_unittest.fasta\ttotal_length\t21\n\
test_files/stats_unittest.fasta\tnumber\t5\n\
test_files/stats_unittest.fasta\tmean_length\t4.20\n\
test_files/stats_unittest.fasta\tlongest\t8\n\
test_files/stats_unittest.fasta\tshortest\t1\n\
test_files/stats_unittest.fasta\tN_count\t4\n\
test_files/stats_unittest.fasta\tGaps\t2\n\
test_files/stats_unittest.fasta\tn10\t8\n\
test_files/stats_unittest.fasta\tn10n\t1\n\
test_files/stats_unittest.fasta\tn20\t8\n\
test_files/stats_unittest.fasta\tn20n\t1\n\
test_files/stats_unittest.fasta\tn30\t8\n\
test_files/stats_unittest.fasta\tn30n\t1\n\
test_files/stats_unittest.fasta\tn40\t6\n\
test_files/stats_unittest.fasta\tn40n\t2\n\
test_files/stats_unittest.fasta\tn50\t6\n\
test_files/stats_unittest.fasta\tn50n\t2\n\
test_files/stats_unittest.fasta\tn60\t6\n\
test_files/stats_unittest.fasta\tn60n\t2\n\
test_files/stats_unittest.fasta\tn70\t4\n\
test_files/stats_unittest.fasta\tn70n\t3\n\
test_files/stats_unittest.fasta\tn80\t4\n\
test_files/stats_unittest.fasta\tn80n\t3\n\
test_files/stats_unittest.fasta\tn90\t2\n\
test_files/stats_unittest.fasta\tn90n\t4\n\
";

    string got = s.toString(FORMAT_GREPPY);
    EXPECT_EQ(0, expected.compare(got));

    // Test gzipped input
    Stats s2("test_files/stats_unittest.fasta.gz");
    got = s.toString(FORMAT_GREPPY);
    EXPECT_EQ(0, expected.compare(got));
}


TEST(Stats, TabDelimited)
{
    Stats s("test_files/stats_unittest.fasta");
    string expected = "filename\ttotal_length\tnumber\tmean_length\tlongest\tshortest\tN_count\tGaps\tN50\tN50n\tN70\tN70n\tN90\tN90n\n\
test_files/stats_unittest.fasta\t21\t5\t4.20\t8\t1\t4\t2\t6\t2\t4\t3\t2\t4\n\
";

    string got = s.toString(FORMAT_TAB);
    EXPECT_EQ(0, expected.compare(got));

    // Test gzipped input
    Stats s2("test_files/stats_unittest.fasta.gz");
    got = s.toString(FORMAT_TAB);
    EXPECT_EQ(0, expected.compare(got));
}


TEST(Stats, TabDelimitedNoHeader)
{
    Stats s("test_files/stats_unittest.fasta");
    string expected = "test_files/stats_unittest.fasta\t21\t5\t4.20\t8\t1\t4\t2\t6\t2\t4\t3\t2\t4\n";
    string got = s.toString(FORMAT_TAB_NO_HEAD);
    EXPECT_EQ(0, expected.compare(got));

    // Test gzipped input
    Stats s2("test_files/stats_unittest.fasta.gz");
    got = s.toString(FORMAT_TAB_NO_HEAD);
    EXPECT_EQ(0, expected.compare(got));
}
