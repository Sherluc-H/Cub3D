/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_description.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 17:55:51 by lhuang            #+#    #+#             */
/*   Updated: 2020/01/03 15:24:54 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_parse_resolution(char *str, t_desc *desc, int *i)
{
	*i = *i + 1;
	if (!(ft_move_space(str, i)))
		return (-1);
	if ((desc->x = ft_get_number(str, i)) == -1)
		return (-1);
	if (!(ft_move_space(str, i)))
		return (-1);
	if ((desc->y = ft_get_number(str, i)) == -1)
		return (-1);
	if (desc->x > 2560)
		desc->x = 2560;
	if (desc->y > 1440)
		desc->y = 1440;
	desc->resolution_ok = 1;
	if (!(ft_end_identifier(str, i)))
		return (-1);
	return (1);
}

int		ft_parse_path(char *str, t_desc *desc, int *i)
{
	int path_id;

	path_id = 0;
	if (!(path_id = ft_get_identifier(str, i, desc)))
		return (-1);
	if (path_id == SPRITE)
		*i = *i + 1;
	else
		*i = *i + 2;
	if (!(ft_move_space(str, i)))
		return (-1);
	if (!(ft_get_path(str, i, desc, path_id)))
		return (-1);
	if (!(ft_end_identifier(str, i)))
		return (-1);
	return (1);
}

int		ft_parse_color(char *str, int tab[3], int *color_ok, int *desc_color)
{
	int i;

	i = 1;
	if (!(ft_move_space(str, &i)))
		return (-1);
	if ((tab[0] = ft_get_number(str, &i)) == -1 || tab[0] < 0 || tab[0] > 255)
		return (-1);
	if (str[i] == ',')
		i = i + 1;
	else
		return (-1);
	if ((tab[1] = ft_get_number(str, &i)) == -1 || tab[1] < 0 || tab[1] > 255)
		return (-1);
	if (str[i] == ',')
		i = i + 1;
	else
		return (-1);
	if ((tab[2] = ft_get_number(str, &i)) == -1 || tab[2] < 0 || tab[2] > 255)
		return (-1);
	*color_ok = 1;
	if (!(ft_end_identifier(str, &i)))
		return (-1);
	*desc_color = tab[0] * 65536 + tab[1] * 256 + tab[2];
	return (1);
}

void	ft_give_path(t_desc *desc, int path_id, char *path)
{
	if (path_id == NORTH)
		desc->north_path = path;
	else if (path_id == SOUTH)
		desc->south_path = path;
	else if (path_id == WEST)
		desc->west_path = path;
	else if (path_id == EAST)
		desc->east_path = path;
	else if (path_id == SPRITE)
		desc->sprite_path = path;
}
