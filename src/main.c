//
// Author: Marwane Khsime 
// Date: 2017-03-16 21:57:16 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-03-16 21:57:16
//

#include "../includes/philosophers.h"

static bool	waitForPhilosophers(t_manager *manager) {
  int		i;

  i = 0;
  while (i < manager->nbPhilos) {
    if (pthread_join(manager->philos[i++].thread, NULL) != 0)
      return false;
    printf("%d a fini\n", i - 1);
  }
  return true;
}

static void	*philosopherAlgorithm(void *_manager) {
  t_manager	*manager;

  manager = (t_manager *)_manager;
  (void)manager;
  printf("philosopher bitch\n");
  sleep(2);
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

static bool	initPhilosopher(t_manager *manager, char **argv) {
  int		i;

  if (!checkParameters(argv))
    return false;
  manager->nbPhilos = atoi(argv[2]);
  manager->nbChopsticks = manager->nbPhilos;
  manager->mealsLimit = atoi(argv[4]);
  manager->limitReached = false;
  if (!(manager->philos = malloc(sizeof(t_philos) * manager->nbPhilos)))
    return false;
  i = 0;
  while (i < manager->nbPhilos) {
    manager->philos[i].id = i;
    manager->philos[i].lastAction = UNDEFINED;
    if (pthread_mutex_init(&manager->philos[i].chopstick, NULL) != 0 ||
	pthread_create(&manager->philos[i].thread, NULL, &philosopherAlgorithm, manager) != 0)
      return false;
    i++;
  }
  return true;
}

static bool     LaunchPhilosopher(char **argv) {
  t_manager	manager;

  if (!initPhilosopher(&manager, argv))
    return EXIT_FAILURE;
  if (!waitForPhilosophers(&manager))
    return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int		main(int argc, char **argv) 
{
    return argc == 5 ? LaunchPhilosopher(argv) : EXIT_FAILURE;
}
