/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:24:40 by yes               #+#    #+#             */
/*   Updated: 2025/03/27 20:38:26 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (s[*i] && s[*i] != '$' && !(ft_strchr(QUOTES, s[*i]))
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
	return (ft_strdup(""));
}

char	*expand_var_in_str(char *s, char *var_value, int i, t_info *info)
{
	char	*new_s;
	int		s_len;
	int		new_len;
	int		var_len;
	int		value_len;

	s_len = ft_strlen(s);
	var_len = i - info->env_start;
	value_len = ft_strlen(var_value);
	new_len = s_len - var_len + value_len;
	new_s = (char *)ft_calloc((new_len + 1), sizeof(char));
	if (!new_s)
		return (ft_strdup(s));
	ft_memcpy(new_s, s, info->env_start);
	if (value_len > 0)
		ft_strlcpy(new_s + info->env_start, var_value, (value_len + 1));
	ft_strlcpy(new_s + info->env_start + value_len, s + i, (s_len - i + 1));
	new_s[new_len] = '\0';
	return (new_s);
}
