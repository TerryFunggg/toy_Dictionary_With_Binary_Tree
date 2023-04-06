#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dict {
  struct dict *left, *right;
  char word[10];
  char meaning[20];
} *Root = NULL;

typedef struct dict dictionary;

void search();
void insert(dictionary *temp);
void view(dictionary *ptr);
int check(char[], char[]);

int check(char a[], char b[]) {
  /* implement own string compare
  int i,j,c;
  // '\0' is the ASCII code represented end of a string
  for (i = 0,j = 0; a[i] != '\0' && b[j] != '\0'; i++, j++)
  {
      if(a[i] > b[j])
      {
          c = 1;
          break;
      }
      else if(a[i] < b[j])
      {
          c -= 1;
          break;
      }
      else
      {
          c = 0;
      }
  }

  if(c == 1) return 1;
  else if (c == -1) return -1;

  return 0;
  */
  return strcmp(a, b);
}

void search() {
  char w[10];
  int flag = 0;
  dictionary *ptr = Root;
  printf("\nEnter the word:\n");
  scanf("%s", w);

  while (ptr != NULL && flag == 0) {
    if (check(w, ptr->word) == 1) {
      ptr = ptr->right;
    } else if (check(w, ptr->word) == -1) {
      ptr = ptr->left;
    } else {
      flag = 1;
      printf("\n Meaning: %s\n", ptr->meaning);
      break;
    }
  }

  if (flag == 0 && ptr == NULL) {
    printf("\n%s not found..\n", w);
  }
}

void insert(dictionary *temp) {
  int flag = 0;
  dictionary *par;
  dictionary *ptr = Root;

  if (Root == NULL) {
      Root = temp;
  } else {

    while (ptr != NULL && flag == 0) {

      if (check(temp->word, ptr->word) == 1) {
        par = ptr;
        ptr = ptr->right;

      } else if (check(temp->word, ptr->word) == -1) {
        par = ptr;
        ptr = ptr->left;

      } else {
        flag = 1;
        printf("\n Word exists!!\n");
        break;
      }
    }

    if(flag ==0){
        if(check(par->word, temp->word) == 1){
            par->left = temp;
        } else if(check(par->word, temp->word) == -1) {
            par->right = temp;
        }
        return;
    }
  }
}

void view(dictionary *ptr) {
    if(ptr == NULL) {
        printf("\nEmpty Dictonary\n");
    } else {
        if(ptr != NULL) {
            view(ptr->left);
            printf("\nWord: %s", ptr->word);
            printf("\nWord: %s", ptr->meaning);
            view(ptr->right);
        }
    }
}

int main(int argc, char const *argv[]) {
  int ch;
  dictionary *temp;


  while (ch != 4) {
    printf("\n1.Search\n2.Insert\n3.View\n4.Quit\n -> ");
    // vaildate input
    int result = scanf("%d", &ch);

    if(result != 1)
    {
        while (getchar() != '\n');
        ch = 5;
    }

    switch (ch) {
    case 1:
      search();
      break;
    case 2:
      temp = (dictionary *)malloc(sizeof(dictionary));
      temp->left = NULL;
      temp->right = NULL;
      printf("\nInsert Word:");
      scanf("%s", temp->word);
      printf("\nInsert Meaning:");
      scanf("%s", temp->meaning);

      insert(temp);
      break;
    case 3:
      view(Root);
      break;
    case 4:
      exit(0);
    }
  }

  return 0;
}
