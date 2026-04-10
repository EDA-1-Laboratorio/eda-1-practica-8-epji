#include "listadl.h"

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
    if (nuevo == NULL)
        return;

    if (lista->cabeza == NULL) {
        nuevo -> siguiente = nuevo;
        nuevo -> previo = nuevo;
        lista->cabeza = nuevo;
    } else {
        dllista *ultimo = lista -> cabeza -> previo;
        nuevo->siguiente = lista->cabeza;
        nuevo -> previo = ultimo;
        lista->cabeza->previo = nuevo;
        ultimo -> siguiente = nuevo;
        lista->cabeza = nuevo;
    }
    lista->longitud++;
}

void insertar_final(ListaDL *lista, DATO dato) {
    dllista *nuevo = crear_elemento(dato);
    if (nuevo == NULL)
        return;

    if (lista->cabeza == NULL) {
        lista->cabeza = nuevo;
    } else {
        dllista *actual = lista->cabeza;
        while (actual->siguiente != NULL)
            actual = actual->siguiente;
        actual->siguiente = nuevo;
        nuevo->previo = actual;
    }
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
    if (lista->cabeza == NULL)
        return -1;

    dllista *eliminado = lista->cabeza;
    DATO dato = eliminado->dato;

    if (lista->cabeza->siguiente == NULL) {
        lista->cabeza = NULL;
    } else {
        lista->cabeza = lista->cabeza->siguiente;
        lista->cabeza->previo = NULL;
    }

    free(eliminado);
    lista->longitud--;
    return dato;
}

DATO eliminar_final(ListaDL *lista) {
    if (lista->cabeza == NULL)
        return -1;

    dllista *actual = lista->cabeza;
    while (actual->siguiente != NULL)
        actual = actual->siguiente;

    DATO dato = actual->dato;

    if (actual->previo == NULL) {
        lista->cabeza = NULL;
    } else {
        actual->previo->siguiente = NULL;
    }

    free(actual);
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

int buscar(ListaDL *lista, DATO dato) {
    dllista *actual = lista->cabeza;
    int posicion = 0;
    while (actual != NULL) {
        if (actual->dato == dato)
            return posicion;
        actual = actual->siguiente;
        posicion++;
    }
    return -1;
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
    if(lista->cabeza == NULL){
        printf("lista vacia\n");
        return;
    }
    dllista *actual = lista->cabeza; 
        
    while (actual != NULL) {
        printf("[%d]", actual->dato);
        if (actual->siguiente != NULL)
            printf(" <-> ");
        actual = actual->siguiente;
    }
    printf(" -> NULL\n");
}

void imprimir_lista_reversa(ListaDL *lista) {
    dllista *actual = lista->cabeza;
    if (actual == NULL) {
        printf(" -> NULL\n");
        return;
    }
    while (actual->siguiente != NULL)
        actual = actual->siguiente;
    while (actual != NULL) {
        printf("[%d]", actual->dato);
        if (actual->previo != NULL)
            printf(" <-> ");
        actual = actual->previo;
    }
    printf(" -> NULL\n");
}

void liberar_lista(ListaDL *lista) {
    dllista *actual = lista->cabeza;
    while (actual != NULL) {
        dllista *siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    free(lista);
}
