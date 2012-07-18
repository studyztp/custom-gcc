/* With -fnon-call-exceptions 0 / 0 should not be eliminated.  The .x
   file sets the option.  */

#ifdef SIGNAL_SUPPRESS
# define DO_TEST 0
#elif defined (__powerpc__) || defined (__PPC__) || defined (__ppc__) || defined (__POWERPC__) || defined (__ppc)
  /* On PPC division by zero does not trap.  */
# define DO_TEST 0
#elif defined (__SPU__)
  /* On SPU division by zero does not trap.  */
# define DO_TEST 0
#elif defined (__sh__)
  /* On SH division by zero does not trap.  */
# define DO_TEST 0
#elif defined (__TMS320C6X__)
  /* On TI C6X division by zero does not trap.  */
# define DO_TEST 0
#elif defined (__arm__)
 /* We cannot rely on division by zero generating a trap. */
# define DO_TEST 0
#elif defined (__mips__) && !defined(__linux__)
  /* MIPS divisions do trap by default, but libgloss targets do not
     intercept the trap and raise a SIGFPE.  The same is probably
     true of other bare-metal environments, so restrict the test to
     systems that use the Linux kernel.  */
# define DO_TEST 0
#elif defined (__mips16) && defined(__linux__)
  /* Not all Linux kernels deal correctly the breakpoints generated by
     MIPS16 divisions by zero.  They show up as a SIGTRAP instead.  */
# define DO_TEST 0
#elif defined (__epiphany__)
  /* Epiphany does not have hardware division, and the software implementation
     has truly undefined behaviour for division by 0.  */
# define DO_TEST 0
#elif defined (__m68k__) && !defined(__linux__)
  /* Attempting to trap division-by-zero in this way isn't likely to work on 
     bare-metal m68k systems.  */
# define DO_TEST 0
#else
# define DO_TEST 1
#endif

#if DO_TEST

#include <signal.h>

void
sigfpe (int signum __attribute__ ((unused)))
{
  exit (0);
}

#endif

/* When optimizing, the compiler is smart enough to constant fold the
   static unset variables i and j to produce 0 / 0, but it can't
   eliminate the assignment to the global k.  */
static int i;
static int j;
int k;

int
main ()
{
#if DO_TEST
  signal (SIGFPE, sigfpe);
  k = i / j;
  abort ();
#else
  exit (0);
#endif
}
