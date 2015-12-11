#include "brotli_c.h"
#include "stdio.h"
#include "assert.h"


// build shared lib:  g++ -fpic -shared brotli_c.cpp -l brotlienc -l brotlidec -o libbrotli_c.so
// build main.c: set -x LD_LIBRARY_PATH .; gcc main.c -L . -l brotli_c -l pthread

int main(){


    /***************************************************************************
     * Create buffers
     **************************************************************************/
    size_t inBufLength  = 20000000;
    size_t outBufLength = 1;


    uint8_t* inBuf  = (uint8_t*)malloc(sizeof(uint8_t) * inBufLength);
    uint8_t* outBuf = NULL;


    for(size_t i = 0; i < inBufLength; i++){
        inBuf[i] = (uint8_t) i;
    }

    /***************************************************************************
     * Compress buffers
     **************************************************************************/
    outBuf = brotli_compress_buffer_parallel(0,  // mode 0,1 or 2
                                             1,  // quality 0 to 11
                                             22, // lgwin 10 to 24
                                             22, // lgblock 16 to 24, if set to 0 then quality based
                                             4,  // number of threads that will be spawned0,
                                             inBufLength,
                                             inBuf,
                                             &outBufLength);

    if(outBuf == NULL){
        printf("Compression error!\n");
    }
    else {
        printf("Compression rate: %f\n", (float) inBufLength/ (float) outBufLength);
    }
    
    /***************************************************************************
     * Decompress buffers
     **************************************************************************/
    int result = 0;

    uint8_t* decompressedBuf    = (uint8_t*)malloc(sizeof(uint8_t) * inBufLength);
    size_t   decompressedBufLength = 0;
    
    result = brotli_decompress_buffer(outBufLength,
				      outBuf,
				      &decompressedBufLength,
				      decompressedBuf);

    if(result == 0){
	printf("Decompression error!\n");
    }
    else {
	for(size_t i = 0; i < inBufLength; i++){
	    assert(inBuf[i] == (uint8_t) i);
	}
	printf("Decompression without errors!\n");
    }

    free(inBuf);
    free(outBuf);
    free(decompressedBuf);
    
    return 0;

}
