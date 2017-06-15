
#include <typeinfo>

namespace wipp {


    template<typename T>
    struct wipp_circular_buffer_template_t_ {
        T *buffer;
        size_t data_type;
        size_t size;
        size_t occupancy;
        size_t position;
    };

    struct wipp_circular_buffer_t_ {
        void *buffer;
        size_t data_type;
        size_t size;
        size_t occupancy;
        size_t position;
    };

    typedef wipp_circular_buffer_template_t_<double> wipp_circular_buffer_double_t_;
    typedef wipp_circular_buffer_template_t_<float> wipp_circular_buffer_float_t_;
    typedef wipp_circular_buffer_template_t_<int16_t> wipp_circular_buffer_int16_t_t_;
    typedef wipp_circular_buffer_template_t_<int32_t> wipp_circular_buffer_int32_t_t_;
    typedef wipp_circular_buffer_template_t_<uint16_t> wipp_circular_buffer_uint16_t_t_;
    typedef wipp_circular_buffer_template_t_<uint32_t> wipp_circular_buffer_uint32_t_t_;

    template<typename T>
    void
    init_cirular_buffer_core(wipp_circular_buffer_template_t_<T> **cb, size_t size, T *init_values, size_t length) {
        *cb = new wipp_circular_buffer_template_t_<T>();
        (*cb)->size = size;
        (*cb)->occupancy = 0;
        (*cb)->position = 0;
        (*cb)->buffer = new T[(*cb)->size];
        (*cb)->data_type = typeid(T).hash_code();
    }

