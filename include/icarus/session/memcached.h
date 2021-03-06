/**
 * @author J. Santos <jamillo@gmail.com>
 * @date April 04, 2016
 */

#ifndef ICARUS_SESSION_MEMCACHED_H
#define ICARUS_SESSION_MEMCACHED_H

#include <icarus/session/session.h>
#include <icarus/memcached.h>

namespace icarus
{
namespace session
{
class memcached_session;

class memcached_manager
	: public icarus::session::manager
{
	friend class memcached_session;
private:
	icarus::memcached_server _server;
protected:
	virtual icarus::session::session_impl* create(const icarus::session::session_id_t &id) override;

public:
	memcached_manager(icarus::config::session_memcached &config);

	virtual void start() override;

	virtual void stop() override;
};

class memcached_session
	: public icarus::session::session_impl
{
private:
	icarus::session::memcached_manager &_manager;

	std::unique_ptr<icarus::memcached_session> _session;
	std::string _group_key;
public:
	memcached_session(icarus::session::memcached_session &&msession);
	memcached_session(icarus::session::memcached_manager &manager, const icarus::session::session_id_t &id);

	virtual std::string get_value(const std::string &key) override;

	virtual void set_value(const std::string &key, const std::string &value) override;
};
}
}


#endif //ICARUS_SESSION_MEMCACHED_H
