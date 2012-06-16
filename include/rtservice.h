/*
 * File      : rtservice.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-03-16     Bernard      the first version
 * 2006-09-07     Bernard      move the kservice APIs to rtthread.h
 * 2007-06-27     Bernard      fix the rt_list_remove bug
 * 2012-03-22     Bernard      rename kservice.h to rtservice.h
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup KernelService
 */

/*@{*/

/**
 * @brief initialize a list object
 */
#define RT_LIST_OBJECT_INIT(object) { &(object), &(object) }

/**
 * @brief initialize a list
 *
 * @param l list to be initialized
 */
rt_inline void rt_list_init(rt_list_t *l)
{
	l->next = l->prev = l;
}

/**
 * @brief insert a node after a list
 *
 * @param l list to insert it
 * @param n new node to be inserted
 */
rt_inline void rt_list_insert_after(rt_list_t *l, rt_list_t *n)
{
	l->next->prev = n;
	n->next = l->next;

	l->next = n;
	n->prev = l;
}

/**
 * @brief insert a node before a list
 *
 * @param n new node to be inserted
 * @param l list to insert it
 */
rt_inline void rt_list_insert_before(rt_list_t *l, rt_list_t *n)
{
	l->prev->next = n;
	n->prev = l->prev;

	l->prev = n;
	n->next = l;
}

/**
 * @brief remove node from list.
 * @param n the node to remove from the list.
 */
rt_inline void rt_list_remove(rt_list_t *n)
{
	n->next->prev = n->prev;
	n->prev->next = n->next;

	n->next = n->prev = n;
}

/**
 * @brief tests whether a list is empty
 * @param l the list to test.
 */
rt_inline int rt_list_isempty(const rt_list_t *l)
{
	return l->next == l;
}

/**
 * @brief get the struct for this entry
 * @param node the entry point
 * @param type the type of structure
 * @param member the name of list in structure
 */
#define rt_list_entry(node, type, member) \
    ((type *)((char *)(node) - (unsigned long)(&((type *)0)->member)))

#ifdef RT_USING_HEAP_SORT

#define RT_HEAP_PARENT(i)	((i) / 2)
#define RT_HEAP_LEFT(i) 	(2 * (i))
#define RT_HEAP_RIGHT(i)	(2 * (i) + 1)
#define RT_HEAP_NODE(h,i)	((h)->nodes[(i)-1])

#define rt_heap_entry rt_list_entry

rt_inline void rt_heap_init(rt_heap_t *heap)
{
	heap->size = 0;
}

rt_inline void rt_heap_node_init(rt_heap_node_t *node)
{
	node->heap = RT_NULL;
	node->i = (rt_size_t)-1;
}

rt_inline void rt_heap_node_clear(rt_heap_node_t *node)
{
	rt_heap_node_init(node);
}

rt_inline rt_heap_node_t *rt_heap_top(rt_heap_t *heap)
{
	RT_ASSERT(heap);

	if (heap->size)
		return RT_HEAP_NODE(heap, 1);
	else
		return RT_NULL;
}

#endif

/*@}*/

#ifdef __cplusplus
}
#endif
