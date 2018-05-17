#include <wipp/wipplogger.h>
#include <boost/filesystem.hpp>


namespace  wipp {

	Logger::Logger(LogLevel level, bool enable, std::ostream &os) : _level(level), _os(os), _enabled(enable) {
	    _levelNames = {"FATAL", "ERROR", "WARN ", "INFO ", "DEBUG", "TRACE"};
	}

	std::ostream &Logger::log(LogLevel level, const char *file, int line)  {
        std::string path(file);
        size_t extension_begin = path.find_last_of(".");
        size_t basename_begin = path.find_last_of("/\\");
        return _os;
	}

	bool Logger::isEnabled(LogLevel level) { return (_enabled && level <= _level); }
	void Logger::enable() { _enabled = true; }
	void Logger::disable() { _enabled = false; }
	void Logger::setLogLevel(LogLevel level) { _level = level; }
}

