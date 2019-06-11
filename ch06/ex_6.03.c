// Haven't removed noise words (if I was to do so, I'd check each
// word wasn't in a given array of words before printing it)
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "getword_2.h"

#define MAXWORD 100
#define MAXLINES 50

struct tnode
{
  char *word;
  int count;
  int lines[MAXLINES];
  struct tnode *left;
  struct tnode *right;
};

int getword_2(char *, int, int *);
struct tnode *addtree(struct tnode *, char *, int linenum);
void treeprint(struct tnode *);

int main(int argc, char *argv[])
{
  struct tnode *root;
  char word[MAXWORD];
  // printf("");
  int *linenum = malloc(sizeof(*linenum));
  *linenum = 0;

  root = NULL;
  while (getword_2(word, MAXWORD, linenum) != EOF)
  {
    if (isalpha(word[0]))
    {
      root = addtree(root, word, *linenum);
    }
  }
  treeprint(root);

  return 0;
}

struct tnode *talloc(void);
char *my_strdup(char *);

struct tnode *addtree(struct tnode *p, char *w, int linenum)
{
  int cond;

  if (p == NULL)
  {
    p = talloc();
    p->word = my_strdup(w);
    p->count = 1;
    p->lines[p->count - 1] = linenum;
    p->left = p->right = NULL;
  }
  else if ((cond = strcmp(w, p->word)) == 0)
  {
    p->count++;
    p->lines[p->count - 1] = linenum;
  }
  else if (cond < 0)
  {
    p->left = addtree(p->left, w, linenum);
  }
  else
  {
    p->right = addtree(p->right, w, linenum);
  }

  return p;
}

void treeprint(struct tnode *p)
{
  if (p != NULL)
  {
    treeprint(p->left);
    printf("COUNT: %4d | WORD: %20s | LINES: ", p->count, p->word);
    for (int i = 0; i < p->count; i++)
    {
      if (i == 0)
      {
        printf("%4d", p->lines[i]);
      }
      else if (p->lines[i] != p->lines[i - 1])
      {
        printf("%4d", p->lines[i]);
      }
    }
    printf("\n");
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