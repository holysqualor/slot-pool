# slot pool

**Slot pool** is a combination of a linked list and a vector. A slot is an analogue of a node from a linked list, but it does not require memory allocation/freeing with each modification of the structure. Memory for slots is allocated in advance and increases when a capacity is reached. Due to reallocations, slot identifiers (`sl_id`), which are byte offsets, are used instead of pointers. A special mechanism ensures efficient memory use: when an element is deleted, its slot is unbound, and the identifier is added to a stack, and if an element is added after that, it will be written to the newly deleted slot. If the stack is empty, the new element is added to the physical end of the pool. Slot data is not modified when deleted, which allows its reuse. The `sl_exp` function shows whether a new (`1`) or old (`0`) slot was used when the element was last added, in which case it is enough to change the data without allocating new memory (this is useful when the pool elements are dynamic objects). The pool destruction function can be passed a destructor that is called for all, even unbound, elements.

Slot pool claims to replace the classic linked list, because it uses memory much more efficiently. Main advantages:
- minimum memory allocations/frees
- memory reuse
- cache locality
- pool cleaning `O(1)`