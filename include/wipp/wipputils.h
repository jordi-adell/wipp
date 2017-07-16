/*
 * wipputils.h
 *
 * -------------------------------------------------------------------
 * Copyright 2016 (c) Jordi Adell
 * Created on: 2015
 * Author: Jordi Adell - adellj@gmail.com
 * -------------------------------------------------------------------
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
 * -------------------------------------------------------------------
 */

#ifndef __IPPUTILS_H_
#define __IPPUTILS_H_

#include <wipp/wippdefs.h>
#include <string>

namespace wipp{

  /** Copy functions -- Theses functions just copy the content of a buffer
   * into another buffer
   **/
  void copyBuffer(const int16_t *inbuffer, int16_t *outbuffer, size_t length);
  void copyBuffer(const uint16_t *inbuffer, uint16_t *outbuffer, size_t length);
  void copyBuffer(const int32_t *inbuffer, int32_t *outbuffer, size_t length);
  void copyBuffer(const double *inbuffer, double *outbuffer, size_t length);
  void copyBuffer(const float *inbuffer, float *outbuffer, size_t length);

  /** Copy function for buffers of different types -- These functions copy te content
   * of a buffer and convert the values to the corresponding type **/
  void copyBuffer(const float *inbuffer, double *outbuffer, size_t length);
  void copyBuffer(const double *inbuffer, float *outbuffer, size_t length);
  void copyBuffer(const int16_t *inbuffer, float *outbuffer, size_t length);
  void copyBuffer(const int16_t *inbuffer, double *outbuffer, size_t length);
  void copyBuffer(const int32_t *inbuffer, float *outbuffer, size_t length);
  void copyBuffer(const int32_t *inbuffer, double *outbuffer, size_t length);
  void copyBuffer(const uint16_t *inbuffer, float *outbuffer, size_t length);
  void copyBuffer(const uint16_t *inbuffer, double *outbuffer, size_t length);
    void copyBuffer(const uint32_t *inbuffer, double *outbuffer, size_t length);
  void copyBuffer(const double *inbuffer, int16_t *outbuffer, size_t length);
  void copyBuffer(const double *inbuffer, int32_t *outbuffer, size_t length);
  void copyBuffer(const double *inbuffer, uint16_t *outbuffer, size_t length);
    void copyBuffer(const double *inbuffer, uint32_t *outbuffer, size_t length);
  void copyBuffer(const float *inbuffer, int16_t *outbuffer, size_t length);
  void copyBuffer(const float *inbuffer, uint16_t *outbuffer, size_t length);
  void copyBuffer(const wipp_complex_t *inbuffer, wipp_complex_t *outbuffer, size_t length);


  void set(double val, double *buffer, size_t length);
  void set(float val, float *buffer, size_t length);
  void set(int16_t val, int16_t *buffer, size_t length);
  void set(int32_t val, int32_t *buffer, size_t length);
  void set(uint32_t val, uint32_t *buffer, size_t length);
  void set(uint16_t val, uint16_t *buffer, size_t length);
  void set(wipp_complex_t val, wipp_complex_t * bufer, size_t length);

  void setZeros(double *buffer, size_t length);
  void setZeros(float *buffer, size_t length);
  void setZeros(int16_t *buffer, size_t length);
  void setZeros(int32_t *buffer, size_t length);
  void setZeros(uint32_t *buffer, size_t length);
  void setZeros(uint16_t *buffer, size_t length);
  void setZeros(wipp_complex_t * bufer, size_t length);


  void add(const double *buffer_a, double *buffer_b, size_t length);
  void add(const float *buffer_a, float* buffer_b, size_t length);
  void add(const int16_t *buffer_a, int16_t* buffer_b, size_t length);
  void add(const int32_t *buffer_a, int32_t* buffer_b, size_t length);
  void add(const uint16_t *buffer_a, uint16_t* buffer_b, size_t length);
  void add(const uint32_t *buffer_a, uint32_t* buffer_b, size_t length);
  void add(const wipp::wipp_complex_t *buffer_a, wipp::wipp_complex_t* buffer_b, size_t length);

