/*
* ippfilter.inl
* Copyright 2016 (c) Jordi Adell
* Created on: 2015
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
#include <wipp/wippfilter.h>
#include <wipp/wippexception.h>
#include <wipp/wipputils.h>

#include <ippcore.h>
#include <ippvm.h>
#include <ipps.h>

#include <string.h>
#include <math.h>
#include <algorithm>
#include <iostream>


namespace wipp {

    void window_hann(double *frame, size_t length) {
        ippsWinHann_64f_I(frame, length);
    }

    void window_hann(float *frame, size_t length) {
        ippsWinHann_32f_I(frame, length);
    }

    void window_hann(int16_t *frame, size_t length) {
        ippsWinHann_16s_I(frame, length);
    }

    template <typename T>
    void window_hann_noIPP(const T* frame_in, T* frame_out, size_t length) {
        Ipp64f intermediate_buffer[length];
        copyBuffer(frame_in, intermediate_buffer, length);
        window_hann(intermediate_buffer, length);
        copyBuffer(intermediate_buffer, frame_out, length);
    }

    void window_hann(uint16_t *frame, size_t length) {
        window_hann_noIPP(frame, frame, length);
    }

    void window_hann(int32_t *frame, size_t length){
        window_hann_noIPP(frame, frame, length);
    }

    void window_hann(uint32_t *frame, size_t length) {
        window_hann_noIPP(frame, frame, length);
    }

    void window_hamming(double *frame, size_t length) {
        ippsWinHamming_64f_I(frame, length);
    }

    void window_hamming(float *frame, size_t length) {
        ippsWinHamming_32f_I(frame, length);
    }

    void window_hamming(int16_t *frame, size_t length) {
        ippsWinHamming_16s_I(frame, length);
    }

    template <typename T>
    void window_hamming_noIPP(const T* frame_in, T* frame_out, size_t length) {
        Ipp64f intermediate_buffer[length];
        copyBuffer(frame_in, intermediate_buffer, length);
        window_hamming(intermediate_buffer, length);
        copyBuffer(intermediate_buffer, frame_out, length);
    }

    void window_hamming(uint16_t *frame, size_t length) {
        window_hamming_noIPP(frame, frame, length);
    }

    void window_hamming(int32_t *frame, size_t length){
        window_hamming_noIPP(frame, frame, length);
    }

    void window_hamming(uint32_t *frame, size_t length) {
        window_hamming_noIPP(frame, frame, length);
    }



    template <typename T>
    void window_core(T *frame, size_t length, wipp_window_t window_type) {
        if (window_type == wippHANN) window_hann(frame, length);
        if (window_type == wippHAMMING) window_hamming(frame, length);
        if (window_type == wippRECTANGULAR) return;
    }

    void window(double *frame, size_t length, wipp_window_t window_type) {
        window_core(frame, length, window_type);
    }

    void window(float *frame, size_t length, wipp_window_t window_type) {
        window_core(frame, length, window_type);
    }

    void window(int16_t *frame, size_t length, wipp_window_t window_type) {
        window_core(frame, length, window_type);
    }
    
    void window(int32_t *frame, size_t length, wipp_window_t window_type) {
        window_core(frame, length, window_type);
    }

    void window(uint16_t *frame, size_t length, wipp_window_t window_type) {
        window_core(frame, length, window_type);
    }

    void window(uint32_t *frame, size_t length, wipp_window_t window_type) {
        window_core(frame, length, window_type);
    }


    inline Ipp8u *fir_coefs_init_buffer(size_t length) {
        int bufferSize;
        ippsFIRGenGetBufferSize(length, &bufferSize);
        return new Ipp8u[bufferSize];
    }

    inline void fir_coefs_free_buffer(Ipp8u *buffer) {
        delete[] buffer;
    }


    void fir_coefs_rectangular(double fmin, double fmax, double *coefs, size_t length,
                                                 IppWinType window_type) {
        auto *buffer = fir_coefs_init_buffer(length);
        //auto status = ippsFIRGenBandpass_64f(fmin, fmax, coefs, log(length * 1.0F) / log(2.0F) + 0.5, window_type, ippTrue, buffer);
        auto status = ippsFIRGenBandpass_64f(fmin, fmax, coefs, length, window_type, ippTrue, buffer);
        if (status != ippStsNoErr)
            throw(WIppException(ippGetStatusString(status)));
        fir_coefs_free_buffer(buffer);
    }


    void fir_coefs_rectangular(double fmin, double fmax, double *coefs, size_t length, wipp_window_t window_type) {
        switch (window_type) {
            case wippHANN: fir_coefs_rectangular(fmin, fmax, coefs, length, ippWinHann); break;
            case wippHAMMING: fir_coefs_rectangular(fmin, fmax, coefs, length, ippWinHamming); break;
            case wippRECTANGULAR: fir_coefs_rectangular(fmin, fmax, coefs, length, ippWinRect); break;
            default:
                throw(WIppException("Unknown window type"));
        }
    }

    void wipp_sinc_time(double lowPassFreq, double *time, size_t length) {
        for (size_t i = 0; i < length; ++i)
            time[i] = (static_cast<double>(i) - length/2)*2*M_PI*lowPassFreq;
    }

    void wipp_sinc(double lowPassFreq, double *sinc, size_t length) {
        Ipp64f time[length], sinus[length];
        Ipp64f sum;

        wipp_sinc_time(lowPassFreq, time, length);

        ippsSin_64f_A26(time, sinus, length);
        ippsDiv_64f(time, sinus, sinc, length);
        sinc[length/2] = 1;
        ippsDivC_64f_I(M_PI, sinc, length);
        ippsSum_64f(sinc, length, &sum);
        ippsDivC_64f_I(sum, sinc, length);
    }

    void wipp_sinc(double fmin, double fmax, double *sinc, size_t length) {
        Ipp64f lowPassMin[length], lowPassMax[length];
        Ipp64f sumMax, sumMin;
        wipp_sinc(fmin, lowPassMin, length);
        wipp_sinc(fmax, lowPassMax, length);
        ippsSub_64f(lowPassMin, lowPassMax, sinc, length);
    }

    void wipp_sinc2(double lowPassFreq, double *sinc2, size_t length) {
        Ipp64f sum;
        wipp_sinc(lowPassFreq, sinc2, length);
        ippsSqr_64f_I(sinc2, length);
        ippsSum_64f(sinc2, length, &sum);
        ippsDivC_64f_I(sum, sinc2, length);
    }

    void wipp_sinc2(double fmin, double fmax, double *sinc2, size_t length) {
        Ipp64f cosineDelay[length];
        Ipp64f time[length];
        Ipp64f cosineTime[length];

        wipp_sinc_time((fmax+fmin)/2, cosineTime, length);
        wipp_sinc_time(fmax - fmin, time, length);
        ippsCos_64f_A26(cosineTime, cosineDelay, length);
        wipp_sinc2((fmax-fmin)/2, sinc2, length);
        ippsMul_64f_I(cosineDelay, sinc2, length);
        ippsMulC_64f_I(2, sinc2, length);
    }

    void fir_coefs_triangular(double fmin, double fmax, double *coefs, size_t length, wipp_window_t window_type) {
//        double bw = fmax - fmin;
//        fmin += (fmax - fmin)/3;
//        fmax -= (fmax - fmin)/3;
//        bw = fmax - fmin;
        wipp_sinc2(fmin, fmax, coefs, length);
        window(coefs, length, window_type);
    }

    void fir_coefs(double fmin, double fmax, double *coefs, size_t length,
                   wipp_window_t window_type, wipp_freq_shape_t freq_shape) {

        switch (freq_shape) {
            case wippfRECTANGULAR:
                fir_coefs_rectangular(fmin, fmax, coefs, length, window_type);
                break;
            case wippfTRIANGULAR:
                fir_coefs_triangular(fmin, fmax, coefs, length, window_type);
                break;
        }
    }

    void fir_coefs(double fmin, double fmax, double *coefs, size_t length, wipp_window_t window_type) {
        fir_coefs(fmin, fmax, coefs, length, window_type, wippfRECTANGULAR);
    }


    struct  wipp_fir_filter_t_ {

        int specification_size;
        int buffer_size;
        int taps_length;

        IppsFIRSpec_64f *spec;
        Ipp8u *buffer;
        Ipp64f *delay_line;
        Ipp64f *taps;

        wipp_fir_filter_t_() {
        }

        void allocate_memory() {
            delay_line = ippsMalloc_64f(taps_length-1);
            ippsFIRSRGetSize(taps_length, ipp64f, &specification_size, &buffer_size);
            buffer = ippsMalloc_8u(buffer_size);
            ippsZero_8u(buffer, buffer_size);
            spec =  reinterpret_cast<IppsFIRSpec_64f*>(ippsMalloc_8u(specification_size));
        }

        void init() {
            allocate_memory();
            ippsFIRSRInit_64f(taps, taps_length, ippAlgAuto, spec);
        }

        void setCoefs(const double *coefs, size_t length) {
            taps_length = length;
            taps = ippsMalloc_64f(taps_length);
            ippsCopy_64f(coefs, taps, length);
        }

        void free () {
            ippsFree(spec);
            ippsFree(buffer);
            ippsFree(delay_line);
            ippsFree(taps);
        }
    };

    void init_fir(wipp_fir_filter_t **fir, const double *coefs, size_t length) {
        *fir = new wipp_fir_filter_t();
        (*fir)->setCoefs(coefs, length);
        (*fir)->init();
    }



    void init_fir(wipp_fir_filter_t **fir, const double *coefs, size_t length, const double *pastValues) {
        init_fir(fir, coefs, length);
    }

    void delete_fir(wipp_fir_filter_t **fir) {
        if (*fir != nullptr) {
            (*fir)->free();
            delete (*fir);
            (*fir) = nullptr;
        }
    }

    void fir_filter(wipp_fir_filter_t *fir, double *signal, size_t length) {
        ippsFIRSR_64f(signal, signal, length, fir->spec, NULL, NULL, fir->buffer);
    }

    void fir_filter(wipp_fir_filter_t *fir, const double *signal_in, double *signal_out, size_t length) {
        ippsFIRSR_64f(signal_in, signal_out, length, fir->spec, NULL, NULL, fir->buffer);
    }


    void fir_get_coefs(wipp_fir_filter_t *fir, double *coefs, size_t length) {
        copyBuffer(fir->taps, coefs, std::min(length, static_cast<size_t>(fir->taps_length)));
    }





    struct  wipp_iir_filter_t_ {

        int state_size;
        int order;
        int buffer_size;
        int taps_length;

        IppsIIRState_64f *state;
        Ipp8u *buffer;
        Ipp64f *taps;
        Ipp64f *coefs_a;
        Ipp64f *coefs_b;
        int length_a;
        int length_b;

        wipp_iir_filter_t_() {
            coefs_a = nullptr;
            coefs_b = nullptr;
        }

        void allocate_memory() {
            ippsIIRGenGetBufferSize(order, &buffer_size);
            buffer = ippsMalloc_8u(buffer_size);
            ippsIIRGetStateSize_64f(order, &state_size);
            state = reinterpret_cast<IppsIIRState_64f*>(ippsMalloc_8u(state_size));
            taps_length = 2*(order+1);
            taps = new double[taps_length];
        }

        void setACoefs(const double *a_coefs, int a_length) {
            length_a = a_length;
            coefs_a = new double[a_length];
            ippsCopy_64f(a_coefs, coefs_a, length_a);
        }

        void setBCoefs(const double *b_coefs, int b_length) {
            length_b = b_length;
            coefs_b = new double[b_length];
            ippsCopy_64f(b_coefs, coefs_b, length_b);
        }


        void init() {
            order = std::max(length_a, length_b)-1;
            allocate_memory();
            ippsZero_64f(taps, taps_length);
            ippsCopy_64f(coefs_b, taps, length_b);
            ippsCopy_64f(coefs_a, &taps[order + 1], length_a);
            ippsIIRInit_64f(&state, taps, order, NULL, buffer);
        }


        void free() {
            delete[] taps;
            delete[] coefs_a;
            delete[] coefs_b;
//            ippsFree(buffer);
            ippsFree(state);
        }

    };


    void init_iir(wipp_iir_filter_t **iir,
                  const double *a_coefs, size_t a_length,
                  const double *b_coefs, size_t b_length) {
        *iir = new wipp_iir_filter_t();
        (*iir)->setACoefs(a_coefs, a_length);
        (*iir)->setBCoefs(b_coefs, b_length);
        (*iir)->init();

    }

    void init_iir(wipp_iir_filter_t **iir,
                  const double *a_coefs, size_t a_length, const double *b_coefs, size_t b_length,
                  const double *x_pastValues, const double *y_pastValues) {
        init_iir(iir, a_coefs, a_length, b_coefs, b_length);
    }

    void delete_iir(wipp_iir_filter_t **iir) {
        if ((*iir) != NULL) {
            (*iir)->free();
            *iir = NULL;
        }
    }

    void iir_filter(wipp_iir_filter_t *iir, double *signal, size_t length) {
        ippsIIR_64f_I(signal, length, iir->state);
    }

    void iir_filter(wipp_iir_filter_t *iir, const double *signal_in, double *signal_out, size_t length) {
        ippsIIR_64f(signal_in, signal_out,length,iir->state);
    }

}