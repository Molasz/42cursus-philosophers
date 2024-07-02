# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/02 18:14:24 by molasz-a          #+#    #+#              #
#    Updated: 2024/07/02 19:08:35 by molasz-a         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= philosophers.c \
			death.c \
			forks.c \
			init.c \
			process.c \
			utils.c \
			libft.c

OBJS 	= $(addprefix obj/, $(SRCS:.c=.o))

DEPS	= $(addprefix obj/, $(SRCS:.c=.d))

NAME	= philo_bonus

RM		= rm -rf

CC		= cc

CFLAGS	= -Wall -Wextra -Werror #-g -fsanitize=thread

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

.PHONY:		all clean fclean re dir
