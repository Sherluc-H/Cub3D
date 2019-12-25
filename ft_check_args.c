/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 17:48:30 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/24 17:36:40 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_check_file_extension(char *filename, char *extension)
{
	int i;
	int count;
	int filename_size;
	int extension_size;

	i = 0;
	count = 0;
	filename_size = ft_strlen(filename);
	extension_size = ft_strlen(extension);
	if (filename_size > extension_size)
	{
		while (extension_size - i > 0)
		{
			if (filename[filename_size - i - 1] ==
				extension[extension_size - i - 1])
				count++;
			i++;
		}
		if (count == extension_size)
			return (1);
	}
	return (0);
}

char	*ft_strjoin_with_sep(char *str1, char *str2, char sep)
{
	int		i;
	int		j;
	int		str1_size;
	int		str2_size;
	char	*str;

	i = 0;
	j = 0;
	if (str1 == NULL)
		str1_size = 0;
	else
		str1_size = ft_strlen(str1);
	str2_size = ft_strlen(str2);
	if (!(str = malloc(sizeof(char) * (str1_size + str2_size + 2))))
		return (NULL);
	while (i < str1_size)
	{
		str[i] = str1[i];
		i++;
	}
	if (str1_size > 0)
	{
		str[i] = sep;
		i++;
	}
	while (j < str2_size)
	{
		str[i + j] = str2[j];
		j++;
	}
	str[i + j] = '\0';
	free(str1);
	// free(str2);//ne pas free la line car elle sera free par le ft_get_next_line
	return (str);
}

void	ft_add_player(t_desc *desc, char player_char, int j, int l)
{
	desc->player_found = 1;
	if (player_char == 'N')
	{
		desc->dir_pos.x = 0;
		desc->dir_pos.y = -1;
		desc->dir_pos.plane_x = 0.66;
		desc->dir_pos.plane_y = 0;
	}
	else if (player_char == 'S')
	{
		desc->dir_pos.x = 0;
		desc->dir_pos.y = 1;
		desc->dir_pos.plane_x = -0.66;
		desc->dir_pos.plane_y = 0;
	}
	else if (player_char == 'W')
	{
		desc->dir_pos.x = -1;
		desc->dir_pos.y = 0;
		desc->dir_pos.plane_x = 0;
		desc->dir_pos.plane_y = -0.66;
	}
	else if (player_char == 'E')
	{
		desc->dir_pos.x = 1;
		desc->dir_pos.y = 0;
		desc->dir_pos.plane_x = 0;
		desc->dir_pos.plane_y = 0.66;
	}
	desc->play_pos.x = j + 0.5;
	desc->play_pos.y = l + 0.5;
}

// int		ft_add_sprite(t_desc *desc, int j, int l)
// {
// 	(void)j;
// 	(void)l;
// 	if (!desc->sprite_list)
// 	{
// 		printf("ok");
// 	}
// 	return (1);
// }

char	*ft_clean_scene_line(t_desc *desc, char *line, int *i, int l)
{
	int		j;
	int		k;
	char	*new_line;

	j = 0;
	k = 0;
	new_line = NULL;
	while (line[*i + k] != '\0' && line[*i + k] != '\n')
	{
		if (!(ft_is_scene_element(line[*i + k]) || ft_is_player_start(line[*i + k]) || line[*i + k] == ' '))
			return (NULL);
		if (ft_is_scene_element(line[*i + k]))
		{
			if (line[*i + k] == '2')
			{
				desc->nb_sprite = desc->nb_sprite + 1;
				// ft_add_sprite(desc, j ,l);
			}
			j++;
		}
		else if (ft_is_player_start(line[*i + k]))
		{
			if (desc->player_found == 1)
				return (NULL);
			ft_add_player(desc, line[*i + k], j, l);
			line[*i + k] = '0';
			j++;
		}
		k++;
	}
	//check size of each line
	if (desc->nb_l == 0)
		desc->nb_col = j;
	else
	{
		if (desc->nb_col != j)
		{
			// printf("col = %d\n", desc->nb_col);
			// printf("j = %d\n", j);
			return (NULL);
		}
	}
	new_line = malloc(sizeof(char) * (j+1));
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
	// printf("#%s\n", new_line);
	return (new_line);
}

