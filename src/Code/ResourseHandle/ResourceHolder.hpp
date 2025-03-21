#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept> // IWYU pragma: export
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void			load(Identifier id, const std::string& filename);
    void            open(Identifier id, const std::string& filename);

	template <typename Parameter>
	void			load(Identifier id, const std::string& filename, const Parameter& secondParam);

    template <typename Parameter>
    void            open(Identifier id, const std::string& filename, const Parameter& secondParam);

	Resource&		get(Identifier id);
	const Resource&	get(Identifier id) const;

	void			insertResource(Identifier id, std::unique_ptr<Resource> resource);
	bool		    isLoaded(Identifier id) const;

private:
	std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;
};

#include "ResourceHolder.inl" 
