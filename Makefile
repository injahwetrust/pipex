# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvaujour <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 11:36:48 by bvaujour          #+#    #+#              #
#    Updated: 2023/03/23 11:36:51 by bvaujour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES = libft/libft.h

FILES = pipex.c utils.c
FILES_B = pipex_bonus.c pipex_bonus_utils.c files.c

LIBS = -L./libft -lft

DIRPATH =	$(sh pwd)
SRCPATH	=	$(DIRPATH)src/
SRCBPATH =	$(DIRPATH)src_bonus/
SRC	=	$(addprefix $(SRCPATH), $(FILES))
SRC_B	=	$(addprefix $(SRCBPATH), $(FILES_B))

LIBFT = libft/libft.a

NAME 	= pipex
NAME_B	= pipex_bonus

CC = gcc

CFLAGS = -g3 -Wall -Werror -Wextra 

OBJ	= $(SRC:.c=.o)
OBJ_B	= $(SRC_B:.c=.o)

all	: $(NAME)

$(NAME)	: $(LIBFT) $(OBJ) $(INCLUDES)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

bonus	: $(NAME_B)

$(NAME_B): $(LIBFT) $(OBJ_B) $(INCLUDES)
	$(CC) $(CFLAGS) $(OBJ_B) $(LIBS) -o $(NAME_B)
	
$(LIBFT) :
	make -C libft

clean:
	make clean -C libft
	rm -rf $(OBJ)
	rm -rf $(OBJ_B)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)
	rm -rf $(NAME_B)
	
re: fclean all

.PHONY: clean fclean re
