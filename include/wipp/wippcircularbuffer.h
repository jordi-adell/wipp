/*
* circularbuffer.h
* Copyright 2017 (c) Jordi Adell
* Created on: 2017
* 	Author: Jordi Adell - adellj@gmail.com
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
*/

#include <cstddef>
#include <cstdint>

namespace wipp {

    struct wipp_circular_buffer_t_;
    typedef wipp_circular_buffer_t_ wipp_circular_buffer_t;

    void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, double *init_values, size_t length);
    void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, float *init_values, size_t length);
    void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, int16_t *init_values, size_t length);
    void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, int32_t *init_values, size_t length);
    void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, uint16_t *init_values, size_t length);
    void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, uint32_t *init_values, size_t length);

    template<typename circular_buffer_base_type>
    void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size) {
        init_cirular_buffer(buffer, size, (circular_buffer_base_type *) NULL, 0);
    }

    void delete_circular_buffer(wipp_circular_buffer_t **buffer);

    void cf_read(wipp_circular_buffer_t *cb, double *buffer, size_t length, size_t *stored);
    void cf_read(wipp_circular_buffer_t *cb, float *buffer, size_t length, size_t *stored);
    void cf_read(wipp_circular_buffer_t *cb, int16_t *buffer, size_t length, size_t *stored);
    void cf_read(wipp_circular_buffer_t *cb, int32_t *buffer, size_t length, size_t *stored);
    void cf_read(wipp_circular_buffer_t *cb, uint16_t *buffer, size_t length, size_t *stored);
    void cf_read(wipp_circular_buffer_t *cb, uint32_t *buffer, size_t length, size_t *stored);

    void cf_next(const wipp_circular_buffer_t *cb, double *buffer, size_t length, size_t *stored);
    void cf_next(const wipp_circular_buffer_t *cb, float *buffer, size_t length, size_t *stored);
    void cf_next(const wipp_circular_buffer_t *cb, int16_t *buffer, size_t length, size_t *stored);
    void cf_next(const wipp_circular_buffer_t *cb, int32_t *buffer, size_t length, size_t *stored);
    void cf_next(const wipp_circular_buffer_t *cb, uint16_t *buffer, size_t length, size_t *stored);
    void cf_next(const wipp_circular_buffer_t *cb, uint32_t *buffer, size_t length, size_t *stored);

    void cf_pointer(const wipp_circular_buffer_t *buffer, const double *pointer);
    void cf_pointer(const wipp_circular_buffer_t *buffer, const float *pointer);
    void cf_pointer(const wipp_circular_buffer_t *buffer, const int16_t *pointer);
    void cf_pointer(const wipp_circular_buffer_t *buffer, const int32_t *pointer);
    void cf_pointer(const wipp_circular_buffer_t *buffer, const uint16_t *pointer);
    void cf_pointer(const wipp_circular_buffer_t *buffer, const uint32_t *pointer);

    void cf_write(wipp_circular_buffer_t *cb, double *buffer, size_t length, size_t *stored);
    void cf_write(wipp_circular_buffer_t *cb, float *buffer, size_t length, size_t *stored);
    void cf_write(wipp_circular_buffer_t *cb, int16_t *buffer, size_t length, size_t *stored);
    void cf_write(wipp_circular_buffer_t *cb, int32_t *buffer, size_t length, size_t *stored);
    void cf_write(wipp_circular_buffer_t *cb, uint16_t *buffer, size_t length, size_t *stored);
    void cf_write(wipp_circular_buffer_t *cb, uint32_t *buffer, size_t length, size_t *stored);

    void cf_skip(wipp_circular_buffer_t *cb, size_t length, size_t *skipped);

    void cf_size(wipp_circular_buffer_t *cb, size_t *size);

    void cf_occupancy(wipp_circular_buffer_t *cb, size_t *occupancy);

    void cf_free(wipp_circular_buffer_t *cb, size_t *free);

}