  void add(const double *buffer_a, const double* buffer_b, double * buffer, size_t length);
  void add(const float *buffer_a, const float* buffer_b, float * buffer, size_t length);
  void add(const int16_t *buffer_a, const int16_t* buffer_b, int16_t * buffer, size_t length);
  void add(const int32_t *buffer_a, const int32_t* buffer_b, int32_t * buffer, size_t length);
  void add(const uint16_t *buffer_a, const uint16_t* buffer_b, uint16_t * buffer, size_t length);
  void add(const uint32_t *buffer_a, const uint32_t* buffer_b, uint32_t * buffer, size_t length);
  void add(const wipp::wipp_complex_t *buffer_a, const wipp::wipp_complex_t* buffer_b, wipp::wipp_complex_t * buffer, size_t length);


  /** Functions to substract a buffer from another one. The _I suffix stands for inplace operation,
   * thus the second buffer is used as input as well as outpuf buffer: outbuffer = outbuffer - inbuffer
   **/

  void sub(const double *buffer_a, double* buffer_b, size_t length);
  void sub(const float *buffer_a, float* buffer_b, size_t length);
  void sub(const int16_t *buffer_a, int16_t* buffer_b, size_t length);
  void sub(const int32_t *buffer_a, int32_t* buffer_b, size_t length);
  void sub(const uint16_t *buffer_a, uint16_t* buffer_b, size_t length);
  void sub(const uint32_t *buffer_a, uint32_t* buffer_b, size_t length);
  void sub(const wipp::wipp_complex_t *buffer_a, wipp::wipp_complex_t* buffer_b, size_t length);

  void sub(const double *buffer_a, const double* buffer_b, double * buffer, size_t length);
  void sub(const float *buffer_a, const float* buffer_b, float * buffer, size_t length);
  void sub(const int16_t *buffer_a, const int16_t* buffer_b, int16_t * buffer, size_t length);
  void sub(const int32_t *buffer_a, const int32_t* buffer_b, int32_t * buffer, size_t length);
  void sub(const uint16_t *buffer_a, const uint16_t* buffer_b, uint16_t * buffer, size_t length);
  void sub(const uint32_t *buffer_a, const uint32_t* buffer_b, uint32_t * buffer, size_t length);
  void sub(const wipp::wipp_complex_t *buffer_a, const wipp::wipp_complex_t* buffer_b, wipp::wipp_complex_t * buffer, size_t length);

  void mult(const double *buffer_a, const double *buffer_b, double *buffer, size_t length);
  void mult(const float *buffer_a, const float *buffer_b, float *buffer, size_t length);
  void mult(const int16_t *buffer_a, const int16_t *buffer_b, int16_t *buffer, size_t length);
  void mult(const int32_t *buffer_a, const int32_t *buffer_b, int32_t *buffer, size_t length);
  void mult(const uint16_t *buffer_a, const uint16_t *buffer_b, uint16_t *buffer, size_t length);
  void mult(const uint32_t *buffer_a, const uint32_t *buffer_b, uint32_t *buffer, size_t length);
  void mult(const double *buffer_a, double *buffer_b, size_t length);
  void mult(const float *buffer_a, float *buffer_b, size_t length);
  void mult(const int16_t *buffer_a, int16_t *buffer_b, size_t length);
  void mult(const int32_t *buffer_a, int32_t *buffer_b, size_t length);
  void mult(const uint16_t *buffer_a, uint16_t *buffer_b, size_t length);
  void mult(const uint32_t *buffer_a, uint32_t *buffer_b, size_t length);
  void mult(const double *buffer_a, wipp_complex_t *buffer_b, size_t length);
  void mult(const double *buffer_a, const wipp_complex_t *buffer_b, wipp_complex_t *buffer, size_t length);
  void mult(const float *buffer_a, wipp_complex_t *buffer_b, size_t length);
  void mult(const float *buffer_a, const wipp_complex_t *buffer_b, wipp_complex_t *buffer, size_t length);
  void mult(const wipp_complex_t *buffer_a, wipp_complex_t *buffer_b, size_t length);
  void mult(const wipp_complex_t *buffer_a, const wipp_complex_t *buffer_b, wipp_complex_t *buffer, size_t length);


