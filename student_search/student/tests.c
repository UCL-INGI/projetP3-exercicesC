#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "student_code.h"
#include "./solutions/student_code_sol.h"
#include "../../course/common/student/CTester/CTester.h"

void free_elem(elem_t *elem){
    if (!elem) return;
    free_elem(elem->left);
    free_elem(elem->right);
    free(elem);
}

void free_tree(tree_t *tree){
    if (!tree) return
    free_elem(tree->head);
    free(tree);
}

void free_node(node_t *node){
    if (!node) return;
    node_t *next = node->next;
    if (malloced(node)) free(node);
    free_node(next);
}

void free_list(list_t *list){
    if (!list) return;
    free_node(list->first);
    free(list);
}

void compare_list(list_t *ret, int *noma, double *grades, int nb){
    CU_ASSERT_NOT_EQUAL(ret, NULL);
    if (ret == NULL) return push_info_msg("You shouldn't return a NULL list");
    node_t *runner = ret->first;
    CU_ASSERT_EQUAL(ret->nbr_of_element, nb);
    if (ret->nbr_of_element != nb) return push_info_msg("You didn't update correctly the size of the list");
    for (size_t i = 0; i < nb; i++)
    {
        CU_ASSERT_NOT_EQUAL(runner, NULL);
        if (!runner) return push_info_msg("Some nodes are missing");
        CU_ASSERT_EQUAL(runner->noma, noma[i]);
        if (runner->noma != noma[i]) return push_info_msg("The nomas aren't in correct order");
        CU_ASSERT_EQUAL(runner->grade, grades[i]);
        if (runner->grade != grades[i]) return push_info_msg("The grades aren't in correct order");
        runner = runner->next;
    }
    if (runner) push_info_msg("Your last node's next should point toward NULL");
    
}

void test1(){
    set_test_metadata("insert", "Test ajout sans élément présent dans l'arbre", 1);

    struct obtree* t1 = (struct obtree*) calloc(1, sizeof(struct obtree));

    SANDBOX_BEGIN;
    insert(t1, 36282000 , "Armand", 12.2);
    SANDBOX_END;

    CU_ASSERT_NOT_EQUAL(t1->head, NULL);

    if(t1->head != NULL){
        CU_ASSERT_EQUAL(t1->head->noma, 36282000);
        if (t1->head->noma != 36282000) push_info_msg("Wrong noma inserted");
        CU_ASSERT_EQUAL(t1->head->name, "Armand");
        if (strcmp(t1->head->name, "Armand") != 0) push_info_msg("Wrong name inserted");
        CU_ASSERT_EQUAL(t1->head->grade, 12.2);
        if (t1->head->grade != 12.2) push_info_msg("Wrong grade inserted");
    }
    free_tree(t1);
}

void test2(){
    set_test_metadata("insert", "Test ajout à un arbre ayant 1 seul élément, avec noma le même", 1);
    struct obtree* t2 = (struct obtree*) calloc(1, sizeof(struct obtree));
    struct element* h2 = (struct element*) calloc(1, sizeof(struct element));
    h2->name = "Bruno";
    h2->noma = 24892000;
    h2->grade = 15.5;
    t2->head = h2;

    SANDBOX_BEGIN;
    insert(t2, 24892000 , "Léon", 13.2);
    SANDBOX_END;

    CU_ASSERT_NOT_EQUAL(t2->head, NULL);
    if (t2->head != NULL){
        CU_ASSERT_EQUAL(t2->head->noma, 24892000);
        CU_ASSERT_EQUAL(t2->head->name, "Léon");
        if (strcmp(t2->head->name, "Léon") != 0) push_info_msg("You have to update the informations");
        CU_ASSERT_EQUAL(t2->head->grade, 13.2);
        if (t2->head->grade != 13.2) push_info_msg("You have to update the informations");
    }
    free_tree(t2);
}

void test3(){
    set_test_metadata("insert", "Test ajout à un arbre ayant 1 seul élément, avec noma plus grand que celui de head", 1);
    struct obtree* t3 = (struct obtree*) calloc(1, sizeof(struct obtree));
    struct element* h3 = (struct element*) calloc(1, sizeof(struct element));
    h3->name = "Bruno";
    h3->noma = 24892000;
    h3->grade = 15.5;
    t3->head = h3;

    SANDBOX_BEGIN;
    insert(t3, 46452000 , "Cédric", 15.6);
    SANDBOX_END;

    CU_ASSERT_NOT_EQUAL(t3->head->right, NULL);
    if (t3->head->right == NULL) return push_info_msg("You have to insert greater nodes on the right side of the tree");
    if (t3->head->right != NULL){
        CU_ASSERT_EQUAL(t3->head->right->noma, 46452000);
        CU_ASSERT_EQUAL(t3->head->right->name, "Cédric");
        CU_ASSERT_EQUAL(t3->head->right->grade, 15.6);
    }
    free_tree(t3);

}

