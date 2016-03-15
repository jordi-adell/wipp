#include <wipp/wipputils.h>

#include <math.h>

namespace wipp{

  void copyBuffer(const short *inbuffer, short *outbuffer, size_t length)
  {
    memcpy(reinterpret_cast<void*>(outbuffer), reinterpret_cast<const void*>(inbuffer), length*sizeof(short));
  }

  void copyBuffer(const int *inbuffer, int *outbuffer, size_t length)
  {
    memcpy(reinterpret_cast<void*>(outbuffer), reinterpret_cast<const void*>(inbuffer), length*sizeof(int));
  }

  void copyBuffer(const double *inbuffer, double *outbuffer, size_t length)
  {
      memcpy(reinterpret_cast<void*>(outbuffer), reinterpret_cast<const void*>(inbuffer), length*sizeof(double));
  }

  void copyBuffer(const float *inbuffer, float *outbuffer, size_t length)
  {
    memcpy(reinterpret_cast<void*>(outbuffer), reinterpret_cast<const void*>(inbuffer), length*sizeof(float));
  }

  void copyBuffer(const float *inbuffer, double *outbuffer, size_t length)
  {
    for (size_t i = 0; i < length; ++i)
      outbuffer[i] = static_cast<double>(inbuffer[i]);
  }

  void copyBuffer(const double *inbuffer, float *outbuffer, size_t length)
  {
    for (size_t i = 0; i < length; ++i)
      outbuffer[i] = static_cast<float>(inbuffer[i]);
  }

  void copyBuffer(const short *inbuffer, float *outbuffer, size_t length)
  {
    for (size_t i = 0; i < length; ++i)
      outbuffer[i] = static_cast<float>(inbuffer[i]);
  }

  void copyBuffer(const short *inbuffer, double *outbuffer, size_t length)
  {
    for (size_t i = 0; i < length; ++i)
      outbuffer[i] = static_cast<double>(inbuffer[i]);
  }

  void copyBuffer(const int *inbuffer, float *outbuffer, size_t length)
  {
    for (size_t i = 0; i < length; ++i)
      outbuffer[i] = static_cast<float>(inbuffer[i]);
  }

  void copyBuffer(const int *inbuffer, double *outbuffer, size_t length)
  {
    for (size_t i = 0; i < length; ++i)
      outbuffer[i] = static_cast<double>(inbuffer[i]);
  }

  void copyBuffer(const double *inbuffer, short *outbuffer, size_t length)
  {
    for (size_t i = 0; i < length; ++i)
      outbuffer[i] = static_cast<short>(inbuffer[i]);
  }

  void copyBuffer(const double *inbuffer, unsigned short *outbuffer, size_t length)
  {
    for (size_t i = 0; i < length; ++i)
      outbuffer[i] = static_cast<unsigned short>(inbuffer[i]);
  }

  void copyBuffer(const float *inbuffer, short *outbuffer, size_t length)
  {
    for (size_t i = 0; i < length; ++i)
      outbuffer[i] = static_cast<short>(inbuffer[i]);
  }

  void copyBuffer(const float *inbuffer, short unsigned int *outbuffer, size_t length)
  {
    for (size_t i = 0; i < length; ++i)
      outbuffer[i] = static_cast<unsigned short>(inbuffer[i]);
  }

  void copyBuffer(const wipp_complex_t *inbuffer, wipp_complex_t *outbuffer, size_t length)
  {
      memcpy(outbuffer, inbuffer, length);
  }


  void subBuffer_I(const short *inbuffer, short *outbuffer, size_t length)
  {
    for (size_t i = 0; i < length; ++i)
      outbuffer[i] -= inbuffer[i];
  }

  void subBuffer_I(const float *inbuffer, float *outbuffer, size_t length)
  {
    for (size_t i = 0; i < length; ++i)
      outbuffer[i] -= inbuffer[i];
  }

