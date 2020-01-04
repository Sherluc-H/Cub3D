/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_sprite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/02 16:02:19 by lhuang            #+#    #+#             */
/*   Updated: 2020/01/03 16:45:41 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_sort_sprite_tab(t_sprite *sprite_tab, double *sprite_dist_tab,
			int nb_sprite)
{
	t_sprite	sprite_tmp;
	double		dist_tmp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < nb_sprite)
	{
		j = 0;
		while (j < nb_sprite - 1)
		{
			if (sprite_dist_tab[j] < sprite_dist_tab[j + 1])
			{
				sprite_tmp = sprite_tab[j];
				sprite_tab[j] = sprite_tab[j + 1];
				sprite_tab[j + 1] = sprite_tmp;
				dist_tmp = sprite_dist_tab[j];
				sprite_dist_tab[j] = sprite_dist_tab[j + 1];
				sprite_dist_tab[j + 1] = dist_tmp;
			}
			j++;
		}
		i++;
	}
}

static void	ft_sprite_data_init(t_mlx_data mlx_data, t_draw_spt_data *draw_dt)
{
	draw_dt->sprite_screen_x = (int)((mlx_data.desc->x / 2) * (1 +
		draw_dt->transform_x / draw_dt->transform_y));
	draw_dt->sprite_height = fabs((double)(int)(mlx_data.desc->y /
		(draw_dt->transform_y)));
	draw_dt->draw_start_y = -draw_dt->sprite_height / 2 + mlx_data.desc->y / 2;
	if (draw_dt->draw_start_y < 0)
		draw_dt->draw_start_y = 0;
	draw_dt->draw_end_y = draw_dt->sprite_height / 2 + mlx_data.desc->y / 2;
	if (draw_dt->draw_end_y >= mlx_data.desc->y)
		draw_dt->draw_end_y = mlx_data.desc->y;
	draw_dt->sprite_width = fabs((double)(int)(mlx_data.desc->y /
		(draw_dt->transform_y)));
	draw_dt->draw_start_x = -draw_dt->sprite_width / 2 +
		draw_dt->sprite_screen_x;
	if (draw_dt->draw_start_x < 0)
		draw_dt->draw_start_x = 0;
	draw_dt->draw_end_x = draw_dt->sprite_width / 2 + draw_dt->sprite_screen_x;
	if (draw_dt->draw_end_x >= mlx_data.desc->x)
		draw_dt->draw_end_x = mlx_data.desc->x;
}

static void	ft_get_transform_x_y(t_mlx_data mlx_data, double *transform_x,
			double *transform_y, int i)
{
	double sprite_x;
	double sprite_y;
	double inv_det;

	sprite_x = mlx_data.desc->sprite_tab[i].x - mlx_data.desc->play_pos.x;
	sprite_y = mlx_data.desc->sprite_tab[i].y - mlx_data.desc->play_pos.y;
	inv_det = 1.0 / (mlx_data.desc->dir_pos.plane_x * mlx_data.desc->dir_pos.y -
		mlx_data.desc->dir_pos.x * mlx_data.desc->dir_pos.plane_y);
	*transform_x = inv_det * (mlx_data.desc->dir_pos.y * sprite_x -
		mlx_data.desc->dir_pos.x * sprite_y);
	*transform_y = inv_det * (-mlx_data.desc->dir_pos.plane_y * sprite_x +
		mlx_data.desc->dir_pos.plane_x * sprite_y);
}

int			ft_draw_sprite(t_mlx_data mlx_data, t_desc *desc,
	double *perp_dist_buffer, int i)
{
	double			*sprite_dist;
	t_draw_spt_data	draw_data;

	if (!(sprite_dist = malloc(sizeof(double) * (desc->nb_sprite + 1))))
		return (-1);
	while (i < desc->nb_sprite)
	{
		sprite_dist[i] = ((desc->play_pos.x - desc->sprite_tab[i].x) *
		(desc->play_pos.x - desc->sprite_tab[i].x) + (desc->play_pos.y -
		desc->sprite_tab[i].y) * (desc->play_pos.y - desc->sprite_tab[i].y));
		i++;
	}
	ft_sort_sprite_tab(desc->sprite_tab, sprite_dist, desc->nb_sprite);
	i = 0;
	draw_data.texture = mlx_data.tex_sprite;
	while (i < desc->nb_sprite)
	{
		ft_get_transform_x_y(mlx_data, &draw_data.transform_x,
			&draw_data.transform_y, i);
		ft_sprite_data_init(mlx_data, &draw_data);
		ft_draw_sprite_loop(mlx_data, draw_data, perp_dist_buffer);
		i++;
	}
	free(sprite_dist);
	return (1);
}
