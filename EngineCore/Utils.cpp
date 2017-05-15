#include  "Utils.h"
#include <fstream>

std::string ReadFile(const std::string & path) 
{
	std::ifstream ifs(path);
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	return content;
}


namespace Utils
{
	//NOTE(vlad): Help struct to split strings
	std::ctype_base::mask const* tokens::get_table()
	{
		typedef std::ctype<char> cctype;
		static const cctype::mask *const_rc = cctype::classic_table();

		static cctype::mask rc[cctype::table_size];
		std::memcpy(rc, const_rc, cctype::table_size * sizeof(cctype::mask));

		rc[','] = std::ctype_base::space;
		//rc[' '] = std::ctype_base::space;
		return &rc[0];
	}

	std::vector<std::string> SplitStrByComma(const std::string& str)
	{
		std::stringstream ss(str);
		ss.imbue(std::locale(std::locale(), new tokens()));
		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end;

		return std::vector<std::string>(begin, end);
	}

	glm::vec3 VectorFromString(const std::string& str)
	{
		std::vector<std::string> elems = SplitStrByComma(str);
		assert(elems.size() == 3, "There must be 3 elements in vector string");

		float e1 = strtof(elems[0].c_str(), nullptr);
		float e2 = strtof(elems[1].c_str(), nullptr);
		float e3 = strtof(elems[2].c_str(), nullptr);

		return glm::vec3(e1, e2, e3);
	}
}
