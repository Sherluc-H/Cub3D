/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:16:26 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/29 17:26:58 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_rotate_camera(t_dir_pos *dir_pos, double rot_angle)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = dir_pos->x;
	dir_pos->x = dir_pos->x * cos(rot_angle) - dir_pos->y * sin(rot_angle);
	dir_pos->y = old_dir_x * sin(rot_angle) + dir_pos->y * cos(rot_angle);
	old_plane_x = dir_pos->plane_x;
	dir_pos->plane_x = dir_pos->plane_x * cos(rot_angle) -
					dir_pos->plane_y * sin(rot_angle);
	dir_pos->plane_y = old_plane_x * sin(rot_angle) +
					dir_pos->plane_y * cos(rot_angle);
}

static void	ft_move_to_new_pos(t_mlx_data *mlx_data,
			double new_play_x, double new_play_y)
{
	if (mlx_data->desc->scene[(int)(float)(new_play_y)]
							[(int)(float)(new_play_x)] == '0')
	{
		mlx_data->desc->play_pos.x = new_play_x;
		mlx_data->desc->play_pos.y = new_play_y;
		ft_draw_walls(*mlx_data);
		ft_draw_map(mlx_data->desc, *mlx_data);
		mlx_put_image_to_window(mlx_data->mlx_ptr,
			mlx_data->win_ptr, mlx_data->img_ptr, 0, 0);
		ft_display_texture_top(*mlx_data);
	}
}

static void	ft_move_left_right(int key, t_mlx_data *mlx_data,
			double *new_play_x, double *new_play_y)
{
	t_player_pos	play_pos;
	t_dir_pos		dir_pos;

	play_pos = mlx_data->desc->play_pos;
	dir_pos = mlx_data->desc->dir_pos;
	if (key == KEY_A || key == KEY_Q)
	{
		if (mlx_data->desc->scene[(int)(float)play_pos.y]
			[(int)(float)(play_pos.x + dir_pos.y *
			(MOVE_DIST + 0.000001))] == '0')
			*new_play_x = play_pos.x + dir_pos.y * (MOVE_DIST);
		if (mlx_data->desc->scene[(int)(float)(play_pos.y - dir_pos.x *
			(MOVE_DIST + 0.000001))][(int)(float)(play_pos.x)] == '0')
			*new_play_y = play_pos.y - dir_pos.x * (MOVE_DIST);
	}
	else if (key == KEY_D)
	{
		if (mlx_data->desc->scene[(int)(float)play_pos.y]
			[(int)(float)(play_pos.x - dir_pos.y *
			(MOVE_DIST + 0.000001))] == '0')
			*new_play_x = play_pos.x - dir_pos.y * (MOVE_DIST);
		if (mlx_data->desc->scene[(int)(float)(play_pos.y + dir_pos.x *
			(MOVE_DIST + 0.000001))][(int)(float)(play_pos.x)] == '0')
			*new_play_y = play_pos.y + dir_pos.x * (MOVE_DIST);
	}
}

static void	ft_move_up_down(int key, t_mlx_data *mlx_data,
			double *new_play_x, double *new_play_y)
{
	t_player_pos	play_pos;
	t_dir_pos		dir_pos;

	play_pos = mlx_data->desc->play_pos;
	dir_pos = mlx_data->desc->dir_pos;
	if (key == KEY_W || key == KEY_Z)
	{
		if (mlx_data->desc->scene[(int)(float)play_pos.y]
			[(int)(float)(play_pos.x + dir_pos.x *
			(MOVE_DIST + 0.000001))] == '0')
			*new_play_x = play_pos.x + dir_pos.x * (MOVE_DIST);
		if (mlx_data->desc->scene[(int)(float)(play_pos.y + dir_pos.y *
			(MOVE_DIST + 0.000001))][(int)(float)(play_pos.x)] == '0')
			*new_play_y = play_pos.y + dir_pos.y * (MOVE_DIST);
	}
	else if (key == KEY_S)
	{
		if (mlx_data->desc->scene[(int)(float)play_pos.y]
			[(int)(float)(play_pos.x - dir_pos.x *
			(MOVE_DIST + 0.000001))] == '0')
			*new_play_x = play_pos.x - dir_pos.x * (MOVE_DIST);
		if (mlx_data->desc->scene[(int)(float)(play_pos.y - dir_pos.y *
			(MOVE_DIST + 0.000001))][(int)(float)(play_pos.x)] == '0')
			*new_play_y = play_pos.y - dir_pos.y * (MOVE_DIST);
	}
}

int			ft_key_pressed(int key, t_mlx_data *mlx_data)
{
	double camera_rot_angle;
	double new_play_x;
	double new_play_y;

	new_play_x = mlx_data->desc->play_pos.x;
	new_play_y = mlx_data->desc->play_pos.y;
	camera_rot_angle = (M_PI / 180) * ROTATION_ANGLE;
	if (key == KEY_ESC)
		ft_exit_hook(mlx_data);
	else if (key == KEY_LEFT)
		ft_rotate_camera(&(mlx_data->desc->dir_pos), -camera_rot_angle);
	else if (key == KEY_RIGHT)
		ft_rotate_camera(&(mlx_data->desc->dir_pos), camera_rot_angle);
	else if (key == KEY_W || key == KEY_Z || key == KEY_S)
		ft_move_up_down(key, mlx_data, &new_play_x, &new_play_y);
	else if (key == KEY_A || key == KEY_Q || key == KEY_D)
		ft_move_left_right(key, mlx_data, &new_play_x, &new_play_y);
	if (fabs((float)new_play_y - (int)(float)new_play_y) < 0.000001 &&
		fabs((float)new_play_x - (int)(float)new_play_x) < 0.000001)
		if ((ft_precise_collision(mlx_data, new_play_x, new_play_y)) == 0)
			return (0);
	ft_move_to_new_pos(mlx_data, new_play_x, new_play_y);
	// printf("!x = %f, int x = %d, y = %f, int y = %d|%c|\n", mlx_data->desc->play_pos.x, (int)(float)(mlx_data->desc->play_pos.x), mlx_data->desc->play_pos.y, (int)(float)(mlx_data->desc->play_pos.y), mlx_data->desc->scene[(int)(float)(mlx_data->desc->play_pos.y)][(int)(float)(mlx_data->desc->play_pos.x)]);
	// printf("dir x = %f, int plane x = %f, dir y = %f, int plane y = %f\n", mlx_data->desc->dir_pos.x, mlx_data->desc->dir_pos.plane_x, mlx_data->desc->dir_pos.y, mlx_data->desc->dir_pos.plane_y);
	//printf("key pressed = %d\n", key);
	return (0);
}