  void subBuffer_I(const double *inbuffer, double *outbuffer, size_t length)
  {
    for (size_t i = 0; i < length; ++i)
      outbuffer[i] -= inbuffer[i];
  }


  template<typename T>
  void set_core(T val, T *buffer, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer[i] = val;
  }

  void set(double val, double *buffer, size_t length) { set_core(val, buffer, length); }
  void set(float val, float *buffer, size_t length) { set_core(val, buffer, length); }
  void set(int16_t val, int16_t *buffer, size_t length) { set_core(val, buffer, length); }
  void set(int32_t val, int32_t *buffer, size_t length) { set_core(val, buffer, length); }
  void set(uint32_t val, uint32_t *buffer, size_t length) { set_core(val, buffer, length); }
  void set(uint16_t val, uint16_t *buffer, size_t length) { set_core(val, buffer, length); }
  void set(wipp_complex_t val, wipp_complex_t * buffer, size_t length) { set_core(val, buffer, length); }


  void sesetZeros(double *buffer, size_t length)
  {
      memset(buffer, 0.0F, length*sizeof(double));
  }
  void setZeros(float *buffer, size_t length)
  {
      memset(buffer, 0.0F, length*sizeof(float));
  }
  void setZeros(int16_t *buffer, size_t length)
  {
      memset(buffer, 0.0F, length*sizeof(int16_t));
  }
  void setZeros(int32_t *buffer, size_t length)
  {
      memset(buffer, 0.0F, length*sizeof(int32_t));
  }
  void setZeros(uint32_t *buffer, size_t length)
  {
      memset(buffer, 0.0F, length*sizeof(uint32_t));
  }
  void setZeros(uint16_t *buffer, size_t length)
  {
      memset(buffer, 0.0F, length*sizeof(uint16_t));
  }

  void setZeros(wipp_complex_t *buffer, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
      {
	  buffer[i].re = 0;
	  buffer[i].im = 0;
      }
  }


  template<typename T>
  void add_core(const T *buffer_a, T* buffer_b, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer_b[i] += buffer_a[i];
  }
  template<typename T>
  void add_core(const T* buffer_a, const T* buffer_b, T* buffer, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer[i] = buffer_a[i] + buffer_b[i];
  }

  void add(const double *buffer_a, double* buffer_b, size_t length) { add_core(buffer_a, buffer_b, length); }
  void add(const float *buffer_a, float* buffer_b, size_t length) { add_core(buffer_a, buffer_b, length); }
  void add(const int16_t *buffer_a, int16_t* buffer_b, size_t length) { add_core(buffer_a, buffer_b, length); }
  void add(const int32_t *buffer_a, int32_t* buffer_b, size_t length) { add_core(buffer_a, buffer_b, length); }
  void add(const uint16_t *buffer_a, uint16_t* buffer_b, size_t length) { add_core(buffer_a, buffer_b, length); }
  void add(const uint32_t *buffer_a, uint32_t* buffer_b, size_t length) { add_core(buffer_a, buffer_b, length); }
  void add(const wipp::wipp_complex_t *buffer_a, wipp::wipp_complex_t* buffer_b, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
      {
	  buffer_b[i].re += buffer_a[i].re;
	  buffer_b[i].im += buffer_a[i].im;
      }
  }

  void add(const double *buffer_a, const double* buffer_b, double * buffer, size_t length) { add_core(buffer_a, buffer_b, buffer, length); }
  void add(const float *buffer_a, const float* buffer_b, float * buffer, size_t length) { add_core(buffer_a, buffer_b, buffer, length); }
  void add(const int16_t *buffer_a, const int16_t* buffer_b, int16_t * buffer, size_t length) { add_core(buffer_a, buffer_b, buffer, length); }
  void add(const int32_t *buffer_a, const int32_t* buffer_b, int32_t * buffer, size_t length) { add_core(buffer_a, buffer_b, buffer, length); }
  void add(const uint16_t *buffer_a, const uint16_t* buffer_b, uint16_t * buffer, size_t length) { add_core(buffer_a, buffer_b, buffer, length); }
  void add(const uint32_t *buffer_a, const uint32_t* buffer_b, uint32_t * buffer, size_t length) { add_core(buffer_a, buffer_b, buffer, length); }
  void add(const wipp::wipp_complex_t *buffer_a, const wipp::wipp_complex_t* buffer_b, wipp::wipp_complex_t * buffer, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
      {
	  buffer[i].re = buffer_b[i].re + buffer_a[i].re;
	  buffer[i].im = buffer_b[i].im + buffer_a[i].im;
      }
  }



