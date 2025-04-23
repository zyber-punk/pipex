/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:41:55 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/04/23 00:35:35 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	polish_list(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (NULL == buf || NULL == clean_node)
		return ;
	last_node = find_last_node(*list);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		++i;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

char	*get_line(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (NULL == list)
		return (NULL);
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (NULL == next_str)
		return (NULL);
	copy_str(list, next_str);
	return (next_str);
}

void	add_to_list(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (NULL == new_node)
		return ;
	if (NULL == last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

void	create_list(t_list **list, int fd)
{
	int		char_read;	
	char	*buf;

	while (!found_newline(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (NULL == buf)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		add_to_list(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*fd_list[OPEN_MAX] = {NULL};
	char			*next_line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	create_list(&fd_list[fd], fd);
	if (fd_list[fd] == NULL)
		return (NULL);
	next_line = get_line(fd_list[fd]);
	polish_list(&fd_list[fd]);
	if (fd_list[fd] == NULL)
		dealloc(&fd_list[fd], NULL, NULL);
	return (next_line);
}

/*
int	main(void)
{
	int		fd;
	char	*line;
	int		lines;

	lines = 1;
	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
		printf("%d->%s\n", lines++, line);
}
*/

/*
int main(void)
{
	int fd1 = open("test1.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	int fd3 = open("test3.txt", O_RDONLY);

	char *line;
	line = get_next_line(fd1);
	printf("Fichier 1: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("Fichier 2: %s", line);
	free(line);

	line = get_next_line(fd1);
	printf("Fichier 1: %s", line);
	free(line);

	line = get_next_line(fd3);
	printf("Fichier 3: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("Fichier 2: %s", line);
	free(line);

	close(fd1);
	close(fd2);
	close(fd3);

	printf("\n\nAttendu:\nFichier 1: Ligne 1 du fichier 1\n");
	printf("Fichier 2: Ligne 1 du fichier 2\n");
	printf("Fichier 1: Ligne 2 du fichier 1\n");
	printf("Fichier 3: Ligne 1 du fichier 3\n");
	printf("Fichier 2: Ligne 2 du fichier 2");
	return (0);
}
*/
