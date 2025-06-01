# Q1

this character array is 6 bytes long

```c
char name[] = "Maria"; // {'M', 'a', 'r', 'i', 'a', '\0'}
```

# Q2

```c
free(data->var);
free(data);
```

we had malloced memory inside data and for data, so if we'd deallocate the data first, we'll not get access to the var inside data. You need to dealloc the inners of this data to not leak memory. 

# Q3


- A linked list's item must keep the reference to the next item.

so it adds N*reference size  (N is how many items) bytes to the structure


# Q4

the malloc variant returns a pointer to that memory in heap. 
the other stack variant (static) you have to declare it outside the func to use it elsewhere. there are workarrounds, but which are bad practices.

# Q5

this qsort is best optimised there is
but it has no clue what and how to access and compare data in given strucure, so it needs an additional function to do comparisson, to find what needs to be found.

