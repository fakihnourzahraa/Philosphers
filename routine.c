/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 14:55:36 by nfakih            #+#    #+#             */
/*   Updated: 2025/11/26 18:17:07 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	*single_routine(void *arg)
{
	t_philosophers *philo;
	long long		time;

	philo = (t_philosophers *)arg;
	pthread_mutex_lock(philo->rules->print);
	pthread_mutex_lock(philo->left);
	time = get_time() - philo->rules->start_time;
	printf("%lld %d has taken a fork\n", time, philo->index);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->rules->print);
	usleep(philo->rules->t_to_die * 1000);
	return (NULL);
}
void	*philos_routine(void *arg)
{
	t_philosophers *philo;
	int				s;

	philo = (t_philosophers *)arg;
	while (1)
	{
		// Check if simulation should stop
		pthread_mutex_lock(philo->rules->death);
		if (philo->rules->finish_all == 1)
		{
			pthread_mutex_unlock(philo->rules->death);
			break;  // Just exit, don't call dying()
		}
		pthread_mutex_unlock(philo->rules->death);
		
		if (philo->index % 2 == 0)
			s = 0;
		else
			s = 1;
		
		taking_fork(philo, s);
		taking_fork(philo, s + 2);
		eating(philo);
		releasing_fork(philo, s);
		releasing_fork(philo, s + 2);
		sleeping_philo(philo);
		thinking(philo);
	}
	return (NULL);
}
// void	*philos_routine(void *arg)
// {
// 	t_philosophers *philo;
// 	int				s;

// 	philo = (t_philosophers *)arg;
// 	pthread_mutex_lock(philo->rules->death);
// 	while (philo->rules->finish_all == 0)
// 	{
// 		pthread_mutex_unlock(philo->rules->death);
// 		if (philo->index % 2 == 0)
// 			s = 0;
// 		else
// 			s = 1;
// 		//thinking(philo);
// 		taking_fork(philo, s);
// 		taking_fork(philo, s + 2);
// 		eating(philo);
// 		releasing_fork(philo, s);
// 		releasing_fork(philo, s + 2);
// 		sleeping_philo(philo);
// 		pthread_mutex_lock(philo->rules->death);
// 		printf("finish in:%d\n", philo->rules->finish_all);
// 	}
// 	printf("finish out:%d\n", philo->rules->finish_all);
// 	pthread_mutex_unlock(philo->rules->death);
// 	pthread_mutex_lock(philo->rules->print);
// 	printf("wtf");
// 	pthread_mutex_unlock(philo->rules->print);
// 	dying(philo);
// 	return (NULL);
// }
