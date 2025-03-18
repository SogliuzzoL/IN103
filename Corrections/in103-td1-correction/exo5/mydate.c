#include <time.h>

int clock_gettime (clockid_t clk_id, struct timespec *tp)
{
  tp->tv_sec = 1893452400; /* 01/01/2030 */
  tp->tv_nsec = 0;
  return 0;
}
