
#include "get_next_line_bonus.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	if (*lst)
	{
		while (*lst != NULL)
		{
			temp = *lst;
			*lst = (*lst)->next;
			free(temp->content);
			free(temp);
		}
		*lst = NULL;
	}
}

static void	ft_append(t_list **lst, char *new)
{
	t_list	*temp;
	t_list	*current;

	if (!ft_strlen(new))
		return ;
	temp = (t_list *)malloc(sizeof(t_list));
	if (!temp)
	{
		return ;
	}
	temp->content = ft_strdup(new);
	temp->next = NULL;
	if (*lst == NULL)
		*lst = temp;
	else
	{
		current = *lst;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = temp;
	}
}

static int	check_lst_nl(t_list *lst, char **cache)
{
	char	*str;
	int		i;

	i = 0;
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	str = ft_strdup(lst->content);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			*cache = ft_strdup(str + i + 1);
			str[i + 1] = '\0';
			free(lst->content);
			lst->content = ft_strdup(str);
			free(str);
			return (1);
		}
		i++;
	}
	free(str);
	return (0);
}

static void	populate_lst(t_list **list, int fd, char **cache)
{
	ssize_t	read_size;
	char	*str_buff;

	str_buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str_buff)
		return ;
	while (check_lst_nl(*list, cache) == 0)
	{
		read_size = read(fd, str_buff, BUFFER_SIZE);
		if (read_size <= 0)
		{
			return (free(str_buff), free(*cache));
		}
		str_buff[read_size] = '\0';
		ft_append(list, str_buff);
	}
	free(str_buff);
}

char	*get_next_line(int fd)
{
	static char	*cache[OPEN_MAX];
	t_list		*line;
	char		*result;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (cache[fd] != NULL)
	{
		if (read(fd, 0, 0) == -1)
		{
			free(cache[fd]);
			cache[fd] = NULL;
			return (cache[fd]);
		}
		ft_append(&line, cache[fd]);
		free(cache[fd]);
		cache[fd] = NULL;
	}
	populate_lst(&line, fd, &cache[fd]);
	result = concatenate_list(&line);
	ft_lstclear(&line);
	return (result);
}
