/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:30:47 by aouhbi            #+#    #+#             */
/*   Updated: 2023/05/01 16:46:33 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	manage_heredoc_cmd(char **argv, int *pipfd, char **env, char *data)
{
	char	**cmd;
	char	**path;
	int		ret;
	int		i;
	int		fd1;

	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
		error_out("dup2");
	if (dup2(pipfd[0], STDIN_FILENO) < 0)
		error_out("dup2");
	cmd = ft_split(argv[3], ' ');
	path = ft_split(env[6], ':');
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin(path[i], cmd[0]);
	i = command_search(path);
	ret = execve(path[i], cmd, env);
	if (ret == -1)
		error_out("execve");
}

int	command_handler_heredoc(int argc, char **argv, int *pipfd, char **env)
{
	int		cmd_n;
	pid_t	pid_b;
	int		j;

	cmd_n = argc - 6;
	j = 4;
	while (cmd_n > 0)
	{
		pid_b = fork();
		if (pid_b == 0)
			manage_children(argv, pipfd, env, j);
		else
			wait(0);
		j++;
		cmd_n--;
	}
	return (j);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	command_search(char **path)
{
	int		i;

	i = -1;
	while (path[++i])
	{
		if (access(path[i], X_OK) == 0)
			return (i);
	}
	return (-1);
}

void	error_out(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
