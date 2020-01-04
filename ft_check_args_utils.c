/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 17:48:02 by lhuang            #+#    #+#             */
/*   Updated: 2020/01/04 11:13:13 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ft_create_line(t_desc *desc, char *line, int j, int *i)
{
	char *new_line;

	new_line = NULL;
	if (desc->nb_l == 0)
		desc->nb_col = j;
	else
	{
		if (desc->nb_col != j)
			return (NULL);
	}
	if (!(new_line = malloc(sizeof(char) * (j + 1))))
		return (NULL);
	j = 0;
	while (line[*i] != '\0' && line[*i] != '\n')
	{
		if (ft_is_scene_element(line[*i]) || ft_is_player_start(line[*i]))
		{
			new_line[j] = line[*i];
			j++;
		}
		*i = *i + 1;
	}
	new_line[j] = '\0';
	return (new_line);
}

static char	*ft_clean_scene_line(t_desc *desc, char *line, int *i, int k)
{
	int		j;

	j = 0;
	while (line[*i + k] != '\0' && line[*i + k] != '\n')
	{
		if (!(ft_is_scene_element(line[*i + k]) ||
			ft_is_player_start(line[*i + k]) || line[*i + k] == ' '))
			return (NULL);
		if (ft_is_scene_element(line[*i + k]))
		{
			if (line[*i + k] == '2')
				desc->nb_sprite = desc->nb_sprite + 1;
			j++;
		}
		else if (ft_is_player_start(line[*i + k]))
		{
			if (desc->player_found == 1)
				return (NULL);
			ft_add_player(desc, line[*i + k], j, desc->nb_l);
			line[*i + k] = '0';
			j++;
		}
		k++;
	}
	return (ft_create_line(desc, line, j, i));
}

static int	ft_create_sprite_tab(t_desc *desc, int i, int j)
{
	int k;

	if (!desc->player_found)
		return (-1);
	if (!(desc->sprite_tab = malloc(sizeof(*(desc->sprite_tab)) *
		desc->nb_sprite)))
		return (-1);
	i = 0;
	k = 0;
	while (desc->scene[i])
	{
		j = 0;
		while (desc->scene[i][j])
		{
			if (desc->scene[i][j] == '2')
			{
				(desc->sprite_tab)[k].x = j + 0.5;
				(desc->sprite_tab)[k].y = i + 0.5;
				k++;
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_add_to_scene(t_desc *desc, char *scene_str, int *i, int count)
{
	char	*clean_line;
	int		j;

	clean_line = NULL;
	j = 0;
	desc->scene[desc->nb_l] = NULL;
	if (!(clean_line = ft_clean_scene_line(desc, scene_str, i, 0)))
		return (0);
	if (clean_line[desc->nb_col - 1] != '1')
	{
		return (ft_free_str(clean_line, 0));
	}
	if (desc->nb_l == 0 || desc->nb_l == count)
	{
		while (clean_line[j])
		{
			if (clean_line[j] != '1')
				return (ft_free_str(clean_line, 0));
			j++;
		}
	}
	desc->scene[desc->nb_l] = clean_line;
	desc->nb_l = desc->nb_l + 1;
	return (1);
}

int			ft_create_scene(t_desc *desc, char *scene_str, int i)
{
	int		count;

	count = 0;
	while (scene_str[i])
	{
		if (scene_str[i] == '\n')
			count++;
		i++;
	}
	if (count <= 1)
		return (-1);
	i = 0;
	if (!(desc->scene = malloc(sizeof(char *) * (count + 2))))
		return (-1);
	while (desc->nb_l < count + 1)
	{
		if ((ft_add_to_scene(desc, scene_str, &i, count)) == 0)
			return (0);
		i++;
	}
	desc->scene[desc->nb_l] = NULL;
	if ((ft_create_sprite_tab(desc, 0, 0)) == -1)
		return (-1);
	return (1);
}
