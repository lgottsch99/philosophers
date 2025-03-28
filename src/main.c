/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:23:14 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/28 18:00:01 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"


void	pre_init(t_program *program)
{
	program->num_philos = 0;
	program->dead_flag = NULL;
	program->philos = NULL;
	program->start_time = 0;
	program->fork_mutexes = NULL;
	program->times_to_eat = -1;
}

int	main(int argc, char *argv[])
{
	t_program	program;
	int			num_philos;
	int			dead_flag;

	dead_flag = 0;
	// program.philos = NULL;
	pre_init(&program);
	//1. check valid input
	if (check_input_valid(argc, argv) == 0)
	{
		// printf("input valid\n");
		num_philos = ft_atoi(argv[1]);

	//2. initialize structs, threads etc
		init_program(&program, argv, &dead_flag);
		//TODO fork array and pass pointers to philos
		
		//init thread for each philo?
		init_threads(&program, num_philos);
		
		// join_threads(&program);
		pthread_join(program.monitor, NULL);
		
		free_program(&program);
	}
	return (0);
}
