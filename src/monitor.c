/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgottsch <lgottsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:02:06 by lgottsch          #+#    #+#             */
/*   Updated: 2025/03/27 18:22:41 by lgottsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philos.h"

void	*monitoring(void *arg)
{
	printf("----MONITORING STARTET----\n");
	t_program *program;


	program = (t_program *)arg;
	//need to ckeck:
		//sb died (time since last meal > time to die?)
		//all ate eough?
	if (program->times_to_eat == -1)
		printf("no max eat times\n");
	else
		printf("everybody should eat %i times\n", program->times_to_eat);

	did_sb_die(program); //OLD VERSION 


	pthread_detach(program->monitor);
	return (NULL);
}

void	did_sb_die(t_program *program)
{		
	// printf("--- DID SB DIE-----\n");

	int		i;
	int		y;
	long	time;

	while (1)//*program->dead_flag == 0)
	{
		//TOdo calcullations for each philo time now vs since last meal 
		i = 0;
		y = 0;
		while (i < program->num_philos) //check each philo
		{
			time = get_time_ms();
			pthread_mutex_lock(&(program->philos[i]->mutex_end_last_meal));
			if (time - program->philos[i]->end_last_meal >= program->philos[i]->time_die)
			{
				*program->dead_flag = 1;
				printf("%ld %i has died\n", time - program->philos[i]->start_time, program->philos[i]->num);
				//free stop everything
				// pthread_mutex_unlock(&(program->philos[i]->mutex_end_last_meal));
				printf("now exiting in monitor\n");
				
				
				pthread_detach(program->monitor);

				exit(0); //remove
			}
			pthread_mutex_unlock(&(program->philos[i]->mutex_end_last_meal));
			
			pthread_mutex_lock(&(program->philos[i]->mutex_times_eaten)); //todo secure
			if (program->times_to_eat != -1)
			{
				if (program->philos[i]->times_eaten >= program->times_to_eat)
					y++;
			}
			pthread_mutex_unlock(&(program->philos[i]->mutex_times_eaten)); //todo secure
			i++;
		}
		if (y == program->num_philos)
		{
			time = get_time_ms();
			printf("%ld ALL ATE ENOUGH ------- \n", time - program->start_time);
			*program->dead_flag = 1;
			for (int u = 0; u < program->num_philos; u++)
			{
				pthread_mutex_lock(&(program->philos[u]->mutex_times_eaten)); //todo secure
				printf("philo %i ate %i times\n", program->philos[u]->num, program->philos[u]->times_eaten);
				pthread_mutex_unlock(&(program->philos[u]->mutex_times_eaten)); //todo secure

			}
			pthread_detach(program->monitor);

				exit(0); //rm

		}
		




		// if (*program->dead_flag == 1)
		// {
		// 	i = 0;
		// 	while (i < program->num_philos)
		// 	{
		// 		if (program->philos[i] && program->philos[i]->dead == 1)
		// 			break ;
		// 		i++;
		// 	}
		// 	time = get_time_ms();
		// 	printf("%ld %i has died\n", time - *program->philos[i]->start_time, program->philos[i]->num);

		// 	//free everythnig?
		// 	exit (0);
		// }
	}

}


