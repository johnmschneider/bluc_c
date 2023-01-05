del bin\main.exe
clang src/*.c src/jms_parse/*.c src/jms_tests/*.c src/jms_utils/*.c -g -O0 -o bin/main.exe
bin\main.exe src\test.bluc
