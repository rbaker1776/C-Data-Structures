#ifndef CVECTOR_H_71621609F1DE
#define CVECTOR_H_71621609F1DE

#include <stdlib.h>
#include <stdio.h>


struct cvector_t;

static size_t _cvector_next_power_of_two(size_t n);

size_t _cvector_size(const struct cvector_t*);
size_t _cvector_capacity(const struct cvector_t*);
size_t _cvector_element_size(const struct cvector_t*);

void _cvector_free(struct cvector_t*);


#define _cvector_construct_type(type) { \
    .m_data = NULL,                     \
    .m_size = 0,                        \
    .m_capacity = 0,                    \
    .m_element_size = sizeof(type),     \
    _CVECTOR_METHODS                    \
}

#define _cvector_construct_size(type, size) {                        \
    .m_data = malloc(sizeof(type)*_cvector_next_power_of_two(size)), \
    .m_size = size,                                                  \
    .m_capacity = _cvector_next_power_of_two(size),                  \
    .m_element_size = sizeof(type),                                  \
    _CVECTOR_METHODS                                                 \
}

#define _cvector_construct_fill(type, size, fill) printf("3\n")

#define _CVECTOR_METHODS\
    .size = _cvector_size,\
    .capacity = _cvector_capacity,\
    .element_size = _cvector_element_size,\
    .free = _cvector_free

#define _CONSTRUCTOR_DISPATCH(type, size, fill, ARGC, ...) ARGC
#define cvector(...) _CONSTRUCTOR_DISPATCH(\
    __VA_ARGS__,\
    _cvector_construct_fill,\
    _cvector_construct_size,\
    _cvector_construct_type\
)(__VA_ARGS__)


struct cvector_t
{
     void* m_data;
    size_t m_size;
    size_t m_capacity;
    size_t m_element_size;

    size_t (*size)(const struct cvector_t*);
    size_t (*capacity)(const struct cvector_t*);
    size_t (*element_size)(const struct cvector_t*);

    void (*free)(struct cvector_t*);
};


static size_t _cvector_next_power_of_two(size_t n)
{
    n |= n >> 1;  // Let the MSB of n "trickle down"
    n |= n >> 2;  // to make n be one less than 
    n |= n >> 4;  // the next power of 2
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;
    return n + 1;
}

size_t _cvector_size(const struct cvector_t* cv) { return cv->m_size; }
size_t _cvector_capacity(const struct cvector_t* cv) { return cv->m_capacity; }
size_t _cvector_element_size(const struct cvector_t* cv) { return cv->m_element_size; }

void _cvector_free(struct cvector_t* cv)
{
    if (cv->m_data != NULL)
        free(cv->m_data);
    cv->m_size = 0;
    cv->m_capacity = 0;
    cv->m_data = NULL;
}


typedef struct cvector_t cvector_t;

#endif // CVECTOR_H_71621609F1DE
