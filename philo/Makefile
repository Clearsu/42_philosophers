# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jincpark <jincpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 04:04:53 by jincpark          #+#    #+#              #
#    Updated: 2022/12/15 14:35:39 by jincpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= philo

CC 				= cc
CFLAG 			= -Wall -Wextra -Werror
DEBUG			= -fsanitize=address -g
DEBUG_TH		= -fsanitize=thread -g

SRCS 			= philo.c \
				  arg_check.c \
				  init_mutex_philo.c \
				  init_etc.c \
				  set_start_time_and_unlock_all.c \
				  monitor.c \
				  think_eat_sleep.c \
				  get_time.c \
				  utils.c \
				  error.c

OBJS 			= $(SRCS:%.c=%.o)

ifdef IF_DEBUG
	CFLAG += $(DEBUG)
endif

ifdef IF_DEBUG_TH
	CFLAG += $(DEBUG_TH)
endif

%.o :	%.c
	$(CC) $(CFLAG) -c $^ -I. -o $@

$(NAME)	:	$(OBJS)
	$(CC) $(CFLAG) -I. -lpthread $^ -o $@

all	:	$(NAME)

clean	:
	rm -f $(OBJS)

fclean	:	clean
	rm -f $(NAME)

re	:	fclean all

debug	:
	$(MAKE) IF_DEBUG=1 all

debugthread	:
	$(MAKE) IF_DEBUG_TH=1 all

.PHONY	:	all clean fclean re debug debugthread
