// Assume variable names start with an alphabet character
// Counting words in strings, but not in comments
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "getword.h"

#define MAXWORD 100

struct tnode
{
  char *word;
  int count;
  int new_group;
  struct tnode *left;
  struct tnode *right;
};

char current_group_prefix[MAXWORD];
int required_len = 6;
int getword(char *, int);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);

int main(int argc, char *argv[])
{
  if (argc > 1)
  {
    while (--argc > 0)
    {
      if (strcmp(*(++argv), "-l"))
      {
        required_len = atoi(*argv);
      }
    }
  }

  struct tnode *root;
  char word[MAXWORD];

  root = NULL;
  while (getword(word, MAXWORD) != EOF)
  {
    if (isalpha(word[0]) && strlen(word) >= required_len)
    {
      root = addtree(root, word);
    }
  }
  treeprint(root);

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
    p->new_group = 0;
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

char *get_str_prefix(char *);

void treeprint(struct tnode *p)
{
  if (p != NULL)
  {
    treeprint(p->left);
    if (strlen(p->word) >= required_len)
    {
      if ((strncmp(p->word, current_group_prefix, required_len) != 0))
      {
        strcpy(current_group_prefix, get_str_prefix(my_strdup(p->word)));
        printf("\nGROUP BEGINNING WITH '%s'\n", current_group_prefix);
      }
      printf("%4d %s\n", p->count, p->word);
    }
    treeprint(p->right);
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

char *get_str_prefix(char *original)
{
  char *trimmed;
  trimmed = (char *)malloc(strlen(original) + 1);
  int counter = 0;
  while (counter < required_len)
  {
    trimmed[counter++] = *original++;
  }

  return trimmed;
}