  template<typename T>
  void sub_core(const T *buffer_a, T* buffer_b, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer_b[i] -= buffer_a[i];
  }
  template<typename T>
  void sub_core(const T* buffer_a, const T* buffer_b, T* buffer, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer[i] = buffer_a[i] - buffer_b[i];
  }

  void sub(const double *buffer_a, double* buffer_b, size_t length) { sub_core(buffer_a, buffer_b, length); }
  void sub(const float *buffer_a, float* buffer_b, size_t length) { sub_core(buffer_a, buffer_b, length); }
  void sub(const int16_t *buffer_a, int16_t* buffer_b, size_t length) { sub_core(buffer_a, buffer_b, length); }
  void sub(const int32_t *buffer_a, int32_t* buffer_b, size_t length) { sub_core(buffer_a, buffer_b, length); }
  void sub(const uint16_t *buffer_a, uint16_t* buffer_b, size_t length) { sub_core(buffer_a, buffer_b, length); }
  void sub(const uint32_t *buffer_a, uint32_t* buffer_b, size_t length) { sub_core(buffer_a, buffer_b, length); }
  void sub(const wipp::wipp_complex_t *buffer_a, wipp::wipp_complex_t* buffer_b, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
      {
	  buffer_b[i].re -= buffer_a[i].re;
	  buffer_b[i].im -= buffer_a[i].im;
      }
  }

  void sub(const double *buffer_a, const double* buffer_b, double * buffer, size_t length) { sub_core(buffer_a, buffer_b, buffer, length); }
  void sub(const float *buffer_a, const float* buffer_b, float * buffer, size_t length) { sub_core(buffer_a, buffer_b, buffer, length); }
  void sub(const int16_t *buffer_a, const int16_t* buffer_b, int16_t * buffer, size_t length) { sub_core(buffer_a, buffer_b, buffer, length); }
  void sub(const int32_t *buffer_a, const int32_t* buffer_b, int32_t * buffer, size_t length) { sub_core(buffer_a, buffer_b, buffer, length); }
  void sub(const uint16_t *buffer_a, const uint16_t* buffer_b, uint16_t * buffer, size_t length) { sub_core(buffer_a, buffer_b, buffer, length); }
  void sub(const uint32_t *buffer_a, const uint32_t* buffer_b, uint32_t * buffer, size_t length) { sub_core(buffer_a, buffer_b, buffer, length); }
  void sub(const wipp::wipp_complex_t *buffer_a, const wipp::wipp_complex_t* buffer_b, wipp::wipp_complex_t * buffer, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
      {
	  buffer[i].re = buffer_b[i].re - buffer_a[i].re;
	  buffer[i].im = buffer_b[i].im - buffer_a[i].im;
      }
  }




  template<typename T>
  void mult_core(const T *buffer_a, const T *buffer_b, T* buffer, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer[i] = buffer_a[i]*buffer_b[i];
  }
  template<typename T>
  void mult_core(const T *buffer_a,T *buffer_b, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer_b[i] = buffer_a[i]*buffer_b[i];
  }


