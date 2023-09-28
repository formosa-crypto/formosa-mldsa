How to add a Jasmin function:

* Write the function in the corresponding file. For instance, reduce.jinc and reduce.jazz. Check montgomery_reduce as an example. The name of the exported function should be the same as the corresponding one in the C file ++ `_jazz`.

* Write a test for the function. Check `dilithium5/test/reduce/test_reduce.c` for an example.

* Add a "guard" to the function in the C file. Check reduce.c `#ifndef montgomery_reduce_jazz` for an example.

* Add an entry to the jasmin_functions_implemented.h file

* To check if the function is included correctly in the library, run (montgomery_reduce used as an example, replace accordingly):

```
$ dilithium-arm/src/libjade/dilithium5$ make small-testing && nm libdilithium5_clean.a | grep " T " | grep montgomery_reduce

00000001 T PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce
00000000 T _PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce_jazz
00000000 T PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce_jazz

```

* with `make small-testing` both functions are included in the .a file.

```
$ dilithium-arm/src/libjade/dilithium5$ make full-testing && nm libdilithium5_clean.a | grep " T " | grep montgomery_reduce

00000000 T _PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce_jazz
00000000 T PQCLEAN_DILITHIUM5_CLEAN_montgomery_reduce_jazz
```

* with `make full-testing` just the Jasmin function in included in the .a file.
