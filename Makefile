##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## PROJECT
##

NASM = nasm

NASM_64FLAGS = -f elf64 -g -w+all 

SRC = $(wildcard src/*.asm)

OBJ_DIR = obj

DEBUG_FILE = vgcore.*

OBJ =  $(SRC:src/%.asm=obj/%.o)

NAME = libasm.so

MY_LIB = my_lib.so

TEST_FILE = unit_tests

all: $(NAME)

$(NAME): $(OBJ)
	ld -shared -o $@ $(OBJ) -z noexecstack

obj/%.o: src/%.asm
	mkdir -p obj
	$(NASM) $(NASM_64FLAGS) $< -o $@

tests_run: 
	@(make re -s)
	gcc -o unit_tests tests/main_tests.c -lcriterion -ldl 
	@(./unit_tests)

clean:
	rm -rf $(MY_LIB)
	rm -f $(NAME)
	rm -f $(OBJ_DIR)/*.o
	rm -f src/$(DEBUG_FILE)
	rm -f unit_test
	rm -f unit_test_base
	rm -f $(TEST_FILE)
	rm -f *.gcda
	rm -f *.gcno

fclean: 
	rm -rf $(MY_LIB)
	rm -f $(NAME)
	rm -f $(OBJ_DIR)/*.o
	rm -f unit_test
	rm -f unit_test_base
	rm -f $(TEST_FILE)
	rm -f *.gcda
	rm -f *.gcno

re:
	make clean
	make fclean
	make all

.PHONY: all clean fclean re
