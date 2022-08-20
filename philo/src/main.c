/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmarin-p <fmarin-p@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:31:30 by fmarin-p          #+#    #+#             */
/*   Updated: 2022/08/20 20:47:02 by fmarin-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_table	*create_table(int argc, char **argv)
{
	t_table	*table;
	int		i;

	table = malloc(sizeof(t_table));
	table->n_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		table->number_of_meals = ft_atoi(argv[5]);
	else
		table->number_of_meals = -2;
	if (table->n_philosophers == -1 || table->time_to_die == -1
		|| table->time_to_eat == -1 || table->time_to_sleep == -1
		|| table->number_of_meals == -1)
		return (0);
	table->fork = malloc(sizeof(pthread_mutex_t) * table->n_philosophers);
	i = -1;
	while (++i < table->n_philosophers)
		pthread_mutex_init(&table->fork[i], NULL);
	pthread_mutex_init(&table->print, NULL);
	table->dead = 0;
	table->g_start.tv_sec = 0;
	return (table);
}

void	end_simulation(t_table *table, pthread_t *philo)
{
	int	i;

	i = -1;
	while (++i < table->n_philosophers)
		pthread_mutex_destroy(&table->fork[i]);
	free(table->fork);
	free(philo);
	free(table);
}

int	main_thread(t_table *table)
{
	pthread_t	*philo;
	int			i;

	philo = malloc(sizeof(pthread_t) * table->n_philosophers);
	i = -1;
	while (++i < table->n_philosophers)
		if (pthread_create(&philo[i], NULL, &philo_routine, (void *)table))
			return (1);
	i = -1;
	while (++i < table->n_philosophers)
		if (pthread_join(philo[i], NULL))
			return (1);
	while (1)
	{
		if (table->dead)
		{
			end_simulation(table, philo);
			break ;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		*table;

	if (argc < 5 || argc > 6)
	{
		print_usage();
		return (0);
	}
	table = create_table(argc, argv);
	if (!table)
	{
		printf("Error while parsing arguments.\n");
		return (0);
	}
	if (main_thread(table))
		printf("Error while creating or waiting on threads\n");
	return (0);
}
