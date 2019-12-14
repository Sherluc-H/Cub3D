# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/30 14:38:10 by lhuang            #+#    #+#              #
#    Updated: 2019/12/14 16:36:06 by lhuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
RM= rm -f
FLAGS= -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -Wall -Werror -Wextra
NAME= Cub3D
SRCS= cub3d.c ft_is.c ft_utils.c ft_check_args.c ft_get_description_utils.c ft_get_description.c
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