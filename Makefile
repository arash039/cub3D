# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashojach <ashojach@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 12:32:18 by ashojach          #+#    #+#              #
#    Updated: 2023/12/19 14:56:37 by ashojach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = cc

# Flags
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L./mlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

# Source files
SRCS = main.c parser.c gnl.c gnl_utils.c drawing.c keys.c texture.c minimap.c gnl_utils_1.c dda.c moves.c parse_data.c parse_map.c

# Object files
OBJS = $(SRCS:.c=.o)

# Target
NAME = cub3D

# Default target
all: $(NAME)

# Rule to build the target
$(NAME): $(OBJS)
	cd mlx && make
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS)

# Clean rule for all generated files
fclean: clean
	rm -f $(NAME)

re: fclean all

# Phony targets
.PHONY: all clean fclean
