#include "stats.h"

Stats::Stats()
{
	methods_ = {
	  {"GET", 0},
	  {"PUT", 0},
	  {"POST", 0},
	  {"DELETE", 0},
	  {"UNKNOWN", 0}
	};

	uris_ = {
	  {"/", 0},
	  {"/order", 0},
	  {"/product", 0},
	  {"/basket", 0},
	  {"/help", 0},
	  {"unknown", 0}
	};
}
void Stats::AddMethod(const std::string_view& method)
{
	if (methods_.find(method) != methods_.end()) 
	{
		methods_[method]++;
	}
	else 
	{
		methods_[std::string_view("UNKNOWN")]++;
	}
}
void Stats::AddUri(const std::string_view& uri)
{
	if (uris_.find(uri) != uris_.end())
	{
		uris_[uri]++;
	}
	else
	{
		uris_[std::string_view("unknown")]++;
	}
}
const std::map<std::string_view, int>& Stats::GetUriStats() const
{
	return uris_;
}
const std::map<std::string_view, int>& Stats::GetMethodStats() const
{
	return methods_;
}
HttpRequest ParseRequest(std::string_view line)
{
	HttpRequest result_request;
	size_t pos = 0;
	size_t space = 0;
	while (line[space] == ' ' && line[space] != line.npos)
	{
		space++;
	}
	line.remove_prefix(space);

	space = line.find(' ', pos);
	result_request.method = line.substr(pos, space);
	line.remove_prefix(space + 1);

	space = line.find(' ', pos);
	result_request.uri = line.substr(pos, space);
	line.remove_prefix(space + 1);

	space = line.find(' ', pos);
	result_request.protocol = line.substr(pos, space);
	line.remove_prefix(space + 1);

	return result_request;

}