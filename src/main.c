/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbranda <frbranda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:04:38 by frbranda          #+#    #+#             */
/*   Updated: 2025/02/26 17:17:51 by frbranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ctr + c handler (make new .c file)
void	sigint_handler(int sig)
{
	(void) sig;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(void)
{
	t_shell	*shell;
	char	*input;

	shell = initialize_shell();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	while (1)
	{
		input = readline("prompt> ");
		if (!input || ft_strncmp(input, "exit", 6) == 0)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		tokenizer(&shell, input);
		add_history(input);
		free_token_list(&shell->token_tree);
		free(input);
	}
	free_shell(&shell);
	return (0);
}

/*	line: 31 -> // ignore on prompt but leave with leak when using cat
	line: 37 -> // Ctrl+D EOF

// Do different "whiles(1)" for main/cat/here_doc also 
// signals are different(ctrl + /) ??? */
