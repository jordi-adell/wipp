/*
 * wippexception.h
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

#ifndef __WIPP_EXCEPTION_H_
#define __WIPP_EXCEPTION_H_

#include <stdexcept>

namespace wipp {

    class WIppException : public std::runtime_error {
    public:
        WIppException(const std::string &message);
    private:
        static void logMessage(const std::string &message);
    };
}

#endif