#include <string.h>

void* memmove(void* dest_v, const void* src_v, size_t size) {
    unsigned char* dest = (unsigned char*) dest_v;
    const unsigned char* src = (const unsigned char*) src_v;
    if (dest < src) {
        for (size_t i=0; i<size; ++i) {
            dest[i] = src[i];
        }
    } else {
        for (size_t i=0; i != 0; --i ) {
            dest[i-1] = src[i-1];
        }
    }
    return dest_v;
}
