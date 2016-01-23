/**
 * @author J. Santos <jamillo@gmail.com>
 * @date November 11, 2015
 **/

#ifndef ICARUSFRAMEWORK_ACTION_HPP
#define ICARUSFRAMEWORK_ACTION_HPP

#include <string>

namespace icarus
{
namespace framework
{
class Action
{
private:
	std::string _method;
	std::string _url;
public:
	Action(const Action &action)
		: _method(action._method), _url(action._url)
	{ }

	Action(std::string url)
		: _method("GET"), _url(url)
	{ }

	Action(std::string method, std::string url)
		: _method(method), _url(url)
	{ }

	const std::string &method() const
	{
		return this->_method;
	}

	Action &method(std::string method)
	{
		this->_method = method;
		return *this;
	}

	const std::string &url() const
	{
		return this->_url;
	}

	Action &url(std::string url)
	{
		this->_url = url;
		return *this;
	}
};
}
}


#endif //ICARUSFRAMEWORK_ACTION_HPP