void test4(){
    set_test_metadata("insert", "Test ajout à un arbre ayant 1 seul élément, avec noma plus petit que celui de head", 1);
    struct obtree* t4 = (struct obtree*) calloc(1, sizeof(struct obtree));
    struct element* h4 = (struct element*) calloc(1, sizeof(struct element));
    h4->name = "Bruno";
    h4->noma = 24892000;
    h4->grade = 15.5;
    t4->head = h4;

    SANDBOX_BEGIN;
    insert(t4, 12192000 , "Didier", 11.2);
    SANDBOX_END;

    CU_ASSERT_NOT_EQUAL(t4->head->left, NULL);
    if (t4->head->left == NULL) return push_info_msg("You have to insert smaller nodes on the left side of the tree");
    if (t4->head->left != NULL){
        CU_ASSERT_EQUAL(t4->head->left->noma, 12192000);
        CU_ASSERT_EQUAL(t4->head->left->name, "Didier");
        CU_ASSERT_EQUAL(t4->head->left->grade, 11.2);
    }
    CU_ASSERT_EQUAL(t4->head->right, NULL);
    free_tree(t4);

}

void test5(){
    set_test_metadata("insert", "Test ajout à un arbre ayant plusieurs éléments, avec noma plus petit que tout ceux présents", 1);
    // 
    struct obtree* t5 = (struct obtree*) calloc(1, sizeof(struct obtree));
    struct element* h5 = (struct element*) calloc(1, sizeof(struct element));
    h5->name = "Jean";
    h5->noma = 50002000;
    h5->grade = 14.8;
    t5->head = h5;

    SANDBOX_BEGIN;
    insert(t5, 40002000 , "Paul", 18.8);
    insert(t5, 30002000 , "Marie", 10.2);
    insert(t5, 20002000 , "Chloe", 19.8);
    insert(t5, 10002000 , "Loic", 10.1);
    SANDBOX_END;

    CU_ASSERT_NOT_EQUAL(t5->head->left, NULL);
    if (t5->head->left == NULL){
        return push_info_msg("You didn't insert correctly");
    }
    CU_ASSERT_NOT_EQUAL(t5->head->left->left->left, NULL);
    if (t5->head->left->left->left == NULL){
        return push_info_msg("You didn't insert correctly");
    }
    CU_ASSERT_NOT_EQUAL(t5->head->left->left->left->left, NULL);
    if (t5->head->left->left->left->left != NULL) return push_info_msg("You didn't insert correctly");
    if (t5->head->left->left->left->left != NULL){
        CU_ASSERT_EQUAL(t5->head->left->left->left->left->noma, 10002000);
        CU_ASSERT_EQUAL(t5->head->left->left->left->left->name, "Loic");
        CU_ASSERT_EQUAL(t5->head->left->left->left->left->grade, 10.1);
    }
    CU_ASSERT_EQUAL(t5->head->right, NULL);
    if (t5->head->right != NULL) push_info_msg("Right tree should be NULL");
    free_tree(t5);

}

void test6(){
    set_test_metadata("insert", "Test ajout à un arbre ayant plusieurs éléments, avec noma random", 1);
    struct obtree* t6 = (struct obtree*) calloc(1, sizeof(struct obtree));
    struct element* h6 = (struct element*) calloc(1, sizeof(struct element));
    h6->name = "Jean";
    h6->noma = 50002000;
    h6->grade = 14.8;
    t6->head = h6;
    SANDBOX_BEGIN;
    insert(t6, 45472000 , "Pauline", 17.8);
    insert(t6, 69902000 , "Marine", 13.2);
    insert(t6, 22102000 , "Claire", 14.8);
    insert(t6, 26472000 , "Léa", 17.1);
    insert(t6, 78742000 , "Juliette", 16.5);
    SANDBOX_END;
    CU_ASSERT_NOT_EQUAL(t6->head->left, NULL);
    if (t6->head->left == NULL){
        return push_info_msg("You didn't insert correctly");
    }
    CU_ASSERT_NOT_EQUAL(t6->head->left->left, NULL);
    if (t6->head->left->left == NULL){
        return push_info_msg("You didn't insert correctly");
    }
    CU_ASSERT_NOT_EQUAL(t6->head->left->left->right, NULL);
    if (t6->head->left->left->right == NULL) return push_info_msg("You didn't insert correctly");
    if (t6->head->left->left->right != NULL){
        CU_ASSERT_EQUAL(t6->head->left->left->right->noma, 26472000);
        CU_ASSERT_EQUAL(t6->head->left->left->right->name, "Léa");
        CU_ASSERT_EQUAL(t6->head->left->left->right->grade, 17.1);
    }
    CU_ASSERT_NOT_EQUAL(t6->head->right->right, NULL);
    if (t6->head->right->right == NULL) return push_info_msg("You didn't insert correctly");
    if (t6->head->right->right != NULL) {
        CU_ASSERT_EQUAL(t6->head->right->right->noma, 78742000);
        CU_ASSERT_EQUAL(t6->head->right->right->name, "Juliette");
        CU_ASSERT_EQUAL(t6->head->right->right->grade, 16.5);
    }
    free_tree(t6);
}

