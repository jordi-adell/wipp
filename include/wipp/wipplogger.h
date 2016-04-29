/*
 * wipplogger.h
 *
 * ----------------------------------------------------------------------
 * Copyright 2016 (c) Jordi Adell
 * Created on: 2015
 * Author: Jordi Adell - adellj@gmail.com
 * ----------------------------------------------------------------------
 *
 * This file is part of WIPP
 *
 * WIPP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WIPP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WIPP.  If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------------------
 */
#ifndef __WIPP_LOGGER_H_
#define __WIPP_LOGGER_H_

#include <iostream>
#include <vector>



namespace wipp
{

class Logger
{
    public:
	typedef enum{FATAL  = 0, ERROR = 1, WARNING = 2, INFO = 3, DEBUG = 4, TRACE = 5} LogLevel;
	Logger(LogLevel level = FATAL, bool enable = true, std::ostream &os = std::cout);

	std::ostream &log(LogLevel level, const char *file, int line);

	bool isEnabled(LogLevel level);
	void enable();
	void disable();
	void setLogLevel(LogLevel level);

    private:
	LogLevel _level;
	std::ostream &_os;
	bool _enabled;
	std::vector<std::string> _levelNames;
};


}

static wipp::Logger _logger_(wipp::Logger::DEBUG);

#ifdef WIPP_DEBUG


#define LOG_STREAM(level, what) {if (_logger_.isEnabled(level)) _logger_.log(level, __FILE__, __LINE__) << what << std::endl;}
#define DEBUG_STREAM(what) LOG_STREAM(wipp::Logger::DEBUG, what)
#define ERROR_STREAM(what) LOG_STREAM(wipp::Logger::ERROR, what)
#define WARN_STREAM(what) LOG_STREAM(wipp::Logger::WARNING, what)
#define INFO_STREAM(what) LOG_STREAM(wipp::Logger::INFO, what)
#define TRACE_STREAM(what) LOG_STREAM(wipp::Logger::TRACE, what)


#else

#ifndef INFO_STREAM
#define INFO_STREAM(x)
#endif

#ifndef WARN_STREAM
#define WARN_STREAM(x)
#endif

#ifndef ERROR_STREAM
#define ERROR_STREAM(x)
#endif

#ifndef DEBUG_STREAM
#define DEBUG_STREAM(x)
#endif

#ifndef TRACE_STREAM
#define TRACE_STREAM(x)
#endif


#endif


#endif //__DSP_LOGGER_H_
