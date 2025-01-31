#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include "../estructuras.h"
#include "../operaciones_estructuras.h"
#include "../obtener_hashes.h"

void test_esta_contenido () {
    push("test1_file");

    // Casos validos
    CU_ASSERT(esta_contenido("test1_file") == 1);
    CU_ASSERT(esta_contenido("test2_file") == 0);

    // Caso invalido
    CU_ASSERT(esta_contenido("test2_file") == 1);
}

void test_push () {
    push("test3_file");
    CU_ASSERT_STRING_EQUAL(tope_pila->nombre_archivo, "test3_file");
    liberar_pila();
}

void test_pop () {
    push("test4_file");
    pop();
    CU_ASSERT_PTR_NULL(tope_pila);
}

void test_insertar_visitados() {
    insertar_visitados("test5_file", "test_hash");
    CU_ASSERT_STRING_EQUAL(cabeza->nombre_archivo, "test5_file");
    CU_ASSERT_STRING_EQUAL(cabeza->valor_hash, "test_hash");
    liberar_lista();
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Operaciones Estructuras", 0, 0);
    CU_add_test(suite, "test_pop", test_pop);
    CU_add_test(suite, "test_esta_contenido", test_esta_contenido);
    CU_add_test(suite, "test_insertar_visitados", test_insertar_visitados);
    CU_add_test(suite, "test_push", test_push);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}