  void mult(const double *buffer_a, const double *buffer_b, double *buffer, size_t length) { mult_core(buffer_a, buffer_b, buffer,length); }
  void mult(const float *buffer_a, const float *buffer_b, float *buffer, size_t length) { mult_core(buffer_a, buffer_b, buffer,length); }
  void mult(const int16_t *buffer_a, const int16_t *buffer_b, int16_t *buffer, size_t length) { mult_core(buffer_a, buffer_b, buffer,length); }
  void mult(const int32_t *buffer_a, const int32_t *buffer_b, int32_t *buffer, size_t length) { mult_core(buffer_a, buffer_b, buffer,length); }
  void mult(const uint16_t *buffer_a, const uint16_t *buffer_b, uint16_t *buffer, size_t length) { mult_core(buffer_a, buffer_b, buffer,length); }
  void mult(const uint32_t *buffer_a, const uint32_t *buffer_b, uint32_t *buffer, size_t length) { mult_core(buffer_a, buffer_b, buffer, length); }

  void mult(const double *buffer_a, double *buffer_b, size_t length) { mult_core(buffer_a, buffer_b, length); }
  void mult(const float *buffer_a, float *buffer_b, size_t length) { mult_core(buffer_a, buffer_b, length); }
  void mult(const int16_t *buffer_a, int16_t *buffer_b, size_t length) { mult_core(buffer_a, buffer_b, length); }
  void mult(const int32_t *buffer_a, int32_t *buffer_b, size_t length) { mult_core(buffer_a, buffer_b, length); }
  void mult(const uint16_t *buffer_a, uint16_t *buffer_b, size_t length) { mult_core(buffer_a, buffer_b, length); }
  void mult(const uint32_t *buffer_a, uint32_t *buffer_b, uint32_t *buffer, size_t length) { mult_core(buffer_a, buffer_b, length); }

  void mult(const double *buffer_a, wipp_complex_t *buffer_b, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
      {
	  buffer_b[i].re *= buffer_a[i];
	  buffer_b[i].im *= buffer_a[i];
      }
  }

  void mult(const wipp_complex_t *buffer_a, wipp_complex_t *buffer_b, size_t length)
  {
      // (a + ib)* (c + id) = ac + iad + ibc - bd = (ac - db) +i(ad + bc)
      wipp_complex_t aux;
      for (size_t i = 0; i < length; ++i)
      {
	  aux = buffer_b[i];
	  buffer_b[i].re = buffer_a[i].re*aux.re - buffer_a[i].im*aux.im;
	  buffer_b[i].im = buffer_a[i].re*aux.im + buffer_a[i].im*aux.re;
      }
  }

  void mult(const wipp_complex_t *buffer_a, const wipp_complex_t *buffer_b, wipp_complex_t *buffer, size_t length)
  {
      // (a + ib)* (c + id) = ac + iad + ibc - bd = (ac - db) +i(ad + bc)
      for (size_t i = 0; i < length; ++i)
      {
	  buffer[i].re = buffer_a[i].re*buffer_b[i].re - buffer_a[i].im*buffer_b[i].im;
	  buffer[i].im = buffer_a[i].re*buffer_b[i].im + buffer_a[i].im*buffer_b[i].re;
      }
  }

  template<typename T>
  void div_core(const T* buffer_a, const T *buffer_b, T* buffer, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer[i] = buffer_b[i]/buffer_a[i];
  }

  template<typename T>
  void div_core(const T* buffer_a, T *buffer_b, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
      {
	  buffer_b[i] /= buffer_a[i];
      }
  }

