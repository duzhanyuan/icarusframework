/*
 * @author Jamillo Santos <jamillo@gmail.com>
 * @date August 18, 2015
 */

#ifndef ICARUSFRAMEWORK_ROUTES_DATA_HPP
#define ICARUSFRAMEWORK_ROUTES_DATA_HPP

#define INPUT_STREAM_BUFFER_SIZE 4096

#include <string>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include <icarus/http/headers.h>

namespace icarus
{
namespace routes
{

/**
 * Regex tokens in a route rule.
 */
class regex_token
{
private:
	std::string _name;
	std::string _regex;
	int _index;
public:
	regex_token(const std::string &name, const std::string &regex);

	regex_token(const std::string &regex);

	const std::string &name() const;

	const std::string &regex() const;

	regex_token &regex(const std::string &regex);

	const int index() const;

	regex_token &index(int index);
};

class composed_uri
{
private:
	std::vector<regex_token> _tokens;

	std::string _prefix;
	std::string _sufix;

	std::unique_ptr<boost::regex> regex;
protected:
	virtual void compile();

public:
	composed_uri();

	composed_uri(const composed_uri &uri);

	composed_uri(const std::string &prefix, const std::string &sufix);

	composed_uri &add(std::string name, std::string regex);

	composed_uri &add(std::string expression);

	std::vector<regex_token> &tokens();

	const std::string prefix() const;

	composed_uri &prefix(const std::string &prefix);

	const std::string sufix() const;

	composed_uri &sufix(const std::string &sufix);

	bool match(std::string requestUri, icarus::http::values<http::values_value> &params);

	std::string str();

	unsigned int size();

	composed_uri &operator=(const composed_uri &uri);
};

/**
 * Class that represents the parameters of a method called in a route.
 */
enum class method_param_type
{
	NORMAL, REFERENCE, POINTER
};

class method_param
{
private:
	std::string _type;
	method_param_type _attribute;
	std::string _name;

public:

	method_param();

	method_param(const std::string type, const method_param_type attribute, const std::string name);

	const std::string &type() const;

	method_param &type(const std::string &type);

	const method_param_type &attribute() const;

	method_param &attribute(const method_param_type &attr);

	const std::string &name() const;

	method_param &name(const std::string &name);

	method_param &operator=(const method_param &param);
};

/**
 * Class that represents the calling method in a route.
 */
class call_method
{
private:
	bool _static;

	std::vector<std::string> _path;
	std::string _name;

	std::vector<method_param> _params;
public:
	call_method();

	call_method(const call_method &callMethod);

	const bool isStatic() const;

	call_method &setStatic(bool _static);

	const std::vector<std::string> &path() const;

	call_method &path(const std::string &path);

	const std::string &name() const;

	call_method &name(const std::string &name);

	std::vector<method_param> &params();

	call_method &add(std::string type, method_param_type attribute, std::string name);

	std::string str();

	call_method &operator=(const call_method &method);
};

/**
 * Abstraction of each part of a routes.
 */
class piece
{
private:
	size_t _line;
public:
	piece(size_t line);

	virtual ~piece();

	size_t line() const;

	void line(size_t line);

	virtual piece *match(std::string method, std::string requestUri, http::values<http::values_value> &values) = 0;
};

class routes;

/**
 * Represents a route.
 */
class route
	: public piece
{
private:
	unsigned int _id;
	std::string _httpMethod;
	composed_uri _composedURI;
	call_method _callMethod;
public:
	route(icarus::routes::route &route);

	route(size_t line);

	route(size_t line, std::initializer_list<std::pair<std::string, std::string>> list);

	const unsigned int id() const;

	route &id(unsigned int id);

	const std::string &httpMethod() const;

	route &httpMethod(const std::string &httpMethod);

	composed_uri &uri();

	call_method &callMethod();

	route &callMethod(call_method &callMethod);

	virtual piece *match(std::string method, std::string uri, http::values<http::values_value> &params) override;
};

class routes
	: public piece
{
private:
	std::vector<std::unique_ptr<piece>> _pieces;
public:
	routes(size_t line);

	const std::vector<std::unique_ptr<piece>> &pieces() const;

	virtual piece *add(piece *piece);

	virtual piece *match(std::string method, std::string requestUri, http::values<http::values_value> &values);
};

class group
	: public routes
{
private:
	composed_uri _composedURI;
public:
	group(size_t line);

	composed_uri &uri();
};

class document
	: public routes
{
private:
	std::string _name;

	std::vector<std::string> _packages;
public:
	document(const std::string &name);

	const std::string &name();

	document &name(std::string name);

	std::vector<std::string> &packages();
};
}
}

#endif // ICARUSFRAMEWORK_ROUTES_DATA_HPP
