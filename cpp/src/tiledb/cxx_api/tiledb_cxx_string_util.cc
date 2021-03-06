#include "tiledb_cxx_string_util.h"


//#include <regex>
//#include <boost/xpressive/xpressive.hpp>

#include <cstdlib>
//#include "json/json.h"

namespace tiledb
{

	bool StringUtil::isBlank(char ch)
	{
		return std::isspace(ch);
	}

	char StringUtil::toLowerInternal(char ch)
	{
		return (char)std::tolower(ch);
	}

	char StringUtil::toUpperInternal(char ch)
	{
		return (char)std::toupper(ch);
	}

	char StringUtil::toLower(char ch)
	{
		return toLowerInternal(ch);
	}

	char StringUtil::toUpper(char ch)
	{
		return toUpperInternal(ch);
	}

	std::string StringUtil::toLower(const std::string& str)
	{
		std::string result(str);
		std::transform(result.begin(), result.end(), result.begin(), toLowerInternal);  //Lower(result);
		return result;
	}

	std::string StringUtil::toUpper(const std::string& str)
	{
		std::string result(str);
		std::transform(result.begin(), result.end(), result.begin(), toUpperInternal);  //Upper(result);
		return result;
	}

	//std::string& StringUtil::Lower(std::string& str)
	//{
	//	std::transform(str.begin(), str.end(), str.begin(), ToLowerInternal);
	//	return str;
	//}

	//std::string& StringUtil::Upper(std::string& str)
	//{
	//	std::transform(str.begin(), str.end(), str.begin(), ToUpperInternal);
	//	return str;
	//}

	//std::string& StringUtil::Trim(std::string& str)
	//{
	//	return LTrim(RTrim(str));
	//}

	bool StringUtil::contains(const std::string& str, const char ch)
	{
		return (str.find(ch) != std::string::npos);
	}

	bool StringUtil::contains(const std::string& str, const char* substr)
	{
		return (str.find(substr) != std::string::npos);
	}

	bool StringUtil::contains(const std::string& str, const std::string& substr)
	{
		return (str.find(substr) != std::string::npos);
	}



	bool StringUtil::startsWith(const std::string& str, const std::string& prefix)
	{
		return (str.size() >= prefix.size()) && (str.compare(0, prefix.size(), prefix) == 0);
	}

	bool StringUtil::endsWith(const std::string& str, const std::string& suffix)
	{
		return (str.size() >= suffix.size()) && (str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0);
	}

	bool StringUtil::startsWithAnyOfWords(const std::string& str, const std::set<std::string>& wordset)
	{
		if (wordset.size() == 0) { return true; }
		for (auto it = wordset.cbegin(); it != wordset.cend(); ++it)
		{
			if (startsWith(str, (*it))) { return true; }
		}
		return false;
	}

 
	bool StringUtil::endsWithAnyOfWords(const std::string& str, const std::set<std::string>& wordset)
	{
		if (wordset.size() == 0) { return true; }
		for (auto it = wordset.cbegin(); it != wordset.cend(); ++it)
		{
			if (endsWith(str, (*it))) { return true; }
		}
		return false;
	}

	bool StringUtil::isAnyOfWordsInStr(const std::string& str, const std::set<std::string>& wordset)
	{
		if (wordset.size() == 0) { return true; }
		for (auto it = wordset.cbegin(); it != wordset.cend(); ++it)
		{
			if (contains(str, (*it))) { return true; }
		}
		return false;
	}//bool StringUtil::isAnyOfWordsInStr(const std::string& str, const std::set<std::string>& wordset)


	bool StringUtil::isAllOfWordsInStr(const std::string& str, const std::set<std::string>& wordset)
	{
		if (wordset.size() == 0) { return true; }
		for (auto it = wordset.cbegin(); it != wordset.cend(); ++it)
		{
			if (!contains(str, (*it))) { return false; }
		}
		return true;
	}//bool StringUtil::isAllOfWordsInStr(const std::string& str, const std::set<std::string>& wordset)

////
	bool StringUtil::isBlank(const char* str)
	{
		for (size_t i = 0; str[i] != 0; ++i)
			if (!isBlank(str[i]))
				return false;

		return true;
	}