  void div(const double *buffer_a, const double *buffer_b, double *buffer, size_t length);
  void div(const float *buffer_a, const float *buffer_b, float *buffer, size_t length);
  void div(const int16_t *buffer_a, const int16_t *buffer_b, int16_t *buffer, size_t length);
  void div(const int32_t *buffer_a, const int32_t *buffer_b, int32_t *buffer, size_t length);
  void div(const uint16_t *buffer_a, const uint16_t *buffer_b, uint16_t *buffer, size_t length);
  void div(const uint32_t *buffer_a, const uint32_t *buffer_b, uint32_t *buffer, size_t length);
  void div(const double *buffer_a, double *buffer_b, size_t length);
  void div(const float *buffer_a, float *buffer_b, size_t length);
  void div(const int16_t *buffer_a, int16_t *buffer_b, size_t length);
  void div(const int32_t *buffer_a, int32_t *buffer_b, size_t length);
  void div(const uint16_t *buffer_a, uint16_t *buffer_b, size_t length);
  void div(const uint32_t *buffer_a, uint32_t *buffer_b, size_t length);
  void div(const wipp_complex_t *buffer_a, const wipp_complex_t *buffer_b, wipp_complex_t *buffer, size_t length);
  void div(const wipp_complex_t *buffer_a, wipp_complex_t *buffer_b, size_t length);


  void addC(double C, const double *buffer_in, double *buffer_out, size_t length);
  void addC(float C, const float *buffer_in, float *buffer_out, size_t length);
  void addC(int16_t C, const int16_t *buffer_in, int16_t *buffer_out, size_t length);
  void addC(int32_t C, const int32_t *buffer_in, int32_t *buffer_out, size_t length);
  void addC(uint16_t C, const uint16_t *buffer_in, uint16_t *buffer_out, size_t length);
  void addC(uint32_t C, const uint32_t *buffer_in, uint32_t *buffer_out, size_t length);
  void addC(double C, double *buffer, size_t length);
  void addC(float C, float *buffer, size_t length);
  void addC(int16_t C, int16_t *buffer, size_t length);
  void addC(int32_t C, int32_t *buffer, size_t length);
  void addC(uint16_t C, uint16_t *buffer, size_t length);
  void addC(uint32_t C, uint32_t *buffer, size_t length);
  void addC(wipp_complex_t C, wipp_complex_t *buffer, size_t length);


  void subC(double C, const double *buffer_in, double *buffer_out, size_t length);
  void subC(float C, const float *buffer_in, float *buffer_out, size_t length);
  void subC(int16_t C, const int16_t *buffer_in, int16_t *buffer_out, size_t length);
  void subC(int32_t C, const int32_t *buffer_in, int32_t *buffer_out, size_t length);
  void subC(uint16_t C, const uint16_t *buffer_in, uint16_t *buffer_out, size_t length);
  void subC(uint32_t C, const uint32_t *buffer_in, uint32_t *buffer_out, size_t length);
  void subC(double C, double *buffer, size_t length);
  void subC(float C, float *buffer, size_t length);
  void subC(int16_t C, int16_t *buffer, size_t length);
  void subC(int32_t C, int32_t *buffer, size_t length);
  void subC(uint16_t C, uint16_t *buffer, size_t length);
  void subC(uint32_t C, uint32_t *buffer, size_t length);


