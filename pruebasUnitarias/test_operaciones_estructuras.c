#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#define _DEFAULT_SOURCE
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include "../estructuras.h"
#include "../operaciones_estructuras.h"
#include "../obtener_hashes.h"

void test_push(void) {
    push("test_file");
    CU_ASSERT_STRING_EQUAL(tope_pila->nombre_archivo, "test_file");
    liberar_pila();
}

void test_pop(void) {
    push("test_file");
    pop();
    CU_ASSERT_PTR_NULL(tope_pila);
}

void test_insertar_visitados(void) {
    insertar_visitados("test_file", "test_hash");
    CU_ASSERT_STRING_EQUAL(cabeza->nombre_archivo, "test_file");
    CU_ASSERT_STRING_EQUAL(cabeza->valor_hash, "test_hash");
    liberar_lista();
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Operaciones Estructuras Suite", 0, 0);
    CU_add_test(suite, "test_push", test_push);
    CU_add_test(suite, "test_pop", test_pop);
    CU_add_test(suite, "test_insertar_visitados", test_insertar_visitados);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}