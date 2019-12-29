/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 17:20:47 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/29 20:53:44 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_show_error(t_error error, t_mlx_data *mlx_data)
{
	printf("%d\n", error);
	write(2, "Error\n", 6);
	if (error == MALLOC)
	{
		write(2, "Problem during allocation\n", 26);
	}
	else if (error == MLX)
	{
		write(2, "Problem during call of a mlx function\n", 39);
	}
	else if (error == ARG)
	{
		write(2, "Wrong arguments\n", 16);
	}
	else if (error == PARSE)
	{
		write(2, "Description file not acceptable\n", 33);
	}
	else if (error == OPEN)
	{
		write(2, "File cannot be found or opened\n", 31);
	}
	else
		write(2, "Something went wrong\n", 21);
	ft_freer(mlx_data->desc);
	system("leaks Cub3D");
	return (0);
}

int		ft_set_error(t_desc *desc, t_error error)
{
	printf("%d\n", error);
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

int		ft_free_str(char *str)
{
	if (str)
	{
		printf("%s\n", str);
		printf("freed\n");
		free(str);
		str = NULL;
	}
	return (0);
}

void	ft_freer(t_desc *desc)
{
	int j;

	j = 0;
	ft_free_str(desc->north_path);
	ft_free_str(desc->south_path);
	ft_free_str(desc->west_path);
	ft_free_str(desc->east_path);
	ft_free_str(desc->sprite_path);
	ft_free_str(desc->scene_str);
	if (desc->sprite_tab)
		free(desc->sprite_tab);
	if (desc->scene)
	{
		while (desc->scene[j])
		{
			ft_free_str(desc->scene[j]);
			j++;
		}
		free(desc->scene);
	}
}
