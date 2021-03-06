/**
 * @author J. Santos <jamillo@gmail.com>
 * @date March 22, 2016
 **/

#include <icarus/dispatcher.h>

void icarus::dispatcher::process(icarus::application &app, icarus::http::client_context *client)
{
	this->find_route(app, client);
	this->destroy_client(client);
}

void icarus::dispatcher::destroy_client(http::client_context *client)
{
	delete client;
}


