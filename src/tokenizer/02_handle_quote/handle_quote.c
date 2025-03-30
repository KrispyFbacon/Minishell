/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:37:48 by yes               #+#    #+#             */
/*   Updated: 2025/03/30 19:45:01 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char *s, int i, t_info *info)
{
	int	len;

	len = strlen(s);
	if (i < 0 || i >= len)
		return ;
	ft_memmove(&s[i], &s[i + 1], len - i);
	s[len - 1] = '\0';
	info->end--;
}

void	handle_quotes(char **s_ptr, int *i, t_info *info)
{
	char	*s;

	s = *s_ptr;
	info->mode = GENERAL;
	*i = info->start;
	while (s[*i] && *i < info->end)
	{
		if (ft_strchr(QUOTES, s[*i]) && info->mode == GENERAL)
		{
			quote_changer(s, i, info);
			*i = *i - 1;
			remove_quotes(s, *i, info);
		}
		else if ((s[*i] == '\'' && info->mode == SINGLE_QUO)
			|| (s[*i] == '"' && info->mode == DOUBLE_QUO))
		{
			quote_changer(s, i, info);
			*i = *i - 1;
			remove_quotes(s, *i, info);
		}
		else
			(*i)++;
	}
}
