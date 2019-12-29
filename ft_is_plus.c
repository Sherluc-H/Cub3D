/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 17:34:40 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/29 17:35:51 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_is_path_identifier(char *str, int i)
{
	return ((str[i] == 'N' && str[i + 1] == 'O') ||
			(str[i] == 'S' && str[i + 1] == 'O') ||
			(str[i] == 'W' && str[i + 1] == 'E') ||
			(str[i] == 'E' && str[i + 1] == 'A') ||
			(str[i] == 'S' && str[i + 1] == ' '));
}

int		ft_is_description_ready_scene(t_desc *desc)
{
	return (desc->resolution_ok && desc->north_path &&
			desc->south_path && desc->west_path && desc->east_path &&
			desc->sprite_path && desc->floor_ok && desc->ceiling_ok);
}
