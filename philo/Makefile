# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molasz-a <molasz-a@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/27 17:13:53 by molasz-a          #+#    #+#              #
#    Updated: 2024/05/28 21:45:41 by molasz-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= philosophers.c

OBJS 	= $(addprefix obj/, $(SRCS:.c=.o))

DEPS	= $(addprefix obj/, $(SRCS:.c=.d))

NAME	= philo

RM		= rm -rf

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

all:		dir ${NAME}

dir:
				mkdir -p obj

obj/%.o:	%.c Makefile
				${CC} ${CFLAGS} -c $< -MMD -o $@

${NAME}:	${OBJS}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
				${RM} obj/

fclean:		clean
				${RM} ${NAME}

re:			fclean all

-include $(DEPS)

.PHONY:		all clean fclean re
