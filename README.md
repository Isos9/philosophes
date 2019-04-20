# Philosophes

C program that uses threads to solves the [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

## Requirements

 - [A Linux distribution](https://en.wikipedia.org/wiki/Linux_distribution)/[Apple's macOS](https://en.wikipedia.org/wiki/MacOS)
 - [Make](https://www.gnu.org/software/make/)
 - [GCC](https://gcc.gnu.org/)

## Execution

```
cd philosophes
make
LD_LIBRARY_PATH=$(pwd)
LD_PRELOAD=./libriceferee.so ./philo
```