    void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, double *init_values, size_t length) {
        init_cirular_buffer_core(reinterpret_cast<wipp_circular_buffer_double_t_ **>(buffer), size, init_values,
                                 length);
    }

    void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, float *init_values, size_t length) {
        init_cirular_buffer_core(reinterpret_cast<wipp_circular_buffer_float_t_ **>(buffer), size, init_values, length);
    }

    void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, int16_t *init_values, size_t length) {
        init_cirular_buffer_core(reinterpret_cast<wipp_circular_buffer_int16_t_t_ **>(buffer), size, init_values,
                                 length);
    }

    void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, int32_t *init_values, size_t length) {
        init_cirular_buffer_core(reinterpret_cast<wipp_circular_buffer_int32_t_t_ **>(buffer), size, init_values,
                                 length);
    }

    void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, uint16_t *init_values, size_t length) {
        init_cirular_buffer_core(reinterpret_cast<wipp_circular_buffer_uint16_t_t_ **>(buffer), size, init_values,
                                 length);
    }

    void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size, uint32_t *init_values, size_t length) {
        init_cirular_buffer_core(reinterpret_cast<wipp_circular_buffer_uint32_t_t_ **>(buffer), size, init_values,
                                 length);
    }

    void init_cirular_buffer(wipp_circular_buffer_t **buffer, size_t size);


    template<typename T>
    void delete_circular_buffer_core(wipp_circular_buffer_t_ **buffer) {
        delete[] reinterpret_cast<T *>((*buffer)->buffer);
        delete *buffer;
        *buffer = NULL;
    }

    void delete_circular_buffer(wipp_circular_buffer_t **buffer) {
        if (buffer != NULL && *buffer != NULL) {
            if (typeid(double).hash_code() == (*buffer)->data_type)
                delete_circular_buffer_core<double>(buffer);
            else if (typeid(float).hash_code() == (*buffer)->data_type)
                delete_circular_buffer_core<float>(buffer);
            else if (typeid(int16_t).hash_code() == (*buffer)->data_type)
                delete_circular_buffer_core<int16_t>(buffer);
            else if (typeid(int32_t).hash_code() == (*buffer)->data_type)
                delete_circular_buffer_core<int32_t>(buffer);
            else if (typeid(uint16_t).hash_code() == (*buffer)->data_type)
                delete_circular_buffer_core<uint16_t>(buffer);
            else if (typeid(uint32_t).hash_code() == (*buffer)->data_type)
                delete_circular_buffer_core<uint32_t>(buffer);
            *buffer = NULL;
        }
    }


    template<typename T>
    void cf_read_core(wipp_circular_buffer_template_t_<T> *cb, T *buffer, size_t length, size_t *stored) {
        size_t i = 0;
        for (;
                i < length && cb->occupancy > 0;
                ++i, cb->position = (cb->position + 1) % cb->size, --cb->occupancy) {
            buffer[i] = cb->buffer[cb->position];
        }
        *stored = i;
    }

    void cf_read(wipp_circular_buffer_t *cb, double *buffer, size_t length, size_t *stored) {
        cf_read_core(reinterpret_cast<wipp_circular_buffer_double_t_ *>(cb), buffer, length, stored);
    }

    void cf_read(wipp_circular_buffer_t *cb, float *buffer, size_t length, size_t *stored) {
        cf_read_core(reinterpret_cast<wipp_circular_buffer_float_t_ *>(cb), buffer, length, stored);
    }

    void cf_read(wipp_circular_buffer_t *cb, int16_t *buffer, size_t length, size_t *stored) {
        cf_read_core(reinterpret_cast<wipp_circular_buffer_int16_t_t_ *>(cb), buffer, length, stored);
    }

    void cf_read(wipp_circular_buffer_t *cb, int32_t *buffer, size_t length, size_t *stored) {
        cf_read_core(reinterpret_cast<wipp_circular_buffer_int32_t_t_ *>(cb), buffer, length, stored);
    }

    void cf_read(wipp_circular_buffer_t *cb, uint16_t *buffer, size_t length, size_t *stored) {
        cf_read_core(reinterpret_cast<wipp_circular_buffer_uint16_t_t_ *>(cb), buffer, length, stored);
    }

    void cf_read(wipp_circular_buffer_t *cb, uint32_t *buffer, size_t length, size_t *stored) {
        cf_read_core(reinterpret_cast<wipp_circular_buffer_uint32_t_t_ *>(cb), buffer, length, stored);
    }

    template<typename T>
    void cf_next_core(const wipp_circular_buffer_template_t_<T> *cb, T *buffer, size_t length, size_t *stored) {
        size_t i = 0;
        size_t position = cb->position;
        size_t occupancy = cb->occupancy;
        for (;
                i < length && occupancy > 0;
                ++i, position = (position + 1) % cb->size, --occupancy) {
            buffer[i] = cb->buffer[position];
        }
        *stored = i;
    }

    void cf_next(const wipp_circular_buffer_t *cb, double *buffer, size_t length, size_t *stored) {
        cf_next_core(reinterpret_cast<const wipp_circular_buffer_double_t_ *>(cb), buffer, length, stored);
    }

    void cf_next(const wipp_circular_buffer_t *cb, float *buffer, size_t length, size_t *stored) {
        cf_next_core(reinterpret_cast<const wipp_circular_buffer_float_t_ *>(cb), buffer, length, stored);
    }

    void cf_next(const wipp_circular_buffer_t *cb, int16_t *buffer, size_t length, size_t *stored) {
        cf_next_core(reinterpret_cast<const wipp_circular_buffer_int16_t_t_ *>(cb), buffer, length, stored);
    }

    void cf_next(const wipp_circular_buffer_t *cb, int32_t *buffer, size_t length, size_t *stored) {
        cf_next_core(reinterpret_cast<const wipp_circular_buffer_int32_t_t_ *>(cb), buffer, length, stored);
    }

    void cf_next(const wipp_circular_buffer_t *cb, uint16_t *buffer, size_t length, size_t *stored) {
        cf_next_core(reinterpret_cast<const wipp_circular_buffer_uint16_t_t_ *>(cb), buffer, length, stored);
    }

    void cf_next(const wipp_circular_buffer_t *cb, uint32_t *buffer, size_t length, size_t *stored) {
        cf_next_core(reinterpret_cast<const wipp_circular_buffer_uint32_t_t_ *>(cb), buffer, length, stored);
    }


    template<typename T>
    void cf_pointer_core(const wipp_circular_buffer_t *cf_buffer, const T *pointer) {
        // Might be interesting to check data type here, to avoid
        // Segmentation fault in case of missuse of the function.
        // However, there would be some overload here.
        //    cf_buffer->data_type
        pointer = reinterpret_cast<T *>(cf_buffer->buffer);
    }

    void cf_pointer(const wipp_circular_buffer_t *buffer, const double *pointer) { cf_pointer_core(buffer, pointer); }

    void cf_pointer(const wipp_circular_buffer_t *buffer, const float *pointer) { cf_pointer_core(buffer, pointer); }

    void cf_pointer(const wipp_circular_buffer_t *buffer, const int16_t *pointer) { cf_pointer_core(buffer, pointer); }

    void cf_pointer(const wipp_circular_buffer_t *buffer, const int32_t *pointer) { cf_pointer_core(buffer, pointer); }

    void cf_pointer(const wipp_circular_buffer_t *buffer, const uint16_t *pointer) { cf_pointer_core(buffer, pointer); }

    void cf_pointer(const wipp_circular_buffer_t *buffer, const uint32_t *pointer) { cf_pointer_core(buffer, pointer); }


    template<typename T>
    void cf_write_core(wipp_circular_buffer_template_t_<T> *cb, T *buffer, size_t length, size_t *stored) {
        size_t i = 0;
        for (size_t k = (cb->position + cb->occupancy) % cb->size;
             i < length && cb->occupancy < cb->size;
             ++i, k = (k + 1) % cb->size, ++cb->occupancy) {
            cb->buffer[k] = buffer[i];
        }
        *stored = i;
    }

    void cf_write(wipp_circular_buffer_t *cb, double *buffer, size_t length, size_t *stored) {
        cf_write_core(reinterpret_cast<wipp_circular_buffer_double_t_ *>(cb), buffer, length, stored);
    }

    void cf_write(wipp_circular_buffer_t *cb, float *buffer, size_t length, size_t *stored) {
        cf_write_core(reinterpret_cast<wipp_circular_buffer_float_t_ *>(cb), buffer, length, stored);
    }

    void cf_write(wipp_circular_buffer_t *cb, int16_t *buffer, size_t length, size_t *stored) {
        cf_write_core(reinterpret_cast<wipp_circular_buffer_int16_t_t_ *>(cb), buffer, length, stored);
    }

    void cf_write(wipp_circular_buffer_t *cb, int32_t *buffer, size_t length, size_t *stored) {
        cf_write_core(reinterpret_cast<wipp_circular_buffer_int32_t_t_ *>(cb), buffer, length, stored);
    }

    void cf_write(wipp_circular_buffer_t *cb, uint16_t *buffer, size_t length, size_t *stored) {
        cf_write_core(reinterpret_cast<wipp_circular_buffer_uint16_t_t_ *>(cb), buffer, length, stored);
    }

    void cf_write(wipp_circular_buffer_t *cb, uint32_t *buffer, size_t length, size_t *stored) {
        cf_write_core(reinterpret_cast<wipp_circular_buffer_uint32_t_t_ *>(cb), buffer, length, stored);
    }


    void cf_size(wipp_circular_buffer_t *cb, size_t *size) {
        *size = cb->size;
    }

    void cf_occupancy(wipp_circular_buffer_t *cb, size_t *occupancy) {
        *occupancy = cb->occupancy;
    }

    void cf_free(wipp_circular_buffer_t *cb, size_t *free) {
        *free = cb->size - cb->occupancy;
    }

    void cf_skip(wipp_circular_buffer_t *cb, size_t length, size_t *skipped) {
        if (length > cb->occupancy) length = cb->occupancy;
        cb->position = (cb->position + length) % cb->size;
        cb->occupancy -= length;
        if (skipped != NULL)
            *skipped = length;
    }

}