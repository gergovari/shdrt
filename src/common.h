#pragma once

/**
 * @def COUNT_ITEMS
 * @brief Helper macro to count items in X-macro lists.
 * 
 * Used in conjunction with X-macros to calculate the number of elements in an enum or list.
 * @param name The name of the item (unused in the expansion).
 */
#define COUNT_ITEMS(name) +1
