/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_temp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yes <yes@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:49:36 by yes               #+#    #+#             */
/*   Updated: 2025/05/15 16:48:46 by yes              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

#define PATH_NOT_FOUND "minishell: Path directory not found\n"

void	close_all_fds(int in_fd, int fd[2])
{
	if (in_fd > 0)
		close(in_fd);	// read end of previous pipe
	if (fd[0] > 0)
		close(fd[0]);	// read end of next pipe
	if (fd[1] > 0)
		close(fd[1]);	// write end of next pipe
}

void	child_exec_handler(t_shell *shell, t_node *node)
{
	char	*path;
	t_bt	func;

	shell->is_child = TRUE;
	if (handle_exec_redir() == ERROR) // yet to be made (change fd in and out)
		exit_child(shell, 1);
	func = is_builtin(node->cmd);
	if (func)
	{
		shell->exit_status = func(node->args, shell);
		exit_child(shell, shell->exit_status);
	}
	path = resolve_path(node->cmd, shell->envp); //yet to be made acess(path , X_OK) and check ./ || use split as well (ivan)
	if (!path)
	{
		ft_printf_fd(2, PATH_NOT_FOUND);
		shell->exit_status = 127;
		exit_child(shell, shell->exit_status);
	}
	if (execve(path, node->args, shell->envp) == -1)
	{
		perror(node->cmd);
		free_ref(&path);
		if (errno == ENOENT)
			shell->exit_status = 127; //no such file/directory
		else if (errno == EACCES || errno == EISDIR) //permission denied or is a directory
			shell->exit_status = 126;
		else
			shell->exit_status = 1;
		exit_child(shell, shell->exit_status);
	}
}

void	execute_process(t_shell *shell)
{
	//TODO put this variables in shell V or call there ^
	t_node	*node;
	int		in_fd;
	int		fd[2];
	int		pid;
	int		count;
	int		status;

	node = shell->process;
	in_fd = 0;
	count = 0;
	while (node)
	{
		if (node->next && pipe(fd) == -1)
		{
			while (count-- > 0)
				waitpid(-1, NULL, 0);
			shell->exit_status = 1;
			return (ft_printf_fd(2, "minishell: pipe: error\n"));
		}
		pid = fork();
		if (pid == -1)
		{
			while (count-- > 0)
				waitpid(-1, NULL, 0);
			shell->exit_status = 1;
			return (ft_printf_fd(2, "minishell: fork: error\n"));
		}
		if (pid == 0)
		{
			if (in_fd != 0)
				dup2(in_fd, STDIN_FILENO);
			if (node->next)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
			}
			close_all_fds(in_fd, fd);
			child_exec_handler(shell, node);
			exit(1);
		}
		count++;
		if (in_fd != 0)
			close(in_fd);
		if (node->next)
		{
			close(fd[1]);
			in_fd = fd[0];
		}
		if (is_builtin(node->cmd) && (node->next && !is_builtin(node->next->cmd)))
			waitpid(pid, NULL, 0);
		node = node->next;
	}
	if (count-- > 1)
		waitpid(-1, &status, 0); // this wait is to prevent zombie children
	waitpid(pid, &status, 0); //this wait is to save for the last child status;
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}

void	execute_process(t_shell *shell)
{
	t_node	*node;
	
	node = shell->process;
	if (count_nodes(shell) == 1 || check_for_pipes() == FALSE)
		single_node_execute(shell, node);
	else
		multi_node_execute(shell, node);
}

/* 
void	execute_process(t_shell *shell)
{
	t_node	*node;
	int		in_fd;
	int		fd[2];
	int		pid;
	int		status;

	node = shell->process;
	in_fd = 0;
	while (node)
	{
		if (node->next && pipe(fd) == -1)
			return perror("pipe");
		pid = fork();
		if (pid == 0)
		{
			if (in_fd != 0)
				dup2(in_fd, STDIN_FILENO);
			if (node->next)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
			}
			close_all_fds(in_fd, fd);
			child_exec_handler(shell, node);
			exit(1);
		}
		if (in_fd != 0)
			close(in_fd);
		if (node->next)
		{
			close(fd[1]);
			in_fd = fd[0];
		}
		if (is_builtin(node->cmd) && (node->next && !is_builtin(node->next->cmd)))
			waitpid(pid, NULL, 0);
		node = node->next;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
} */