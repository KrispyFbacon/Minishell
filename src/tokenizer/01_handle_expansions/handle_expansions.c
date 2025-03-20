/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:19:21 by yes               #+#    #+#             */
/*   Updated: 2025/03/20 20:00:33 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (NULL);
	ft_memcpy(new_s, s, info->env_start);
	ft_strlcpy(new_s + info->env_start, var_value, (value_len + 1));
	ft_strlcpy(new_s + info->env_start + value_len, s + i, (s_len - i + 1));
	new_s[new_len] = '\0';
	return (new_s);
}

char	*remove_dollar(char **s_ptr, int *i, t_info *info)
{
	char	*new_s;
	char	*s;
	
	s = *s_ptr;
	new_s = expand_var_in_str(s, "", *i, info);
	free(s);
	*s_ptr = new_s;
	*i = info->env_start;
	return (new_s);
}

void	expand_env(t_shell *shell, char **s_ptr, int *i, t_info *info)
{
	char	*var_name;
	char	*var_value;
	char	*new_s;
	char	*s;

	s = *s_ptr;
	info->env_start = (*i);
	(*i)++;
	// missing $$ pid giver
	// make fuctions with true or false to return
	if(!(s[*i]) || ft_strchr(WHITE_SPACES, s[*i]))
		return ;
	if (ft_strchr(QUOTES, s[*i]))
	{
		if (info->mode == GENERAL)
			new_s = remove_dollar(s_ptr, i, info);
		return ;
	}
	var_name = take_var_name(s, i);
	info->env_end = (*i);
	var_value = get_env_value(var_name, shell->env);
	new_s = expand_var_in_str(s, var_value, *i, info);
	free (var_name);
	free (s);
	*s_ptr = new_s;
	(*i) = info->env_start + ft_strlen(var_value);
}

void	node_expand(t_shell **shell, t_token **token)
{
	t_info	info;
	char	*s;
	int		i;

	info.mode = GENERAL;
	s = (*token)->token;
	i = 0;
	while (s[i])
	{
		if (s[i] && ft_strchr(QUOTES, s[i]))
			quote_changer(s, &i, &info);
		else if (s[i] == '$' && info.mode != SINGLE_QUO)
			expand_env(*shell, &s, &i, &info);
		else
			i++;
	}
	(*token)->token = s;
}

void	handle_expansions(t_shell **shell)
{
	t_token	*token;

	token = (*shell)->token_list;
	while (token)
	{
		node_expand(shell, &token);
		token = token->next;
	}
}
