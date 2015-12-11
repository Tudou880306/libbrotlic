// STL
#include <iostream>
#include <array>
#include <chrono>


// BROTLI
#include <brotli/dec/decode.h>
#include <brotli/enc/encode.h>
#include <brotli/enc/encode_parallel.h>


// Compile: g++ main.cpp -std=c++11 -l brotlienc -l brotlidec -l pthread;
// Run:     ./a.out

int main(){

    const size_t nElements     = 20000000;
    std::vector<uint8_t> inputBuffer(nElements);
    
    for(size_t i = 0; i < nElements; i++){
    	inputBuffer.at(i) = static_cast<uint8_t>(i);

    }

    // Compression parameters (taken from defaults)
    brotli::BrotliParams params;
    params.mode = brotli::BrotliParams::Mode::MODE_GENERIC;
    params.quality = 11;
    params.lgwin = 22;
    params.lgblock = 22;
    params.n_threads = 4;

    // Sequential compression
    {
    	auto start = std::chrono::system_clock::now();

    	size_t nCompressedElements = nElements + (nElements >> 3) + 1024;
    	std::vector<uint8_t> outputBuffer(nCompressedElements);    
	
    	int result = brotli::BrotliCompressBuffer(params,
    						  nElements,
    						  inputBuffer.data(),
    						  &nCompressedElements,
    						  outputBuffer.data());

    	if(result == 0){
    	    std::cout << "Error on sequential compression" << std::endl;
	
    	}

    	if(result == 1){
    	    std::cout << "Sequential nCompressedElements: " << nCompressedElements << std::endl;
	
    	}
    	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
    	std::cout << "Sequential duration: " << duration.count() << " ms" << std::endl;

    }

    // Parallel compression
    {
	auto start = std::chrono::system_clock::now();

	size_t nCompressedElements = nElements + (nElements >> 3) + 1024;
	std::vector<uint8_t> outputBuffer(nCompressedElements);    
    
    	int result = brotli::BrotliCompressBufferParallel(params,
    							  nElements,
    							  inputBuffer.data(),
    							  &nCompressedElements,
    							  outputBuffer.data());

    	if(result == 0){
    	    std::cout << "Error on parallel compression" << std::endl;
	
    	}

    	if(result == 1){
    	    std::cout << "Parallel nCompressedElements: " << nCompressedElements << std::endl;
	
    	}
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start);
	std::cout << "Parallel duration: " << duration.count() << " ms"<< std::endl;


	/***************************************************************************
	 * Decompress buffers
	 **************************************************************************/
	size_t nDecompressedElements = 0;
	std::vector<uint8_t> decompressedBuffer(nElements);
	result = BrotliDecompressBuffer(outputBuffer.size(),
					outputBuffer.data(),
					&nDecompressedElements,
					decompressedBuffer.data());

	decompressedBuffer.resize(nDecompressedElements);
	
	if(result == 0){
	    printf("Decompression error!\n");
	}
	else {
	    for(size_t i = 0; i < decompressedBuffer.size(); i++){
		assert(decompressedBuffer[i] == (uint8_t) i);
	    }
	    printf("Decompression without errors!\n");
	}
    
	
    }

    return 0;
}
