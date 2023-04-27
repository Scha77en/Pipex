/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:47:54 by aouhbi            #+#    #+#             */
/*   Updated: 2023/04/25 20:11:07 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

// int	main(int argc, char **argv, char **env)
// {
// 	char		**cmd;
// 	char		**cmd2;
// 	char		**path;
// 	char		**path2;
// 	int			fd1;
// 	int			fd2;
// 	int			pa;
// 	int			pa2;
// 	int			pipfd[2];
// 	int			i = -1;
// 	int			ret;
// 	pid_t		pid;
// 	// int	i;

// 	// i = 0;
// 	// while (env[i])
// 	// {

// 	// checking if the file exist and readable;
// 	if (access(argv[1], F_OK | R_OK) == 0)
// 		printf("the file exist and readable\n");
// 	// opening the argv[1] and replacing stdin with argv[1];
// 	fd1 = open(argv[1], O_RDONLY);
// 	if (fd1 == -1)
// 	{
// 		perror("open");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (dup2(fd1, STDIN_FILENO) < 0)
// 	{
// 		perror("dup2");
// 		exit(EXIT_FAILURE);
// 	}
// 	// spliting the given commad and the path to check for it;
// 	cmd = ft_split(argv[2], ' ');
// 	cmd2 = ft_split(argv[3], ' ');
// 	path = ft_split(env[6], ':');
// 	path2 = ft_split(env[6], ':');
// 	while (path[++i])
// 	{
// 		path[i] = ft_strjoin(path[i], cmd[0]);
// 		printf("the path : %s\n", path[i]);
// 	}
// 	i = -1;
// 	while (path[++i])
// 	{
// 		path2[i] = ft_strjoin(path2[i], cmd2[0]);
// 		printf("the path : %s\n", path2[i]);
// 	}
// 	// printf("%s\n", env[6]);

// 	// checking if the command does exist;
// 	pa = command_search(cmd, path);
// 	if (pa == -1)
// 	{
// 		write(1, "command 1 not found\n", 19);
// 		exit(0);
// 	}
// 	else
// 		printf("command 1 exist and excutable\n");
// 	pa2 = command_search(cmd2, path2);
// 	if (pa2 == -1)
// 	{
// 		write(1, "command 2 not found\n", 19);
// 		exit(0);
// 	}
// 	else
// 		printf("command 2 exist and excutable\n");
	
// 	// setting the pipe();
	
// 	if (pipe(pipfd) == -1)
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid == 0) // child process;
// 	{
// 		close(pipfd[0]); // close the write end of the pipe;
// 		if (dup2(pipfd[1], STDOUT_FILENO) == -1)
// 		{
// 			perror("dup2");
// 			exit(EXIT_FAILURE);
// 		}
// 		close(pipfd[1]);
// 		execve()
// 	}
// 	else //parent process;
// 	{
// 		close(pipfd[0]);
// 		write(filedes[1], "Hello from parent", 17);
// 		close(pipfd[1]);
// 	}

// 	fd2 = open(argv[4], O_CREAT | O_RDWR, 0777);
// 	if (fd2 == -1)
// 	{
// 		perror("open");
// 		exit(EXIT_FAILURE);
// 	}
// 	printf("[%d]\n", fd2);
// 	if (dup2(fd2, STDOUT_FILENO) < 0)
// 	{
// 		perror("dup2");
// 		exit(EXIT_FAILURE);
// 	}
// 	ret = execve(path[pa], cmd, NULL);
// 	if (ret == -1)
// 	{
// 		perror("execve");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (0);
// 	// cmd = ft_split(argv[2], ' ');
// 	// pid = fork();
// 	// if (pid == -1)
// 	// {
// 	// 	perror("fork");
// 	// 	return (1);
// 	// }
// 	// // 	i++;
// 	// // }

// 	// return (0);
// }

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
		perror("expected args : ./pipex INfile cmd1 cmd2 OUTfile\n");
		exit(0);
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
	path = ft_split(env[6], ':');
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin(path[i], cmd[0]);
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
	path = ft_split(env[6], ':');
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin(path[i], cmd[0]);
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
