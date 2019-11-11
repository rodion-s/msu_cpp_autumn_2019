#include <iostream>


enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';
public:

    explicit Serializer(std::ostream& out) : out_(out) {}

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator() (ArgsT... args) {
        return process(args...);
    }
    
private:
    std::ostream& out_;
    Error process() {
		return Error::NoError;
	}
	
	Error process(uint64_t val) {
		out_ << val << Separator;
		return Error::NoError;
	}

	Error process(bool val) {
		out_ << (val ? "true" : "false") << Separator;
		return Error::NoError;
	}

	template <class T, class... Args>
	Error process(T&& val, Args&&... args) {
		if (process(val) == Error::NoError) {
			return process(std::forward<Args>(args)...);
		} else {
			return Error::CorruptedArchive;
		}
	}
};

class Deserializer
{
public:
	explicit Deserializer(std::istream& in) : in_(in) {}

	template <class T>
	Error load(T& object) {
		return object.serialize(*this);
	}

	template <class... ArgsT>
	Error operator() (ArgsT&&... args) {
		return process(args...);
	}
	
private:
	std::istream& in_;
	Error process(bool& item) {
		std::string text;
		in_ >> text;

		if (text == "true") {
			item = true;
			return Error::NoError;
		} else if (text == "false") {
			item = false;
			return Error::NoError;
		} else {
			return Error::CorruptedArchive;
		}
	}
	
	Error process() {
		return Error::NoError;
	}
	
	Error process(uint64_t& item) {
		std::string text;
		in_ >> text;
		if (text.empty() || text[0] == '-') {
			return Error::CorruptedArchive;
		}
		item = std::stoull(text);
		return Error::NoError;
	}

	template <class T, class... Args>
	Error process(T&& val, Args&&... args) {
		if (process(val) == Error::NoError) {
			return process(std::forward<Args>(args)...);
		} else {
			return Error::CorruptedArchive;
		}
	}
};