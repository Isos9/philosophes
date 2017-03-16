//
// Author: Marwane Khsime 
// Date: 2017-03-16 21:57:16 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-03-16 21:57:16
//

#include "../includes/philosophers.h"

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
  if (!(manager->philos = malloc(sizeof(t_philos) * manager->nbPhilos)))
    return false;
  i = 0;
  while (i < manager->nbPhilos) {
    manager->philos[i].id = i;
    manager->philos[i].lastAction = UNDEFINED;
    i++;
    // thread && mutex
  }
  return true;
}

static bool     LaunchPhilosopher(char **argv) {
  t_manager	manager;

  if (!initPhilosopher(&manager, argv))
    return EXIT_FAILURE;
  for (int i = 0; i < manager.nbPhilos; i++) {
    printf("Philosophe [%d] => %d\n", manager.philos[i].id, (int)manager.philos[i].lastAction);
  }
  (void)manager;
  (void)argv;
  return EXIT_SUCCESS;
}

int		main(int argc, char **argv) 
{
    return argc == 5 ? LaunchPhilosopher(argv) : EXIT_FAILURE;
}
