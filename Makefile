DEBUG = 1
EXECUTABLE_NAME = geodistance

SOURCE_DIR = .
BUILD_DIR = .

CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99
CPPFLAGS =
LDFLAGS = -lm

ifeq ($(DEBUG), 1)
CFLAGS += -g -O0
else
CFLAGS += -O3
endif

# additional flags for gcov
TESTFLAGS = -fprofile-arcs -ftest-coverage

COMPILER_CALL = $(CC) $(CFLAGS) $(CPPFLAGS)

##############
## TARGETS  ##
##############
build: haversine.o main.o
	$(COMPILER_CALL) haversine.o main.o $(LDFLAGS) -o $(BUILD_DIR)/$(EXECUTABLE_NAME)

main.o:
	$(COMPILER_CALL) main.c -c

haversine.o:
	$(COMPILER_CALL) haversine.c -c

test: test.c haversine.h haversine.c
	$(CC) $(CFLAGS) $(TESTFLAGS) test.c haversine.c $(LDFLAGS) -o ./test
	./test
	gcov -c -p test-haversine
	
clean:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(BUILD_DIR)/*.gcov *gcda *gcno test
	rm -f $(BUILD_DIR)/$(EXECUTABLE_NAME)

