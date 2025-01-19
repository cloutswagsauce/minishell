#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/01 18:17:13 by lfaria-m          #+#    #+#              #
#    Updated: 2025/01/19 18:17:49 by lfaria-m         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# Program name
NAME = minishell

# Directories
SRC_DIR = srcs
OBJ_DIR = objs
LIB_DIR = includes/libft

# Source files (explicitly listed)
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/parser.c $(SRC_DIR)/utils.c \
$(SRC_DIR)/handle_command.c $(SRC_DIR)/free_stuff.c $(SRC_DIR)/ft_cd.c \
$(SRC_DIR)/ft_echo.c $(SRC_DIR)/ft_env.c $(SRC_DIR)/ft_exit.c $(SRC_DIR)/ft_export.c \
$(SRC_DIR)/ft_unset.c $(SRC_DIR)/ft_pwd.c  $(SRC_DIR)/ft_lst.c $(SRC_DIR)/handle_variable.c \
$(SRC_DIR)/execute_process.c $(SRC_DIR)/ft_pipex.c
       

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -fsanitize=address -Werror

# To link readline
RD = -lreadline -lncurses
# Libraries
LIB = $(LIB_DIR)/libft.a
LIB_FLAGS = -L$(LIB_DIR) -lft

# Tools
AR = ar rcs
RM = rm -f

# Build rules
all: $(NAME)

# Link the final program
$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) $(RD) -o $(NAME)

# Compile source files to object files in the objs directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIB_DIR) -c $< -o $@

# Ensure the objs directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build Libft if not already built
$(LIB):
	make -C $(LIB_DIR)

# Clean up object files
clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJ_DIR)
	make -C $(LIB_DIR) clean

# Clean up everything, including the executable
fclean: clean
	$(RM) $(NAME)
	make -C $(LIB_DIR) fclean

# Rebuild the project
re: fclean all

.PHONY: all clean fclean re
