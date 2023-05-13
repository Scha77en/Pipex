/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:35:38 by aouhbi            #+#    #+#             */
/*   Updated: 2023/05/13 15:28:53 by aouhbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_bonus.h"

static int	rows_num(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*get_word(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static void	*free_mem(char **ptr, int j)
{
	while (j >= 0)
	{
		free(ptr[j]);
		j--;
	}
	free(ptr);
	return (0);
}

char	**ft_split(char *s, char c)
{
	size_t	g_end;
	size_t	j;
	int		g_start;
	char	**ptr;

	ptr = malloc((rows_num(s, c) + 1) * sizeof(char *));
	if (!s || !ptr)
		return (0);
	g_end = -1;
	j = 0;
	g_start = -1;
	while (++g_end <= ft_strlen(s))
	{
		if (s[g_end] != c && g_start < 0)
			g_start = g_end;
		else if ((s[g_end] == c || g_end == ft_strlen(s)) && g_start >= 0)
		{
			ptr[j++] = get_word(s, g_start, g_end);
			if (!ptr[j - 1])
				return (free_mem(ptr, (j - 1)), NULL);
			g_start = -1;
		}
	}
	return (ptr[j] = 0, ptr);
}