  void div(const double *buffer_a, const double *buffer_b, double *buffer, size_t length) { div_core(buffer_a, buffer_b, buffer, length); }
  void div(const float *buffer_a, const float *buffer_b, float *buffer, size_t length) { div_core(buffer_a, buffer_b, buffer, length); }
  void div(const int16_t *buffer_a, const int16_t *buffer_b, int16_t *buffer, size_t length) { div_core(buffer_a, buffer_b, buffer, length); }
  void div(const int32_t *buffer_a, const int32_t *buffer_b, int32_t *buffer, size_t length) { div_core(buffer_a, buffer_b, buffer, length); }
  void div(const uint16_t *buffer_a, const uint16_t *buffer_b, uint16_t *buffer, size_t length) { div_core(buffer_a, buffer_b, buffer, length); }
  void div(const uint32_t *buffer_a, const uint32_t *buffer_b, uint32_t *buffer, size_t length) { div_core(buffer_a, buffer_b, buffer, length); }
  void div(const double *buffer_a, double *buffer_b, size_t length) { div_core(buffer_a, buffer_b, length); }
  void div(const float *buffer_a, float *buffer_b, size_t length) { div_core(buffer_a, buffer_b, length); }
  void div(const int16_t *buffer_a, int16_t *buffer_b, size_t length) { div_core(buffer_a, buffer_b, length); }
  void div(const int32_t *buffer_a, int32_t *buffer_b, size_t length) { div_core(buffer_a, buffer_b, length); }
  void div(const uint16_t *buffer_a, uint16_t *buffer_b, size_t length) { div_core(buffer_a, buffer_b, length); }
  void div(const uint32_t *buffer_a, uint32_t *buffer_b, size_t length) { div_core(buffer_a, buffer_b, length); }

  void div(const wipp_complex_t *buffer_a, const wipp_complex_t *buffer_b, wipp_complex_t *buffer, size_t length)
  {
      // (a + jb)/(c + jd) = (c - jd)(a + jb)/(c2 + d2) = (ca + jcb - jda + db)/(c2 + d2) =
      // = (ca + db)/(c2 + d2) + j (cb - da)/(c2 + d2)
      for (size_t i = 0; i < length; ++i)
      {
	  buffer[i].re = (buffer_a[i].re*buffer_b[i].re + buffer_a[i].im*buffer_b[i].im)
			 /
			 (buffer_a[i].re*buffer_a[i].re + buffer_a[i].im*buffer_a[i].im);

	  buffer[i].im = (buffer_a[i].re*buffer_b[i].im + buffer_a[i].im*buffer_b[i].re)
			 /
			 (buffer_a[i].re*buffer_a[i].re + buffer_a[i].im*buffer_a[i].im);
      }
  }

  void div(const wipp_complex_t *buffer_a, wipp_complex_t *buffer_b, size_t length)
  {
      div(buffer_b, buffer_b, buffer_b, length);
  }



  template<typename T>
  void addC_core(T C, T *buffer, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer[i] += C;
  }

  template<typename T>
  void addC_core(T C, const T *buffer_in, T *buffer_out, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer_out[i] = buffer_in[i] + C;
  }

  void addC(double C, const double *buffer_in, double *buffer_out, size_t length) { addC_core(C, buffer_in, buffer_out, length); }
  void addC(float C, const float *buffer_in, float *buffer_out, size_t length) { addC_core(C, buffer_in, buffer_out, length); }
  void addC(int16_t C, const int16_t *buffer_in, int16_t *buffer_out, size_t length) { addC_core(C, buffer_in, buffer_out, length); }
  void addC(int32_t C, const int32_t *buffer_in, int32_t *buffer_out, size_t length) { addC_core(C, buffer_in, buffer_out, length); }
  void addC(uint16_t C, const uint16_t *buffer_in, uint16_t *buffer_out, size_t length) { addC_core(C, buffer_in, buffer_out, length); }
  void addC(uint32_t C, const uint32_t *buffer_in, uint32_t *buffer_out, size_t length) { addC_core(C, buffer_in, buffer_out, length); }
  void addC(double C, double *buffer, size_t length) { addC_core(C, buffer, length); }
  void addC(float C, float *buffer, size_t length) { addC_core(C, buffer, length); }
  void addC(int16_t C, int16_t *buffer, size_t length) { addC_core(C, buffer, length); }
  void addC(int32_t C, int32_t *buffer, size_t length) { addC_core(C, buffer, length); }
  void addC(uint16_t C, uint16_t *buffer, size_t length) { addC_core(C, buffer, length); }
  void addC(uint32_t C, uint32_t *buffer, size_t length) { addC_core(C, buffer, length); }



