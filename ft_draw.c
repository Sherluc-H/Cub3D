/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:30:30 by lhuang            #+#    #+#             */
/*   Updated: 2020/01/03 16:45:01 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_wall_data_init(t_mlx_data mlx_data,
	t_draw_wall_data *draw_data, int x)
{
	draw_data->camera_x = 2 * x / (double)mlx_data.desc->x - 1.;
	draw_data->raydir_x = mlx_data.desc->dir_pos.x +
		mlx_data.desc->dir_pos.plane_x * draw_data->camera_x;
	draw_data->raydir_y = mlx_data.desc->dir_pos.y +
		mlx_data.desc->dir_pos.plane_y * draw_data->camera_x;
	draw_data->map_x = (int)draw_data->play_pos.x;
	draw_data->map_y = (int)draw_data->play_pos.y;
	draw_data->deltadist_x = fabs(1.0 / draw_data->raydir_x);
	draw_data->deltadist_y = fabs(1.0 / draw_data->raydir_y);
	draw_data->hit = 0;
	draw_data->top = 1;
	draw_data->left = -1;
	draw_data->step_x = draw_data->raydir_x < 0 ? -1 : 1;
	draw_data->sidedist_x = draw_data->raydir_x < 0 ? (draw_data->play_pos.x -
		draw_data->map_x) * draw_data->deltadist_x : (draw_data->map_x + 1.0 -
			draw_data->play_pos.x) * draw_data->deltadist_x;
	draw_data->step_y = draw_data->raydir_y < 0 ? -1 : 1;
	draw_data->sidedist_y = draw_data->raydir_y < 0 ? (draw_data->play_pos.y -
		draw_data->map_y) * draw_data->deltadist_y : (draw_data->map_y + 1.0 -
			draw_data->play_pos.y) * draw_data->deltadist_y;
}

static double	ft_wall_hit_dist(t_mlx_data mlx_data,
	t_draw_wall_data *draw_data)
{
	while (draw_data->hit == 0)
	{
		if (draw_data->sidedist_x < draw_data->sidedist_y)
		{
			draw_data->sidedist_x += draw_data->deltadist_x;
			draw_data->map_x += draw_data->step_x;
			draw_data->side = 1;
		}
		else
		{
			draw_data->sidedist_y += draw_data->deltadist_y;
			draw_data->map_y += draw_data->step_y;
			draw_data->side = 0;
		}
		if (mlx_data.desc->scene[draw_data->map_y][draw_data->map_x] == '1')
			draw_data->hit = 1;
	}
	draw_data->perpwalldist = draw_data->side == 0 ? (draw_data->map_y -
		draw_data->play_pos.y + (1 - draw_data->step_y) / 2) /
			(double)draw_data->raydir_y : (draw_data->map_x -
				draw_data->play_pos.x + (1 - draw_data->step_x) / 2) /
					(double)draw_data->raydir_x;
	if (draw_data->perpwalldist < 0.0066)
		draw_data->perpwalldist = 0.0066;
	return (draw_data->perpwalldist);
}

static void		ft_wall_tex_init(t_mlx_data mlx_data,
	t_draw_wall_data *draw_data)
{
	draw_data->texture = mlx_data.tex_north;
	if (mlx_data.desc->scene[draw_data->map_y][draw_data->map_x] == '1' &&
			draw_data->left == 1 && draw_data->side)
		draw_data->texture = mlx_data.tex_east;
	else if (mlx_data.desc->scene[draw_data->map_y][draw_data->map_x] == '1' &&
			draw_data->left == -1 && draw_data->side)
		draw_data->texture = mlx_data.tex_west;
	else if (mlx_data.desc->scene[draw_data->map_y][draw_data->map_x] == '1' &&
			draw_data->top == 1 && !draw_data->side)
		draw_data->texture = mlx_data.tex_north;
	else if (mlx_data.desc->scene[draw_data->map_y][draw_data->map_x] == '1' &&
			draw_data->top == -1 && !draw_data->side)
		draw_data->texture = mlx_data.tex_south;
	draw_data->wall_x = draw_data->side == 0 ? draw_data->play_pos.x +
		draw_data->perpwalldist * draw_data->raydir_x : draw_data->play_pos.y +
			draw_data->perpwalldist * draw_data->raydir_y;
	draw_data->wall_x -= floor(draw_data->wall_x);
	draw_data->texture_x = (int)(draw_data->wall_x *
		(double)draw_data->texture.width);
	if (draw_data->side == 0 && draw_data->raydir_y > 0)
		draw_data->texture_x = draw_data->texture.width -
			draw_data->texture_x - 1;
	if (draw_data->side == 1 && draw_data->raydir_x < 0)
		draw_data->texture_x = draw_data->texture.width -
			draw_data->texture_x - 1;
}

static void		ft_draw_walls(t_mlx_data mlx_data, double *perp_dist_buffer)
{
	int					x;
	t_draw_wall_data	draw_dt;

	x = 0;
	draw_dt.play_pos = mlx_data.desc->play_pos;
	while (x < mlx_data.desc->x)
	{
		ft_wall_data_init(mlx_data, &draw_dt, x);
		if (draw_dt.raydir_y > 0)
			draw_dt.top = -1;
		if (draw_dt.raydir_x > 0)
			draw_dt.left = 1;
		perp_dist_buffer[x] = ft_wall_hit_dist(mlx_data, &draw_dt);
		draw_dt.line_height = (int)(mlx_data.desc->y / draw_dt.perpwalldist);
		draw_dt.draw_start_y = -draw_dt.line_height / 2 + mlx_data.desc->y / 2;
		if (draw_dt.draw_start_y < 0)
			draw_dt.draw_start_y = 0;
		draw_dt.draw_end_y = draw_dt.line_height / 2 + mlx_data.desc->y / 2;
		if (draw_dt.draw_end_y > mlx_data.desc->y)
			draw_dt.draw_end_y = mlx_data.desc->y;
		ft_wall_tex_init(mlx_data, &draw_dt);
		ft_draw_wall_loop(mlx_data, draw_dt, x, 0);
		x++;
	}
}

int				ft_draw(t_mlx_data mlx_data)
{
	double *perp_dist_buffer;

	if (!(perp_dist_buffer = malloc(sizeof(double) * (mlx_data.desc->x + 1))))
		return (-1);
	ft_draw_walls(mlx_data, perp_dist_buffer);
	if ((ft_draw_sprite(mlx_data, mlx_data.desc, perp_dist_buffer, 0)) == -1)
		return (-1);
	free(perp_dist_buffer);
	return (1);
}
