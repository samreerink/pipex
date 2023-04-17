#ifndef PIPEX_H
#define PIPEX_H

# include	<unistd.h>

size_t	find_path_env(char *str);

char	**ft_split(char const *s, char c);

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strjoin_free(char *s1, char *s2);

void	*ft_calloc(size_t count, size_t size);

char	*ft_strdup(const char *s1);

#endif
