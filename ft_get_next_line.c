/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:54:27 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/29 17:41:22 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_create_remain(t_remain **remain, int i, int end_line, char *buf)
{
	int		j;
	char	*new_remain;

	j = 0;
	new_remain = 0;
	if (end_line && i + j < (*remain)->size)
	{
		if (!(new_remain = malloc(sizeof(char) * ((*remain)->size + 1))))
			return (-1);
		while (end_line && i + j < (*remain)->size)
		{
			new_remain[j] = buf[i + j];
			j++;
		}
		new_remain[j] = '\0';
		free((*remain)->str);
		(*remain)->str = new_remain;
		(*remain)->size = j;
		return (1);
	}
	free((*remain)->str);
	(*remain)->str = NULL;
	(*remain)->size = 0;
	return (1);
}

int	ft_cut_remain(char *buf, t_remain **remain, int *end_line, char **line)
{
	int		i;
	char	*str2;

	i = 0;
	if (!(str2 = malloc(sizeof(char) * ((*remain)->size + 1))))
		return (-1);
	while (i < (*remain)->size && !*end_line)
	{
		if (buf[i] == '\n')
			*end_line = 1;
		str2[i] = buf[i];
		if (*end_line)
			str2[i] = '\0';
		i++;
	}
	str2[i] = '\0';
	*line = str2;
	if ((ft_create_remain(remain, i, *end_line, buf) == -1))
		return (-1);
	return (1);
}

int	ft_cut_line(char *buf, t_remain **remain, int *rd, char **line)
{
	int		i;
	char	*str2;

	i = 0;
	if (!(str2 = malloc(sizeof(char) * (*rd + 1))))
		return (-1);
	while (i < *rd)
	{
		str2[i] = buf[i];
		if (buf[i] == '\n')
		{
			str2[i] = '\0';
			*line = ft_strjoin(*line, str2);
			(*remain)->size = *rd;
			return ((ft_create_remain(remain, i + 1, 1, buf)));
		}
		else if (i == *rd - 1)
		{
			str2[i + 1] = '\0';
			*line = ft_strjoin(*line, str2);
			return (0);
		}
		i++;
	}
	return (-1);
}

int	ft_remain_init(int fd, char **line, t_remain **remain, int *end_line)
{
	*end_line = 0;
	*line = NULL;
	if (!*remain)
	{
		if (!(*remain = malloc(sizeof(**remain))))
			return (-1);
		(*remain)->str = NULL;
		(*remain)->size = 0;
	}
	if (fd >= 0)
	{
		if ((*remain)->size > 0)
			ft_cut_remain((*remain)->str, remain, end_line, line);
		else
		{
			if (!(*line = malloc(sizeof(char) * 1)))
				return (-1);
			(*line)[0] = '\0';
		}
	}
	return (1);
}

int	ft_get_next_line(int fd, char **line)
{
	static t_remain	*remain = NULL;
	int				end_line;
	int				rd;
	char			*buf;

	if ((ft_remain_init(fd, line, &remain, &end_line)) == -1)
		return (-1);
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!end_line && end_line != -1 && (rd = read(fd, buf, BUFFER_SIZE)))
		end_line = ft_cut_line(buf, &remain, &rd, line);
	free(buf);
	buf = NULL;
	if (!end_line && rd == 0)
	{
		ft_free_remain(&remain);
		return (0);
	}
	else if (end_line == -1 || rd < 0)
	{
		ft_free_remain(&remain);
		return (-1);
	}
	return (1);
}
