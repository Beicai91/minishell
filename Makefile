# Name of the executable
NAME = minishell

# Compiler
CC = gcc 
# gcc -g -o so_long so_long.c
# Compiler flags
#CFLAGS = -Wall -Wextra -Werror -Wno-unused-but-set-variable -Wno-unused-const-variable -Wno-unused-parameter -Wno-unused-variable -Wno-sign-compare
CFLAGS := -Wall -Wextra -Werror -g -MMD -MP
# Include paths for header files
INCLUDES := -I. -I /usr/local/Cellar/readline/8.2.10/include

# Library paths
LDFLAGS := -L./libft -L /usr/local/Cellar/readline/8.2.10/lib

# Libraries to link against, including the math library if needed
LDLIBS := -lft -lreadline

LFT = libft/libft.a
# Source files
SRC = $(wildcard *.c) \
		$(wildcard executing/*.c) \
		$(wildcard wildcards/*.c) \
		$(wildcard utils/*c)

# Object files
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)

#include dependency files
-include $(DEP)




# Default target
all: $(NAME)

# Rule to link the program
$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LFT) $(LDLIBS) -o $(NAME)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LFT):
	make -C libft all

# Rule to clean object files and other temporary files
clean:
	rm -f $(OBJ) $(DEP)
	make -C libft clean

# Rule to fully clean the project, including the executable
fclean: clean
	rm -f $(NAME)
	make -C libft fclean

# Rule to re-make the project
re: fclean all

# Phony targets for make commands
.PHONY: all clean fclean re