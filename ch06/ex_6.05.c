#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

struct nlist
{
  struct nlist *next;
  char *name;
  char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *);
struct nlist *install(char *, char *);
struct nlist *lookup(char *);
int undef(char *);

int main()
{
  // Trivial (hardcoded) check for program correctness
  install("foo", "bar");
  install("a", "b");
  install("check", "mate");

  char *search_term = malloc(sizeof(char) * 100);
  strcpy(search_term, "foo");
  unsigned hash_val = hash(search_term);
  struct nlist *instance = lookup(search_term);
  printf("%u | %s: %s\n", hash_val, instance->name, instance->defn);

  undef(search_term);

  instance = lookup(search_term);
  if (instance != NULL) {
    printf("Unfortunately the deletion didn't work..\n");
    printf("%u | %s: %s\n", hash_val, instance->name, instance->defn);
  } else {
    printf("IT WORKED.. 'foo' and its definition were removed\n");

    strcpy(search_term, "a");
    instance = lookup(search_term);
    hash_val = hash(search_term);
    printf("%u | %s: %s\n", hash_val, instance->name, instance->defn);

    strcpy(search_term, "check");
    instance = lookup(search_term);
    hash_val = hash(search_term);
    printf("%u | %s: %s\n", hash_val, instance->name, instance->defn);
  }
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

int undef(char *name)
{
  unsigned hashed_val = hash(name);
  struct nlist *current_struct = hashtab[hashed_val];

  if (current_struct == NULL)
  {
    return 1;
  }
  else
  {
    if (strcmp(name, current_struct->name) == 0)
    {
      if (current_struct->next == NULL)
      {
        hashtab[hashed_val] = NULL;
      }
      else
      {
        hashtab[hashed_val] = current_struct->next;
      }
      return 1;
    }

    struct nlist *previous_struct;
    while (current_struct->next != NULL)
    {
      previous_struct = current_struct;
      current_struct = current_struct->next;
      if (strcmp(name, current_struct->name) == 0)
      {
        if (current_struct->next == NULL)
        {
          previous_struct->next = NULL;
        }
        else
        {
          previous_struct->next = current_struct->next;
        }
        return 1;
      }
    }
    return 1;
  }
  return 0;
}