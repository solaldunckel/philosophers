# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 12:02:19 by sdunckel          #+#    #+#              #
#    Updated: 2019/12/21 13:38:54 by sdunckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo_one

SRCS_LIST		= \
					main.c \
					ft.c \
					utils.c \
					actions.c

OBJS			= ${SRCS_LIST:.c=.o}

CC				= gcc
CFLAGS 			= -Wall -Wextra -Werror
RM				= rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) -I . $(OBJS) -o $(NAME)

%.o: %.c
				@$(CC) $(CFLAGS) -I . -o $@ -c $<

clean:
				@$(RM) $(OBJS)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean all

.PHONY: 		all fclean clean re
