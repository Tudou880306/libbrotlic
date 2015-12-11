// BROTLI
#include <brotli/dec/decode.h>
#include <brotli/enc/encode.h>
#include <brotli/enc/encode_parallel.h>

#include "brotli_c.h"

uint8_t* brotli_compress_buffer_parallel(const int mode,
                                         const int quality,
                                         const int lgwin,
                                         const int lgblock,
                                         const int nThreads,
                                         const size_t inBufLength,
                                         const uint8_t* inBuf,
                                         size_t* outBufLength) {

    brotli::BrotliParams params;
    params.mode      = static_cast<brotli::BrotliParams::Mode>(mode);
    params.quality   = quality;
    params.lgwin     = lgwin;
    params.lgblock   = lgblock;
    params.n_threads = nThreads;    

    *outBufLength = inBufLength + (inBufLength >> 3) + 1024;

    uint8_t* preOutBuf = new uint8_t[*outBufLength];

    int result = brotli::BrotliCompressBufferParallel(params,
						      inBufLength,
						      inBuf,
						      outBufLength,
						      preOutBuf);

    if(result == 0){
	return NULL;
    }
    else {
	uint8_t* outBuf = new uint8_t[*outBufLength];
	std::copy(preOutBuf, preOutBuf + *outBufLength, outBuf);
	return outBuf;

    }
    
    delete[] preOutBuf;
}

int brotli_decompress_buffer( const size_t inBufLength,
			      const uint8_t* inBuf,
			      size_t *outBufLength,
			      uint8_t *outBuf) {


    int result = BrotliDecompressBuffer(inBufLength,
						inBuf,
						outBufLength,
						outBuf);
    return result;
}
