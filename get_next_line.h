
#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}			t_list;
char	*concatenate_list(t_list **lst);
void	ft_lstclear(t_list **lst);
#endif