void test7(){
    set_test_metadata("convert", "Test convert avec un arbre ne contenant pas d'élément", 1);
    struct obtree* t7 = (struct obtree*) calloc(1, sizeof(struct obtree));
    t7->head = NULL;
    struct linked_list * m = NULL;

    SANDBOX_BEGIN;
    m = convert(t7->head);
    SANDBOX_END;

    CU_ASSERT_NOT_EQUAL(m, NULL);
    if (m == NULL) return push_info_msg("You shouldn't return NULL when the tree is NULL");

    CU_ASSERT_EQUAL(m->first, NULL);
    if (m->first != NULL) push_info_msg("You should set first to NULL when the tree is NULL");
    free_tree(t7);
    free_list(m);
}

void test8(){
    set_test_metadata("convert", "Test convert avec un arbre contenant 1 seul élément", 1);
    struct obtree* t8 = (struct obtree*) calloc(1, sizeof(struct obtree));
    struct element* h8 = (struct element*) calloc(1, sizeof(struct element));
    h8->name = "Jean";
    h8->noma = 50002000;
    h8->grade = 14.8;
    t8->head = h8;
    struct linked_list * m = NULL;

    SANDBOX_BEGIN;
    m = convert(t8->head);
    SANDBOX_END;

    CU_ASSERT_NOT_EQUAL(m, NULL);
    if (m == NULL) return push_info_msg("You shouldn't return NULL when the tree is NULL");

    CU_ASSERT_NOT_EQUAL(m->first, NULL);
    CU_ASSERT_EQUAL(m->nbr_of_element, 1);
    if (m->nbr_of_element != 1) push_info_msg("Don't forget to update the size of the list");
    if (m->first != NULL){
        CU_ASSERT_EQUAL(m->first->noma, 50002000);
        CU_ASSERT_EQUAL(m->first->grade, 14.8);
        CU_ASSERT_EQUAL(m->first->name, "Jean");
        CU_ASSERT_EQUAL(m->first->next, NULL);
    }
    free_list(m);
    free_tree(t8);

}

void test9(){
    set_test_metadata("convert", "Test convert avec un arbre contenant des éléments ajouté avec des noma random", 1);
    struct obtree* t9 = (struct obtree*) calloc(1, sizeof(struct obtree));
    struct element* h9 = (struct element*) calloc(1, sizeof(struct element));
    h9->name = "Jean";
    h9->noma = 50002000;
    h9->grade = 14.8;
    t9->head = h9;

    insert_sol(t9, 45472000 , "Pauline", 17.8);
    insert_sol(t9, 69902000 , "Marine", 13.2);
    insert_sol(t9, 22102000 , "Claire", 14.8);
    insert_sol(t9, 26472000 , "Léa", 17.1);
    insert_sol(t9, 78742000 , "Juliette", 16.5);

    struct linked_list * m = NULL;

    SANDBOX_BEGIN;
    m = convert(t9->head);
    SANDBOX_END;

    int expected_noma[] = {22102000, 26472000, 45472000, 50002000, 69902000, 78742000};
    double expected_grade[] = {14.8, 17.1, 17.8, 14.8, 13.2, 16.5};
    
    compare_list(m, expected_noma, expected_grade, 6);

    free_tree(t9);
    free_list(m);
}

void test10(){
    set_test_metadata("convert", "Test convert avec un arbre contenant des éléments ajouté avec des noma décroissants (l'arbre est fortement déséquilibré)", 1);
    struct obtree* t10 = (struct obtree*) calloc(1, sizeof(struct obtree));
    struct element* h10 = (struct element*) calloc(1, sizeof(struct element));
    h10->name = "Jean";
    h10->noma = 50002000;
    h10->grade = 14.8;
    t10->head = h10;

    insert_sol(t10, 40002000 , "Paul", 18.8);
    insert_sol(t10, 30002000 , "Marie", 10.2);
    insert_sol(t10, 20002000 , "Chloe", 19.8);
    insert_sol(t10, 10002000 , "Loic", 10.1);

    struct linked_list * m = NULL;

    SANDBOX_BEGIN;
    m = convert(t10->head);
    SANDBOX_END;

    int expected_noma[] = {10002000, 20002000, 30002000, 40002000, 50002000};
    double expected_grade[] = {10.1, 19.8, 10.2, 18.8, 14.8};

    compare_list(m, expected_noma, expected_grade, 5);

    free_tree(t10);
    free_list(m);
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1,test2, test3, test4, test5, test6, test7, test8, test9,test10);
}
