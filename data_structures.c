/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfakih <nfakih@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:08:42 by nfakih            #+#    #+#             */
/*   Updated: 2025/11/24 13:06:42 by nfakih           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time()
{
	long long		t;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	t = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (t);
}
void	init_forks(t_rules *in)
{
	int	i;

	i = 0;
	in->forks = malloc(sizeof(pthread_mutex_t) * in->philo_amount);
	while (i < in->philo_amount)
	{
		pthread_mutex_init(&in->forks[i], NULL);
		i++;
	}
}

int	fill_in(t_rules *in, char **argv)
{
	if (argv[1] && ft_atoi(argv[1]) > 0)
		in->philo_amount = ft_atoi(argv[1]);
	else
		return (0);
	if (argv[2] && ft_atoi(argv[2]) > 0)
		in->t_to_die = ft_atoi(argv[2]);
	else
		return (0);
	if (argv[3] && ft_atoi(argv[3]) > 0)
		in->t_to_eat = ft_atoi(argv[3]);
	else
		return (0);
	if (argv[4] && ft_atoi(argv[4]) > 0)
		in->t_to_sleep = ft_atoi(argv[4]);
	else
		return (0);
	if (argv[5] && ft_atoi(argv[5]) > 0)
		in->must_eat = ft_atoi(argv[5]);
	else if (argv[5] && ft_atoi(argv[5]) <= 0)
		return (0);
	else
		in->must_eat = -1;
	init_forks(in);
	return (1);
}

t_philosophers	*new_philo(t_rules *rules, int i, t_philosophers *philo)
{
	philo->index = i;
	philo->alive = true;
	philo->last_meal = rules->start_time;
	philo->left = NULL;
	philo->right = NULL;
	philo->meals = 0;
	philo->rules = rules;
	return (philo);
}

t_philosophers	**fill_philo(t_rules *rules)
{
	int				i;
	t_philosophers **philos;
	int				philo_amount;
    t_philosophers  *ph;

	i = 0;
	philo_amount = rules->philo_amount;
	philos = malloc(sizeof(t_philosophers *) * philo_amount);
	while (i < philo_amount)
	{
        ph = malloc(sizeof(t_philosophers));
		philos[i] = new_philo(rules, i, ph);
		i++;
	}
	i = 0;
	while (i < philo_amount)
	{
		philos[i]->left = &(rules->forks)[i];
		philos[i]->right = &(rules->forks)[(i + 1) % philo_amount];
		i++;
	}
	return (philos);
}
t_rules	*init_in()
{
	t_rules	 *in;

	in = malloc(sizeof(t_rules));
	in->philo_amount = 0;
	in->t_to_die = 0;
	in->t_to_eat = 0;
	in->t_to_sleep = 0;
	in->must_eat = 0;
	in->finish_all = 0;
	in->start_time = get_time();
	in->print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(in->print, NULL);
	in->death = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(in->death, NULL);
	return (in);
}