int		ft_create_scene(t_desc *desc, char *scene_str)
{
	char	*clean_line;
	int		count;
	int		i;
	int		j;
	int		k;
	
	i = 0;
	count = 0;
	while (scene_str[i])
	{
		if (scene_str[i] == '\n')
			count++;
		i++;
	}
	i = 0;
	// printf("count %d\n", count);
	if(!(desc->scene = malloc(sizeof(char *) * (count + 2))))
		return (-1);
	// printf("count = %d\n", count);
	while (desc->nb_l < count + 1)
	{
		if(!(clean_line = ft_clean_scene_line(desc, scene_str, &i, desc->nb_l)))
			return (-1);
		j = 0;
		if (clean_line[desc->nb_col - 1] != '1')
			return (-1);
		if (desc->nb_l == 0 || desc->nb_l == count)//checkfirst and last line
		{
			while (clean_line[j])
			{
				if (clean_line[j] != '1')
					return (-1);
				j++;
			}
		}
		i++;
		// printf("@%d -> %s\n", desc->nb_l, clean_line);
		desc->scene[desc->nb_l] = clean_line;
		desc->nb_l = desc->nb_l + 1;
	}
	desc->scene[desc->nb_l] = NULL;
	desc->sprite_tab = malloc(sizeof(*(desc->sprite_tab)) * desc->nb_sprite);
	i = 0;
	j = 0;
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
				// desc->scene[i][j] = '0';
				// printf("!!k = %d, x = %f, y = %f \n", k, (desc->sprite_tab)[k].x, (desc->sprite_tab)[k].y);
				k++;
			}
			j++;
		}
		i++;
	}
	// printf("nb = %d\n", desc->nb_l);
	// printf("nb = %d\n", desc->nb_col);
	return (0);
}

int		ft_check_line(t_desc *desc, char *line, char first_char)
{
	int i;

	i = 0;
	if (first_char == 'R' && desc->resolution_ok == 0)
		return (ft_parse_resolution(line, desc, &i));
	else if (ft_is_path_identifier(line, i))
		return (ft_parse_path(line, desc, &i));
	else if (first_char == 'F' && desc->floor_ok == 0)
	{
		if (!(ft_parse_color(line, desc->floor_tab, &(desc->floor_ok), &(desc->floor_color))))
			return (-1);
		return (1);
	}
	else if (first_char == 'C' && desc->ceiling_ok == 0)
	{
		if (!(ft_parse_color(line, desc->ceiling_tab, &(desc->ceiling_ok), &(desc->ceiling_color))))
			return (-1);
		return (1);
	}
	else if (first_char == '1' && ft_is_description_ready_scene(desc))
	{
		desc->start_parse_scene = 1;
		desc->scene_str = ft_strjoin_with_sep(desc->scene_str, line, '\n');
		return (1);
	}
	else if ((first_char == '\n' || first_char == '\0') && !desc->start_parse_scene)
		return (1);
	return (-1);
}

int		ft_check_description(char *filename, t_desc *desc)
{
	int		fd;
	int		rd;
	char	*line;
	int		res;

	if (!(ft_check_file_extension(filename, ".cub")))
		return (0);
	rd = 0;
	if((fd = open(filename, O_RDONLY)) == -1)
		return (0);
	while ((res = ft_get_next_line(fd, &line)))
	{
		// printf("->%d, %s|\n", res, line);
		if ((ft_check_line(desc, line, line[0])) == -1)
			return (0);
		free(line);
		line = NULL;
	}
	// printf("->%d, %s\n", res, line);
	if ((ft_check_line(desc, line, line[0])) == -1)
		return (0);
	free(line);
	line = NULL;
	if ((ft_create_scene(desc, desc->scene_str)) == -1)
		return (0);
	return (1);
}

int		ft_check_args(int argc, char **argv, t_desc *desc)
{
	char *desc_file;

	desc_file = NULL;
	if (argc <= 1 || argc > 3)
	{
		write(2, "Error\n", 6);
		write(2, "Wrong number of argument\n", 25);
		return (0);
	}
	if (argc == 3)
	{
		if (!(ft_strcmp(argv[1], "-save")))
		{
			write(2, "Error\n", 6);
			write(2, "Second argument is wrong\n", 25);
			return (0);
		}
	}
	desc_file = argc == 3 ? argv[2] : argv[1];
	if (!(ft_check_description(desc_file, desc)))
	{
		write(2, "Error\n", 6);
		write(2, "Problem in description file\n", 28);
		return (0);
	}
	return (1);
}
