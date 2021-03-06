/**
 * @author J. Santos <jamillo@gmail.com>
 * @date November 06, 2015
 **/

#ifndef ICARUSFRAMEWORK_EXCEPTIONS_H
#define ICARUSFRAMEWORK_EXCEPTIONS_H

#include <string>
#include <boost/locale.hpp>

namespace icarus
{
namespace bl = boost::locale;

class exception
	: public std::exception
{
private:
	std::string _message;
	std::exception *_cause;
public:
	exception(const std::string &message, std::exception *cause);

	exception(const std::string &message);

	virtual ~exception();

	virtual const char *what() const _GLIBCXX_USE_NOEXCEPT;

	std::string message();

	std::exception *cause();
};

class file_not_found
	: icarus::exception
{
public:
	file_not_found(std::string fname, std::exception *cause);

	file_not_found(std::string fname);
};

class not_a_file
	: icarus::exception
{
public:
	not_a_file(std::string fname, std::exception *cause);

	not_a_file(std::string fname);
};

class open_file
	: public icarus::exception
{

public:
	open_file(const std::string &message, std::exception *cause);

	open_file(const std::string &message);
};

class premature_eof
	: public icarus::exception
{
public:
	premature_eof();

	premature_eof(unsigned int line);
};

class invalid_pointer
	: public icarus::exception
{
public:
	invalid_pointer(const std::string &message, std::exception *cause);

	invalid_pointer(const std::string &message);
};

class json_expected_exception
	: public icarus::exception
{
public:
	json_expected_exception();
};
}

#endif //ICARUSFRAMEWORK_EXCEPTIONS_H
