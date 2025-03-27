/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:19:21 by yes               #+#    #+#             */
/*   Updated: 2025/03/27 21:11:18 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(t_shell *shell, char *s, int *i, t_info *info)
{
	char	*var_name;
	char	*var_value;
	char	*new_s;

	var_name = take_var_name(s, i);
	info->env_end = (*i);
	var_value = get_env_value(var_name, shell->env);
	new_s = expand_var_in_str(s, var_value, *i, info);
	free(var_name);
	if (new_s)
		free(s);
	else
		s = new_s;
	*i = info->env_start + ft_strlen(var_value);
	return (s);
}

void	expand_env(t_shell *shell, char **s_ptr, int *i, t_info *info)
{
	char	*s;
	char	*new_s;

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
	if (s[*i] == '?')
	{
		*s_ptr = handle_question_mark(shell, s, i, info);
		return ;
	}
	printf("s_ptr: %p -> {%s}\n", *s_ptr, *s_ptr);
	new_s = expand_variable(shell, s, i, info);
	if (new_s != s)
		free(s);
	*s_ptr = new_s;
	printf("s: %p -> {%s}\n", s, s);
	printf("s_ptr: %p -> {%s}\n", *s_ptr, *s_ptr);
	*i = info->start;
}

void	handle_expansions(t_shell *shell, char **s_ptr, t_info *info)
{
	char	*s;
	int		i;

	s = *s_ptr;
	printf("Before expansion: %p -> {%s}\n", s, s);
	i = info->start;
	info->mode = GENERAL;
	while (s[i] && i < info->end)
	{
		if (s[i] && ft_strchr(QUOTES, s[i]))
			quote_changer(s, &i, info);
		else if (s[i] == '$' && info->mode != SINGLE_QUO)
		{
			printf("HERE: {%s}\n", *s_ptr);
			printf("i: %i\n", i);
			printf("ptr_s[i]: %c\n", (*s_ptr)[i]);
			printf("start: %i\n", info->start);
			printf ("ptr_s[start]: %c\n", (*s_ptr)[info->start]);
			printf("end: %i\n", info->end);
			printf ("ptr_s[end]: %c\n", (*s_ptr)[info->end]);
			expand_env(shell, &s, &i, info);
			*s_ptr = s;
			while (s[i] && (info->mode != GENERAL ||
				!(ft_strchr(WHITE_SPACES, s[i]))))
				i++;
			info->end = i;
			printf ("HERE: {%s}\n", *s_ptr);
			printf ("i: %i\n", i);
			printf ("ptr_s[i]: %c\n", (*s_ptr)[i]);
			printf("start: %i\n", info->start);
			printf ("ptr_s[start]: %c\n", (*s_ptr)[info->start]);
			printf("end: %i\n", info->end);
			printf ("ptr_s[end]: %c\n", (*s_ptr)[info->end]);
			printf("After expansion: %p -> {%s}\n", s, s);
			return ;
		}
		else
			i++;
	}
	printf("After expansion: %p -> {%s}\n", s, s);
}
