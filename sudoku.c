#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){

  int arr[10];
    // verificar filas
    for (int j = 0; j < 9; j++){
        for (int i = 0; i < 10; i++) arr[i] = 0;
        for (int k = 0; k < 9; k++){
            int val = n->sudo[j][k];
            if (val != 0){
                if (arr[val]) return 0;
                arr[val] = 1;
            }
        }
    }

    // verificar columnas
    for (int k = 0; k < 9; k++){
        for (int i = 0; i < 10; i++) arr[i] = 0;
        for (int j = 0; j < 9; j++){
            int val = n->sudo[j][k];
            if (val != 0){
                if (arr[val]) return 0;
                arr[val] = 1;
            }
        }
    }

    // verificar submatrices 3x3
    for (int k = 0; k < 9; k++){
        for (int i = 0; i < 10; i++) arr[i] = 0;
        for (int p = 0; p < 9; p++){
            int fila = 3*(k/3) + (p/3);
            int col  = 3*(k%3) + (p%3);
            int val = n->sudo[fila][col];
            if (val != 0){
                if (arr[val]) return 0;
                arr[val] = 1;
            }
        }
    }

    return 1;
}




List* get_adj_nodes(Node* n){
    List* lista_adj =createList();
    int j,k;
    for (j = 0; j < 9; j++){
        for (k = 0; k < 9; k++){
            if (n->sudo[j][k] == 0){
                
              //intentar con numeros del 1 al 9
              for (int i = 1; i <= 9; i++){
                    Node* new = copy(n);
                    new->sudo[j][k] = i;
                    if (is_valid(new)){
                        //printf("valid\n");
                    pushBack(lista_adj, new);}
                    
                }
                return lista_adj;
            }
        }
    }
    return lista_adj;
  }
    


int is_final(Node* n){
    for (int j = 0; j < 9; j++){
        for (int k = 0; k < 9; k++){
            if (n->sudo[j][k] == 0){
                return 0;
            }
        }
    }
    return 1;

    
  
   return 0;
}

Node* DFS(Node* initial, int* cont){
  
  Stack* stack = createStack();
  push(stack, initial);

  while (top(stack) != NULL){
    Node* n = top(stack);
    pop(stack);
    (*cont)++;
    
    if (is_final(n)){
        return n;
    }
    
    List* adj = get_adj_nodes(n);
    Node* aux = first(adj);
    
    
    push(stack, aux);
    aux = next(adj);
    
    
    clean(adj);
  }
  
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/