// Semi-vague exercise, so will implement my interpretation: read in program word by word,
// substitute defined constants/words, and print the program back out word by word.
// This will skip comment lines

#include <stdio.h>
#include <stdlib.h>
#include "getword_3.h"

#define MAXWORD 100
#define HASHSIZE 101

struct nlist
{
  struct nlist *next;
  char *name;
  char *defn;
};

int getword(char *, int);

static struct nlist *hashtab[HASHSIZE];
unsigned hash(char *);
struct nlist *install(char *, char *);
struct nlist *lookup(char *);

int getch(void);
void ungetch(int);

int main()
{
  char word[MAXWORD];
  char key[MAXWORD], val[MAXWORD];
  struct nlist *key_val_pair;
  char define[] = "#define";

  while (getword(word, MAXWORD) != EOF)
  {
    if (strcmp(word, define) == 0)
    {
      getword(key, MAXWORD);
      getch(); // Get space between name and definition
      getword(val, MAXWORD);
      getch(); // Skip newline after define statement
      hashtab[hash(word)] = install(key, val);
    }
    else if ((key_val_pair = lookup(word)) != NULL)
    {
      printf("%s", key_val_pair->defn);
    }
    else
    {
      printf("%s", word);
    }
  }
  printf("\n");

  return 0;
}

unsigned hash(char *s)
{
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++)
  {
    hashval = *s + 31 * hashval;
  }
  return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
  struct nlist *np;

  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
  {
    if (strcmp(s, np->name) == 0)
    {
      return np;
    }
  }
  return NULL;
}

struct nlist *install(char *name, char *defn)
{
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL)
  {
    np = (struct nlist *)malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL)
    {
      return NULL;
    }
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  }
  else
  {
    free((void *)np->defn);
  }
  if ((np->defn = strdup(defn)) == NULL)
  {
    return NULL;
  }
  return np;
}