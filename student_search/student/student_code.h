#ifndef S_CODE_H
#define S_CODE_H
//structures données dans l'énoncé
typedef struct element {
    struct element* left;
    struct element* right;
    int noma;
    char* name;
    double grade;
}elem_t;

typedef struct obtree{
    struct element* head;
}tree_t;

typedef struct linked_node{
    struct linked_node* next;
    int noma;
    char* name;
    double grade;
}node_t ;

typedef struct linked_list{
    struct linked_node* first;
    int nbr_of_element;
}list_t ;



struct obtree* insert(struct obtree *tree, int noma, char* name, double grade);


/*
 *@pre n!=NULL
 *@post retourne la liste chainée n contenant tous les éléments présent dans l'arbre passé en argument, dont les étudiants sont triés par
        ordre croissant suivant leur noma
 */

struct linked_list *convert(struct element * head);
#endif