  template<typename T>
  void subC_core(T C, T *buffer, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer[i] -= C;
  }

  template<typename T>
  void subC_core(T C, const T *buffer_in, T *buffer_out, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer_out[i] = buffer_in[i] - C;
  }

  void subC(double C, const double *buffer_in, double *buffer_out, size_t length) { subC_core(C, buffer_in, buffer_out, length); }
  void subC(float C, const float *buffer_in, float *buffer_out, size_t length) { subC_core(C, buffer_in, buffer_out, length); }
  void subC(int16_t C, const int16_t *buffer_in, int16_t *buffer_out, size_t length) { subC_core(C, buffer_in, buffer_out, length); }
  void subC(int32_t C, const int32_t *buffer_in, int32_t *buffer_out, size_t length) { subC_core(C, buffer_in, buffer_out, length); }
  void subC(uint16_t C, const uint16_t *buffer_in, uint16_t *buffer_out, size_t length) { subC_core(C, buffer_in, buffer_out, length); }
  void subC(uint32_t C, const uint32_t *buffer_in, uint32_t *buffer_out, size_t length) { subC_core(C, buffer_in, buffer_out, length); }
  void subC(double C, double *buffer, size_t length) { subC_core(C, buffer, length); }
  void subC(float C, float *buffer, size_t length) { subC_core(C, buffer, length); }
  void subC(int16_t C, int16_t *buffer, size_t length) { subC_core(C, buffer, length); }
  void subC(int32_t C, int32_t *buffer, size_t length) { subC_core(C, buffer, length); }
  void subC(uint16_t C, uint16_t *buffer, size_t length) { subC_core(C, buffer, length); }
  void subC(uint32_t C, uint32_t *buffer, size_t length) { subC_core(C, buffer, length); }





  template<typename T>
  void multC_core(T C, T *buffer, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer[i] *= C;
  }

  template<typename T>
  void multC_core(T C, const T *buffer_in, T *buffer_out, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer_out[i] = buffer_in[i] * C;
  }

  void multC(double C, const double *buffer_in, double *buffer_out, size_t length) { multC_core(C, buffer_in, buffer_out, length); }
  void multC(float C, const float *buffer_in, float *buffer_out, size_t length) { multC_core(C, buffer_in, buffer_out, length); }
  void multC(int16_t C, const int16_t *buffer_in, int16_t *buffer_out, size_t length) { multC_core(C, buffer_in, buffer_out, length); }
  void multC(int32_t C, const int32_t *buffer_in, int32_t *buffer_out, size_t length) { multC_core(C, buffer_in, buffer_out, length); }
  void multC(uint16_t C, const uint16_t *buffer_in, uint16_t *buffer_out, size_t length) { multC_core(C, buffer_in, buffer_out, length); }
  void multC(uint32_t C, const uint32_t *buffer_in, uint32_t *buffer_out, size_t length) { multC_core(C, buffer_in, buffer_out, length); }
  void multC(double C, double *buffer, size_t length) { multC_core(C, buffer, length); }
  void multC(float C, float *buffer, size_t length) { multC_core(C, buffer, length); }
  void multC(int16_t C, int16_t *buffer, size_t length) { multC_core(C, buffer, length); }
  void multC(int32_t C, int32_t *buffer, size_t length) { multC_core(C, buffer, length); }
  void multC(uint16_t C, uint16_t *buffer, size_t length) { multC_core(C, buffer, length); }
  void multC(uint32_t C, uint32_t *buffer, size_t length) { multC_core(C, buffer, length); }



