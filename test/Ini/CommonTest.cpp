#include <gtest/gtest.h>

#include <fstream>

#include "Ini.hpp"

using namespace ES;

TEST(Ini, a1) {
    std::ifstream is("test_stream.ini");
    Ini i;
    i.parseFromStream(is);

    ASSERT_EQ(i["SessionKey.UsePotionMP"]["Key1.Offset"], "72");
}
