#include <stdexcept>

class ColorException : public std::exception { 
	public:
		ColorException(std::string msg): msg(std::move(msg)) {}

	const char *what() const noexcept override {
		return msg.c_str();
	}

	private:
		const std::string msg;
};