  template<typename T>
  void divC_core(T C,T *buffer, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer[i] /= C;
  }
  template<typename T>
  void divC_core(T C, const T *buffer_in, T *buffer_out, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer_out[i] = buffer_in[i]/C;
  }
  void divC(double C, const double *buffer_in, double *buffer_out, size_t length) { divC_core(C, buffer_in, buffer_out, length); }
  void divC(float C, const float *buffer_in, float *buffer_out, size_t length) { divC_core(C, buffer_in, buffer_out, length); }
  void divC(int16_t C, const int16_t *buffer_in, int16_t *buffer_out, size_t length) { divC_core(C, buffer_in, buffer_out, length); }
  void divC(int32_t C, const int32_t *buffer_in, int32_t *buffer_out, size_t length) { divC_core(C, buffer_in, buffer_out, length); }
  void divC(uint16_t C, const uint16_t *buffer_in, uint16_t *buffer_out, size_t length) { divC_core(C, buffer_in, buffer_out, length); }
  void divC(uint32_t C, const uint32_t *buffer_in, uint32_t *buffer_out, size_t length) { divC_core(C, buffer_in, buffer_out, length); }
  void divC(double C, double *buffer, size_t length) { divC_core(C, buffer, length); }
  void divC(float C, float *buffer, size_t length) { divC_core(C, buffer, length); }
  void divC(int16_t C, int16_t *buffer, size_t length) { divC_core(C, buffer, length); }
  void divC(int32_t C, int32_t *buffer, size_t length) { divC_core(C, buffer, length); }
  void divC(uint16_t C, uint16_t *buffer, size_t length) { divC_core(C, buffer, length); }
  void divC(uint32_t C, uint32_t *buffer, size_t length) { divC_core(C, buffer, length); }


  template<typename T>
  void sqrt_core(T *buffer, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer[i] *= buffer[i];
  }

  template<typename T>
  void sqrt_core(const T *buffer_in, T* buffer_out, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer_out[i] = buffer_in[i] * buffer_in[i];
  }

  void sqrt(double *buffer, size_t length){ sqrt_core(buffer, length);}
  void sqrt(float *buffer, size_t length){ sqrt_core(buffer, length);}
  void sqrt(int16_t *buffer, size_t length){ sqrt_core(buffer, length);}
  void sqrt(int32_t *buffer, size_t length){ sqrt_core(buffer, length);}
  void sqrt(uint16_t *buffer, size_t length){ sqrt_core(buffer, length);}
  void sqrt(uint32_t *buffer, size_t length){ sqrt_core(buffer, length);}

  void sqrt(const double *buffer_in, double *buffer_out, size_t length){ sqrt_core(buffer_in, buffer_out, length);}
  void sqrt(const float *buffer_in, float *buffer_out, size_t length){ sqrt_core(buffer_in, buffer_out, length);}
  void sqrt(const int16_t *buffer_in, int16_t *buffer_out, size_t length){ sqrt_core(buffer_in, buffer_out, length);}
  void sqrt(const int32_t *buffer_in, int32_t *buffer_out, size_t length){ sqrt_core(buffer_in, buffer_out, length);}
  void sqrt(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length){ sqrt_core(buffer_in, buffer_out, length);}
  void sqrt(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length){ sqrt_core(buffer_in, buffer_out, length);}



  template<typename T>
  void abs_core(T *buffer, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer[i] = fabs(buffer[i]);
  }

  template<typename T>
  void abs_core(const T *buffer_in, T* buffer_out, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer_out[i] = fabs(buffer_in[i]);
  }

  void abs(double *buffer, size_t length){ abs_core(buffer, length);}
  void abs(float *buffer, size_t length){ abs_core(buffer, length);}
  void abs(int16_t *buffer, size_t length){ abs_core(buffer, length);}
  void abs(int32_t *buffer, size_t length){ abs_core(buffer, length);}
  void abs(uint16_t *buffer, size_t length){ abs_core(buffer, length);}
  void abs(uint32_t *buffer, size_t length){ abs_core(buffer, length);}

