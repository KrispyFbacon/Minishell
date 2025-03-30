/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:20:23 by yes               #+#    #+#             */
/*   Updated: 2025/03/30 16:37:39 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: change header

#include "minishell.h"

void	quote_changer(char *s, int *i, t_info *info)
{
	if (s[*i] == '\'')
	{
		if (info->mode == GENERAL)
			info->mode = SINGLE_QUO;
		else if (info->mode == SINGLE_QUO)
			info->mode = GENERAL;
	}
	else if (s[*i] == '\"')
	{
		if (info->mode == GENERAL)
			info->mode = DOUBLE_QUO;
		else if (info->mode == DOUBLE_QUO)
			info->mode = GENERAL;
	}
	(*i)++;
}
