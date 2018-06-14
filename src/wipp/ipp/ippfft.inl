/*
* ippfft.inl
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
#include <wipp/wippfft.h>

#include "IPPException.h"

#include <ipps.h>
#include <ippcore.h>

#include <memory>
#include <math.h>

#define CCS_FORMAT_EXTRA_LENGTH 2

namespace wipp {

    struct wipp_fft_t_ {
        int length;
        int order;

        int internalBufferSize;
        int specificationStructureBufferSize;
        int specificationStructureSize;
        int spectrumLength;

        double *spectrum;
        Ipp8u *internalBuffer;
        Ipp8u *specificationStructureBuffer;
        Ipp8u *charSpecificationStructure;
        IppsFFTSpec_R_64f *specificationStructure;

        void init_variables(size_t length_) {
            order = (int) log2(length_ - 1) + 1;
            length = (1 << order);
            spectrumLength = length + CCS_FORMAT_EXTRA_LENGTH;
            spectrum = new double[spectrumLength];
            ippsFFTGetSize_R_64f(order, IPP_FFT_DIV_INV_BY_N, ippAlgHintNone,
                                 &specificationStructureSize, &specificationStructureBufferSize, &internalBufferSize);
        }

        void allocateBuffers() {
            charSpecificationStructure = (Ipp8u*) ippMalloc(specificationStructureSize);
            specificationStructure = (IppsFFTSpec_R_64f *) charSpecificationStructure;
            specificationStructureBuffer = reinterpret_cast<Ipp8u*>((specificationStructureBufferSize > 0) ? ippMalloc(specificationStructureBufferSize) : nullptr);
            internalBuffer = reinterpret_cast<Ipp8u*>((internalBufferSize > 0) ? ippMalloc(internalBufferSize) : nullptr);
            spectrum = new double[spectrumLength];
        }

        void initSpecifications() {
            allocateBuffers();
            ippsFFTInit_R_64f(&specificationStructure, order, IPP_FFT_DIV_INV_BY_N, ippAlgHintFast,
                              charSpecificationStructure, specificationStructureBuffer);
        }


        wipp_fft_t_(size_t length) {
            init_variables(length);
            initSpecifications();
        }

        ~wipp_fft_t_() {
            if (internalBufferSize > 0) ippFree(internalBuffer);
            if (specificationStructureBufferSize > 0) ippFree(specificationStructureBuffer);
            if (specificationStructureSize > 0) ippFree(specificationStructure);
            delete[] spectrum;
        }


        void delete_fft(wipp_fft_t **fft) {
            delete *fft;
            fft = nullptr;
        }


    };


    void check_lengths(wipp_fft_t *fft, int signalLength, int spectrumLength) {
        if (spectrumLength != fft->spectrumLength || signalLength != fft->length)
            throw IPPException("Either the signal or the spectrum buffer lengths are wrong");
    }

    wipp_fft_t *fft(const double *signal, int signalLength, double *spectrum, int spectrumLength,
                    wipp_fft_t *fft) {
        check_lengths(fft, signalLength, spectrumLength);
        ippsFFTFwd_RToCCS_64f(signal, spectrum, fft->specificationStructure, fft->internalBuffer);
    }

    wipp_fft_t *ifft(const double *spectrum, int spectrumLength, double *signal, int signalLength,
                     wipp_fft_t *fft) {
        check_lengths(fft, signalLength, spectrumLength);
        ippsFFTInv_CCSToR_64f(spectrum, signal, fft->specificationStructure, fft->internalBuffer);
    }

    void init_fft(wipp_fft_t **fft, size_t length) {
        *fft =  (length <= 0) ? nullptr : new wipp_fft_t_(length);
    }


    void delete_fft(wipp_fft_t **fft) {
        delete *fft;
        *fft = nullptr;
    }

    wipp_fft_t* fft(const double *signal, double *spectrum, wipp_fft_t* wipp_fft) {
        ippsFFTFwd_RToCCS_64f(signal, spectrum, wipp_fft->specificationStructure, wipp_fft->internalBuffer);
    }

    wipp_fft_t* ifft(const double *spectrum, double *signal, wipp_fft_t* wipp_fft) {
        ippsFFTInv_CCSToR_64f(spectrum, signal, wipp_fft->specificationStructure, wipp_fft->internalBuffer);
    }

    int get_fft_length(wipp_fft_t* wipp_fft) {
        return wipp_fft->length;
    }

}
