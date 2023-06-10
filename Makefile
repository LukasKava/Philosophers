# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkavalia <lkavalia@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/24 18:43:55 by lkavalia          #+#    #+#              #
#    Updated: 2023/06/10 12:17:23 by lkavalia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

#LIBFT_PATH		= my_libft

SRCS	= 	main.c \
			init.c \
			routine_functions.c \
			utils.c

OBJS = $(SRCS:.c=.o)

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

$(NAME): $(SRCS)
		$(CC) $(CFLAGS) $(SRCS) -lpthread -o $(NAME)
		@echo "Making the files"

checking:
		$(CC) $(CFLAGS) $(SRCS) -lpthread -fsanitize=thread -o check
		
all: $(NAME)

clean:
	rm -f $(OBJS)
	@echo "cleaning the files"

fclean: clean
	rm -f $(NAME)
	@echo "fcleaning the files"

re: fclean all
	@echo "remaking the files"