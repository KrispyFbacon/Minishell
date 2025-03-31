/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:19:21 by yes               #+#    #+#             */
/*   Updated: 2025/03/31 12:52:58 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(t_shell *shell, char **s_ptr, int *i, t_info *info)
{
	char	*var_name;
	char	*var_value;
	char	*new_s;
	char	*s;

	s = *s_ptr;
	var_name = take_var_name(s, i);
	info->env_end = (*i);
	var_value = get_env_value(var_name, shell->env);
	new_s = expand_var_in_str(s, var_value, *i, info);
	free(var_name);
	*i = info->env_start + ft_strlen(var_value);
	return (new_s);
}

int	expand_env(t_shell *shell, char **s_ptr, int *i, t_info *info)
{
	char	*s;
	char	*new_s;

	s = *s_ptr;
	info->env_start = (*i);
	(*i)++;
	if (!(s[*i]) || ft_strchr(WHITE_SPACES, s[*i]))
		return (FALSE);
	else if (ft_strchr(QUOTES, s[*i]) && info->mode == DOUBLE_QUO)
		return (FALSE);
	else if (ft_strchr(QUOTES, s[*i]) && info->mode == GENERAL)
		new_s = remove_dollar(&s, i, info);
	else if (s[*i] == '$')
		new_s = handle_double_dollar(shell, s, i, info);
	else if (s[*i] == '?')
		new_s = handle_question_mark(shell, s, i, info);
	else
		new_s = expand_variable(shell, &s, i, info);
	*s_ptr = new_s;
	return (TRUE);
}

int	handle_expansions(t_shell *shell, char **s_ptr, int *i, t_info *info)
{
	char	*s;

	s = *s_ptr;
	info->mode = GENERAL;
	*i = info->start;
	while (s[*i] && *i < info->end)
	{
		if (s[*i] && ft_strchr(QUOTES, s[*i]))
			quote_changer(s, i, info);
		else if (s[*i] == '$' && info->mode != SINGLE_QUO)
		{
			if (expand_env(shell, s_ptr, i, info) == FALSE)
				continue ;
			else
			{
				free(s);
				*i = info->start;
				return (TRUE);
			}
		}
		else
			(*i)++;
	}
	return (FALSE);
}
// TODO DELETE v

/* printf("HERE: {%s}\n", *s_ptr);
			printf("i: %i\n", i);
			printf("ptr_s[i]: %c\n", (*s_ptr)[i]);
			printf("start: %i\n", info->start);
			printf ("ptr_s[start]: %c\n", (*s_ptr)[info->start]);
			printf("end: %i\n", info->end);
			printf ("ptr_s[end]: %c\n", (*s_ptr)[info->end]);
			expand_env(shell, &s, &i, info);
			printf ("HERE: {%s}\n", *s_ptr);
			printf ("i: %i\n", i);
			printf ("ptr_s[i]: %c\n", (*s_ptr)[i]);
			printf("start: %i\n", info->start);
			printf ("ptr_s[start]: %c\n", (*s_ptr)[info->start]);
			printf("end: %i\n", info->end);
			printf ("ptr_s[end]: %c\n", (*s_ptr)[info->end]); */