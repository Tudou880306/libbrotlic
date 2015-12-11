# libbrotli C#

C interface for parallel brotli compression.

## Build ##

`g++ -fpic -shared brotli_c.cpp -l brotlienc -l brotlidec -o libbrotli_c.so`

## Usage ##

`gcc my_code_using_libbrotli_c.c -L /Path/to/libbrotli_c.so -l brotli_c -l pthread`
