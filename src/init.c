/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:23:21 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/21 17:52:03 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

static t_philo	*malloc_philo(int i, char *argv[], int *dead_flag)
{printf("in malloc philo\n");
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * 1);
	if (!philo)
		return (NULL);
	philo->num = i;
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->times_to_eat = ft_atoi(argv[5]);
	else
		philo->times_to_eat = -1;
	philo->fork = 1;
	philo->dead = 0;
	philo->times_eaten = 0;
	philo->dead_flag = dead_flag;
	return (philo);
}


static t_philo	**init_structs(char *argv[], int *dead_flag)
{printf("in init structs\n");
	t_philo **array;
	int		i;
	int		num_philos;

	i = 0;
	num_philos = ft_atoi(argv[1]);
	// printf("num philos: %i\n", num_philos);
	//malloc space for philos
		//malloc array of t philo * ptrs
	array = (t_philo **)malloc (sizeof(t_philo *) * num_philos); //mlloc n philo ptrs
	if (!array)
	{
		printf("Malloc error\n");
		return (NULL);
	}
		//malloc each philo struct
	while (i < num_philos)
	{
		array[i] = malloc_philo(i, argv, dead_flag);
		if (!array[i])
		{
			//free all before
			free_philos(array, i);
			printf("Malloc Philo error\n");
			return (NULL);
		}
		printf("created philo no %i\n", array[i]->num);
		i++;
	}
	return (array);
}

void	init_threads(t_program *program, int num_philos)
{printf("in init threads\n");
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_create(&program->philos[i]->thread, NULL, &routine, (void *)program->philos[i]) != 0)
		{
			printf("Error creating thread\n");
			//destroy and free everything
			return (NULL);
		}
		printf("created thread %i\n", i);
		i++;
	}
}

void		init_program(t_program *program, char *argv[])
{
	program->dead_flag = 0; //dead flag once any philo died
	program->philos = init_structs(argv, &program->dead_flag);
	if (!program->philos)
	{
		//free and exit
		return ;
	}
}