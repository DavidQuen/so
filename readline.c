#include <stdio.h>
#include <stdlib.h>
#include <commons/txt.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

// Lista de comandos disponibles
const char *comandos[] = {
    "exit", "help", "clear", "listar", "abrir", "guardar", "borrar", NULL
};

// Función generadora de palabras para autocompletado
char *generar_completado(const char *texto, int estado) {
    static int indice, longitud;
    
    if (estado == 0) { // Primera vez que se llama, inicializar variables
        indice = 0;
        longitud = strlen(texto);
    }

    while (comandos[indice]) {
        if (strncmp(comandos[indice], texto, longitud) == 0) {
            return strdup(comandos[indice++]);
        }
        indice++;
    }

    return NULL; // No hay más coincidencias
}

// Función para integrar autocompletado en Readline
char **completar_texto(const char *texto, int inicio, int fin) {
    return rl_completion_matches(texto, generar_completado);
}

// Inicialización de Readline con autocompletado
void inicializar_readline() {
    rl_attempted_completion_function = completar_texto;
}

int main(int argc, char* argv[]) {
    txt_write_in_stdout("Hola, Operativos!!\n");

    inicializar_readline(); // Activamos el autocompletado

    char *linea;
    while (1) {
        linea = readline(">> ");

        if (linea) {
            add_history(linea);
        }
        if (!strncmp(linea, "exit", 4)) {
            free(linea);
            break;
        }

        printf("%s\n", linea);
        free(linea);
    }

    return 0;
}
