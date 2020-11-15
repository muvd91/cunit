#include<time.h>
#include<stdio.h>

#define __call(S,E,T) \
 for(double h = 0, T = 0; h < 1; h++) \
   for(\
     clock_t i = 0, E = 0, S = clock(); \
     i < 1; \
     i++, E = clock(), T = (double)(E - S)/CLOCKS_PER_SEC, printf("Elapsed time: %f sec.\n", T)) \

#define __call_def_elapsed(S,E,T) \
 double T = 0; \
 for(\
   clock_t i = 0, E = 0, S = clock(); \
   i < 1; \
   i++, E = clock(), T = (double)(E - S)/CLOCKS_PER_SEC) \

#define __expand2(COUNTER) __call(__start ## COUNTER, __end ## COUNTER, __elapsed ## COUNTER)

#define __expand(COUNTER) __expand2(COUNTER)

#define measure_time __expand(__COUNTER__)

#define __expand_elapsed2(E, COUNTER) __call_def_elapsed(__start ## COUNTER, __end ## COUNTER, E)

#define __expand_elapsed(E, COUNTER) __expand_elapsed2(E, COUNTER)

#define get_measure_time(E) __expand_elapsed(E, __COUNTER__)

