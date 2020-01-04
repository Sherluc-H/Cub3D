/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 17:20:47 by lhuang            #+#    #+#             */
/*   Updated: 2020/01/04 11:05:50 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_show_error(t_error error, t_mlx_data *mlx_data)
{
	write(2, "Error\n", 6);
	if (error == MALLOC || error == PARSE)
		write(2, "Something went wrong\n", 21);
	else if (error == MLX)
		write(2, "Problem during call of a mlx function\n", 38);
	else if (error == ARG)
		write(2, "Wrong arguments\n", 16);
	else if (error == OPEN)
		write(2, "File cannot be found or opened\n", 31);
	else if (error == SCENE)
		write(2, "Scene creation went wrong\n", 26);
	else
		write(2, "Something went wrong\n", 21);
	ft_freer(mlx_data->desc);
	return (0);
}

int		ft_set_error(t_desc *desc, t_error error)
{
	desc->error = error;
	return (0);
}

int		ft_free_remain(t_remain **remain)
{
	if ((*remain))
	{
		free((*remain)->str);
		(*remain)->str = NULL;
		(*remain)->size = 0;
		free(*remain);
	}
	return (0);
}

int		ft_free_str(char *str, int r)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (r);
}

void	ft_freer(t_desc *desc)
{
	int j;

	j = 0;
	ft_free_str(desc->north_path, 0);
	ft_free_str(desc->south_path, 0);
	ft_free_str(desc->west_path, 0);
	ft_free_str(desc->east_path, 0);
	ft_free_str(desc->sprite_path, 0);
	ft_free_str(desc->scene_str, 0);
	if (desc->sprite_tab)
		free(desc->sprite_tab);
	if (desc->scene)
	{
		while (desc->scene[j])
		{
			ft_free_str(desc->scene[j], 0);
			j++;
		}
		free(desc->scene);
	}
}
