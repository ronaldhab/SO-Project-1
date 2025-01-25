#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t pila_hash_mutex;
sem_t visitados_mutex;
sem_t coord_hash;
sem_t compara_coord;

void inicializar_semaforos(){
    sem_init(&coord_hash, 0, 0);
    sem_init(&compara_coord, 0, 0);
    sem_init(&pila_hash_mutex, 0, 1);
    sem_init(&visitados_mutex, 0, 1);
}

void test_inicializar_semaforos(void) {
    inicializar_semaforos();
    int value;
    sem_getvalue(&coord_hash, &value);
    CU_ASSERT_EQUAL(value, 0);
    sem_getvalue(&pila_hash_mutex, &value);
    CU_ASSERT_EQUAL(value, 1);
    sem_destroy(&coord_hash);
    sem_destroy(&compara_coord);
    sem_destroy(&pila_hash_mutex);
    sem_destroy(&visitados_mutex);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Semaforos Suite", 0, 0);
    CU_add_test(suite, "test_inicializar_semaforos", test_inicializar_semaforos);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}