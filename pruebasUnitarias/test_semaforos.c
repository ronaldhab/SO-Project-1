#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../semaforos.h"

void test_inicializar_semaforos(void) {
    inicializar_semaforos();
    int value;

    sem_getvalue(&coord_hash, &value);
    CU_ASSERT_EQUAL(value, 0);

    sem_getvalue(&hash_mutex, &value);
    CU_ASSERT_EQUAL(value, 1);

    sem_getvalue(&compara_coord, &value);
    CU_ASSERT_EQUAL(value, 0);


    sem_destroy(&coord_hash);
    sem_destroy(&hash_mutex);
    sem_destroy(&compara_coord);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Semaforos Suite", 0, 0);
    CU_add_test(suite, "test_inicializar_semaforos", test_inicializar_semaforos);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}