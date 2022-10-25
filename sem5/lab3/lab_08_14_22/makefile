CFLAGS := -std=c99 -pedantic -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
CC := gcc
OBJ_PATH := out/
INC_PATH := inc/
SRC_PATH := src/
UNIT_TESTS_PATH := unit_tests/
CHECKFLAGS = -lcheck


$(OBJ_PATH)process.o: $(SRC_PATH)process.c $(INC_PATH)defines.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_PATH)

$(OBJ_PATH)matrix.o: $(SRC_PATH)matrix.c $(INC_PATH)defines.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_PATH)

$(OBJ_PATH)iolib.o: $(SRC_PATH)iolib.c $(INC_PATH)defines.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_PATH)

$(OBJ_PATH)main.o: $(SRC_PATH)main.c $(INC_PATH)defines.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_PATH)

app.exe: $(OBJ_PATH)process.o $(OBJ_PATH)iolib.o $(OBJ_PATH)matrix.o $(OBJ_PATH)main.o
	$(CC) $(CFLAGS) -o $@ $^ -I $(INC_PATH)


$(OBJ_PATH)utilities_for_check.o: $(UNIT_TESTS_PATH)utilities_for_check.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INC_PATH)

$(OBJ_PATH)check_mult.o: $(UNIT_TESTS_PATH)check_mult.c $(INC_PATH)matrix.h $(INC_PATH)utilities_for_check.h
	mkdir -p $(OBJ_PATH)
	$(CC) -std=c99 -o $@ -c $< -I $(INC_PATH)

$(OBJ_PATH)check_add.o: $(UNIT_TESTS_PATH)check_add.c $(INC_PATH)matrix.h $(INC_PATH)utilities_for_check.h
	mkdir -p $(OBJ_PATH)
	$(CC) -std=c99 -o $@ -c $< -I $(INC_PATH)

$(OBJ_PATH)check_invert.o: $(UNIT_TESTS_PATH)check_invert.c $(INC_PATH)matrix.h $(INC_PATH)utilities_for_check.h
	mkdir -p $(OBJ_PATH)
	$(CC) -std=c99 -o $@ -c $< -I $(INC_PATH)

$(OBJ_PATH)check_main.o: $(UNIT_TESTS_PATH)check_main.c
	mkdir -p $(OBJ_PATH)
	$(CC) -std=c99 -o $@ -c $< -I $(INC_PATH)
	
unit_tests.exe: $(OBJ_PATH)check_main.o $(OBJ_PATH)check_add.o $(OBJ_PATH)check_mult.o $(OBJ_PATH)check_invert.o $(OBJ_PATH)matrix.o $(OBJ_PATH)process.o $(OBJ_PATH)iolib.o $(OBJ_PATH)utilities_for_check.o
	$(CC) -o $@ $^ $(CHECKFLAGS)


clean:
	rm $(OBJ_PATH)*.o *.exe