	bool StringUtil::isBlank(const std::string& str)
	{
		if (str.empty())
			return true;

		for (auto ch : str)
			if (!isBlank(ch))
				return false;

		return true;
	}

	std::string StringUtil::toLTrim(const std::string& str)
	{
		return std::string(std::find_if(str.begin(), str.end(), [](int c) { return !std::isspace(c); }), str.end());
	}

	std::string StringUtil::toRTrim(const std::string& str)
	{
		return std::string(str.begin(), std::find_if(str.rbegin(), str.rend(), [](int c) { return !std::isspace(c); }).base());
	}

	std::string StringUtil::toTrim(const std::string& str)
	{
		auto start = std::find_if(str.begin(), str.end(), [](int c) { return !std::isspace(c); });
		auto end = std::find_if(str.rbegin(), str.rend(), [](int c) { return !std::isspace(c); }).base();

		return (start != str.end()) ? std::string(start, end) : std::string();
	}

	std::string StringUtil::toTrimDotSuffix(const std::string& str)
	{
		std::vector<std::string> items = split(str, '.');
		if (items.size() == 0)
		{
			return "";
		}
		return items[0];
	}

 
	std::string StringUtil::getDotSuffix(const std::string& str)
	{
		std::vector<std::string> items = split(str, '.');
		if (items.size() == 0)
		{
			return "";
		}
		return items[items.size() - 1];
	}
	//////

	double StringUtil::toDouble(const std::string& str)
	{
		return atof(str.c_str());
	}

 
	int StringUtil::toInt(const std::string& str)
	{
		return atoi(str.c_str());
	}

 
	int64_t StringUtil::toInt64(const std::string& str)
	{
		return atoll(str.c_str());
	}

	//std::string& StringUtil::LTrim(std::string& str)
	//{
	//	str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int c) { return !std::isspace(c); }));
	//	return str;
	//}

	//std::string& StringUtil::RTrim(std::string& str)
	//{
	//	str.erase(std::find_if(str.rbegin(), str.rend(), [](int c) { return !std::isspace(c); }).base(), str.end());
	//	return str;
	//}




	size_t StringUtil::countAll(const std::string& str, const std::string& substr)
	{
		size_t count = 0;

		size_t pos = 0;
		while ((pos = str.find(substr, pos)) != std::string::npos)
		{
			pos += substr.size();
			++count;
		}

		return count;
	}

	bool StringUtil::replaceFirst(std::string& str, const std::string& substr, const std::string& with)
	{
		size_t pos = str.find(substr);
		if (pos == std::string::npos)
			return false;

		str.replace(pos, substr.size(), with);
		return true;
	}

	bool StringUtil::replaceLast(std::string& str, const std::string& substr, const std::string& with)
	{
		size_t pos = str.rfind(substr);
		if (pos == std::string::npos)
			return false;

		str.replace(pos, substr.size(), with);
		return true;
	}

	bool StringUtil::replaceAll(std::string& str, const std::string& substr, const std::string& with)
	{
		bool result = false;

		size_t pos = 0;
		while ((pos = str.find(substr, pos)) != std::string::npos)
		{
			str.replace(pos, substr.size(), with);
			pos += with.size();
			result = true;
		}

		return result;
	}

	std::vector<std::string> StringUtil::split(const std::string& str, char delimiter, bool skip_empty)
	{
		std::vector<std::string> tokens;

		size_t pos_current;
		size_t pos_last = 0;
		size_t length;

		while (true)
		{
			pos_current = str.find(delimiter, pos_last);
			if (pos_current == std::string::npos)
				pos_current = str.size();

			length = pos_current - pos_last;
			if (!skip_empty || (length != 0))
				tokens.emplace_back(str.substr(pos_last, length));

			if (pos_current == str.size())
				break;
			else
				pos_last = pos_current + 1;
		}

		return tokens;
	}

