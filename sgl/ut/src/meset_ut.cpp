#include "sgl.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace sgl;

class MEMTEST_F: public ::testing::Test
{
protected:
    static const unsigned bufferSize = 100;

    uint16_t bufferTEST0[bufferSize]; // empty
    uint16_t bufferTEST1[bufferSize];
    uint16_t bufferTEST2[bufferSize];
    
    uint16_t minValue = 0x0000;
    uint16_t max_value = 0xFFFF;
    uint16_t mid_value = 0xABCD;

    unsigned rangeFrom1 = 10;
    unsigned rangeTo1 = 20;
    unsigned rangeFrom2 = 25;
    unsigned rangeTo2 = 60;

protected:
    void SetUp() override
    {
        memset(bufferTEST0, minValue, bufferSize * sizeof(uint16_t));
        memset(bufferTEST1, minValue, bufferSize * sizeof(uint16_t));
        memset(bufferTEST2, minValue, bufferSize * sizeof(uint16_t));

        bufferTEST1[0] = mid_value;
        for(int i = rangeFrom1; i < rangeTo1; ++i)
        {
            bufferTEST2[i] = mid_value;
        }
        for(int i = rangeFrom2; i < rangeTo2; ++i)
        {
            bufferTEST2[i] = max_value;
        }
    }
};

TEST_F(MEMTEST_F, memset16_fill)
{
    memset16(bufferTEST0, minValue, bufferSize);
    uint16_t* beg = bufferTEST0;
    uint16_t* end = bufferTEST0 + bufferSize;
    bool res0 = true;
    for(;beg < end; ++ beg)
    {
        if(*beg != minValue)
        {
            res0 &= false;
        }
    }
    EXPECT_EQ(res0, true) << "MEMSET16 EMPY TEST BUFFER";

    memset16(bufferTEST0, mid_value, bufferSize);
    beg = bufferTEST0;
    end = bufferTEST0 + bufferSize;
    res0 = true;
    for(;beg < end; ++ beg)
    {
        if(*beg != mid_value)
        {
        res0 &= false;
        }
    }
    EXPECT_EQ(res0, true) << "MEMSET16 MIDVALUE TEST FILL";

    memset16(bufferTEST0, max_value, bufferSize);
    beg = bufferTEST0;
    end = bufferTEST0 + bufferSize;
    res0 = true;
    for(;beg < end; ++ beg)
    {
        if(*beg != max_value)
        {
        res0 &= false;
        }
    }
    EXPECT_EQ(res0, true) << "MEMSET16 MAXVALUE TEST FILL";
}

TEST_F(MEMTEST_F, memset16_fast_fill)
{
    memset16_fast(bufferTEST0, minValue, bufferSize);
    uint16_t* beg = bufferTEST0;
    uint16_t* end = bufferTEST0 + bufferSize;
    bool res0 = true;
    for(;beg < end; ++ beg)
    {
        if(*beg != minValue)
        {
            res0 &= false;
        }
    }
    EXPECT_EQ(res0, true) << "MEMSET16_FAST EMPY TEST BUFFER";

    memset16_fast(bufferTEST0, mid_value, bufferSize);
    beg = bufferTEST0;
    end = bufferTEST0 + bufferSize;
    res0 = true;
    for(;beg < end; ++ beg)
    {
        if(*beg != mid_value)
        {
        res0 &= false;
        }
    }
    EXPECT_EQ(res0, true) << "MEMSET16_FAST MIDVALUE TEST FILL";

    memset16_fast(bufferTEST0, max_value, bufferSize);
    beg = bufferTEST0;
    end = bufferTEST0 + bufferSize;
    res0 = true;
    for(;beg < end; ++ beg)
    {
        if(*beg != max_value)
        {
        res0 &= false;
        }
    }
    EXPECT_EQ(res0, true) << "MEMSET16_FAST MAXVALUE TEST FILL";
}

TEST_F(MEMTEST_F, memset16_border)
{
    memset16(bufferTEST0, mid_value, 1);
    memset16(bufferTEST0 + bufferSize - 1, mid_value, 1);

    memset16(bufferTEST0, mid_value, 1);
    memset16(bufferTEST0 + bufferSize - 1, mid_value, 1);
    EXPECT_EQ(bufferTEST0[0], mid_value);
    EXPECT_EQ(bufferTEST0[bufferSize - 1], mid_value);



    memset16(bufferTEST0, max_value, 1);
    memset16(bufferTEST0 + bufferSize - 1, max_value, 1);

    memset16(bufferTEST0, max_value, 1);
    memset16(bufferTEST0 + bufferSize - 1, max_value, 1);
    EXPECT_EQ(bufferTEST0[0], max_value);
    EXPECT_EQ(bufferTEST0[bufferSize - 1], max_value);
}

TEST_F(MEMTEST_F, memset16_fast_border)
{
    memset16_fast(bufferTEST0, mid_value, 1);
    memset16_fast(bufferTEST0 + bufferSize - 1, mid_value, 1);

    memset16_fast(bufferTEST0, mid_value, 1);
    memset16_fast(bufferTEST0 + bufferSize - 1, mid_value, 1);
    EXPECT_EQ(bufferTEST0[0], mid_value);
    EXPECT_EQ(bufferTEST0[bufferSize - 1], mid_value);



    memset16_fast(bufferTEST0, max_value, 1);
    memset16_fast(bufferTEST0 + bufferSize - 1, max_value, 1);

    memset16_fast(bufferTEST0, max_value, 1);
    memset16_fast(bufferTEST0 + bufferSize - 1, max_value, 1);
    EXPECT_EQ(bufferTEST0[0], max_value);
    EXPECT_EQ(bufferTEST0[bufferSize - 1], max_value);
}

TEST_F(MEMTEST_F, memset16__fill_part)
{
    memset16((bufferTEST0 + rangeFrom1), mid_value, rangeTo1 - rangeFrom1);
    memset16((bufferTEST0 + rangeFrom2), max_value, rangeTo2 - rangeFrom2);
    bool res = true;
    for(int i = 0; i < bufferSize; ++i)
    {
        ASSERT_EQ(bufferTEST0[i], bufferTEST2[i]) << "ERROR AT INDEX: " << i; 
    }
}

TEST_F(MEMTEST_F, memset16_fast_fill_part)
{
    memset16_fast((bufferTEST0 + rangeFrom1), mid_value, rangeTo1 - rangeFrom1);
    memset16_fast((bufferTEST0 + rangeFrom2), max_value, rangeTo2 - rangeFrom2);
    bool res = true;
    for(int i = 0; i < bufferSize; ++i)
    {
        ASSERT_EQ(bufferTEST0[i], bufferTEST2[i]) << "ERROR AT INDEX: " << i; 
    };
}