
Nothing changed between the -O0 and -O2 versions of a at compile time or run time (clean compile and segmentation fault on execution)
Nothing changed between the -O0 and -O2 versions of b. A compiler error warns of returning the address of a local.
Nothing changed between the -O0 and -O2 versions of c. Compiles cleanly then prints "1".
So what surprised me is that the -O0 and -O2 versions of the compile command didn't seem to change anything. I assumed that you put that in there expecting that I would get different results.

Rebuilding a with -fsanitize=address,unkown prints a very detailed error message instead of just "Segmentation fault", as does rebuilding b.
