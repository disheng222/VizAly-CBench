add_executable (testint_compress testint_compress.c)
target_link_libraries (testint_compress SZ zlib zstd m)

add_executable (testint_decompress testint_decompress.c)
target_link_libraries (testint_decompress SZ zlib zstd m)

add_executable (testfloat_compress testfloat_compress.c)
target_link_libraries (testfloat_compress SZ zlib zstd m)

add_executable (testfloat_decompress testfloat_decompress.c)
target_link_libraries (testfloat_decompress SZ zlib zstd m)

add_executable (testdouble_compress testdouble_compress.c)
target_link_libraries (testdouble_compress SZ zlib zstd m)

add_executable (testdouble_decompress testdouble_decompress.c)
target_link_libraries (testdouble_decompress SZ zlib zstd m)

add_executable (sz sz.c)
target_link_libraries (sz SZ zlib zstd m)

install (TARGETS testint_compress testint_decompress testfloat_compress testfloat_decompress
	testdouble_compress testdouble_decompress sz
         RUNTIME DESTINATION bin)


