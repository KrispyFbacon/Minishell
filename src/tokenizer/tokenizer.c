/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/03/25 19:16:29 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	*s_ptr = expand_variable(shell, s, i, info);
}

void	handle_expansions(t_shell *shell, char **ptr_s, t_info *info)
{
	char	*s;
	int		i;

	s = *ptr_s;
	i = info->start;
	info->mode = GENERAL;
	while (s[i])
	{
		if (s[i] && ft_strchr(QUOTES, s[i]))
			quote_changer(s, &i, &info);
		else if (s[i] == '$' && info->mode != SINGLE_QUO)
			expand_env(shell, &s, &i, &info);
		else
			i++;
	}
	*ptr_s = s;
}

void	tokenizer(t_shell **shell, char *s)
{
	t_token	*token_list;
	t_info	info;
	char	*temp;
	int		i;

	token_list = NULL;
	info.mode = GENERAL;
	i = 0;
	(*shell)->env = initialize_env();
	while (s[i])
	{
		split_spaces(token_list, s, &i, &info);
		handle_expantions(*shell, &s, &info);
		temp = ft_substr(s, info.start, info.len);
		if (info.len > 0 || (info.type >= REDIR_IN && info.type <= HEREDOC))
		{
			ft_printf ("Token: {%s}\n", temp);
			print_type(&info);
			ft_printf("-----------------------\n");
		}
		add_new_token(&token_list, temp, &info);
	}
	//token_split_space(&s, &i);
	(*shell)->token_list = token_list;
	(*shell)->head = token_list;
	print_tokens(token_list);
	free((*shell)->env);
	(*shell)->env = NULL;
}

t_env	*initialize_env(void)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	new->name = "VAR";
	new->value = "s   -";
	new->next = NULL;
	return (new);
}

void	print_type(t_info *info)
{
	if (info->len <= 0)
		return ;
	if (info->type == CMD)
		ft_printf("Type : CMD\n");
	else if (info->type == ARG)
		ft_printf("Type : ARG\n");
	else if (info->type == PIPE)
		ft_printf("Type : PIPE\n");
	else if (info->type == REDIR_OUT)
		ft_printf("Type : REDIR_OUT\n");
	else if (info->type == REDIR_IN)
		ft_printf("Type : REDIR_IN\n");
	else if (info->type == APPEND)
		ft_printf("Type : APPEND\n");
	else if (info->type == HEREDOC)
		ft_printf("Type : HEREDOC\n");
	else
		ft_printf("Type : NULL\n");
}

/* ft_printf("DOING A LOOP\n");
	ft_printf("input[i]: %c\n", input[*i]);
	ft_printf("i       : %i\n", *i);
	ft_printf("start   : %i\n", info.start);
	ft_printf("mode    : %i\n", info.mode);
	ft_printf("------------\n"); */