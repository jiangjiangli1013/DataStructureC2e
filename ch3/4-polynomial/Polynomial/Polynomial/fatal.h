#ifndef FATAL_H
#define FATAL_H

#include <stdio.h>
#include <stdlib.h>

#define reportError(Str) reportFatalError(Str);
#define reportFatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)

#endif /* FATAL_H */