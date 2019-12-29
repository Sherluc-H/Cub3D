/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_keys_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 17:26:23 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/29 17:28:14 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_precise_collision(t_mlx_data *mlx_data,
	double new_play_x, double new_play_y)
{
	if (new_play_y < mlx_data->desc->play_pos.y)
	{
		if (mlx_data->desc->scene[(int)(float)(new_play_y) - 1]
			[(int)(float)(new_play_x) - 1] != '0')
			return (0);
	}
	else if (new_play_y > mlx_data->desc->play_pos.y)
	{
		if (mlx_data->desc->scene[(int)(float)(new_play_y)]
			[(int)(float)(new_play_x) - 1] != '0')
			return (0);
	}
	if (new_play_x > mlx_data->desc->play_pos.x)
	{
		if (mlx_data->desc->scene[(int)(float)(new_play_y) - 1]
			[(int)(float)(new_play_x)] != '0')
			return (0);
	}
	else if (new_play_x < mlx_data->desc->play_pos.x)
	{
		if (mlx_data->desc->scene[(int)(float)(new_play_y) - 1]
			[(int)(float)(new_play_x) - 1] != '0')
			return (0);
	}
	return (1);
}
