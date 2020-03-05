# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aortega- <aortega-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/14 13:40:01 by egarcia-          #+#    #+#              #
#    Updated: 2020/03/05 17:31:22 by aortega-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= cub3d.c keys.c read_map.c raycastingaux.c spritecastingaux.c general.c pathsmap.c utils.c

OBJS	= $(SRCS:.c=.o)

CC		= gcc
RM		= rm -fr
CFLAGS	= -Wall -Wextra -Werror -I.
LIBS	= -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

NAME	= cub3d

all:		$(NAME)

$(NAME):	$(OBJS)
				gcc ${CFLAGS} ./libft/libft.a -o ${NAME} ${OBJS} ${LIBS} 

clean:		
			$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)

re:			fclean $(NAME)
