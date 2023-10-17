#ifndef	_EXIT_H
#define _EXIT_H 1

#define attribute_hidden
#define INTDEF(name)

#include <stdbool.h>
#include <stdint.h>

enum
{
  ef_free,	/* `ef_free' MUST be zero!  */
  ef_us,
  ef_on,
  ef_at,
  ef_cxa
};

struct exit_function
  {
    /* `flavour' should be of type of the `enum' above but since we need
       this element in an atomic operation we have to use `long int'.  */
    long int flavor;
    union
      {
	void (*at) (void);
	struct
	  {
	    void (*fn) (int status, void *arg);
	    void *arg;
	  } on;
	struct
	  {
	    void (*fn) (void *arg, int status);
	    void *arg;
	    void *dso_handle;
	  } cxa;
      } func;
  };
struct exit_function_list
  {
    struct exit_function_list *next;
    size_t idx;
    struct exit_function fns[32];
  };
extern struct exit_function_list *__exit_funcs attribute_hidden;
extern struct exit_function_list *__quick_exit_funcs attribute_hidden;

extern struct exit_function *__new_exitfn (struct exit_function_list **listp);
extern uint64_t __new_exitfn_called attribute_hidden;

extern void __run_exit_handlers (int status, struct exit_function_list **listp,
				 bool run_list_atexit)
  attribute_hidden __attribute__ ((__noreturn__));

extern int __internal_atexit (void (*func) (void *), void *arg, void *d,
			      struct exit_function_list **listp)
  attribute_hidden;
extern int __cxa_at_quick_exit (void (*func) (void *), void *d);

extern int __cxa_atexit (void (*func) (void *), void *arg, void *d);
extern int __cxa_atexit_internal (void (*func) (void *), void *arg, void *d)
     attribute_hidden;

extern void __cxa_finalize (void *d);

#endif	/* exit.h  */