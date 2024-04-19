#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
  int isWord;
  struct Trie* next[26];
};

// Initializes a trie structure
struct Trie *createTrie()
{
  struct Trie* myTree = malloc(sizeof(struct Trie));
  myTree->isWord = 0;
  int i;
  for (i=0; i<26; i++)
    myTree->next[i] = NULL;
  return myTree;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
  struct Trie *current = pTrie;
  for (int i = 0; i < strlen(word); i++) {
    int index = word[i] - 'a';
    if (!current->next[index])
      current->next[index] = createTrie();
    current = current->next[index];
  }
  current->isWord = 1;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
  struct Trie *current = pTrie;
  for (int i = 0; i < strlen(word); i++) {
    int index = word[i] - 'a';
    if (!current->next[index])
      return 0;
    current = current->next[index];
  }
  return current != NULL && current->isWord ? 1 : 0;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
  for (int i = 0; i < 26; i++)
    if (pTrie->next[i])
      deallocateTrie(pTrie->next[i]);
  return NULL;
}


// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
  FILE *file = fopen(filename, "r");
  int numWords = 0;
  char word[100];
  while (fscanf(file, "%s", word) != EOF) {
      pInWords[numWords] = strdup(word);
      numWords++;
  }

  fclose(file);
  return numWords;
}

int main(void)
{
  char *inWords[256];

  //read the number of the words in the dictionary
  int numWords = readDictionary("dictionary.txt", inWords);
  for (int i=0;i<numWords;++i)
  {
    printf("%s\n",inWords[i]);
  }

  struct Trie *pTrie = createTrie();
  for (int i=0;i<numWords;i++)
  {
    insert(pTrie, inWords[i]);
  }
  // parse lineby line, and insert each word to the trie data structure
  char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
  for (int i=0;i<5;i++)
  {
    printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
  }
  pTrie = deallocateTrie(pTrie);
  if (pTrie != NULL)
    printf("There is an error in this program\n");
  return 0;
}