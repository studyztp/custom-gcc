/* Test for strftime format attributes: can't have first_arg_num != 0.  */
/* Origin: Joseph Myers <jsm28@cam.ac.uk> */
/* { dg-do compile } */
/* { dg-options "-std=gnu99 -Wformat" } */

extern void foo0 (const char *) __attribute__((__format__(__strftime__, 1, 0)));
extern void foo1 (const char *, ...) __attribute__((__format__(__strftime__, 1, 2))); /* { dg-error "cannot format" "strftime first_arg_num != 0" } */
