# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/30 14:38:10 by lhuang            #+#    #+#              #
#    Updated: 2019/12/21 18:18:45 by lhuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
RM= rm -f
CFLAGS= -Wall -Werror -Wextra
NAME= Cub3D
SRCS= cub3d.c ft_is.c ft_utils.c ft_check_args.c ft_get_description_utils.c ft_get_description.c ft_get_textures.c ft_draw_utils.c ft_draw.c ft_handle_keys.c ft_get_next_line.c
OBJS= $(SRCS:.c=.o)
HEADER= cub3d.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit $(OBJS) -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re