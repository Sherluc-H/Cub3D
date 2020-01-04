# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/30 14:38:10 by lhuang            #+#    #+#              #
#    Updated: 2020/01/04 11:24:51 by lhuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= gcc
RM= rm -f
CFLAGS= -Wall -Werror -Wextra
NAME= cub3D
SRCS= cub3d.c \
		ft_handle_errors.c \
		ft_is.c ft_is_plus.c \
		ft_utils.c \
		ft_utils_plus.c \
		ft_check_args.c \
		ft_check_args_utils.c \
		ft_get_description_utils.c \
		ft_get_description.c \
		ft_get_textures.c \
		ft_draw_utils.c \
		ft_draw.c \
		ft_draw_sprite.c \
		ft_draw_map.c \
		ft_handle_keys.c \
		ft_handle_keys_utils.c \
		ft_get_next_line.c \
		ft_save_screen.c
OBJS= $(SRCS:.c=.o)
HEADER= cub3d.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit $(OBJS) -o $@

bonus: all

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
