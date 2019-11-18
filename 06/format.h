#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <exception>

template<typename T>
const std::string to_string(T &&obj) {
	std::stringstream output;
	output << obj;
	return output.str();
}
template<typename... Args>
std::string format(const std::string &str, Args&&... args) {
	std::stringstream output;
	std::vector<std::string> pos_args = { to_string(std::forward<Args>(args))... };

	for (size_t idx = 0; idx < str.size(); ++idx) {
		if (str[idx] == '}') {
			throw std::runtime_error("");
		}
		if (str[idx] == '{') {
			++idx;
			size_t end = 0;
			unsigned long arg_index = 0;
			try {
				arg_index = stoull(str.substr(idx, str.size() - idx), &end);
			} catch (std::logic_error &exc) {
				throw std::runtime_error("");
			}
			end += idx;
			if (str[end] != '}' || arg_index >= pos_args.size()) {
				throw std::runtime_error("");
			}
			idx = end;
			output << pos_args[arg_index];
		} else {
			output << str[idx];
		}
	}
	return output.str();
}
