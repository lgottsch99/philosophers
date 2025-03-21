# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 11:25:47 by lgottsch          #+#    #+#              #
#    Updated: 2025/03/21 15:54:34 by lgottsch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_FOLDER = ./src/
SRC = $(addprefix $(SRC_FOLDER), main.c input.c utils.c free.c init.c)


OBJ = $(SRC:.c=.o)

$(NAME): re
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)
	make clean

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

	
.PHONY: all clean fclean re