	std::vector<std::string> StringUtil::split(const std::string& str, const std::string& delimiter, bool skip_empty)
	{
		std::vector<std::string> tokens;

		size_t pos_current;
		size_t pos_last = 0;
		size_t length;

		while (true)
		{
			pos_current = str.find(delimiter, pos_last);
			if (pos_current == std::string::npos)
				pos_current = str.size();

			length = pos_current - pos_last;
			if (!skip_empty || (length != 0))
				tokens.emplace_back(str.substr(pos_last, length));

			if (pos_current == str.size())
				break;
			else
				pos_last = pos_current + delimiter.size();
		}

		return tokens;
	}

	std::vector<std::string> StringUtil::splitByAny(const std::string& str, const std::string& delimiters, bool skip_empty)
	{
		std::vector<std::string> tokens;

		size_t pos_current;
		size_t pos_last = 0;
		size_t length;

		while (true)
		{
			pos_current = str.find_first_of(delimiters, pos_last);
			if (pos_current == std::string::npos)
				pos_current = str.size();

			length = pos_current - pos_last;
			if (!skip_empty || (length != 0))
				tokens.emplace_back(str.substr(pos_last, length));

			if (pos_current == str.size())
				break;
			else
				pos_last = pos_current + 1;
		}

		return tokens;
	}

	std::string StringUtil::join(const std::vector<std::string>& tokens, bool skip_empty, bool skip_blank)
	{
		if (tokens.empty())
			return "";

		std::ostringstream result;

		for (size_t i = 0; i < tokens.size(); ++i)
			if (!((skip_empty && tokens[i].empty()) || (skip_blank && isBlank(tokens[i]))))
				result << tokens[i];

		return result.str();
	}

	std::string StringUtil::join(const std::vector<std::string>& tokens, char delimiter, bool skip_empty, bool skip_blank)
	{
		if (tokens.empty())
			return "";

		std::ostringstream result;

		for (size_t i = 0; i < tokens.size() - 1; ++i)
			if (!((skip_empty && tokens[i].empty()) || (skip_blank && isBlank(tokens[i]))))
				result << tokens[i] << delimiter;

		if (!((skip_empty && tokens[tokens.size() - 1].empty()) || (skip_blank && isBlank(tokens[tokens.size() - 1]))))
			result << tokens[tokens.size() - 1];

		return result.str();
	}

	std::string StringUtil::join(const std::vector<std::string>& tokens, const char* delimiter, bool skip_empty, bool skip_blank)
	{
		if (tokens.empty())
			return "";

		std::ostringstream result;

		for (size_t i = 0; i < tokens.size() - 1; ++i)
			if (!((skip_empty && tokens[i].empty()) || (skip_blank && isBlank(tokens[i]))))
				result << tokens[i] << delimiter;

		if (!((skip_empty && tokens[tokens.size() - 1].empty()) || (skip_blank && isBlank(tokens[tokens.size() - 1]))))
			result << tokens[tokens.size() - 1];

		return result.str();
	}

	std::string StringUtil::join(const std::vector<std::string>& tokens, const std::string& delimiter, bool skip_empty, bool skip_blank)
	{
		if (tokens.empty())
			return "";

		std::ostringstream result;

		for (size_t i = 0; i < tokens.size() - 1; ++i)
			if (!((skip_empty && tokens[i].empty()) || (skip_blank && isBlank(tokens[i]))))
				result << tokens[i] << delimiter;

		if (!((skip_empty && tokens[tokens.size() - 1].empty()) || (skip_blank && isBlank(tokens[tokens.size() - 1]))))
			result << tokens[tokens.size() - 1];

		return result.str();
	}

	std::vector<double> StringUtil::splitStrToDoubleVector(const std::string& str, const std::string& delimiter)
	{
		std::vector<double> result;

		std::vector<std::string> items = split(str, delimiter, false);
		result.reserve(items.size());
		for (auto it = items.begin(); it != items.end(); ++it)
		{
			result.push_back(atof( (*it).c_str() ));
		}

		return result;
	}

