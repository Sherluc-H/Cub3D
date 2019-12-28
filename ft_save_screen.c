/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 12:31:30 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/28 20:33:00 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_add_header_bmp(unsigned char *h_tab, t_mlx_data mlx_data, int i)
{
	int *int_p;

	while (i < 54)
	{
		h_tab[i] = 0;
		i++;
	}
	h_tab[0] = 0x42;
	h_tab[1] = 0x4d;
	int_p = (int *)(&h_tab[2]);
	*int_p = (54 + mlx_data.desc->x * mlx_data.desc->y * 4);
	h_tab[10] = 0x36;
	h_tab[14] = 0x28;
	int_p = (int *)(&h_tab[18]);
	*int_p = mlx_data.desc->x;
	int_p = (int *)(&h_tab[22]);
	*int_p = mlx_data.desc->y;
	h_tab[26] = 0x01;
	h_tab[28] = mlx_data.main_img_bpp;
	int_p = (int *)(&h_tab[34]);
	*int_p = mlx_data.desc->x * mlx_data.desc->y * 4;
	int_p = (int *)(&h_tab[38]);
	*int_p = mlx_data.desc->x;
	int_p = (int *)(&h_tab[42]);
	*int_p = mlx_data.desc->y;
}

static int	ft_screen_bmp(t_mlx_data mlx_data, int i, int l)
{
	unsigned char	*tab;
	unsigned char	h_tab[54];
	int				fd;

	if (!(tab = malloc(sizeof(unsigned char) * (mlx_data.desc->x * 4))))
		return (-1);
	if ((fd = open("cub3d.bmp", O_CREAT | O_WRONLY,
		S_IRWXU | S_IRWXG | S_IRWXO)) == -1)
		return (-2);
	ft_add_header_bmp(h_tab, mlx_data, 0);
	write(fd, h_tab, 54);
	while (l < mlx_data.desc->y)
	{
		if (i == mlx_data.desc->x * 4)
		{
			write(fd, tab, mlx_data.desc->x * 4);
			i = 0;
			l++;
		}
		tab[i] = mlx_data.main_img_data[mlx_data.main_img_size_line *
		(mlx_data.desc->y - 1) - (mlx_data.main_img_size_line * l) + i];
		i++;
	}
	free(tab);
	return (1);
}

int			ft_save(t_mlx_data mlx_data)
{
	int ret;

	ret = ft_screen_bmp(mlx_data, 0, 0);
	if (ret == -1)
		return (ft_show_error(MALLOC, &mlx_data));
	else if (ret == -2)
		return (ft_show_error(OPEN, &mlx_data));
	ft_exit_hook(&mlx_data);
	return (0);
}
