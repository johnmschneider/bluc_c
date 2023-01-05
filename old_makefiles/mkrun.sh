clang *.c -fsanitize=memory -fsanitize-memory-track-origins -g -O0 -o test
./test