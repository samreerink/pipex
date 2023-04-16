/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sreerink <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/25 15:19:29 by sreerink      #+#    #+#                 */
/*   Updated: 2022/11/25 22:01:17 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static void	free_words(char **arr, size_t index)
{
	while (index != 0)
	{
		free(arr[index - 1]);
		index--;
	}
	free(arr);
}

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			i++;
			if (s[i] == c || s[i] == '\0')
				words++;
		}
	}
	return (words);
}

static size_t	length_words(const char *s, char c, size_t *i)
{
	size_t	j;
	size_t	i_save;

	j = *i;
	i_save = *i;
	while (s[j] != c)
	{
		j++;
		if (s[j] == c || s[j] == '\0')
		{
			*i = j;
			return (j - i_save);
		}
	}
	return (0);
}

static char	**make_words(const char *s, char **arr, char c)
{
	size_t	i;
	size_t	a;
	size_t	len;
	size_t	start;

	i = 0;
	a = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			start = i;
			len = length_words(s, c, &i);
			arr[a] = ft_substr(s, start, len);
			if (!arr[a])
				return (free_words(arr, a), NULL);
			a++;
		}
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = ft_calloc(sizeof(char *), (words + 1));
	if (!arr)
		return (NULL);
	if (make_words(s, arr, c) == NULL)
		return (NULL);
	return (arr);
}
