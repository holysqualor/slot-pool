#ifndef SLPOOL_H
#define SLPOOL_H

#include <stddef.h>

/**
 * @brief Pool descriptor (opaque structure pointer)
 */
typedef struct sl_pool_s *sl_pool;

/**
 * @brief Slot identifier type (instead of pointers).
 * Stable during memory reallocations.
 */
typedef size_t sl_id;

/**
 * @brief Empty identifier value (NULL analog)
 */
extern const sl_id nullid;


/* --- Life cycle --- */


/**
 * @brief Creates a new pool for elements of size element_size
 * @param element_size Size of one data element in bytes
 * @return sl_pool handle or NULL on failure
 */
sl_pool sl_create(size_t element_size);

/**
 * @brief Destroys the pool and frees all memory
 * @param pool Pool handle
 * @param destructor Function to clean up data inside slots (can be NULL)
 * @note Destructor is called for all created objects
 * @return Always returns NULL
 */
sl_pool sl_destroy(sl_pool pool, void (*destructor)(void*));

/**
 * @brief Clears the pool without freeing the main buffer
 * @param pool Pool handle
 * @return Pool handle for chaining
 */
sl_pool sl_clear(sl_pool pool);


/* --- Manipulation --- */


/**
 * @brief Adds new element into the pool before the specified element
 * @param pool Pool handle
 * @param element Pointer to the data to copy (can be NULL)
 * @param before ID of the element before which to insert (nullid for end)
 * @return sl_id New object identifier or nullid in case of error
 */
sl_id sl_add(sl_pool pool, const void *element, sl_id before);

/**
 * @brief Removes the object from the pool linked list
 * @param pool Pool handle
 * @param slot ID of the slot to remove
 * @note Removed slots are moved to an internal stack for reuse
 * @return sl_id Next object identifier or nullid in case of pool end
 */
sl_id sl_remove(sl_pool pool, sl_id slot);


/* --- Quick wraps --- */


sl_id sl_push_back(sl_pool pool, const void *element);
sl_id sl_push_front(sl_pool pool, const void *element);


/* --- Navigation and state --- */


sl_id sl_first(sl_pool pool);
sl_id sl_last(sl_pool pool);
sl_id sl_prev(sl_pool pool, sl_id slot);
sl_id sl_next(sl_pool pool, sl_id slot);
size_t sl_length(sl_pool pool);
int sl_is_empty(sl_pool pool);

/**
 * @brief Returns a direct pointer to the slot data
 * @param pool Pool handle
 * @param slot Slot ID
 * @return void* pointer to data or NULL if slot is nullid
 */
void *sl_get(sl_pool pool, sl_id slot);

/**
 * @brief Checks if the last addition expanded the pool
 * @param pool Pool handle
 * @return 1 if a brand new slot was used, 0 if an old hole was reused
 */
int sl_exp(sl_pool pool);

/**
 * @brief Iterates over all active elements
 * @param pool Pool handle
 * @param f Callback function (data, context)
 * @param ctx User context pointer
 * @return Pool handle for chaining
 */
sl_pool sl_for_each(sl_pool pool, void (*f)(void*, const void*), const void *ctx);

#endif /* SLPOOL_H */
