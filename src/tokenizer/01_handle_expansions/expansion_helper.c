/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:24:40 by yes               #+#    #+#             */
/*   Updated: 2025/03/20 18:33:10 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*take_var_name(char *s, int *i)
{
	int	start;
	int	len;

	start = *i;
	len = 0;
	if (s[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (s[*i] && s[*i] != '\"' && s[*i] != '$'
		&& !(ft_strchr(WHITE_SPACES, s[*i])))
	{
		(*i)++;
		len++;
	}
	return (ft_strndup(&s[start], len));
}

char	*get_env_value(char *var_name, t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		if (ft_strcmp(temp->name, var_name) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return ("");
}
