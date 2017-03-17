//
// Author: Marwane Khsime 
// Date: 2017-03-16 21:57:16 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-03-16 21:57:16
//

#include "../includes/philosophers.h"

static bool	waitForPhilosophers(t_table *table, t_philo *philosophers) {
  int		i;

  i = 0;
  while (i < table->nbPhilos) {
    if (pthread_join(philosophers[i++].thread, NULL) != 0)
      return false;
    printf("%d a fini\n", i - 1);
  }
  return true;
}

static void	*philosopherAlgorithm(void *_philosopher) {
  t_philo	*philosopher;
  int		i;

  philosopher = (t_philo *)_philosopher;
  i = philosopher->id + 1;
  while (!philosopher->table->limitReached)
    {
      if (pthread_mutex_trylock(&philosopher->table->bowls[i - 1]) != 0
	  && pthread_mutex_trylock(&philosopher->table->bowls[i]) != 0)
	philoSleep(philosopher);
      else if (pthread_mutex_trylock(&philosopher->table->bowls[i - 1]) == 0
	       && pthread_mutex_trylock(&philosopher->table->bowls[i]) != 0)
	philoThink(philosopher, 0);
      else if (pthread_mutex_trylock(&philosopher->table->bowls[i - 1]) != 0
	       && pthread_mutex_trylock(&philosopher->table->bowls[i]) == 0)
	philoThink(philosopher, 1);
      else
	philoEat(philosopher);
    }
  pthread_exit(NULL);
}

/*
** Check Parameters.
*/
static bool	checkParameters(char **argv) {
  if ((atoi(argv[2]) <= 0) ||
      (atoi(argv[4]) <= 0))
    return false;
  if ((strcmp(argv[1], "-p") != 0) ||
      (strcmp(argv[3], "-e") != 0))
    return false;
  return true;
};

static bool	initPhilosopher(t_table *table, char **argv) {
  int		i;

  if (!checkParameters(argv))
    return false;

  table->nbPhilos = atoi(argv[2]);
  table->mealsLimit = atoi(argv[4]);
  table->limitReached = false;
  if (pthread_cond_init(&table->cond, NULL) != 0)
    return false;

  pthread_mutex_t	_bowls[table->nbPhilos];
  t_philo		philosophers[table->nbPhilos];

  table->bowls = _bowls;
  i = 0;
  while (i < table->nbPhilos)
    if (pthread_mutex_init(&table->bowls[i++], NULL) != 0)
      return false;

  i = 0;
  while (i < table->nbPhilos) {
    philosophers[i].id = i;
    philosophers[i].nbMeals = 0;
    philosophers[i].lastAction = UNDEFINED;
    philosophers[i].table = table;
    philosophers[i].timeToEat = (rand() % 5) + 1;
    philosophers[i].timeToSleep = (rand() % 5) + 1;
    philosophers[i].timeToThink = (rand() % 5) + 1;

    if (pthread_create(&philosophers[i].thread, NULL, &philosopherAlgorithm, &philosophers[i]) != 0)
      return false;
    i++;
  }
  if (!waitForPhilosophers(table, philosophers))
    return false;
  return true;
}

static bool     LaunchPhilosopher(char **argv) {
  t_table	table;

  srand(time(NULL));
  if (!initPhilosopher(&table, argv))
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int		main(int argc, char **argv) 
{
    return argc == 5 ? LaunchPhilosopher(argv) : EXIT_FAILURE;
}
