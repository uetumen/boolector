#ifdef NDEBUG
#undef NDEBUG
#endif

#include "testtestcases.h"
#include "btormain.h"
#include "btorstack.h"
#include "testrunner.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static BtorCharPtrStack args;

static void
test_testcase (void)
{
  (void) btor_main (BTOR_COUNT_STACK (args), args.start);
}

void
init_testcases_tests (void)
{
}

void
run_testcases_tests (int argc, char** argv)
{
  BtorCharStack buffer;
  BtorMemMgr* mem;
  char* token;
  FILE* file;
  int ch;

  assert ((file = fopen ("testcases", "r")));

  mem = btor_new_mem_mgr ();

  BTOR_INIT_STACK (args);
  BTOR_INIT_STACK (buffer);

  for (;;)
  {
    ch = fgetc (file);
    if (ch == EOF) break;

    if (isspace (ch)) continue;

    if (ch == '#')
    {
      while ((ch = getc (file)) != '\n' && ch != EOF)
        ;

      continue;
    }

    assert (BTOR_EMPTY_STACK (buffer));

    do
    {
      BTOR_PUSH_STACK (mem, buffer, ch);
      ch = fgetc (file);
    } while (ch != '\n' && ch != EOF);
    BTOR_PUSH_STACK (mem, buffer, 0);

    assert (BTOR_EMPTY_STACK (args));

    token = strtok (buffer.start, " \t");
    while (token)
    {
      BTOR_PUSH_STACK (mem, args, token);
      token = strtok (0, " \t");
    }

    BTOR_RESET_STACK (buffer);

    run_test_case (argc, argv, test_testcase, args.start[0], 1);

    BTOR_RESET_STACK (args);
  }

  fclose (file);

  BTOR_RELEASE_STACK (mem, buffer);
  BTOR_RELEASE_STACK (mem, args);

  btor_delete_mem_mgr (mem);
}

void
finish_testcases_tests (void)
{
}