  void multC(double C, const double *buffer_in, double *buffer_out, size_t length);
  void multC(float C, const float *buffer_in, float *buffer_out, size_t length);
  void multC(int16_t C, const int16_t *buffer_in, int16_t *buffer_out, size_t length);
  void multC(int32_t C, const int32_t *buffer_in, int32_t *buffer_out, size_t length);
  void multC(uint16_t C, const uint16_t *buffer_in, uint16_t *buffer_out, size_t length);
  void multC(uint32_t C, const uint32_t *buffer_in, uint32_t *buffer_out, size_t length);
  void multC(double C, double *buffer, size_t length);
  void multC(float C, float *buffer, size_t length);
  void multC(int16_t C, int16_t *buffer, size_t length);
  void multC(int32_t C, int32_t *buffer, size_t length);
  void multC(uint16_t C, uint16_t *buffer, size_t length);
  void multC(uint32_t C, uint32_t *buffer, size_t length);


  void divC(double C, const double *buffer_in, double *buffer_out, size_t length);
  void divC(float C, const float *buffer_in, float *buffer_out, size_t length);
  void divC(int16_t C, const int16_t *buffer_in, int16_t *buffer_out, size_t length);
  void divC(int32_t C, const int32_t *buffer_in, int32_t *buffer_out, size_t length);
  void divC(uint16_t C, const uint16_t *buffer_in, uint16_t *buffer_out, size_t length);
  void divC(uint32_t C, const uint32_t *buffer_in, uint32_t *buffer_out, size_t length);

  void divC(double C, double *buffer, size_t length);
  void divC(float C, float *buffer, size_t length);
  void divC(int16_t C, int16_t *buffer, size_t length);
  void divC(int32_t C, int32_t *buffer, size_t length);
  void divC(uint16_t C, uint16_t *buffer, size_t length);
  void divC(uint32_t C, uint32_t *buffer, size_t length);


  void addProduct(const double* buffer_a, const double *buffer_b, const double *buffer_c, double *buffer, size_t length);
  void addProduct(const float* buffer_a, const float *buffer_b, const float *buffer_c, float *buffer, size_t length);
  void addProduct(const int16_t* buffer_a, const int16_t *buffer_b, const int16_t *buffer_c, int16_t *buffer, size_t length);
  void addProduct(const int32_t* buffer_a, const int32_t *buffer_b, const int32_t *buffer_c, int32_t *buffer, size_t length);
  void addProduct(const uint16_t* buffer_a, const uint16_t *buffer_b, const uint16_t *buffer_c, uint16_t *buffer, size_t length);
  void addProduct(const uint32_t* buffer_a, const uint32_t *buffer_b, const uint32_t *buffer_c, uint32_t *buffer, size_t length);

  void addProduct(const wipp_complex_t* buffer_a, const wipp_complex_t *buffer_b, const wipp_complex_t *buffer_c, wipp_complex_t *buffer, size_t length);

  void addProduct(const double* buffer_a, const double *buffer_b, double *buffer, size_t length);
  void addProduct(const float* buffer_a, const float *buffer_b, float *buffer, size_t length);
  void addProduct(const int16_t* buffer_a, const int16_t *buffer_b, int16_t *buffer, size_t length);
  void addProduct(const int32_t* buffer_a, const int32_t *buffer_b, int32_t *buffer, size_t length);
  void addProduct(const uint16_t* buffer_a, const uint16_t *buffer_b, uint16_t *buffer, size_t length);
  void addProduct(const uint32_t* buffer_a, const uint32_t *buffer_b, uint32_t *buffer, size_t length);

  void addProductC(double C, const double* buffer_a, const double *buffer_b, double *buffer, size_t length);
  void addProductC(float C, const float* buffer_a, const float *buffer_b, float *buffer, size_t length);
  void addProductC(int16_t C, const int16_t* buffer_a, const int16_t *buffer_b, int16_t *buffer, size_t length);
  void addProductC(int32_t C, const int32_t* buffer_a, const int32_t *buffer_b, int32_t *buffer, size_t length);
  void addProductC(uint16_t C, const uint16_t* buffer_a, const uint16_t *buffer_b, uint16_t *buffer, size_t length);
  void addProductC(uint32_t C, const uint32_t* buffer_a, const uint32_t *buffer_b, uint32_t *buffer, size_t length);

