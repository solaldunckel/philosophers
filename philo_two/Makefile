# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/24 12:46:01 by sdunckel          #+#    #+#              #
#    Updated: 2020/09/21 14:08:22 by sdunckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo_two

SRCS_LIST		= \
					main.c \
					routine.c \
					parsing.c \
					utils.c \
					print_utils.c

OBJS			= ${SRCS_LIST:.c=.o}

CC				= gcc
CFLAGS 		= -Wall -Wextra -Werror
RM				= rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) -I . $(OBJS) -o $(NAME) -lpthread

%.o: %.c
				@$(CC) $(CFLAGS) -I . -o $@ -c $<

clean:
				@$(RM) $(OBJS)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean all

.PHONY: 		all fclean clean re
