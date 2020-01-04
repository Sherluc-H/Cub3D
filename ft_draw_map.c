/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/01 17:30:48 by lhuang            #+#    #+#             */
/*   Updated: 2020/01/03 22:48:35 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_draw_one_element(t_mlx_data mlx_data, t_map_data m_dt,
	int j, int k)
{
	int l;
	int m;
	int y;
	int x;

	l = 0;
	y = j * m_dt.element_size;
	while (y + l < y + m_dt.element_size)
	{
		x = k * m_dt.element_size;
		m = 0;
		while (x + m < x + m_dt.element_size)
		{
			if (mlx_data.desc->scene[j][k] == '1')
				ft_put_pixel_to_image(mlx_data, x + m, y + l, m_dt.wall_color);
			else if (mlx_data.desc->scene[j][k] == '2')
				ft_put_pixel_to_image(mlx_data, x + m, y + l,
					m_dt.sprite_color);
			else if (mlx_data.desc->scene[j][k] != '\0')
				ft_put_pixel_to_image(mlx_data, x + m, y + l, m_dt.empty_color);
			m++;
		}
		l++;
	}
}

static void	ft_draw_map_all_elements(t_mlx_data mlx_data, t_map_data map_data)
{
	int k;
	int j;

	k = 0;
	j = 0;
	while (mlx_data.desc->scene[j])
	{
		k = 0;
		while (mlx_data.desc->scene[j][k])
		{
			if (mlx_data.desc->scene[j][k] == '1')
				ft_draw_one_element(mlx_data, map_data, j, k);
			else if (mlx_data.desc->scene[j][k] == '2')
				ft_draw_one_element(mlx_data, map_data, j, k);
			else if (mlx_data.desc->scene[j][k] != '\0')
				ft_draw_one_element(mlx_data, map_data, j, k);
			k++;
		}
		j++;
	}
}

static void	ft_draw_player(t_mlx_data mlx_data, t_map_data map_data)
{
	int x;
	int y;

	x = map_data.element_size * mlx_data.desc->play_pos.x;
	y = map_data.element_size * mlx_data.desc->play_pos.y;
	ft_put_pixel_to_image(mlx_data, x, y, map_data.player_color);
	ft_put_pixel_to_image(mlx_data, x + 1, y + 1, map_data.player_color);
	ft_put_pixel_to_image(mlx_data, x - 1, y - 1, map_data.player_color);
	ft_put_pixel_to_image(mlx_data, x + 1, y - 1, map_data.player_color);
	ft_put_pixel_to_image(mlx_data, x - 1, y + 1, map_data.player_color);
	ft_put_pixel_to_image(mlx_data, x, y + 1, map_data.player_color);
	ft_put_pixel_to_image(mlx_data, x, y - 1, map_data.player_color);
	ft_put_pixel_to_image(mlx_data, x + 1, y, map_data.player_color);
	ft_put_pixel_to_image(mlx_data, x - 1, y, map_data.player_color);
}

static void	ft_draw_camera(t_mlx_data mlx_data, t_map_data map_data)
{
	int x;
	int y;
	int m;
	int l;

	x = mlx_data.desc->play_pos.x * map_data.element_size + 10 / 2 *
		mlx_data.desc->dir_pos.x - map_data.element_size / 4;
	m = 0;
	while (x + m < x + map_data.element_size / 2)
	{
		l = 0;
		y = mlx_data.desc->play_pos.y * map_data.element_size + 10 / 2 *
			mlx_data.desc->dir_pos.y - map_data.element_size / 4;
		while (y + l < y + map_data.element_size / 2)
		{
			ft_put_pixel_to_image(mlx_data, x + m, y + l,
				map_data.camera_color);
			l++;
		}
		m++;
	}
}

int			ft_draw_map(t_mlx_data mlx_data)
{
	t_map_data	map_data;
	t_desc		*desc;

	desc = mlx_data.desc;
	map_data.element_size =
		(desc->y / 5) / desc->nb_l < (desc->x / 5) / desc->nb_col ?
			(desc->y / 5) / desc->nb_l : (desc->x / 5) / desc->nb_col;
	map_data.player_color = RED;
	map_data.camera_color = YELLOW;
	map_data.wall_color = BLACK;
	map_data.empty_color = GREEN;
	map_data.sprite_color = BLUE;
	ft_draw_map_all_elements(mlx_data, map_data);
	ft_draw_camera(mlx_data, map_data);
	ft_draw_player(mlx_data, map_data);
	return (1);
}
