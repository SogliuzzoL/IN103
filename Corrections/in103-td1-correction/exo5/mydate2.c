#define _GNU_SOURCE  /* Pour avoir RTLD_NEXT. */
#include <time.h>
#include <dlfcn.h>

int
clock_gettime (clockid_t clk_id, struct timespec *tp)
{
  static int (*orig_clock_gettime) (clockid_t, struct timespec *) = 0;

  if (!orig_clock_gettime)
    orig_clock_gettime = dlsym (RTLD_NEXT, "clock_gettime");

  orig_clock_gettime (clk_id, tp);
  tp->tv_sec += 24 * 60 * 60;
  return 0;
}
