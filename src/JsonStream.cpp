#include "JsonStream.h"
#include "version.h"
#include "Configuration.h"
#include "Namespace.h"

namespace FLYINGCOLLECTION_NAMESPACE
{
	bool JsonStream::flush()
	{
		if (o_currentjsonstream->tellp() > 1)
			*o_currentjsonstream << '}';
		jsoncollection.emplace_back(o_currentjsonstream->str());
		o_currentjsonstream = new std::ostringstream();
		return true;
	}


	uint16_t JsonStream::size()
	{
		return jsoncollection.size();
	}

	std::vector<std::string> JsonStream::getJsons()
	{
		this->flush();
		return this->jsoncollection;
	}

} // namespace FLYINGCOLLECTION_NAMESPACE
