#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfaria-m <lfaria-m@42lausanne.ch>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/01 18:17:13 by lfaria-m          #+#    #+#              #
#    Updated: 2024/12/02 08:01:45 by lfaria-m         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# Program name
NAME = push_swap

# Source files
SRCS = main.c lst.c push_op.c operation_helper.c rotate_op.c swap_op.c sort_three.c utils.c init_stack.c more_utils.c sort_stack.c free_stack_error.c even_more_utils.c validate_input.c

# Object files
OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -fsanitize=address -Werror 

# Directories for libraries
LIB_DIR = includes/libft

# Libraries
LIB = $(LIB_DIR)/libft.a


LIB_FLAGS = -L $(LIB_DIR) -lft

# Tools
AR = ar rcs
RM = rm -f

# Build rules
all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIB_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIB_DIR) -c $< -o $@


# Build Libft if not already built
$(LIB):
	make -C $(LIB_DIR)

clean:
	$(RM) $(OBJS)
	make -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re