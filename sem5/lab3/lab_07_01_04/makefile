CFLAGS := -std=c99 -pedantic -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
CC := gcc
OBJ_PATH := ./
INC_PATH := inc/
SRC_PATH := src/
UNIT_TESTS_PATH := unit_tests/
CHECKFLAGS = -lcheck
CHECKOBJS = $(OBJ_PATH)key.o $(OBJ_PATH)mysort.o $(OBJ_PATH)check_main.o $(OBJ_PATH)check_mysort.o $(OBJ_PATH)check_key.o 



$(OBJ_PATH)mysort.o: $(SRC_PATH)mysort.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH)key.o: $(SRC_PATH)key.c $(INC_PATH)defines.h
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_PATH)

$(OBJ_PATH)iolib.o: $(SRC_PATH)iolib.c $(INC_PATH)defines.h
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_PATH)

$(OBJ_PATH)process.o: $(SRC_PATH)process.c $(INC_PATH)defines.h $(INC_PATH)mysort.h $(INC_PATH)key.h
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_PATH)

$(OBJ_PATH)main.o: $(SRC_PATH)main.c $(INC_PATH)defines.h $(INC_PATH)process.h
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_PATH)


app.exe: $(OBJ_PATH)mysort.o $(OBJ_PATH)key.o $(OBJ_PATH)iolib.o $(OBJ_PATH)process.o $(OBJ_PATH)main.o
	$(CC) $(CFLAGS) -o $@ $^ -I $(INC_PATH)


$(OBJ_PATH)check_mysort.o: $(UNIT_TESTS_PATH)check_mysort.c $(INC_PATH)defines.h $(UNIT_TESTS_PATH)check_mysort.h
	$(CC) -std=c99 -o $@ -c $< -I $(INC_PATH)

$(OBJ_PATH)check_key.o: $(UNIT_TESTS_PATH)check_key.c  $(INC_PATH)defines.h $(UNIT_TESTS_PATH)check_key.h
	$(CC) -std=c99 -o $@ -c $< -I $(INC_PATH)

$(OBJ_PATH)check_main.o: $(UNIT_TESTS_PATH)check_main.c $(INC_PATH)defines.h
	$(CC) -std=c99 -o $@ -c $< -I $(INC_PATH)

unit_tests.exe: $(CHECKOBJS)
	$(CC) -o $@ $(CHECKOBJS) $(CHECKFLAGS)

clean:
	rm *.o *.exe