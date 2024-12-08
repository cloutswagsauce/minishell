# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfaria-m <lfaria-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/01 18:17:13 by lfaria-m          #+#    #+#              #
#    Updated: 2024/12/08 14:51:25 by lfaria-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = minishell

# Directories
SRC_DIR = srcs
OBJ_DIR = objs
LIB_DIR = includes/libft

# Source files (explicitly listed)
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/parser.c $(SRC_DIR)/utils.c $(SRC_DIR)/handle_command.c $(SRC_DIR)/free_stuff.c
       

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
