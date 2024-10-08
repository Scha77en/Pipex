/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:47:54 by aouhbi            #+#    #+#             */
/*   Updated: 2023/05/16 21:24:32 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	command_search(char **path)
{
	int		i;

	i = -1;
	while (path[++i])
	{
		if (access(path[i], X_OK) == 0)
			return (i);
	}
	perror("Command Not Found");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **env)
{
	int		pipfd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc == 5)
	{
		if (pipe(pipfd) == -1)
			error_out("pipe");
		pid1 = fork();
		if (pid1 == 0)
			manage_child(argv, pipfd, env);
		pid2 = fork();
		if (pid2 == 0)
			manage_child2(argv, pipfd, env);
		close(pipfd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	else
	{
		write(2, "[ Error ] expected args : ./pipex INfile cmd1 \
cmd2 OUTfile\n", 57);
		exit(EXIT_FAILURE);
	}
}

void	manage_child(char **argv, int *pipfd, char **env)
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
	path = find_path(env);
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin_b(path[i], cmd[0]);
	i = command_search(path);
	ret = execve(path[i], cmd, env);
	if (ret == -1)
		error_out("execve");
}

void	manage_child2(char **argv, int *pipfd, char **env)
{
	char	**cmd;
	char	**path;
	int		ret;
	int		i;
	int		fd2;

	fd2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd2 == -1)
		error_out("open");
	close(pipfd[1]);
	if (dup2(pipfd[0], STDIN_FILENO) < 0)
		error_out("dup2");
	if (dup2(fd2, STDOUT_FILENO) < 0)
		error_out("dup2");
	cmd = ft_split(argv[3], ' ');
	path = find_path(env);
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin_b(path[i], cmd[0]);
	i = command_search(path);
	ret = execve(path[i], cmd, env);
	if (ret == -1)
		error_out("execve");
}

void	error_out(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
