#include <stdlib.h>
#include <stdio.h>
#include "student_code_sol.h"

struct obtree* insert_sol(struct obtree *tree, int noma, char* name, double grade) {

    struct element *current = tree->head;
    struct element *current1l;
    struct element *current1r;

    while (current != NULL){
        current1l = NULL;
        current1r = NULL;
        if (current->noma == noma) {       // si jamais le noma est déjà présent dans l'arbre, remplacer les anciennes données
            current->name = name;          // de l étudiant par les nouvelles données passées en arguments
            current->grade = grade;
            return tree;
        }
        else {
            if (current->noma < noma) {
                current1r = current;
                current = current->right;
            } else {
                current1l = current;
                current = current->left;
            }
        }
    }
    struct element *to_add = (struct element *) malloc(sizeof(struct element));
    if (to_add == NULL){
        return NULL;
    }
    to_add->noma = noma;
    to_add->name = name;
    to_add->left = NULL;
    to_add->right = NULL;
    to_add->grade = grade;

    if (current1l == NULL && current1r != NULL){
        current1r->right = to_add;
        current1r = NULL;
        return tree;
    }
    if (current1r == NULL && current1l != NULL) {
        current1l->left = to_add;
        current1l = NULL;
        return tree;
    }
    if (tree->head == NULL) {
        tree->head = to_add;
        return tree;
    }
    return NULL;
}


void push_sol(node_t **node, int noma, char *name, double grade){
    node_t *ret = malloc(sizeof(node_t));
    ret->next = *node;
    ret->noma = noma;
    ret->name = name;
    ret->grade = grade;
    *node = ret;
}

node_t *convert_help_sol(elem_t *head, node_t **acc, int *count){
    if (!head) return NULL;
    convert_help_sol(head->right, acc, count);
    push_sol(acc, head->noma, head->name, head->grade);
    (*count)++;
    convert_help_sol(head->left, acc, count);
    return *acc;
}



/*
 *@pre n!=NULL
 *@post retourne la liste chainée n contenant tous les éléments présent dans l'arbre passé en argument, dont les étudiants sont triés par
        ordre croissant suivant leur noma
 */

list_t *convert_sol(elem_t * head){
    list_t *ret = malloc(sizeof(list_t));
    node_t *acc[1] = {NULL};
    ret->first = convert_help_sol(head, acc, &ret->nbr_of_element);
    return ret;
}



