# Name of the executable
NAME = minishell

# Compiler
CC = gcc 
# gcc -g -o so_long so_long.c
# Compiler flags
#CFLAGS = -Wall -Wextra -Werror -Wno-unused-but-set-variable -Wno-unused-const-variable -Wno-unused-parameter -Wno-unused-variable -Wno-sign-compare
CFLAGS := -Wall -Wextra -Werror -g -MMD -MP
# Include paths for header files
H_PATH := -I. -I /usr/local/Cellar/readline/8.2.1/include

# Library paths
LIB_PATH := -L./libft -L /usr/local/Cellar/readline/8.2.1/lib

# Libraries to link against, including the math library if needed
LDLIBS := -lft -lreadline

LFT = libft/libft.a
# Source files
SRC = executing/builtin_utils1.c \
	  executing/builtin_utils2.c \
	  executing/builtins1.c \
	  executing/builtins2.c \
	  executing/builtins3.c \
	  executing/custom_readline.c \
	  executing/errors_exit.c \
	  executing/exec_cmds.c \
	  executing/exec_pipe.c \
	  executing/execute.c \
	  executing/free_finaltree1.c \
	  executing/free_finaltree2.c \
	  executing/handle_envvar1.c \
	  executing/handle_envvar2.c \
	  executing/handle_envvar3.c \
	  executing/heredoc_utils1.c \
	  executing/heredoc_utils2.c \
	  executing/redir_heredoc1.c \
	  executing/redir_heredoc2.c \
	  executing/redir_heredoc3.c \
	  wildcards/wildcards_in_out.c \
	  wildcards/wildcards_sort.c \
	  wildcards/wildcards_utils.c \
	  wildcards/wildcards_utils2.c \
	  wildcards/wildcards.c \
	  cmd_args_utils.c \
	  cmd_args.c \
	  cmdstruct_init1.c \
	  cmdstruct_init2.c \
	  free_memory1.c \
	  free_memory2.c \
	  get_type1.c \
	  get_type2.c \
	  last_set1.c \
	  last_set2.c \
	  main_utils.c \
	  main.c \
	  parsing_utils.c \
	  parsing1.c \
	  parsing2.c \
	  safe_malloc.c \
	  signals1.c \
	  signals2.c \
	  utils.c \
	  initial_setup_util.c

DODIR = dofile

# Define object files (define, not generate)
OBJ = $(patsubst %.c,$(DODIR)/%.o,$(SRC))
# Define dependency files (define, not generate)
DEP = $(patsubst %.o,%.d,$(OBJ))


# Default target
all: $(NAME)

#include dependency files: SHOULD BE PLACED AFTER DEFAULT TARGET!
-include $(DEP)

# Rule to link the program
$(NAME): $(OBJ) $(LFT)	
	$(CC) $(OBJ) $(LIB_PATH) $(LDLIBS) -o $(NAME)

# Rule to compile source files into object files, d files are generated as well at the same time when -MMD is included
$(OBJ): $(DODIR)/%.o: %.c | $(DODIR)
	@mkdir -p $(dir $@)	
	$(CC) $(CFLAGS) $(H_PATH) -c $< -o $@ -MF $(DODIR)/$*.d

# rule to create the diretories. -p makes sure that if they exist already, nothing will be done
$(DODIR):
	mkdir -p $@

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