# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: linaboumahdi <linaboumahdi@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/06 17:54:38 by akloster          #+#    #+#              #
#    Updated: 2025/01/08 13:10:36 by linaboumahd      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM          = rm -rf
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Iincludes

SRC_DIR     = src/
SRC         = $(wildcard $(SRC_DIR)*.c)

GNL_DIR     = GNL/
GNL_SRC     = $(wildcard $(GNL_DIR)*.c)

# Headers
HEADERS     = includes/cub3d.h GNL/get_next_line.h

LIBft       = libft/libft.a

OBJ_DIR     = objs/
SRC_OBJ     = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
GNL_OBJ     = $(patsubst $(GNL_DIR)%.c, $(OBJ_DIR)%.o, $(GNL_SRC))
OBJ         = $(SRC_OBJ) $(GNL_OBJ)

NAME        = cub3d

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@make -C ./libft
	$(CC) $(OBJ) $(LIBft) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(GNL_DIR)%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make clean -C ./libft
	$(RM) $(OBJ_DIR)

fclean: clean
	@make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
