/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_plus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 10:59:53 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/29 11:49:05 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ft_str_merge(char *str1, char *str2, int str1_size, int str2_size)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = NULL;
	if (!(str = malloc(sizeof(char) * (str1_size + str2_size + 1))))
		return (NULL);
	while (i < str1_size)
	{
		str[i] = str1[i];
		i++;
	}
	while (j < str2_size)
	{
		str[i + j] = str2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

static void	ft_str_merge_end(char *str, char *str2, int start, int str2_size)
{
	int j;

	j = 0;
	while (j < str2_size)
	{
		str[start + j] = str2[j];
		j++;
	}
	str[start + j] = '\0';
}

char		*ft_strjoin_with_sep(char *str1, char *str2, char sep)
{
	int		i;
	int		str1_size;
	int		str2_size;
	char	*str;

	i = 0;
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
	ft_str_merge_end(str, str2, i, str2_size);
	free(str1);
	return (str);
}

char		*ft_strjoin(char *str1, char *str2)
{
	int		str1_size;
	int		str2_size;
	char	*str;

	str1_size = ft_strlen(str1);
	str2_size = ft_strlen(str2);
	str = ft_str_merge(str1, str2, str1_size, str2_size);
	free(str1);
	free(str2);
	return (str);
}
