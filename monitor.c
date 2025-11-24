/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 19:50:47 by nour              #+#    #+#             */
/*   Updated: 2025/11/24 13:43:16 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	t_to_die_exceeded(t_rules *rules)
// {
// 	int			i;
// 	long long	time;

// 	i = 0;
// 	while (rules->finish_all == 0 && i < rules->philo_amount)
// 	{
// 		pthread_mutex_lock(rules->print);
// 		time = get_time() - rules->philos[i]->last_meal;		
// 		if (time >= rules->t_to_die)
// 		{
// 			dying(rules->philos[i]);
// 			pthread_mutex_lock(rules->death);
// 			rules->finish_all = 1;
// 			pthread_mutex_unlock(rules->death);
// 			return ;
// 		}
// 		i++;
// 	}
// }

void	t_to_die_exceeded(t_rules *rules)
{
	int			i;
	long long	current_time;
	long long	time_since_last_meal;
	long long	timestamp;

	i = 0;
	while (i < rules->philo_amount)
	{
		current_time = get_time();
		time_since_last_meal = current_time - rules->philos[i]->last_meal;
		
		if (time_since_last_meal >= rules->t_to_die)
		{
			pthread_mutex_lock(rules->print);
			timestamp = get_time() - rules->start_time;
			printf("%lld %d died\n", timestamp, rules->philos[i]->index);
			pthread_mutex_unlock(rules->print);
			
			pthread_mutex_lock(rules->death);
			rules->finish_all = 1;
			pthread_mutex_unlock(rules->death);
			return;
		}
		i++;
	}
}

void	all_have_eaten(t_rules *rules)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (rules->finish_all == 0 && i < rules->philo_amount)
	{
		pthread_mutex_lock(rules->print);		
		if (rules->philos[i]->meals >= rules->must_eat)
		{
			t = 1;
		}
		pthread_mutex_unlock(rules->print);
		i++;
	}
	if (t == 0)
	{
		pthread_mutex_lock(rules->death);
		rules->finish_all = 1;
		pthread_mutex_unlock(rules->death);
	}
}

void	*monitor_thread(void *arg)
{
	t_rules *rules;
	int		done;

	done = 0;
	rules = (t_rules *)arg;
	while (!done)
	{
		pthread_mutex_lock(rules->death);
		done = rules->finish_all;
		pthread_mutex_unlock(rules->death);
		
		if (!done)
		{
			t_to_die_exceeded(rules);
			all_have_eaten(rules);
			usleep(1000);
		}
	}
	return (NULL);
}
