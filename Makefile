# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/30 14:38:10 by lhuang            #+#    #+#              #
#    Updated: 2019/11/30 18:08:53 by lhuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
RM= rm -f
FLAGS= -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -Wall -Werror -Wextra
NAME= Cub3D
SRCS= cub3d.c
OBJS= $(SRCS:.c=.o)
HEADER= cub3d.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(FLAGS) $(OBJS) -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re