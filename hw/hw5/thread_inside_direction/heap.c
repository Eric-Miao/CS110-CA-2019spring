/*
 * File: heap.c
 * 
 *   Implementation of library functions manipulating a min priority queue.
 *     Feel free to add, remove, or modify these library functions to serve
 *     your algorithm.
 *  
 * Jose @ ShanghaiTech University
 *
 */

#include <stdlib.h>     /* malloc, free */
#include <limits.h>     /* INT_MAX */
#include "heap.h"

/* 
 * Initialize a min heap. The heap is constructed using array-based
 *   implementation. Returns the pointer to the new heap.
 *
 */
heap_t *
heap_init (void)
{
    heap_t *h = malloc(sizeof(heap_t));
    h->size = 0;
    h->capacity = INIT_CAPACITY;    /* Initial capacity = 1000. */
    h->nodes = malloc(INIT_CAPACITY * sizeof(node_t *));
    h->nodes[0] = malloc(sizeof(node_t));
    h->nodes[0]->Ffs = -INT_MAX;      /* Dummy node at index 0. */
    h->nodes[0]->Rfs = -INT_MAX;      /* Dummy node at index 0. */
    return h;
}

/* 
 * Delete the memory occupied by the min heap H.
 *
 */
void
heap_destroy (heap_t *h)
{
    free(h->nodes[0]);
    free(h->nodes);
    free(h);
}

/* 
 * Insert a node N into the min heap H.
 *
 */
void
heap_insertF (heap_t *h, node_t *n)
{
    int cur = ++h->size;    /* Index 0 lays dummy node, so increment first. */
    h->nodes[h->size] = n;
    while (node_lessF(n, h->nodes[cur / 2])&&cur!=0) {
        h->nodes[cur] = h->nodes[cur / 2];
        h->nodes[cur]->heap_idF = cur;
        cur /= 2;
    }
    h->nodes[cur] = n;
    n->heap_idF = cur;

    /* If will exceed current capacity, doubles the capacity. */
    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->nodes = realloc(h->nodes, h->capacity * sizeof(node_t *));
    }
}

/* 
 * Extract the root (i.e. the minimum node) in min heap H. Returns the pointer
 *   to the extracted node.
 *
 */
node_t *
heap_extractF (heap_t *h)
{
    node_t *ret = h->nodes[1];
    node_t *last = h->nodes[h->size--];
    int cur, child;
    for (cur = 1; 2 * cur <= h->size; cur = child) {
        child = 2 * cur;
        if (child < h->size && node_lessF(h->nodes[child + 1],
                                         h->nodes[child]))
            child++;
        if (node_lessF(h->nodes[child], last)) {
            h->nodes[cur] = h->nodes[child];
            h->nodes[cur]->heap_idF = cur;
        } else
            break;
    }
    h->nodes[cur] = last;
    last->heap_idF = cur;
    return ret;
}

/* 
 * Update the min heap H in case that node N has changed its f-score.
 *
 */
void
heap_updateF (heap_t *h, node_t *n)
{
    int cur = n->heap_idF;
    while (node_lessF(n, h->nodes[cur / 2])&&cur!=0) {
        h->nodes[cur] = h->nodes[cur / 2];
        h->nodes[cur]->heap_idF = cur;
        cur /= 2;
    }
    h->nodes[cur] = n;
    n->heap_idF = cur;
}


void
heap_insertR (heap_t *h, node_t *n)
{
    int cur = ++h->size;    /* Index 0 lays dummy node, so increment first. */
    h->nodes[h->size] = n;
    while (node_lessR(n, h->nodes[cur / 2])&&cur!=0) {
        h->nodes[cur] = h->nodes[cur / 2];
        h->nodes[cur]->heap_idR = cur;
        cur /= 2;
    }
    h->nodes[cur] = n;
    n->heap_idR = cur;

    /* If will exceed current capacity, doubles the capacity. */
    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->nodes = realloc(h->nodes, h->capacity * sizeof(node_t *));
    }
}

/*
 * Extract the root (i.e. the minimum node) in min heap H. Returns the pointer
 *   to the extracted node.
 *
 */
node_t *
heap_extractR (heap_t *h)
{
    node_t *ret = h->nodes[1];
    node_t *last = h->nodes[h->size--];
    int cur, child;
    for (cur = 1; 2 * cur <= h->size; cur = child) {
        child = 2 * cur;
        if (child < h->size && node_lessR(h->nodes[child + 1],
                                          h->nodes[child]))
            child++;
        if (node_lessR(h->nodes[child], last)) {
            h->nodes[cur] = h->nodes[child];
            h->nodes[cur]->heap_idR = cur;
        } else
            break;
    }
    h->nodes[cur] = last;
    last->heap_idR = cur;
    return ret;
}

/*
 * Update the min heap H in case that node N has changed its f-score.
 *
 */
void
heap_updateR (heap_t *h, node_t *n)
{
    int cur = n->heap_idR;
    while (node_lessR(n, h->nodes[cur / 2])&&cur!=0) {
        h->nodes[cur] = h->nodes[cur / 2];
        h->nodes[cur]->heap_idR = cur;
        cur /= 2;
    }
    h->nodes[cur] = n;
    n->heap_idR = cur;
}
