/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhuang <lhuang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:34:06 by lhuang            #+#    #+#             */
/*   Updated: 2019/12/01 18:07:57 by lhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_is_space(char c)
{
	return (c == ' ');
}

int		ft_is_number(char c)
{
	return (c >= '0' && c <= '9');
}

int		ft_is_print(char c)
{
	return (c >= 32 && c <= 126);
}

int		ft_is_scene_element(char c)
{
	return (c == '0' || c == '1' || c == '2');
}

int		ft_is_player_start(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