  void abs(const double *buffer_in, double *buffer_out, size_t length){ abs_core(buffer_in, buffer_out, length);}
  void abs(const float *buffer_in, float *buffer_out, size_t length){ abs_core(buffer_in, buffer_out, length);}
  void abs(const int16_t *buffer_in, int16_t *buffer_out, size_t length){ abs_core(buffer_in, buffer_out, length);}
  void abs(const int32_t *buffer_in, int32_t *buffer_out, size_t length){ abs_core(buffer_in, buffer_out, length);}
  void abs(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length){ abs_core(buffer_in, buffer_out, length);}
  void abs(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length){ abs_core(buffer_in, buffer_out, length);}



  template<typename T>
  void logn_core(const T *buffer_in, T *buffer_out, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer_out[i] = log(buffer_in[i]);
  }
  template<typename T>
  void logn_core(T *buffer, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  buffer[i] = log(buffer[i]);
  }

  void logn(double *buffer, size_t length){ logn_core(buffer, length);}
  void logn(float *buffer, size_t length){ logn_core(buffer, length);}
  void logn(int16_t *buffer, size_t length){ logn_core(buffer, length);}
  void logn(int32_t *buffer, size_t length){ logn_core(buffer, length);}
  void logn(uint16_t *buffer, size_t length){ logn_core(buffer, length);}
  void logn(uint32_t *buffer, size_t length){ logn_core(buffer, length);}

  void logn(const double *buffer_in, double *buffer_out, size_t length){ logn_core(buffer_in, buffer_out, length);}
  void logn(const float *buffer_in, float *buffer_out, size_t length){ logn_core(buffer_in, buffer_out, length);}
  void logn(const int16_t *buffer_in, int16_t *buffer_out, size_t length){ logn_core(buffer_in, buffer_out, length);}
  void logn(const int32_t *buffer_in, int32_t *buffer_out, size_t length){ logn_core(buffer_in, buffer_out, length);}
  void logn(const uint16_t *buffer_in, uint16_t *buffer_out, size_t length){ logn_core(buffer_in, buffer_out, length);}
  void logn(const uint32_t *buffer_in, uint32_t *buffer_out, size_t length){ logn_core(buffer_in, buffer_out, length);}

  void real2complex(const double *real, const double *imag, wipp_complex_t *complex, size_t length)
  {
      if (real == NULL)
	  if (imag == NULL)
	      for (size_t i = 0; i < length; ++i)
	      {
		  complex[i].im = 0;
		  complex[i].re = 0;
	      }
	  else
	      for (size_t i = 0; i < length; ++i)
	      {
		  complex[i].im = imag[i];
		  complex[i].re = 0;
	      }
      else
      {
	  if (imag == NULL)
	      for (size_t i = 0; i < length; ++i)
	      {
		  complex[i].im = 0;
		  complex[i].re = real[i];
	      }
	  else
	      for (size_t i = 0; i < length; ++i)
	      {
		  complex[i].im = imag[i];
		  complex[i].re = real[i];
	      }
      }
  }

  void real(const wipp_complex_t *complex, double *real, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  real[i] = complex[i].re;
  }

  void imag(const wipp_complex_t *complex, double *imag, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  imag[i] = complex[i].im;
  }


  void conj(const wipp_complex_t *complex_in, wipp_complex_t *complex_out, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
      {
	  complex_out[i].im = -complex_in[i].im;
	  complex_out[i].re =  complex_in[i].re;
      }
  }

  void conj(wipp_complex_t *complex, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
	  complex[i].im = -complex[i].im;
  }

  void conjFlip(const wipp_complex_t *complex_in, wipp_complex_t *complex_out, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
      {
	  complex_out[i].re =   complex_in[length-i-1].re;
	  complex_out[i].im = - complex_in[length-i-1].im;
      }
  }

  void polar2cart(const double *module, const double *phase, wipp_complex_t *cart, size_t length)
  {
      for (size_t i = 0; i < length; ++i)
      {
	  cart[i].re = module[i]*cos(phase[i]);
	  cart[i].im = module[i]*sin(phase[i]);
      }
  }

}