	std::string StringUtil::joinDoubleVectorToStr(const std::vector<double>& vs, const std::string& delimiter, int precision)
	{
		std::stringstream ss;
		ss << std::setprecision(precision);
		int count = 0;
		for (auto it = vs.begin(); it != vs.end(); ++it)
		{
			if (count > 0)
			{
				ss << delimiter;
			}
			ss << (*it);
			++count;
		}

		return ss.str();
	}

	std::vector<int> StringUtil::splitStrToIntVector(const std::string& str, const std::string& delimiter)
	{
		std::vector<int> result;

		std::vector<std::string> items = split(str, delimiter, false);
		result.reserve(items.size());
		for (auto it = items.begin(); it != items.end(); ++it)
		{
			result.push_back(atoi((*it).c_str()));
		}

		return result;
	}

	std::string StringUtil::joinIntVectorToStr(const std::vector<int>& vs, const std::string& delimiter)
	{
		std::stringstream ss;

		int count = 0;
		for (auto it = vs.begin(); it != vs.end(); ++it)
		{
			if (count > 0)
			{
				ss << delimiter;
			}
			ss << (*it);
			++count;
		}


		return ss.str();
	}

	std::vector<int64_t> StringUtil::splitStrToInt64Vector(const std::string& str, const std::string& delimiter)
	{
		std::vector<int64_t> result;

		std::vector<std::string> items = split(str, delimiter, false);
		result.reserve(items.size());
		for (auto it = items.begin(); it != items.end(); ++it)
		{
			result.push_back(atoll((*it).c_str()));
		}

		return result;
	}

	std::string StringUtil::joinInt64VectorToStr(const std::vector<int64_t>& vs, const std::string& delimiter)
	{
		std::stringstream ss;

		int count = 0;
		for (auto it = vs.begin(); it != vs.end(); ++it)
		{
			if (count > 0)
			{
				ss << delimiter;
			}
			ss << (*it);
			++count;
		}


		return ss.str();
	}

	//bool StringUtil::isValidJsonStr(const std::string& s)
	//{
	//	Json::Value root;
	//	Json::CharReaderBuilder builder;
	//	std::stringstream ss;
	//	std::string errs;
	//	ss << s;
	//	bool isok = Json::parseFromStream(builder, ss, &root, &errs);

	//	return isok;
	//}
	//std::string StringUtil::getValueForKeyInJsonStr(const std::string& s, const std::string& key)
	//{
	//	std::string result = "";

	//	Json::Value root;
	//	Json::CharReaderBuilder builder;
	//	std::stringstream ss;
	//	std::string errs;
	//	ss << s;
	//	bool isok = Json::parseFromStream(builder, ss, &root, &errs);
	//	if (!isok)
	//	{
	//		return result;
	//	}
	//	
	//	if (root.isMember(key))
	//	{
	//		const Json::Value v = root[key];
	////		Json::StreamWriterBuilder wbuilder;
	////		result = Json::writeString(wbuilder, &v);

	//		Json::FastWriter fastWriter;
	//		fastWriter.omitEndingLineFeed();
	//		result = fastWriter.write(v);
	//	}
	//	
 //

	//	return result;
	// 
	//}

	//std::vector<std::string> StringUtil::getKeysForJsonStr(const std::string& s)
	//{
	//	std::vector<std::string> result;

	//	Json::Value root;
	//	Json::CharReaderBuilder builder;
	//	std::stringstream ss;
	//	std::string errs;
	//	ss << s;
	//	bool isok = Json::parseFromStream(builder, ss, &root, &errs);
	//	if (!isok)
	//	{
	//		return result;
	//	}

	//	for (auto const& name : root.getMemberNames())
	//	{
	//		result.push_back(name);
	//	}
	// 
	//	return result;
	//}
	//std::string StringUtil::removeKeysForJsonStr(const std::string& s, std::vector<std::string>& keys)
	//{

	//	Json::Value root;
	//	Json::CharReaderBuilder builder;
	//	std::stringstream ss;
	//	std::string errs;
	//	ss << s;
	//	bool isok = Json::parseFromStream(builder, ss, &root, &errs);
	//	if (!isok)
	//	{
	//		return s;
	//	}

	//	for (auto const& key : keys)
	//	{
	//		if (root.isMember(key))
	//		{
	//			root.removeMember(key);
	//		}
	//	}

