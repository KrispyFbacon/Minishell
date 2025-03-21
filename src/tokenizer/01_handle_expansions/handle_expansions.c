/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:19:21 by yes               #+#    #+#             */
/*   Updated: 2025/03/21 15:53:50 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(char *s, int *i, t_shell *shell, t_info *info)
{
	char	*var_name;
	char	*var_value;
	char	*new_s;

	var_name = take_var_name(s, i);
	info->env_end = (*i);
	var_value = get_env_value(var_name, shell->env);
	new_s = expand_var_in_str(s, var_value, *i, info);
	free(var_name);
	free(s);
	*i = info->env_start + ft_strlen(var_value);
	return (new_s);
}

void	expand_env(t_shell *shell, char **s_ptr, int *i, t_info *info)
{
	char	*s;

	s = *s_ptr;
	info->env_start = (*i);
	(*i)++;
	if (!(s[*i]) || ft_strchr(WHITE_SPACES, s[*i]))
		return ;
	if (ft_strchr(QUOTES, s[*i]))
	{
		if (info->mode == GENERAL)
			*s_ptr = remove_dollar(s_ptr, i, info);
		return ;
	}
	if (s[*i] == '$')
	{
		*s_ptr = handle_double_dollar(shell, s, i, info);
		return ;
	}
	*s_ptr = expand_variable(s, i, shell, info);
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
