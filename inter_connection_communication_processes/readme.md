### Inter connection communcation
- [Shared Memeory](shared_memory_interconnection)
- [Message Passing](message_sharing_using_pipes)
  - using pipes()
- [Signals](signals.c)

### Pipes()
```
 * All about pipe()
 *              +---------------+
 * write, fd[1] -->                read, fd[0]-->
 *              +---------------+
 * write 512 bytes one a time
 * read 1 bytes one a time
 * the read flow waited till write flow
 * return 0 -> for sucessful
 * return -1 -> for error
 ```