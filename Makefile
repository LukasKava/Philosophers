# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkavalia <lkavalia@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/24 18:43:55 by lkavalia          #+#    #+#              #
#    Updated: 2022/08/30 01:40:41 by lkavalia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

#LIBFT_PATH		= my_libft


SRCS	= 	main.c \
			test_function.c \
			utils.c

OBJS = $(SRCS:.c=.o)

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

$(NAME): $(SRCS)
		$(CC) $(CFLAGS) $(SRCS) -lpthread -o $(NAME)
		@echo "Making the files"

all: $(NAME)

clean:
	rm -f $(OBJS)
	@echo "cleaning the files"

fclean: clean
	rm -f $(NAME)
	@echo "fcleaning the files"

re: fclean all
	@echo "remaking the files"