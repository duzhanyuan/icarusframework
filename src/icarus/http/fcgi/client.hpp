/**
 * @author J. Santos <jamillo@gmail.com>
 * @date February 22, 2016
 **/

#ifndef ICARUSFRAMEWORK_HTTP_FCGI_CLIENT_HPP
#define ICARUSFRAMEWORK_HTTP_FCGI_CLIENT_HPP

#include <icarus/http/client.hpp>
#include <fcgiapp.h>
#include "request.hpp"
#include "response.hpp"

namespace icarus
{
namespace http
{
namespace fcgi
{
class ClientContext
	: public icarus::http::ClientContext
{
private:
	FCGX_Request *_fcgxRequest;

	fcgi::Request *_fcgiRequest;
	fcgi::Response *_fcgiResponse;
public:
	ClientContext(FCGX_Request *fcgiRequest)
		: icarus::http::ClientContext::ClientContext(*(this->_fcgiRequest = new fcgi::Request()), *(this->_fcgiResponse = new fcgi::Response())), _fcgxRequest(fcgiRequest)
	{
	}

	virtual ~ClientContext() override
	{
		LOG_TRACE("~ClientContext");
		delete this->_fcgiRequest;
		delete this->_fcgiResponse;
		FCGX_Finish_r(_fcgxRequest);
	}

	void init()
	{
		this->_fcgiRequest->init(*this->_fcgxRequest);
		LOG_TRACE("Request URI: " << this->_fcgiRequest->uri());
		this->_fcgiResponse->init(*this->_fcgxRequest);
	}
};
}
}
}

#endif //ICARUSFRAMEWORK_HTTP_FCGI_CLIENT_HPP
