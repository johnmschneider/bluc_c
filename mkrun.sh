rm -f bin/bluc
# -fsanitize=address
gcc src/*.c src/jms_oop_utils/*.c src/jms_oop_utils/jms_reflection/*.c src/jms_parse/*.c src/jms_tests/*.c src/jms_utils/*.c -g -O0 -o bin/bluc
./bin/bluc src/test.bluc