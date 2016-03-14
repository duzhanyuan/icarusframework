/*
 * @author Jamillo Santos <jamillo@gmail.com>
 * @date September 09, 2015
 */

#ifndef ICARUSFRAMEWORK_ROUTESWRITER_H
#define ICARUSFRAMEWORK_ROUTESWRITER_H

#include <ostream>
#include <sstream>

#include "data.h"

namespace icarus
{
namespace routes
{
class routes_writer
{
protected:
	unsigned int _routeId;

	unsigned int _routes_written;

	virtual void writeBeginDoc(std::ostream &stream, document &document);

	virtual void writeBeginDoc(std::ostream &stream, icarus::routes::group& group);

	/**
	 * Write the initialization of the route.
	 */
	virtual void writeBeginDoc(std::ostream &stream, route& route);

	/**
	 * Writes the end of the routing file.
	 */
	virtual void writeEndDoc(std::ostream &stream, document &document);

	/**
	 * Writes the evaluation of the URI for a route, if ok it will dispatch the method that needs to be called.
	 *
	 * @param route Route that will be evaluated.
	 */
	virtual void write(std::ostream &stream, icarus::routes::route &route);

	/**
	 * Places all the routes of a group.
	 *
	 * @see write(std::ostream, Route&);
	 */
	virtual void write(std::ostream &stream, const group &group);

	/**
	 * Evaluates what `piece` is (class type) and call the proper `write` method for it.
	 */
	virtual void write(std::ostream &stream, piece &piece);

	/**
	 * Write the reverse route for the document.
	 *
	 * @param @std::ostream Document
	 * @param icarus::routes::Document& Document that will be written
	 */
	virtual void writeReverseRoutes(std::ostream &stream, icarus::routes::document &document);

	virtual void writeReverseRoutes(std::ostream &stream, icarus::routes::route &route);
public:
	routes_writer();

	virtual void write(std::ostream &stream, icarus::routes::document &document);
};
}
}

#endif //ICARUSFRAMEWORK_ROUTESWRITER_H