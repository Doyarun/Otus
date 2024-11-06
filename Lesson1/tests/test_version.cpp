#define BOOST_TEST_MODULE test_version

#include "../src/lib.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
    BOOST_CHECK(version() > 1);
}

BOOST_AUTO_TEST_SUITE_END()
