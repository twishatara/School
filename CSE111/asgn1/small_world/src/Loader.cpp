
#include "Loader.h"

#include <fstream>
#include "picojson.h"

// loads items of various types from the file system
// here, we hand deserialize stuff from JSON in a file
// In most commerical systems, this would be done using an automatic deserializer
using namespace picojson;

std::shared_ptr<Room> Loader::load_room(const std::string & filename) const {

	// load a room from the JSON contained in filename
	// if there are errors, note these to std::cerr, and return nullptr
	// otherwise, return a shared_ptr to the room

	picojson::value v;
	std::ifstream file(filename);

	file >> v;

	std::string err = picojson::get_last_error();

	if (!err.empty()) {
		std::cerr << "Error reading file : " << filename << " : " << err << std::endl;
		return nullptr;
	}

	if (!v.is<picojson::object>()) {
		std::cerr << "Contents of file : " << filename << " are not a valid JSON object : " << v.to_str() << std::endl;
		return nullptr;
	}
	
	// it's an object, so uses it as such	
	picojson::object& obj = v.get<picojson::object>();

	if (!has_string_field(obj, "Id")) {
		std::cerr << "filename : " << filename << " does not contain an Id property (or it is not a string)" << std::endl; 
		return nullptr;
	}

	if (!has_string_field(obj, "Name")) {
		std::cerr << "filename : " << filename << " does not contain a Name Property (or it is not a string)" << std::endl;
		return nullptr;
	}

	if (!has_string_field(obj, "Description")) {
		std::cerr << "filename : " << filename << " does not contain a Description property (or it is not a string)" << std::endl;
		return nullptr;
	}

	picojson::value vId = obj["Id"];
	picojson::value vName = obj["Name"];
	picojson::value vDesc = obj["Description"];

	std::shared_ptr<Room> room = std::make_shared<Room>(vId.get<std::string>(), vName.get<std::string>(), vDesc.get<std::string>());	

	// now load the links to other rooms, if any
		
	if (!has_object_field(obj, "Links")) {
		return room;  // it's fine to be a "standalone" room with no links
	}

	if (!load_links(filename, obj["Links"].get<picojson::object>(), room)) {
		return nullptr;   // if there are links, they have to be right!
	}

	return room;

}

bool Loader::has_string_field(picojson::value::object & obj, const std::string & fieldname) const {

	// illustates data verification - does this object name the named field, and is it a string?

	if (obj.find(fieldname) == obj.end()) return false;
	if (!obj[fieldname].is<std::string>()) return false;

	return true;

}

bool Loader::has_object_field(picojson::value::object & obj, const std::string & fieldname) const {

	if (obj.find(fieldname) == obj.end()) return false;
	if (!obj[fieldname].is<picojson::object>()) return false;

	return true;

}

bool Loader::load_links(const std::string & filename, const picojson::value::object & obj, std::shared_ptr<Room> room) const {


	// load links to other rooms.  An example of using an iterator to iterate a JSON OBJECT

	for (picojson::value::object::const_iterator i = obj.begin(); i != obj.end(); ++i) {
		const std::string & direction = i->first;
		picojson::value linked_room = i->second;
		if (!linked_room.is<std::string>()) {
			std::cerr << "Link in filename : " << filename << " named " << direction << " is not a string" << std::endl;
			return false;
		}

		room->add_link(direction, linked_room.get<std::string>());
	}

	return true;
}	



