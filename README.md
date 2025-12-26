# slpool

A lightweight, high-performance **Slab Allocator** and **Object Pool** with an integrated doubly linked list for C applications.

`slpool` was designed for systems that require frequent insertion/deletion of fixed-size objects while maintaining memory locality and stable identifiers.

---

## Key Features

- **Stable Identifiers (`sl_id`)**: Unlike raw pointers, IDs remain valid even after the internal buffer is reallocated.
- **Zero Fragmentation**: Uses an internal "holes" stack to reuse deleted slots immediately.
- **High Water Mark Optimization**: Tracks the physical growth of the pool to support lazy initialization.
- **O(1) Manipulations**: Adding, removing, and accessing elements are constant-time operations.
- **Cache Friendly**: All data is stored in a contiguous memory block.

---

## Installation

Simply include the header and source in your project:

```bash
cp include/slpool.h your_project/
cp src/slpool.c your_project/
