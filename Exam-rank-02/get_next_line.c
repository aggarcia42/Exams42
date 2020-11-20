#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

char *ft_strdup(char *s)
{
	char *str;
	int  i = 0;
	if (!(str = malloc(ft_strlen(s) + 1)))
		return (0);
	while (str[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char *ft_strjoin(char *s1, char *s2)
{
	int i = 0;
	int j = 0;
	char *str;
	if (!(str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strchr(char *s, char c)
{
	int i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (c == '\0' ? &s[i] : 0);
}

char *ft_substr(char *s, int start, int len)
{
	int i = 0;
	char *str;
	if (!(str = malloc(len + 1)))
		return (0)	
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	while (s[i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int get_next_line(char **line)
{
	static char *s;
	char *buff;
	char *aux;
	char *temp;
	int i;
	int control = 42;

	if (!(buff = malloc(43)) || !line)
		return (-1);
	if (!s)
	{
		control = read(0, buff, 42);
		if (control == 0)
		{
			*line = ft_strdup("");
			free(buff);
			return (0);
		}
		if (control < 0)
		{
			free(buff);
			return (-1);
		}
		buff[control] = '\0';
		s = ft_strdup(buff);
		free(buff);
		if (!(buff = malloc(43)))
			return (-1);
	}
	while (control == 42)
	{
		if (ft_strchr(s, '\n') != 0)
			break ;
		control = read(0, buff, 42);
		if (control < 0)
		{
			free(s);
			free(buff);
			return (-1);
		}
		buff[control] = '\0';
		aux = ft_strjoin(s, buff);
		free(s);
		s = aux;
	}
	free(buff);
	while (s[i] != '\n' && s[i])
		i++;
	if (s[i] == '\n')
	{
		*line = ft_substr(s, 0, i);
		temp = ft_strdup(&s[i + 1]);
		free(s);
		s = temp;
	}
	else
	{
		*line = ft_strdup(s);
		free(s);
		s = 0;
		return (0);
	}
	return (1);
}