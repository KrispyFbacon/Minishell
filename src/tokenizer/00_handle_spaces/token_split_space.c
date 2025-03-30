/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:23:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/30 19:32:40 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_word_handler(char *s, int *i, t_info *info)
{
	while (s[*i])
	{
		if (ft_strchr(QUOTES, s[*i]))
			quote_changer (s, i, info);
		else if (info->mode != GENERAL && ft_strchr(WHITE_SPACES, s[*i]))
			(*i)++;
		else if (info->mode == GENERAL && ft_strchr(OPERATOR, s[*i])
			&& (info->type_flag == TRUE))
			(*i)++;
		else if (info->mode == GENERAL && (ft_strchr(WHITE_SPACES, s[*i])
				|| ft_strchr(OPERATOR, s[*i])))
			break ;
		else
			(*i)++;
	}
}

void	token_redir_handler(char *s, int *i, t_info *info)
{
	get_token_redir_type(s, *i, info);
	if (info->type == 0)
		return ;
	if (info->type == REDIR_OUT || info->type == REDIR_IN)
		(*i)++;
	else if (info->type == APPEND || info->type == HEREDOC)
		*i = *i + 2;
	while (s[*i] && ft_strchr(WHITE_SPACES, s[*i]))
		(*i)++;
	info->start = *i;
}

void	split_spaces(t_token *token_list, char *s, int *i, t_info *info)
{
	info->mode = GENERAL;
	while (s[*i] && ft_strchr(WHITE_SPACES, s[*i]))
		(*i)++;
	info->start = *i;
	if (s[*i] && ft_strchr(T_PIPE, s[*i]) && info->type_flag == FALSE)
	{
		info->type = PIPE;
		(*i)++;
	}
	else
	{
		if (s[*i] && ft_strchr(T_REDIR, s[*i]) && info->type_flag == FALSE)
		{
			token_redir_handler(s, i, info);
		}
		else
			get_token_type(token_list, info);
		token_word_handler(s, i, info);
	}
	info->type_flag = TRUE;
	info->end = *i;
	info->len = info->end - info->start;
}