  void addProductC(double C, const double *buffer_in, double *buffer_out, size_t length);
  void addProductC(float C, const float *buffer_in, float *buffer_out, size_t length);
  void addProductC(int16_t C, const int16_t *buffer_in, int16_t *buffer_out, size_t length);
  void addProductC(int32_t C, const int32_t *buffer_in, int32_t *buffer_out, size_t length);
  void addProductC(uint16_t C, const uint16_t *buffer_in, uint16_t *buffer_out, size_t length);
  void addProductC(uint32_t C, const uint32_t *buffer_in, uint32_t *buffer_out, size_t length);


  void abs(double *buffer,size_t length);
  void abs(float *buffer, size_t length);
  void abs(int16_t *buffer,size_t length);
  void abs(int32_t *buffer, size_t length);

  void abs(const double *buffer_in, double *buffer_out, size_t length);
  void abs(const float *buffer_in, float *buffer_out, size_t length);
  void abs(const int16_t *buffer_in, int16_t *buffer_out, size_t length);
  void abs(const int32_t *buffer_in, int32_t *buffer_out, size_t length);


  void sqrt(double *buffer,size_t length);
  void sqrt(float *buffer, size_t length);
  void sqrt(int16_t *buffer,size_t length);
  void sqrt(int32_t *buffer, size_t length);
  void sqrt(uint32_t *buffer, size_t length);
  void sqrt(uint16_t *buffer, size_t length);

  void sqrt(const double *buffer_in, double *buffer_out, size_t length);
  void sqrt(const float *buffer_in, float *buffer_out, size_t length);
  void sqrt(const int16_t *buffer_in, int16_t *buffer_out, size_t length);
  void sqrt(const int32_t *buffer_in, int32_t *buffer_out, size_t length);
  void sqrt(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length);
  void sqrt(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length);


  void sqr(double *buffer,size_t length);
  void sqr(float *buffer, size_t length);
  void sqr(int16_t *buffer,size_t length);
  void sqr(int32_t *buffer, size_t length);
  void sqr(uint32_t *buffer, size_t length);
  void sqr(uint16_t *buffer, size_t length);

  void sqr(const double *buffer_in, double *buffer_out, size_t length);
  void sqr(const float *buffer_in, float *buffer_out, size_t length);
  void sqr(const int16_t *buffer_in, int16_t *buffer_out, size_t length);
  void sqr(const int32_t *buffer_in, int32_t *buffer_out, size_t length);
  void sqr(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length);
  void sqr(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length);


  void logn(double *buffer,size_t length);
  void logn(float *buffer, size_t length);
  void logn(int16_t *buffer,size_t length);
  void logn(int32_t *buffer, size_t length);
  void logn(uint32_t *buffer, size_t length);
  void logn(uint16_t *buffer, size_t length);

  void logn(const double *buffer_in, double *buffer_out, size_t length);
  void logn(const float *buffer_in, float *buffer_out, size_t length);
  void logn(const int16_t *buffer_in, int16_t *buffer_out, size_t length);
  void logn(const int32_t *buffer_in, int32_t *buffer_out, size_t length);
  void logn(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length);
  void logn(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length);


  void real2complex(const double *real, const double *imag, wipp_complex_t *complex, size_t length);
  void real(const wipp_complex_t *complex, double *real, size_t length);
  void imag(const wipp_complex_t *complex, double *imag, size_t length);
  void conj(wipp_complex_t *complex, size_t length);
  void conj(const wipp_complex_t *complex_in, wipp_complex_t *complex_out, size_t length);
  void conjFlip(const wipp_complex_t *complex_in, wipp_complex_t *complex_out, size_t length);

  void polar2cart(const double *module, const double *phase, wipp_complex_t *cart, size_t length);

//
//  /** Check if status indicates an error or not and the generates and exception if
//   * throwException is true in case of error. Also handle expected errors such as
//   * Waterfall
//   * Return true if an error has occured.
//   **/
//  bool checkStatus(int istatus, bool throwException=false);

}

#endif // __IPPUTILS_H_
