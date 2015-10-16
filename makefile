
MAIN=main
TEST=test

all: default

default:
	clang util.c main.c -o $(MAIN) -std=gnu11

tests:
	rm -f $(TEST)
	clang++ util_test.c util.c -o $(TEST) -std=c++11 -lgtest -g3

clean:
	rm -f .conman $(MAIN) $(TEST)
