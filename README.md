# pipex

A program that simulates pipes in C

For this project you will have to learn how pipes work, the code is short but understanding and learning what this mini hell hound of a code does takes time.  
I struglled a lot with leaks since you'll have to handle things such as child processes, pipes, and A LOT of fd tracking.  
The condition `> 2` for the fds is to avoid closing a `STDIN` or `STDOUT` or `STDERR`, that would be troublesome.  
Another thing, this guy might leak, due to the pc I mean — in the child processes I launch commands such as `grep` or `ls`.

FYI this one below is the valgrind for `ls`:

```
==38103== HEAP SUMMARY:
==38103==     in use at exit: 20,644 bytes in 10 blocks
==38103==   total heap usage: 47 allocs, 37 frees, 92,967 bytes allocated
==38103== 
==38103== LEAK SUMMARY:
==38103==    definitely lost: 0 bytes in 0 blocks
==38103==    indirectly lost: 0 bytes in 0 blocks
==38103==      possibly lost: 0 bytes in 0 blocks
==38103==    still reachable: 20,644 bytes in 10 blocks
==38103==         suppressed: 0 bytes in 0 blocks
==38103== Rerun with --leak-check=full to see details of leaked memory
==38103== 
==38103== For lists of detected and suppressed errors, rerun with: -s
==38103== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

Yeah, lots of still reachable, nothing to actually worry about since it's probably because of your pc.  
Here in 42 Rome this often happens.

```
valgrind --show-leak-kinds=all ./pipex Makefile "cat" "ls" outfile                                     
==38704== Memcheck, a memory error detector
==38704== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==38704== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==38704== Command: ./pipex Makefile cat ls outfile
==38704==
```
Straight up decides to not do his job anymore

This shi was tiring asf since i was burned out

ADVICE: For the Milestone 2 i highly suggest this way of working

push_swap->pipex/minitalk->minilibx_related.
