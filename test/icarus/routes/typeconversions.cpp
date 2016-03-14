/**
 * @author J. Santos <jamillo@gmail.com>
 * @date March 12, 2016
 **/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE typeconversions

#include <boost/test/unit_test.hpp>

#include <icarus/routes/typeconversion.h>
#include <icarus/routes/typeconversion-commons.h>

BOOST_AUTO_TEST_CASE(conversion_int)
{
	{
		std::string t("123");
		unsigned int tmp = 0;
		icarus::type_conversion<unsigned int>::from(t, tmp);
		BOOST_CHECK_EQUAL(123, tmp);
	}

	{
		std::string t("-123");
		int tmp = 0;
		icarus::type_conversion<int>::from(t, tmp);
		BOOST_CHECK_EQUAL(-123, tmp);
	}
}

BOOST_AUTO_TEST_CASE(conversion_short)
{
	{
		std::string t("123");
		unsigned short tmp = 0;
		icarus::type_conversion<unsigned short>::from(t, tmp);
		BOOST_CHECK_EQUAL(123, tmp);
	}

	{
		std::string t("-123");
		short tmp = 0;
		icarus::type_conversion<short>::from(t, tmp);
		BOOST_CHECK_EQUAL(-123, tmp);
	}
}
