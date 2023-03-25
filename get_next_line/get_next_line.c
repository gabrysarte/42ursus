/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsartesc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 14:20:29 by gsartesc          #+#    #+#             */
/*   Updated: 2023/03/02 16:39:38 by gsartesc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, int *i)
{
	char	*buff;
	int		a;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	a = read(fd, buff, BUFFER_SIZE);
	if (a < 0 || fd < 0 || fd > 1024)
	{
		free (buff);
		return (NULL);
	}
	buff[a] = '\0';
	*i = a;
	return (buff);
}

char	*ft_after_nl(char *statico)
{
	char	*res;
	int		i;
	int		b;

	i = 0;
	b = 0;
	while (statico[i] && statico[i] != '\n')
		i++;
	if (statico[i] == '\n')
		i++;
	res = (char *)malloc(sizeof(char) * (ft_strlen(statico) - i) + 1);
	while (statico[i])
	{
		res[b] = statico[i];
		i++;
		b++;
	}
	res[b] = '\0';
	free(statico);
	return (res);
}

char	*ft_line_towrite(char *statico)
{
	char	*res;
	int		i;

	i = 0;
	while (statico[i] && statico[i] != '\n')
		i++;
	if (statico[i] == '\n')
		res = (char *)malloc(sizeof(char) * i + 2);
	else
		res = (char *)malloc(sizeof(char) * i + 1);
	i = 0;
	while (statico[i] && statico[i] != '\n')
	{
		res[i] = statico[i];
		i++;
	}
	if (statico[i] == '\n')
	{
		res[i] = '\n';
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*statico;
	char		*buff;
	int			reading;
	int			i;

	reading = 1;
	while (reading > 0)
	{
		i = 0;
		buff = ft_read(fd, &reading);
		statico = ft_strjoin(statico, buff);
		if (statico == NULL || statico[0] == '\0')
			return (ft_freenreturn(statico));
		while (statico[i] != '\n' && statico[i])
			i++;
		if (statico[i] == '\n' || reading == 0)
		{
			buff = ft_line_towrite(statico);
			statico = ft_after_nl(statico);
			return (buff);
		}
	}
	return (NULL);
}
