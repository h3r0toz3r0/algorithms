/**
 * @file linked_list.c
 * @brief Implementation of the Singly Linked List data structure.
 * 
 * @section operations Operations
 * - **Create**: Creates an empty linked list.
 * - **Destroy**: Deletes all elements in the linked list and destroys the list.
 * - **Insert**: Adds a new element to the beginning, end, or any position in the linked list.
 * - **Delete**: Removes an element from the linked list by key or position.
 * - **Search By Key**: Finds an element in the linked list by key.
 * - **Search By Index**: Finds an element in the linked list by index.
 * - **Traversal**: Visits each element in the linked list sequentially.
 * - **Reverse**: Reverses the order of the elements in the linked list.
 * 
 * @section complexity Complexity
 * - **Time Complexity**:   O(1) for insertion and deletion at the p_head, 
 *                          O(N) for insertion, deletion, and search, where N is the number of nodes.
 * - **Space Complexity**: O(N) for storing elements in the linked list, where N is the number of nodes.
 * 
 * @author  Anna DeVries
 * @date    August 21, 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

static void linked_list_del_node(linked_list_node_t *p_node, del_func del_f);
static linked_list_node_t *linked_list_create_node(void *p_data);

linked_list_t *linked_list_create(del_func del_f, cmp_func cmp_f, print_func print_f)
{
    linked_list_t * p_list = NULL;

    if ((NULL != del_f) && (NULL != cmp_f) && (NULL != print_f))
    {
        p_list = calloc(1, sizeof(linked_list_t));

        if (NULL != p_list)
        {
            p_list->p_head = NULL;
            p_list->cmp_f = cmp_f;
            p_list->del_f = del_f;
            p_list->print_f = print_f;
        }
    }

    return p_list;
}

void linked_list_destroy(linked_list_t *p_list)
{
    if (NULL != p_list)
    {
        linked_list_node_t * p_head = p_list->p_head;

        while (NULL != p_head)
        {
            linked_list_node_t * current = p_head;
            p_head = p_head->p_next;
            linked_list_del_node(current, p_list->del_f);
        }

        p_list->cmp_f = NULL;
        p_list->del_f = NULL;
        p_list->print_f = NULL;

        free(p_list);
        p_list = NULL;
    }

    return;
}

linked_list_t *linked_list_preappend(linked_list_t *p_list, void *p_data)
{
    return linked_list_insert(p_list, p_data, 0);
}

linked_list_t *linked_list_insert(linked_list_t *p_list, void *p_data, int index)
{
    if ((NULL == p_list) || (NULL == p_data) || (0 > index))
    {
        goto EXIT;
    }

    // create new node
    linked_list_node_t *p_new_node = NULL;
    p_new_node = linked_list_create_node(p_data);

    if (NULL == p_new_node)
    {
        goto EXIT;
    }

    // handle preappend operations
    if (0 == index)
    {
        p_new_node->p_next = p_list->p_head;
        p_list->p_head = p_new_node;
    }
    else
    {
        int count = 0;
        linked_list_node_t *p_curr = p_list->p_head;
        linked_list_node_t *p_prev = NULL;

        while ((NULL != p_curr) && (count < index))
        {
            p_prev = p_curr;
            p_curr = p_curr->p_next;
            count++;
        }

        if (count == index) // handle insertion operation at specific index
        {
            p_new_node->p_next = p_curr;
            p_prev->p_next = p_new_node;
        }
        else // count exceeds index; remove new node
        {
            linked_list_del_node(p_new_node, p_list->del_f);
        }
    }

EXIT:
    return p_list;
}

// linked_list_t *linked_list_del_at(linked_list_t *p_list, int index)
// {
//     return NULL;
// }

// linked_list_t *linked_list_at(linked_list_t *p_list, int index)
// {
//     return NULL;
// }

// linked_list_node_t *linked_list_find(linked_list_t *p_list, void *p_data)
// {
//     return NULL;
// }

// int linked_list_size(linked_list_t *p_list)
// {
//     return NULL;
// }

void linked_list_print(linked_list_t *p_list) 
{
    printf("\nLinked List: ");

    if ((NULL != p_list) && (NULL != p_list->print_f)) 
    {
        linked_list_node_t *current = p_list->p_head;

        while (NULL != current) 
        {
            p_list->print_f(current->p_data);
            current = current->p_next;
        }
    }

    printf("\n\n");

    return;
}

/**
 * @brief Deletes a node from the linked list and frees its memory.
 * 
 * This function deallocates the memory used by a single node in the linked list. It calls 
 * the provided delete function to handle the node's data and then frees the memory allocated 
 * for the node itself. After freeing the memory, it sets pointers in the node to `NULL` to 
 * avoid dangling pointers.
 * 
 * @param p_node Pointer to the node to be deleted.
 * @param del_f  Function pointer to the function used to delete the node's data.
 * 
 * @note The node's data and next pointer are set to `NULL` before freeing the node to prevent
 *       potential issues with dangling pointers.
 */
static void linked_list_del_node(linked_list_node_t *p_node, del_func del_f)
{
    if (NULL != p_node)
    {
        if (NULL != del_f)
        {
            del_f(p_node->p_data);
            p_node->p_data = NULL;
            p_node->p_next = NULL;
        }

        free(p_node);
        p_node = NULL;
    }

    return;
}

/**
 * @brief Creates and initializes a new node for the linked list.
 * 
 * This function allocates memory for a new node in the linked list and initializes its
 * members. The node's data pointer is set to the provided data, and the next pointer is
 * set to NULL. The function returns a pointer to the newly created node, or NULL if
 * memory allocation fails.
 * 
 * @param p_data Pointer to the data to be stored in the new node.
 * 
 * @return linked_list_node_t* Pointer to the newly created node, or NULL if memory
 *         allocation fails.
 * 
 * @note The provided data pointer `p_data` is directly assigned to the node without
 *       copying or validation. Ensure that the data pointer is valid and properly managed
 *       by the caller.
 */
static linked_list_node_t *linked_list_create_node(void *p_data)
{
    linked_list_node_t *node = NULL;
    node = calloc(1, sizeof(linked_list_node_t));

    if (NULL != node)
    {
        node->p_data = p_data;
        node->p_next = NULL;
    }

    return node;
}
