/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 17:48:30 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/29 21:02:26 by lhuang           ###   ########.fr       */
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
	char	*line;
	int		res;

	if (!(ft_check_file_extension(filename, ".cub")))
		return (0);
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (-2);
	while ((res = ft_get_next_line(fd, &line)))
	{
		if ((ft_check_line(desc, line, line[0])) == -1)
			return (ft_free_str(line));
		free(line);
		line = NULL;
	}
	if ((ft_check_line(desc, line, line[0])) == -1)
		return (ft_free_str(line));
	free(line);
	line = NULL;
	if ((ft_create_scene(desc, desc->scene_str)) != 1)
		return (-1);
	return (1);
}

int		ft_check_args(int argc, char **argv, t_desc *desc)
{
	char	*desc_file;
	int		ret;

	desc_file = NULL;
	if (argc <= 1 || argc > 3)
		return (ft_set_error(desc, ARG));
	if (argc == 3)
	{
		if (!(ft_strcmp(argv[1], "-save")))
			return (ft_set_error(desc, ARG));
		desc->to_save = 1;
	}
	desc_file = argc == 3 ? argv[2] : argv[1];
	ret = ft_check_description(desc_file, desc);
	if (ret == -1)
		return (ft_set_error(desc, MALLOC));
	else if (ret == 0)
		return (ft_set_error(desc, PARSE));
	else if (ret == -2)
		return (ft_set_error(desc, OPEN));
	return (1);
}
