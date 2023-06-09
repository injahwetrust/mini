/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:12:41 by bvaujour          #+#    #+#             */
/*   Updated: 2023/06/09 14:42:34 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isin_env(t_data *data, char *str)
{
	int	i;
	int j;
	
	i = 0;
	j = 0;
	while (str[i] != '=')
		i++;
	while (data->env[j])
	{
		if (ft_strncmp(data->env[j], str, i) == 0)
		{
			free(data->env[j]);
			data->env[j] = ft_strdup(str);
			return (1);
		}
		j++;
	}
	return (0);
}
void    new_envi(t_data *data, char *str)
{
    int i;
	
	if (isin_env(data, str))
		return ;
    i = 0;
    while (data->env[i])
        i++;
    data->new_env = malloc(sizeof(char *) * (i + 2));
    i = -1;
    while (data->env[++i])
	{
        data->new_env[i] = data->env[i];
	}
	data->new_env[i] = ft_strdup(str);
    data->new_env[i + 1] = 0;
    data->env = data->new_env;
}

static void echo(t_data *data, char *cmd)
{
	int	i;
	int	nl;

	i = 3;
	nl = 1;
	while (cmd[++i])
	{
		if (cmd[i] == '-' && cmd[i + 1] == 'n' && (cmd[i + 2] == ' ' || cmd[i + 2] == '\t'))
			nl = 0;
		if (cmd[i] != ' ' && cmd[i] != '\t')
			break;
	}
	i = 3;
	if (nl == 0)
		while (cmd[i] != 'n')
			i++;
	else
		i = 3;
	i++;
	while (cmd[i] == ' ' || cmd[i] == '\t')
		i++;
	while (cmd[i])
	{
		ft_printf("%c", cmd[i]);
		i++;
	}
	if (nl == 1)
		ft_printf("\n");
	end_process(data);
}

void	print_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		ft_printf("%s\n", data->env[i]);
		i++;
	}
	end_process(data);
}

void	cd_manage(t_data *data, char *cmd)
{
	char *path;

	if (cmd[2] == '\0')
	{
		chdir("//home");
		close (data->base_fd[0]);
		close (data->base_fd[1]);
		return ;
	}
	path = ft_strdup(cmd + 2);
	if (!path)
		exit(ft_dprintf(2, "Malloc error\n"));
	path = ft_strtrim(path, " \t", 1);
	if (!path)
		exit(ft_dprintf(2, "Malloc error\n"));
	ft_dprintf(2, "path = %s\n", path);
	chdir(path);
	close (data->base_fd[0]);
	close (data->base_fd[1]);
}

void	recoded(t_data *data, char *cmd, int option)
{

	if (ft_strcmp("pwd", cmd) == 0)
	{
		ft_printf("%s\n", data->cwd);
		end_process(data);
	}
	else if (ft_strcmp("env", cmd) == 0)
		print_env(data);
	else if (ft_strcmp("exit", cmd) == 0 || ft_strncmp("export", cmd, 6) == 0 || ft_strncmp("cd", cmd, 2) == 0)
	{
		if (option == 1)
			free(cmd);
		end_process(data);
	}
	else if (ft_strncmp("echo", cmd, 4) == 0)
		echo(data, cmd);
}