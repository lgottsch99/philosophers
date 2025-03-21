/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:23:14 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/21 18:16:16 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void *function()
{
	printf("Hello\n");
	return NULL;
}

void	*routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;


	printf("===== Hello from philo no %i\n", philo->num);

	//
	//eat for time to eat
	
	// (check if time since last meal > time to die, if yes dead)
		//try to get 2 forks
		//If ok: times eaten ++
			//reset start time
	//sleep for time to sleep
		
	//think
	return (NULL);
}


int	main(int argc, char *argv[])
{
	t_program	program;
	int			num_philos;

	// program.philos = NULL;
	//1. check valid input
	if (check_input_valid(argc, argv) == 0)
	{
		num_philos = ft_atoi(argv[1]);
		// printf("number philos: %i\n", ft_atoi(argv[1]));
		// printf("time to die: %i\n", ft_atoi(argv[2]));
		// printf("time to eat: %i\n", ft_atoi(argv[3]));
		// printf("time to sleep: %i\n", ft_atoi(argv[4]));
		// if (argv[5])
		// 	printf("times to eat: %i\n", ft_atoi(argv[5]));

		//2. initialize structs, threads etc
		init_program(&program, argv);
		//init thread for each philo?
		init_threads(&program, num_philos);

		//3. run + monitor
		simulation();//the sim. only starts once ALL threads are created!!!

		for (int y = 0; y < num_philos; y++)
		{
			pthread_join(program.philos[y]->thread, NULL);
		}
		//4. free if dead or error?

			
		printf("freeing philos\n");
		free_philos(program.philos, num_philos - 1);





	}
	
	return (0);
}