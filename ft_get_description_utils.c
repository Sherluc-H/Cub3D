/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_description_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 17:58:25 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/01 18:07:37 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_move_space(char *str, int *i)
{
	if (ft_is_space(str[*i]))
	{
		while (ft_is_space(str[*i]))
		{
			*i = *i + 1;
		}
	}
	else
		return (0);
	return (1);
}

int		ft_end_identifier(char *str, int *i)
{
	if (ft_is_space(str[*i]) || str[*i] == '\n')
	{
		while (ft_is_space(str[*i]))
			*i = *i + 1;
		if (str[*i] == '\n')
		{
			while (str[*i] == '\n')
				*i = *i + 1;
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
}

int		ft_get_number(char *str, int *i)
{
	int		j;
	char	*new;

	j = 0;
	new = NULL;
	if (ft_is_number(str[*i]))
	{
		j = 0;
		while (ft_is_number(str[*i + j]))
			j++;
		new = malloc(sizeof(char) * (j + 1));
		j = 0;
		while (ft_is_number(str[*i]))
		{
			new[j] = str[*i];
			*i = *i + 1;
			j++;
		}
		new[j] = '\0';
		return (ft_atoi_simple(new));
	}
	else
		return (-1);
}

int		ft_get_path(char *str, int *i, t_desc *desc, int path_id)
{
	int		j;
	char	*new;

	j = 0;
	new = NULL;
	if (ft_is_print(str[*i]))
	{
		j = 0;
		while (ft_is_print(str[*i + j]))
			j++;
		new = malloc(sizeof(char) * (j + 1));
		j = 0;
		while (ft_is_print(str[*i]))
		{
			new[j] = str[*i];
			*i = *i + 1;
			j++;
		}
		new[j] = '\0';
		if (path_id == NORTH)
			desc->north = new;
		else if (path_id == SOUTH)
			desc->south = new;
		else if (path_id == WEST)
			desc->west = new;
		else if (path_id == EAST)
			desc->east = new;
		else if (path_id == SPRITE)
			desc->sprite = new;
		return (1);
	}
	else
		return (0);
}

int		ft_get_identifier(char *str, int *i, t_desc *desc)
{
	if (str[*i] == 'N' && str[*i + 1] == 'O' && desc->north == NULL)
	{
		*i = *i + 2;
		return (NORTH);
	}
	else if (str[*i] == 'S' && str[*i + 1] == 'O' && desc->south == NULL)
	{
		*i = *i + 2;
		return (SOUTH);
	}
	else if (str[*i] == 'W' && str[*i + 1] == 'E' && desc->west == NULL)
	{
		*i = *i + 2;
		return (WEST);
	}
	else if (str[*i] == 'E' && str[*i + 1] == 'A' && desc->east == NULL)
	{
		*i = *i + 2;
		return (EAST);
	}
	else if (str[*i] == 'S' && desc->sprite == NULL)
	{
		*i = *i + 1;
		return (SPRITE);
	}
	else
		return (0);
}
