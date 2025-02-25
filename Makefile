# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/01 18:17:13 by lfaria-m          #+#    #+#              #
#    Updated: 2025/02/25 20:14:29 by lfaria-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = minishell

# Directories
SRC_DIR = srcs
OBJ_DIR = objs
LIB_DIR = includes/libft

# Source files (explicitly listed)
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/main_helper.c  $(SRC_DIR)/utils/utils.c \
$(SRC_DIR)/executor/handle_command.c $(SRC_DIR)/end/free_stuff.c $(SRC_DIR)/builtin/ft_cd.c \
$(SRC_DIR)/builtin/ft_echo.c $(SRC_DIR)/builtin/ft_env.c $(SRC_DIR)/builtin/ft_exit.c $(SRC_DIR)/builtin/ft_export.c \
$(SRC_DIR)/builtin/ft_unset.c $(SRC_DIR)/builtin/ft_pwd.c $(SRC_DIR)/ft_lst.c $(SRC_DIR)/executor/handle_variable.c \
$(SRC_DIR)/executor/execute_process.c $(SRC_DIR)/executor/ft_pipex.c $(SRC_DIR)/parsing/tokenizer.c $(SRC_DIR)/parsing/parser_utils.c \
$(SRC_DIR)/executor/ft_redirect.c $(SRC_DIR)/parsing/parser.c $(SRC_DIR)/parsing/handle_tokens.c $(SRC_DIR)/parsing/squotes.c $(SRC_DIR)/parsing/parser_helpers.c \
$(SRC_DIR)/parsing/token_utils.c $(SRC_DIR)/builtin/export_utils.c $(SRC_DIR)/signals/signals.c $(SRC_DIR)/builtin/env_utils.c $(SRC_DIR)/signals/signals_extra.c $(SRC_DIR)/parsing/parser_extras.c $(SRC_DIR)/parsing/tokenizer_extras.c \
$(SRC_DIR)/parsing/tokenizer_utils.c $(SRC_DIR)/parsing/tokenizer_helper.c $(SRC_DIR)/parsing/handle_tokens_helper.c




# Object files (stored in objs/)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Extract directories from source files (for automatic creation)
DIRS = $(sort $(dir $(OBJS)))

# Compiler and flags
CC = cc
CFLAGS = -Wall -g -Wextra -Werror

# To link readline
#RD = -lreadline -lncurses
RD = -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -lreadline -lncurses


# Libraries
LIB = $(LIB_DIR)/libft.a
LIB_FLAGS = -L$(LIB_DIR) -lft

# Tools
AR = ar rcs
RM = rm -f

# Default target
all: $(NAME)

# Link the final program
#$(NAME): $(OBJS) $(LIB)
#	$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) $(RD) -o $(NAME)
$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) -L/opt/homebrew/opt/readline/lib -lreadline -lncurses -o $(NAME)



# Compile source files to object files
#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
#	mkdir -p $(dir $@)  # Ensure the directory exists
#	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -I/opt/homebrew/opt/readline/include -c $< -o $@



# Ensure all necessary subdirectories exist before compiling
$(DIRS):
	mkdir -p $@

# Build Libft if not already built
$(LIB):
	@if [ ! -f "$@" ]; then make -C $(LIB_DIR); fi

# Clean up object files
clean:
	$(RM) $(OBJS)
	rm -rf $(OBJ_DIR)
	make -C $(LIB_DIR) clean

# Clean up everything, including the executable
fclean: clean
	$(RM) $(NAME)
	make -C $(LIB_DIR) fclean

# Rebuild the project
re: fclean all

.PHONY: all clean fclean re
