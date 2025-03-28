# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 11:25:47 by lgottsch          #+#    #+#              #
#    Updated: 2025/03/28 17:07:59 by lgottsch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread

SRC_FOLDER = ./src/
SRC = $(addprefix $(SRC_FOLDER), main.c input.c utils.c free.c init.c routine.c \
	monitor.c )


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