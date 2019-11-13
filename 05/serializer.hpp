#include <iostream>


enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';
public:

    explicit Serializer(std::ostream& output) : output_(output) {}
    

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator() (ArgsT&&... args) {
        return process(std::forward<ArgsT>(args)...);
    }
    
private:
    std::ostream& output_;
    Error process() {
		return Error::NoError;
	}
	
	Error process(uint64_t item) {
		output_ << item << Separator;
		return Error::NoError;
	}

	Error process(bool item) {
		output_ << (item ? "true" : "false") << Separator;
		return Error::NoError;
	}

	template <class T, class... Args>
	Error process(T&& item, Args&&... args) {
		if (process(item) == Error::NoError) {
			return process(std::forward<Args>(args)...);
		} else {
			return Error::CorruptedArchive;
		}
	}
};

class Deserializer
{
public:
	explicit Deserializer(std::istream& input) : input_(input) {}

	template <class T>
	Error load(T& object) {
		return object.serialize(*this);
	}

	template <class... ArgsT>
	Error operator() (ArgsT&&... args) {
		return process(std::forward<ArgsT>(args)...);
	}
private:
	std::istream& input_;
	Error process(bool& item) {
		std::string text;
		input_ >> text;

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
		input_ >> text;
		if (text.empty() || text[0] == '-') {
			return Error::CorruptedArchive;
		}
		item = std::stoull(text);
		return Error::NoError;
	}
	template <class T, class... Args>
	Error process(T&& item, Args&&... args) {
		if (process(item) == Error::NoError) {
			return process(std::forward<Args>(args)...);
		} else {
			return Error::CorruptedArchive;
		}
	}
};