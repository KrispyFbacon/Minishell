/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:12:25 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/26 17:29:08 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_string(char *input, int *i)
{
	char	*new_s;
	int		len;
	int		j;

	j = 0;
	len = 0;
	while (input[*i] && input[*i] != ' ')
	{
		*i = *i + 1;
		len++;
	}
	new_s = (char *)ft_calloc((len + 1), sizeof(char));
	if (!new_s)
		return (NULL);
	while (len != 0)
	{
		new_s[j] = input[*i - len];
		len--;
		j++;
	}
	new_s[j] = '\0';
	*i = *i - 1;
	return (new_s);
}

void	token_split(t_token **token, char *input, int *i)
{
	t_token	*new_token;
	char	*s;

	if (input[*i] == '|')
	{
		ft_printf("PIPE: |\n");
		new_token = initialize_token("|", PIPE);
		add_last_token(token, new_token);
	}
	else
	{
		while(input[*i] && input[*i] != '|')
		{
			s = new_string(s, i);
			if (!s)
				return ;
			new_token = initialize_token(s, ARG);
			add_last_token(token, new_token);
			free(s);
			*i += 1;
		}
		*i -= 1;
	}
}

void	node_split(t_token_tree **token_list, char *input)
{
	t_token_tree	*new_node;
	t_token			*token;
	int				i;

	i = 0;
	token = NULL;
	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		else
		{
			token_split(&token, input, &i);
			if(token->token[0] == '|')
				new_node = initialize_token_list(token, PIPE);
			else
				new_node = initialize_token_list(token, EXEC);
			add_last_node(token_list, new_node);
		}
		i++;
	}
	
}

void	tokenizer(t_shell **shell, char *input)
{
	t_token_tree	*token_list;

	token_list = NULL;
	node_split(&token_list, input);
	print_token_list(token_list);
	(*shell)->token_tree = token_list;
}