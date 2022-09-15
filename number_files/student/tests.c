#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <dlfcn.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "student_code.h"
#include "../../course/common/student/CTester/CTester.h"

DIR *(*previous)(const char *path) = NULL;

typedef struct fail_count{
    int count;
    int activated;
    int nb;
}fail_t;

fail_t fail;

void set_fail(int count){
    fail.nb = 0;
    fail.activated = 1;
    fail.count = count;
}

DIR *opendir(const char *path){
    if (!previous){
        previous = dlsym(RTLD_NEXT, "opendir");
    }

    if (fail.activated){
        fail.nb++;
        if (fail.nb == fail.count) return NULL;
    }
    return previous(path);
}

void error(int nb, int exp){
    char *template = "Your code doesn't work correctly. The expected result was %d, but you returned %d";
    char msg[strlen(template)];
    sprintf(msg, template, exp, nb);
    push_info_msg(msg);
}

void test1(){

    set_test_metadata("number_files", "Test Documents folder", 1);

    // test de base minimaliste

    int res;
    SANDBOX_BEGIN;
    res = get_number_of_files("./Home/Documents");
    SANDBOX_END;

    CU_ASSERT_EQUAL(3,res);
    if (res != 3) error(res, 3);
}
    
void test2(){

    set_test_metadata("number_files", "Test Downloads folder", 1);

    int res;
    SANDBOX_BEGIN;
    res = get_number_of_files("./Home/Downloads");
    SANDBOX_END;
    CU_ASSERT_EQUAL(2,res);
    if (res != 2) error(res, 2);
}

void test3(){

    set_test_metadata("number_files", "Test y folder", 1);

    int res;
    SANDBOX_BEGIN;
    res = get_number_of_files("./Home/Downloads/y");
    SANDBOX_END;
    CU_ASSERT_EQUAL(1,res);
    if (res != 1) error(res, 1);
}

void test4(){

    set_test_metadata("number_files", "Test for Home folder", 1);
    int res;
    SANDBOX_BEGIN;
    res = get_number_of_files("./Home");
    SANDBOX_END;
    CU_ASSERT_EQUAL(5,res);
    if (res != 4) error(res, 5);
    
}

void test5(){

    set_test_metadata("number_files", "Test with unexisting path", 1);

    int res;

    SANDBOX_BEGIN;
    res = get_number_of_files("./Test");
    SANDBOX_END;
    CU_ASSERT_EQUAL(res,-1);
    if (res != -1) push_info_msg("You should return -1 when path doesn't exists (When stat fails)");
    
}

void test6(){
    set_test_metadata("number_files", "Test with failed opendir", 1);

    set_fail(1);

    int res;

    SANDBOX_BEGIN;
    res = get_number_of_files("./Home");
    SANDBOX_END;

    CU_ASSERT_EQUAL(res,-2);
    if (res != -2) push_info_msg("You should return -2 when opendir fails");
}

void test7(){
    set_test_metadata("number_files", "Test with failed opendir when 2 first opendir succeeded", 1);

    set_fail(3);

    int res;

    SANDBOX_BEGIN;
    res = get_number_of_files("./Home");
    SANDBOX_END;

    CU_ASSERT_EQUAL(res,-2);
    if (res != -2) push_info_msg("You should return -2 when opendir fails");
}

void test8(){
    set_test_metadata("number_files", "Test with empty folder", 1);

    int res;

    SANDBOX_BEGIN;
    res = get_number_of_files("./Empty");
    SANDBOX_END;

    CU_ASSERT_EQUAL(res,0);
    if (res != 0) error(res, 0);
}

int main(int argc,char** argv)
{
    BAN_FUNCS();
    RUN(test1, test2, test3, test4, test5, test6, test7, test8);
}
