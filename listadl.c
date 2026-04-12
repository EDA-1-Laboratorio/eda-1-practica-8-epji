#include "listadl.h"



int main() {
    ListaDL *mi_lista = crear_lista();
    
    insertar_inicio(mi_lista, 10);
    insertar_final(mi_lista, 20);
    insertar_inicio(mi_lista, 5);
    
    printf("Lista Circular: \n");
    imprimir_lista(mi_lista);
    liberar_lista(mi_lista);

    printf("Lista Reversa: \n");
    imprimir_lista_reversa(mi_lista);
    return 0;

}

dllista *crear_elemento(DATO dato) {
    dllista *nuevo = (dllista *)malloc(sizeof(dllista));
    if (nuevo == NULL)
        return NULL;
    nuevo->dato = dato;
    nuevo->previo = NULL;
    nuevo->siguiente = NULL;
    return nuevo;
}

ListaDL *crear_lista(void) {
    ListaDL *lista = (ListaDL *)malloc(sizeof(ListaDL));
    if (lista == NULL)
        return NULL;
    lista->cabeza = NULL;
    lista->longitud = 0;
    return lista;
}

void insertar_inicio(ListaDL *lista, DATO dato) {
    dllista *nuevo = crear_elemento(dato);
    if (nuevo == NULL) return;

    if (lista->cabeza == NULL) {
        lista->cabeza = nuevo;
        nuevo->siguiente = nuevo;
        nuevo->previo = nuevo;
    } else {
        dllista *ultimo = lista->cabeza->previo;
        nuevo->siguiente = lista->cabeza;
        nuevo->previo = ultimo;
        lista->cabeza->previo = nuevo;
        ultimo->siguiente = nuevo;
        lista->cabeza = nuevo;
    }
    lista->longitud++;
}

void insertar_final(ListaDL *lista, DATO dato) {
    if (lista->cabeza == NULL) {
        insertar_inicio(lista, dato);
        return;
    }
    dllista *nuevo = crear_elemento(dato);
    if (nuevo == NULL) return;

    dllista *ultimo = lista->cabeza->previo;
    nuevo->siguiente = lista->cabeza;
    nuevo->previo = ultimo;
    ultimo->siguiente = nuevo;
    lista->cabeza->previo = nuevo;
    lista->longitud++;
}


void insertar_en_posicion(ListaDL *lista, DATO dato, int posicion) {
    if (posicion < 0 || posicion > lista->longitud)
        return;

    if (posicion == 0) {
        insertar_inicio(lista, dato);
        return;
    }
    if (posicion == lista->longitud) {
        insertar_final(lista, dato);
        return;
    }

    dllista *nuevo = crear_elemento(dato);
    if (nuevo == NULL)
        return;

    dllista *actual = lista->cabeza;
    for (int i = 0; i < posicion; i++)
        actual = actual->siguiente;

    nuevo->previo = actual->previo;
    nuevo->siguiente = actual;
    actual->previo->siguiente = nuevo;
    actual->previo = nuevo;
    lista->longitud++;
}

DATO eliminar_inicio(ListaDL *lista) {
    if (lista->cabeza == NULL) return -1;
    dllista *eliminado = lista->cabeza;
    DATO dato = eliminado->dato;

    if (lista->longitud == 1) {
        lista->cabeza = NULL;
    } else {
        dllista *ultimo = lista->cabeza->previo;
        lista->cabeza = lista->cabeza->siguiente;
        lista->cabeza->previo = ultimo;
        ultimo->siguiente = lista->cabeza;
    }
    free(eliminado);
    lista->longitud--;
    return dato;
}

DATO eliminar_final(ListaDL *lista) {
    if (lista->cabeza == NULL) return -1;
    if (lista->longitud == 1) return eliminar_inicio(lista);

    dllista *ultimo = lista->cabeza->previo;
    DATO dato = ultimo->dato;
    dllista *penultimo = ultimo->previo;

    penultimo->siguiente = lista->cabeza;
    lista->cabeza->previo = penultimo;

    free(ultimo);
    lista->longitud--;
    return dato;
}

DATO eliminar_en_posicion(ListaDL *lista, int posicion) {
    if (posicion < 0 || posicion >= lista->longitud)
        return -1;

    if (posicion == 0)
        return eliminar_inicio(lista);
    if (posicion == lista->longitud - 1)
        return eliminar_final(lista);

    dllista *actual = lista->cabeza;
    for (int i = 0; i < posicion; i++)
        actual = actual->siguiente;

    DATO dato = actual->dato;
    actual->previo->siguiente = actual->siguiente;
    actual->siguiente->previo = actual->previo;
    free(actual);
    lista->longitud--;
    return dato;
}


DATO obtener(ListaDL *lista, int posicion) {
    if (posicion < 0 || posicion >= lista->longitud)
        return -1;

    dllista *actual = lista->cabeza;
    for (int i = 0; i < posicion; i++)
        actual = actual->siguiente;
    return actual->dato;
}

int esta_vacia(ListaDL *lista) {
    return lista->cabeza == NULL;
}

int longitud(ListaDL *lista) {
    return lista->longitud;
}

void imprimir_lista(ListaDL *lista) {
    if (lista->cabeza == NULL) {
        printf("lista vacia\n");
        return;
    }
    dllista *actual = lista->cabeza;
    do {
        printf("[%d]", actual->dato);
        if (actual->siguiente != lista->cabeza) printf(" <-> ");
        actual = actual->siguiente;
    } while (actual != lista->cabeza);
    printf(" <-> (Cabeza)\n");
}

int buscar(ListaDL *lista, DATO dato) {
    if (lista->cabeza == NULL) return -1;
    dllista *actual = lista->cabeza;
    int pos = 0;
    do {
        if (actual->dato == dato) return pos;
        actual = actual->siguiente;
        pos++;
    } while (actual != lista->cabeza);
    return -1;
}

void imprimir_lista_reversa(ListaDL *lista) {
    if (lista->cabeza == NULL) {
        printf("lista vacia\n");
        return;
    }

    // En circular, el anterior a la cabeza es el ÚLTIMO nodo
    dllista *actual = lista->cabeza->previo; 
    int i = 0;

    printf("Lista Reversa: ");
    while (i < lista->longitud) {
        printf("[%d]", actual->dato);
        
        if (i < lista->longitud - 1) {
            printf(" <-> ");
        }
        
        // Caminamos hacia atrás
        actual = actual->previo;
        i++;
    }
    printf(" <-> (Atras)\n");
}

void liberar_lista(ListaDL *lista) {
    if (lista->cabeza != NULL) {
        dllista *actual = lista->cabeza;
        int total = lista->longitud;
        for (int i = 0; i < total; i++) {
            dllista *sig = actual->siguiente;
            free(actual);
            actual = sig;
        }
    }
    free(lista);
}
