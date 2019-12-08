/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_description.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 17:55:51 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/08 16:45:19 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_parse_resolution(char *str, t_desc *desc, int *i)
{
	*i = *i + 1;
	if (!(ft_move_space(str, i)))
		return (0);
	if ((desc->x = ft_get_number(str, i)) == -1)
		return (0);
	if (!(ft_move_space(str, i)))
		return (0);
	if ((desc->y = ft_get_number(str, i)) == -1)
		return (0);
	desc->resolution_ok = 1;
	if (!(ft_end_identifier(str, i)))
		return (0);
	return (1);
}

int		ft_parse_path(char *str, t_desc *desc, int *i)
{
	int path_id;

	path_id = 0;
	if (!(path_id = ft_get_identifier(str, i, desc)))
		return (0);
	if (!(ft_move_space(str, i)))
		return (0);
	if (!(ft_get_path(str, i, desc, path_id)))
		return (0);
	if (!(ft_end_identifier(str, i)))
		return (0);
	return (1);
}

int		ft_parse_color(char *str, int tab[3], int *i, int *color_ok)
{
	*i = *i + 1;
	if (!(ft_move_space(str, i)))
		return (0);
	if ((tab[0] = ft_get_number(str, i)) == -1 || tab[0] < 0 || tab[0] > 255)
		return (0);
	if (str[*i] == ',')
		*i = *i + 1;
	else
		return (0);
	if ((tab[1] = ft_get_number(str, i)) == -1 || tab[1] < 0 || tab[1] > 255)
		return (0);
	if (str[*i] == ',')
		*i = *i + 1;
	else
		return (0);
	if ((tab[2] = ft_get_number(str, i)) == -1 || tab[2] < 0 || tab[2] > 255)
		return (0);
	*color_ok = 1;
	if (!(ft_end_identifier(str, i)))
		return (0);
	return (1);
}

int		ft_is_path_identifier(char *str, int i)
{
	return ((str[i] == 'N' && str[i + 1] == 'O') ||
			(str[i] == 'S' && str[i + 1] == 'O') ||
			(str[i] == 'W' && str[i + 1] == 'E') ||
			(str[i] == 'E' && str[i + 1] == 'A') ||
			str[i] == 'S');
}

int		ft_is_description_ready_scene(t_desc *desc)
{
	return (desc->resolution_ok && desc->north &&
			desc->south && desc->west && desc->east &&
			desc->sprite && desc->floor_ok && desc->ceiling_ok);
}

int		ft_is_scene_ok(char *str, int i)
{
	return (ft_is_scene_element(str[i]) || ft_is_player_start(str[i]) ||
			(str[i] == '\n' && str[i - 1] == '1') ||
			(str[i] == ' ' && (ft_is_scene_element(str[i - 1]) ||
			ft_is_player_start(str[i - 1]) || str[i - 1] == ' ')));
}

int		ft_check_scene(t_desc *desc)
{
	int j;
	int k;
	int first_line;

	j = 0;
	first_line = 0;
	while (desc->scene[j])
	{
		k = 0;
		while (desc->scene[j][k])
			k++;
		if (first_line == 0)
			first_line = k;
		if (first_line != k)
			return (0);
		j++;
	}
	desc->nb_col = k;
	desc->nb_l = j;
	//check first line
	k = 0;
	while (desc->scene[0][k])
	{
		if (desc->scene[0][k] != '1')
			return (0);
		k++;
	}
	k = 0;
	//check last line
	while (desc->scene[j - 1][k])
	{
		if (desc->scene[j - 1][k] != '1')
			return (0);
		k++;
	}
	return (1);
}

int		ft_check_file_content(char *str, t_desc *desc)
{
	int		i;
	int		j;
	int		k;
	int		l;
	int		player_found;
	int		first_line;
	int		row;

	row = 0;
	player_found = 0;
	first_line = 1;
	i = 0;
	j = 0;
	k = 0;
	l = 0;
	while (str[i])
	{
		if (str[i] == 'R' && desc->resolution_ok == 0)
		{
			if (!(ft_parse_resolution(str, desc, &i)))
				return (0);
		}
		else if (ft_is_path_identifier(str, i))
		{
			if (!(ft_parse_path(str, desc, &i)))
				return (0);
		}
		else if (str[i] == 'F' && desc->floor_ok == 0)
		{
			if (!(ft_parse_color(str, desc->floor_tab, &i, &(desc->floor_ok))))
				return (0);
			desc->floor_color = desc->floor_tab[0] * 65536 + desc->floor_tab[1] * 256 + desc->floor_tab[2];
		}
		else if (str[i] == 'C' && desc->ceiling_ok == 0)
		{
			if (!(ft_parse_color(str, desc->ceiling_tab, &i, &(desc->ceiling_ok))))
				return (0);
			desc->ceiling_color = desc->ceiling_tab[0] * 65536 + desc->ceiling_tab[1] * 256 + desc->ceiling_tab[2];
		}
		else if (str[i] == '1' && ft_is_description_ready_scene(desc))
		{
			j = 0;
			while (str[i] && ft_is_scene_ok(str, i))
			{
				if (str[i] == '\n')
					row++;
				if (ft_is_player_start(str[i]) && player_found)
					return (0);
				if (ft_is_player_start(str[i]))
				{
					if (str[i] == 'N')
					{
						desc->dir_pos.x = 0;
						desc->dir_pos.y = -1;
					}
					else if(str[i] == 'S')
					{
						desc->dir_pos.x = 0;
						desc->dir_pos.y = 1;
					}
					else if(str[i] == 'W')
					{
						desc->dir_pos.x = -1;
						desc->dir_pos.y = 0;
					}
					else if(str[i] == 'E')
					{
						desc->dir_pos.x = 1;
						desc->dir_pos.y = 0;
					}
					player_found = 1;
				}
				if (str[i] == '\n')//check first char of line
				{
					if (str[i + 1] != '1')
						return (0);
				}
				i++;
				j++;
			}
			if (str[i] == '\0' && str[i - 1] == '1')
			{
				row++;
				desc->scene = malloc(sizeof(char *) * (row + 1));
				row = 0;
				i = i - j;
				while (str[i] && ft_is_scene_ok(str, i))
				{
					k = 0;
					j = 0;
					l = 0;
					while (str[i + j] != '\n' && str[i + j] != '\0')
					{
						if (str[i + j] != ' ')
							l++;
						j++;
					}
					desc->scene[row] = malloc(sizeof(char) * (l + 1));
					l = 0;
					while (k < j)
					{
						if (str[i] != ' ')
						{
							desc->scene[row][l] = str[i];
							l++;
						}
						i++;
						k++;
					}
					desc->scene[row][l] = '\0';
					if (str[i] == '\n' || str[i] == '\0')
						row++;
					i++;
				}
				desc->scene[row] = NULL;
				if (!(ft_check_scene(desc)))
					return (0);
				free(str);
				str = NULL;
				return (1);
			}
			else
				return (0);
		}
		else
			return (0);
	}
	return (1);
}
