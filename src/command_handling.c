/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 14:31:49 by aouhbi            #+#    #+#             */
/*   Updated: 2023/05/15 14:13:50 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"
#include "../include/pipex.h"

char	**find_path(char **env)
{
	int		k;
	char	**path;

	k = get_env_path(env);
	path = ft_split(env[k], ':');
	return (path);
}

int	get_env_path(char **env)
{
	char	*path;
	int		i;

	path = "PATH=";
	i = 0;
	while (ft_strncmp(path, env[i], 5) != 0)
	{
		if (!env[i])
			perror("The Command Path Does Not Exist!");
		i++;
	}
	return (i);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