	//	Json::StreamWriterBuilder wbuilder;
	//	return Json::writeString(wbuilder, root);
 //
	//}
	//std::string StringUtil::keepKeysForJsonStr(const std::string& s, std::vector<std::string>& keep_keys)
	//{
	//	Json::Value root;
	//	Json::CharReaderBuilder builder;
	//	std::stringstream ss;
	//	std::string errs;
	//	ss << s;
	//	bool isok = Json::parseFromStream(builder, ss, &root, &errs);
	//	if (!isok)
	//	{
	//		return s;
	//	}

	//	std::vector<std::string> names = root.getMemberNames();

	//	for (auto const& name : names)
	//	{
	//		if (std::find(keep_keys.begin(),keep_keys.end(), name) == keep_keys.end() )
	//		{
	//			root.removeMember(name);
	//		}
	//	}

	//	Json::StreamWriterBuilder wbuilder;
	//	return Json::writeString(wbuilder, root);
	//}

//////////////

	std::string StringUtil::intToStr(int i) {
		std::stringstream ss;
		ss << std::fixed << i;
		return ss.str();
	}

	std::string StringUtil::uintToStr(unsigned int i)
	{
		std::stringstream ss;
		ss << std::fixed << i;
		return ss.str();
	}

	std::string StringUtil::longToStr(long l) {
		std::stringstream ss;
		ss << std::fixed << l;
		return ss.str();
	}

	std::string StringUtil::longlongToStr(long long ll) {
		std::stringstream ss;
		ss << std::fixed << ll;
		return ss.str();
	}

	std::string StringUtil::size_tToStr(size_t st) {
		std::stringstream ss;
		ss << std::fixed << st;
		return ss.str();
	}

	std::string StringUtil::int64ToStr(int64_t i) {
		std::stringstream ss;
		ss << std::fixed << i;
		return ss.str();
	}
	std::string StringUtil::doubleToStr(double d) {
		std::stringstream ss;
		ss << std::setprecision(16) << d; //ss << std::fixed << std::setprecision(4) << d;
		return ss.str();
	}
	std::string StringUtil::boolToStr(bool b) {
		return b ? "true" : "false";
	}

	//bool StringUtil::matchPattern(const std::string& s, const std::string& pattern)
	//{
	//	bool isok = false;
	//	try
	//	{
	//		//		std::cout << "start to compile sregex:" << expirepattern << std::endl;
	//		boost::xpressive::sregex reg = boost::xpressive::sregex::compile(pattern);
	//		boost::xpressive::smatch match;
	//		isok = boost::xpressive::regex_match(s, match, reg);
	//	}
	//	catch (...)
	//	{
	//		isok = false;
	//	//	std::cout << "StringUtil::matchPattern,s:" << s << ",pattern:" << pattern << std::endl;
	//	//	LOGW("StringUtil::matchPattern,s:" + s + ",pattern:" + pattern);

	//	}
	//	return isok;
	//}
 //
	//std::vector<std::string> StringUtil::getMatchedGroups(const std::string& s, const std::string& pattern)
	//{
	//	std::vector<std::string> result;

	//	bool isok = false;
	//	try
	//	{
	//		//		std::cout << "start to compile sregex:" << expirepattern << std::endl;
	//		boost::xpressive::sregex reg = boost::xpressive::sregex::compile(pattern);
	//		boost::xpressive::smatch match;
	//		isok = boost::xpressive::regex_match(s, match, reg);
	//		if (isok)
	//		{
	//			result.reserve(match.size());
	//			for (int i = 0; i < (int)match.size(); ++i)
	//			{
	//				result.push_back(match.str(i));
	//			}
	//		}//if(isok)
	//	}
	//	catch (...)
	//	{
	//		isok = false;
	//		//	std::cout << "StringUtil::matchPattern,s:" << s << ",pattern:" << pattern << std::endl;
	//		//	LOGW("StringUtil::matchPattern,s:" + s + ",pattern:" + pattern);

	//	}

	//	return result;
	//}

}//namespace 