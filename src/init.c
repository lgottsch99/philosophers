/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:23:21 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/28 17:59:56 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

static t_philo	*malloc_philo(int i, char *argv[], t_program *program)
{
	// printf("in malloc philo\n");
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * 1);
	if (!philo)
		return (NULL);
	philo->num = i + 1; //todo: check if ok
	philo->time_die = ft_atoi(argv[2]);
	philo->time_eat = ft_atoi(argv[3]);
	philo->time_sleep = ft_atoi(argv[4]);
	philo->dead = 0;
	philo->times_eaten = 0;
	philo->dead_flag = program->dead_flag;
	philo->start_time = program->philo_start; //3 seconds after start?
	philo->mutex_own_fork = &program->fork_mutexes[i];
	if (i + 1 < program->num_philos)
		philo->mutex_fork_right = &program->fork_mutexes[i + 1];
	else
		philo->mutex_fork_right = &program->fork_mutexes[0];
	philo->mutex_dead_flag = &program->mutex_dead_flag;
	philo->end_last_meal = philo->start_time;
	pthread_mutex_init(&philo->mutex_times_eaten, NULL); //protect
	pthread_mutex_init(&philo->mutex_end_last_meal, NULL); //protect
	philo->write_lock = &program->write_lock;
	return (philo);
}


static t_philo	**init_structs(char *argv[], t_program *program)
{
	// printf("in init structs\n");
	t_philo **array;
	int		i;

	i = 0;
	//malloc space for philos
		//malloc array of t philo * ptrs
	array = (t_philo **)malloc (sizeof(t_philo *) * program->num_philos); //mlloc n philo ptrs
	if (!array)
	{
		printf("Malloc error\n");
		return (NULL);
	}
		//malloc each philo struct
	while (i < program->num_philos)
	{
		array[i] = malloc_philo(i, argv, program);
		if (!array[i])
		{
			//free all before
			free_philos(array, i);
			printf("Malloc Philo error\n");
			return (NULL);
		}
		// printf("created philo no %i\n", array[i]->num);
		// print_philo(array[i]);
		i++;
	}
	return (array);
}



void	init_threads(t_program *program, int num_philos)
{
	// printf("in init threads\n");
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_create(&program->philos[i]->thread, NULL, &routine, (void *)program->philos[i]) != 0)
		{
			printf("Error creating thread\n");
			//destroy and free everything
			return ;
		}
		// printf("created thread %i\n", i);
		i++;
	}
}


pthread_mutex_t	*init_fork_mutex(int num_philos)
{
	pthread_mutex_t *mutexes;
	pthread_mutex_t	*tmp;
	int				i;
	//malloc space for all

	mutexes = NULL;
	mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_philos);
	if (! mutexes)
		return (NULL);
	tmp = mutexes;
	i = 0;
	//loop and init mutex for each
	while (i < num_philos)
	{
		// if (pthread_mutex_init(&mutexes[i], NULL) == -1)
		if (pthread_mutex_init(tmp, NULL) == -1)
		{
			// free everything
			return (NULL);
		}
		i++;
		tmp++;
	}
	tmp = NULL;
	return (mutexes);
}

void	init_program(t_program *program, char *argv[], int *dead_flag)
{
	// printf("init program\n");

	program->num_philos = ft_atoi(argv[1]);
	// printf("num philos: %i\n", program->num_philos);
	program->dead_flag = dead_flag; //dead flag once any philo died
	program->start_time = get_time_ms();
	program->philo_start = program->start_time + 1200;
	program->fork_mutexes = init_fork_mutex(program->num_philos);
	if (!program->fork_mutexes)
	{
		//free and exit
		return ;
	}
	if (pthread_mutex_init(&program->write_lock, NULL) == -1)
	{
		// free everything
		return;
	}
	if (pthread_mutex_init(&program->mutex_dead_flag, NULL) == -1)
	{
		// free everything
		return;
	}

	program->philos = init_structs(argv, program);
	if (!program->philos)
	{
		//free and exit
		return ;
	}
	if (pthread_create(&program->monitor, NULL, &monitoring, (void *)program) != 0)
	{
		printf("Error creating thread\n");
		//destroy and free everything
		return ;
	}
	if (argv[5])
		program->times_to_eat = ft_atoi(argv[5]);
	else
		program->times_to_eat = -1;
	program->time_die = ft_atoi(argv[2]);
}