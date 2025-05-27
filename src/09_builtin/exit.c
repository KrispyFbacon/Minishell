/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:20:01 by mmiguelo          #+#    #+#             */
/*   Updated: 2025/05/27 23:39:12 by mmiguelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_exit_code_size(char *arg)
{
	long long	exit_code;
	char		*code;
	int			size;
	int			i;

	i = 0;
	size = ft_strlen(arg);
	if (arg[i] == '+')
		size--;
	exit_code = ft_atoll(arg);
	code = ft_itol(exit_code);
	if (size > 20 || (size_t)size != ft_strlen(code))
		return (1);
	else
	{
		if (exit_code < LLONG_MIN || exit_code > LLONG_MAX)
			return (1);
		else
			return (0);
	}
}

/**
 * @brief Exits the shell with a specified status or prints an error message.
 * 
 * The function implements the `exit` command for the shell. It checks the number
 * of arguments provided, verifies if the exit status is a valid number, and then
 * terminates the shell with the appropriate exit status. If there are too many
 * arguments or an invalid numeric value is provided, it prints an error message
 * and terminates the shell with a status of `2`.
 * 
 * @param args Array of command arguments. The first argument (`args[0]`) is 
 * always `"exit"`, and the second argument (`args[1]`) is the exit status
 * (optional).
 * @param shell Pointer to the shell structure (used to clean up and exit the
 * shell).
 * @return int Returns `0` if the shell exit is handled successfully, or `1` for 
 * incorrect argument input. The shell process will be terminated by the
 * `ft_kill` function.
 */
int	ft_exit(char **args, t_shell *shell)
{
	ft_printf("exit\n");
	if (ft_arrlen(args) > 2)
	{
		if (!ft_isnum(args[1]))
		{
			ft_printf_fd(2, NO_NUMERIC, args[1]);
			ft_kill(&shell, 2);
		}
		else
			return (ft_printf_fd(2, "minishell: exit: too many\
				arguments\n"), 1);
	}
	if (ft_arrlen(args) == 2)
	{
		if (!ft_isnum(args[1]))
		{
			ft_printf_fd(2, NO_NUMERIC, args[1]);
			ft_kill(&shell, 2);
		}
		else if (check_exit_code_size(args[1]) == 1)
		{
			ft_printf_fd(2, NO_NUMERIC, args[1]);
			ft_kill(&shell, 2);
		}
		else
			ft_kill(&shell, ft_atoi(args[1]));
	}
	if (ft_arrlen(args) == 1)
		ft_kill(&shell, 0);
	return (0);
}
