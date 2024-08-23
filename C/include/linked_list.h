/**
 * @file    linked_list.h
 * @brief   Header file for `linked_list.c`.
 *
 * @author  Anna DeVries
 * @date    August 21, 2024
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/**
 * @brief Function pointer type for a custom delete function.
 * 
 * This function pointer is intended to delete or free the data stored
 * within a linked list node. For simple data types (e.g., integers, 
 * basic structs), this can be as straightforward as pointing to the 
 * `free` function.
 * 
 * @param p_data Pointer to the data within the node that needs to be deleted.
 * 
 * @note The function should handle any necessary cleanup to avoid memory leaks.
 * 
 * @example
 * To delete integers/chars/strings:
 * @code
 * void delete_function(void *p_data) {
 *     free(p_data);
 *     p_data = NULL;
 * }
 * @endcode
 */
typedef void (*del_func)(void * p_data);

/**
 * @brief Function pointer type for a custom print function.
 * 
 * This function pointer is used to print the data stored within a 
 * linked list node. The specific implementation of this function 
 * should be tailored to the data type stored in the node.
 * 
 * @param p_data Pointer to the data within the node that needs to be printed.
 * 
 * @note Ensure the function properly formats the output according to the 
 *       data type being printed.
 * 
 * @example
 * To print integers:
 * @code
 * void print_int(void *p_data) {
 *     printf("%d\n", *(int *)p_data);
 * }
 * @endcode
 * 
 * To print characters:
 * @code
 * void print_char(void *p_data) {
 *     printf("%c\n", *(char *)p_data);
 * }
 * @endcode
 * 
 * To print strings:
 * @code
 * void print_string(void *p_data) {
 *     printf("%s\n", (char *)p_data);
 * }
 * @endcode
 */
typedef void (*print_func)(void * p_data);

/**
 * @brief Function pointer type for a custom comparison function.
 * 
 * This function pointer is designed to compare two arbitrary data types 
 * stored within linked list nodes. The comparison function should return 
 * an integer value that indicates the relative order of the two data items, 
 * similar to the behavior of the standard `strcmp` function.
 * 
 * @param p_lhs Pointer to the left-hand side data for comparison.
 * @param p_rhs Pointer to the right-hand side data for comparison.
 * 
 * @returns 
 * - A negative value if p_lhs is less than p_rhs.
 * - Zero if p_lhs is equal to p_rhs.
 * - A positive value if p_lhs is greater than p_rhs.
 * 
 * @note The return values are intended to be compatible with standard 
 *       sorting and comparison functions, following the conventions 
 *       established by `strcmp`.
 * 
 * @example
 * To compare integers:
 * @code
 * int compare_ints(void *p_lhs, void *p_rhs) {
 *     int lhs = *(int *)p_lhs;
 *     int rhs = *(int *)p_rhs;
 *     return (lhs > rhs) - (lhs < rhs);
 * }
 * @endcode
 * 
 * To compare characters:
 * @code
 * int compare_chars(void *p_lhs, void *p_rhs) {
 *     char lhs = *(char *)p_lhs;
 *     char rhs = *(char *)p_rhs;
 *     return (lhs > rhs) - (lhs < rhs);
 * }
 * @endcode
 * 
 * To compare strings:
 * @code
 * int compare_strings(void *p_lhs, void *p_rhs) {
 *     return strcmp((char *)p_lhs, (char *)p_rhs);
 * }
 * @endcode
 */
typedef int (*cmp_func)(void * p_lhs, void * p_rhs);

/**
 * @brief Structure representing a node in the linked list.
 * 
 * This structure represents a single node in a linked list. Each node contains a pointer 
 * to the data it holds and a pointer to the next node in the list. It allows the linked list
 * to manage and traverse a sequence of elements.
 */
typedef struct linked_list_node {
    void *p_data;
    struct linked_list_node *p_next;
} linked_list_node_t;

/**
 * @brief Structure representing a linked list.
 * 
 * This structure represents the entire linked list. It includes a pointer to the head node of 
 * the list and function pointers for managing the nodes' data. The functions provided allow 
 * for deleting, comparing, and printing node data, facilitating custom behavior for the list.
 */
