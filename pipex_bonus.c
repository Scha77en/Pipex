/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:22:08 by aouhbi            #+#    #+#             */
/*   Updated: 2023/04/29 18:08:45 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	int		pipfd[2];
	int		cmd_n;
	int		j;
	pid_t	pid1;
	pid_t	pid_b;
	pid_t	pid2;

	if (argc >= 5)
	{
		if (pipe(pipfd) == -1)
			error_out("pipe");
		pid1 = fork();
		if (pid1 == 0)
			manage_first_child(argv, pipfd, env);
		cmd_n = argc - 5;
		j = 3;
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
		pid2 = fork();
		if (pid2 == 0)
		{
			manage_last_child(argv, pipfd, env, j);
		}
		else
		{
			wait(0);
			close(pipfd[1]);
			close(pipfd[0]);
		}
	}
}

void	manage_first_child(char **argv, int *pipfd, char **env)
{
	char	**cmd;
	char	**path;
	int		ret;
	int		i;
	int		fd1;

	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
		error_out("open");
	close(pipfd[0]);
	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
		error_out("dup2");
	if (dup2(fd1, STDIN_FILENO) < 0)
		error_out("dup2");
	cmd = ft_split(argv[2], ' ');
	path = ft_split(env[6], ':');
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin(path[i], cmd[0]);
	i = command_search(path);
	ret = execve(path[i], cmd, env);
	if (ret == -1)
		error_out("execve");
}

void	manage_children(char **argv, int *pipfd, char **env, int j)
{
	char	**cmd;
	char	**path;
	int		ret;
	int		i;

	if (dup2(pipfd[0], STDIN_FILENO) < 0)
		error_out("dup2");
	if (dup2(pipfd[1], STDOUT_FILENO) < 0)
		error_out("dup2");
	printf("argv[j] : %s\n", argv[j]);
	cmd = ft_split(argv[j], ' ');
	path = ft_split(env[6], ':');
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin(path[i], cmd[0]);
	i = command_search(path);
	ret = execve(path[i], cmd, env);
	if (ret == -1)
		error_out("execve");
}

void	manage_last_child(char **argv, int *pipfd, char **env, int j)
{
	char	**cmd;
	char	**path;
	int		ret;
	int		i;
	int		fd2;

	fd2 = open(argv[j + 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd2 == -1)
		error_out("open");
	close(pipfd[1]);
	if (dup2(pipfd[0], STDIN_FILENO) < 0)
		error_out("dup2");
	if (dup2(fd2, STDOUT_FILENO) < 0)
		error_out("dup2");
	cmd = ft_split(argv[j], ' ');
	path = ft_split(env[6], ':');
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin(path[i], cmd[0]);
	i = command_search(path);
	ret = execve(path[i], cmd, env);
	if (ret == -1)
		error_out("execve");
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
