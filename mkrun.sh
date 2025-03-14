rm -f bin/bluc
gcc src/*.c src/jms_oop_utils/*.c src/jms_oop_utils/jms_reflection/*.c src/jms_parse/*.c src/jms_tests/*.c src/jms_utils/*.c -g -fsanitize=address -O0 -o bin/bluc
./bin/bluc src/test.bluc