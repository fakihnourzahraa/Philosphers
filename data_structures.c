/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nour <nour@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:08:42 by nfakih            #+#    #+#             */
/*   Updated: 2025/11/23 19:02:12 by nour             ###   ########.fr       */
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
	in->forks = malloc(sizeof(pthread_mutex_t) * in->num);
	while (i < in->num)
	{
		pthread_mutex_init(&in->forks[i], NULL);
		i++;
	}
}

int	fill_in(t_rules *in, char **argv)
{
	if (argv[1] && ft_atoi(argv[1]) > 0)
		in->num = ft_atoi(argv[1]);
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
	in->start_time = get_time();
	init_forks(in);
	return (1);
}

t_philosophers	*new_philo(t_rules in, int i, t_philosophers *philo)
{
	t_rules	*rules;

	philo->index = i;
	philo->alive = true;
	philo->left = NULL;
	philo->right = NULL;
	return (philo);
}

t_philosophers	**init_philo(t_rules *old)
{
	int				i;
	t_philosophers **philos;
	int				num;
	t_rules			*in;
    t_philosophers  *ph;

	i = 0;
	in = malloc(sizeof(t_rules));
	num = old->num;
	philos = malloc(sizeof(t_philosophers *) * num);
	while (i < num)
	{
        ph = malloc(sizeof(t_philosophers));
		philos[i] = new_philo(*in, i, ph);
		philos[i]->rules = old;
		i++;
	}
	i = 0;
	while (i < num)
	{
		philos[i]->left = &(in->forks)[i];
		philos[i]->right = &(in->forks)[(i + 1) % num];
		i++;
	}
	return (philos);
}

t_rules	*init_in()
{
	t_rules	 *in;

	in = malloc(sizeof(t_rules));
	in->num = 0;
	in->t_to_die = 0;
	in->t_to_eat = 0;
	in->t_to_sleep = 0;
	in->must_eat = 0;
	in->finish_all = 0;
	return (in);
}