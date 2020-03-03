# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egarcia- <emilioggo@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/14 13:40:01 by egarcia-          #+#    #+#              #
#    Updated: 2020/03/02 18:48:03 by egarcia-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= cub3d.c key_manager.c read_map.c read_map2.c raycasting.c raycasting2.c save.c utils.c

OBJS	= $(SRCS:.c=.o)

CC		= gcc
RM		= rm -fr
CFLAGS	= -Wall -Wextra -Werror -I.
LIBS	= -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
LIBSMAC = -I /usr/local/include -L /minilibx/  libmlx.a  -framework OpenGL \
			-framework AppKit ./libft/libft.a

NAME	= cub3d

all:		$(NAME)

$(NAME):	$(OBJS)
				gcc ${CFLAGS} ./libft/libft.a -o ${NAME} ${OBJS} ${LIBS} 

macbook:	$(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LIBSMAC} 
			

clean:		
			$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)

re:			fclean $(NAME)
