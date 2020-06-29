#include <string.h>

void* memcpy(void* restrict dst_v, const void* restrict src_v, size_t size) {
    unsigned char* dst = (unsigned char*) dst_v;
    const unsigned char* src = (unsigned char*) src_v;
    for(size_t i=0; i<size; ++i) {
        dst[i] = src[i];
    }
    return dst_v;
}
