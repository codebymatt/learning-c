#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "getword.h"

#define MAXWORD 100
#define MAXLINES 50
#define MAX_NUM_WORDS 1000

struct tnode
{
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

int getword(char *, int);
int treesize = 0;
struct tnode *addtree(struct tnode *, char *);
int compare_node_count(const void *, const void *);
void flatten_tree(struct tnode *, struct tnode *[]);

int main(int argc, char *argv[])
{
  struct tnode *root;
  char word[MAXWORD];

  root = NULL;
  while (getword(word, MAXWORD) != EOF)
  {
    if (isalpha(word[0]))
    {
      root = addtree(root, word);
    }
  }

  struct tnode *node_array[MAX_NUM_WORDS];
  flatten_tree(root, node_array);
  qsort(node_array, treesize, sizeof(struct tnode *), compare_node_count);
  for (int i = 0; i < treesize; i++) {
    struct tnode *node = node_array[i];
    printf("%4d %s\n", node->count, node->word);
  }
  return 0;
}

struct tnode *talloc(void);
char *my_strdup(char *);

struct tnode *addtree(struct tnode *p, char *w)
{
  int cond;

  if (p == NULL)
  {
    p = talloc();
    p->word = my_strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  }
  else if ((cond = strcmp(w, p->word)) == 0)
  {
    p->count++;
  }
  else if (cond < 0)
  {
    p->left = addtree(p->left, w);
  }
  else
  {
    p->right = addtree(p->right, w);
  }

  return p;
}

void flatten_tree(struct tnode *p, struct tnode *node_array[])
{
  if (p != NULL)
  {
    flatten_tree(p->left, node_array);
    node_array[treesize++] = p;
    flatten_tree(p->right, node_array);
  }
}

struct tnode *talloc(void)
{
  return (struct tnode *)malloc(sizeof(struct tnode));
}

char *my_strdup(char *s)
{
  char *p;

  p = (char *)malloc(strlen(s) + 1);
  if (p != NULL)
  {
    strcpy(p, s);
  }
  return p;
}

int compare_node_count(const void *n1, const void *n2)
{
  // Got tripped up below: *n1, *n2 are POINTERS TO THE ARRAY ELEMENTS I'm comparing,
  // not the actual elements.
  struct tnode *node_1 = *(struct tnode **)n1;
  struct tnode *node_2 = *(struct tnode **)n2;
  int count_1 = node_1->count, count_2 = node_2->count;

  return (count_2 - count_1);
}