typedef struct {
    linked_list_node_t *p_head;
    del_func del_f;
    cmp_func cmp_f;
    print_func print_f;
} linked_list_t;

/**
 * @brief Creates and initializes a new linked list.
 * 
 * This function allocates memory for a new linked list and initializes its members.
 * The linked list is configured with custom delete, compare, and print functions 
 * provided by the user.
 * 
 * @param del_f   Pointer to a function that will be used to delete a node's data.
 * @param cmp_f   Pointer to a function that will be used to compare two nodes' data.
 * @param print_f Pointer to a function that will be used to print a node's data.
 * 
 * @return linked_list_t* Pointer to the newly created linked list, 
 *                        or NULL if memory allocation fails or if any provided 
 *                        function pointer is NULL.
 */
linked_list_t *linked_list_create(del_func del_f, cmp_func cmp_f, print_func print_f);

/**
 * @brief Destroys the linked list and frees its resources.
 * 
 * This function iterates through the linked list, freeing the memory allocated for each node's
 * data using the delete function pointer. It then frees the memory for each node and finally
 * frees the memory allocated for the linked list structure itself. The function sets function
 * pointers to NULL after use to prevent potential dangling pointer issues.
 * 
 * @param p_list Pointer to the linked list to be destroyed.
 * 
 * @note The linked list itself, including all its nodes and data, will be deallocated. After
 *       calling this function, the provided pointer to the linked list will be invalid.
 */
void linked_list_destroy(linked_list_t *p_list);

/**
 * @brief Prepends a new node with the given data to the start of the linked list.
 * 
 * This function is a convenience wrapper around `linked_list_insert` that inserts
 * a new node at the head (index 0) of the linked list. The new node becomes the 
 * first node in the list.
 * 
 * @param p_list Pointer to the linked list where the node will be prepended.
 * @param p_data Pointer to the data to be stored in the new node.
 * 
 * @return linked_list_t* Pointer to the updated linked list, or NULL if the operation fails.
 * 
 * @note The function assumes that the `p_data` pointer is valid and properly managed 
 *       by the caller. The function may return NULL if the list pointer or data pointer 
 *       is invalid, or if memory allocation for the new node fails.
 */
linked_list_t *linked_list_preappend(linked_list_t *p_list, void *p_data);

/**
 * @brief Inserts a new node with the given data at the specified index in the linked list.
 * 
 * This function inserts a new node at the specified index in the linked list. If the index 
 * is 0, the new node is inserted at the head. If the index is greater than the number of 
 * nodes in the list, the function appends the node at the end.
 * 
 * @param p_list Pointer to the linked list.
 * @param p_data Pointer to the data to be stored in the new node.
 * @param index  The position at which to insert the new node (0-based index).
 * 
 * @return linked_list_t* Pointer to the updated linked list, or NULL if insertion fails.
 * 
 * @note The function assumes that the `p_data` pointer is valid and properly managed 
 *       by the caller.
 */
linked_list_t *linked_list_insert(linked_list_t *p_list, void *p_data, int index);


linked_list_t *linked_list_del_at(linked_list_t *p_list, int index);
linked_list_t *linked_list_at(linked_list_t *p_list, int index);
linked_list_node_t *linked_list_find(linked_list_t *p_list, void *p_data);
int linked_list_size(linked_list_t *p_list);

/**
 * @brief Prints the data in each node of the linked list.
 * 
 * This function traverses the linked list and uses the provided print function pointer
 * to print the data stored in each node. The traversal continues until all nodes have
 * been processed. The function does nothing if the linked list or the print function is `NULL`.
 * 
 * @param p_list Pointer to the linked list to be printed.
 * 
 * @note The function assumes that `p_list` is valid and that `p_list->print_f` is not `NULL`.
 *       If either of these conditions is not met, the function does nothing.
 */
void linked_list_print(linked_list_t *p_list);

#endif // LINKED_LIST_H
