#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    uint8_t* brotli_compress_buffer_parallel(const int mode,
                                             const int quality,
                                             const int lgwin,
                                             const int lgblock,
                                             const int nThreads,
                                             const size_t inBufLength,
                                             const uint8_t* inBuf,
                                             size_t* outBufLength
                                             );


    int brotli_decompress_buffer(const size_t inBufLength,
				 const uint8_t* inBuf,
				 size_t* outBufLength,
				 uint8_t* outBuf
				 );


    
#ifdef __cplusplus
}
#endif
