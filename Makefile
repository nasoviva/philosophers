# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hverda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 13:02:35 by hverda            #+#    #+#              #
#    Updated: 2022/01/17 13:02:39 by hverda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = philo

LIST =	philo.c\
		threads.c\
		init.c\
		utils.c

LIST_H = philo.h

OBJ = $(patsubst %.c,%.o,$(LIST))

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(FLAGS) $(LIST) -o $(NAME)

%.o : %.c Makefile $(LIST_H)
	gcc $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
