#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int n;
    int degree;
    struct node *parent;
    struct node *child;
    struct node *sibling;
};

struct node *MAKE_bin_HEAP();
int bin_LINK(struct node *, struct node *);
struct node *CREATE_NODE(int);
struct node *bin_HEAP_UNION(struct node *, struct node *);
struct node *bin_HEAP_INSERT(struct node *, struct node *);
struct node *bin_HEAP_MERGE(struct node *, struct node *);
struct node *bin_HEAP_EXTRACT_MIN(struct node *);
int REVERT_LIST(struct node *);
int DISPLAY(struct node *);
struct node *FIND_NODE(struct node *, int);
int bin_HEAP_DECREASE_KEY(struct node *, int, int);
int bin_HEAP_DELETE(struct node *, int);

#endif