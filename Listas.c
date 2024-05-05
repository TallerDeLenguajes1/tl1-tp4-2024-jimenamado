#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAMA 100

/*------------------TP4-  REALIZADO SIN INTERFAZ DE USUARIO ----------------------------------*/

char *descripcion[] = {"comprar Mercaderia", "cerrar caja", "llenar tanque", "pagar alquiler"};
int duracion[] = {10, 20, 30, 40};
int id = 1000;

struct
{
    int tareaID; // Numérico autoincremental comenzando en 1000
    char *Descripcion;
    int duracion; // entre 10 – 100

} typedef Tarea;

struct Nodo
{
    Tarea T;
    struct Nodo *siguiente;

} typedef Nodo;

Tarea cargarTareaPendiente(int id)
{

    Tarea nuevaTarea;
    nuevaTarea.tareaID = id;

    int indice = rand() % 4;
    nuevaTarea.Descripcion = descripcion[indice];

    int indice2 = rand() % 4;
    nuevaTarea.duracion = duracion[indice2];

    return nuevaTarea;
}

Nodo *crearNodo(Tarea tarea)
{

    Nodo *nuevoNodo;
    nuevoNodo = malloc(sizeof(Nodo));

    nuevoNodo->T = tarea;
    nuevoNodo->siguiente = NULL;

    return nuevoNodo;
}

Nodo *crearListaVacia()
{

    return (NULL);
}

void insertarNodoEnLista(Nodo **Lista, Nodo *nodo)
{

    nodo->siguiente = (*Lista);
    *Lista = nodo;
}

void cargarDatos(Nodo **Lista, int cant)
{

    for (int i = 0; i < cant; i++)
    {
        int id = 1000 + i;
        Tarea tarea = cargarTareaPendiente(id);
        Nodo *nuevoNodo = crearNodo(tarea);
        insertarNodoEnLista(Lista, nuevoNodo);
    }
}

void mostrar(Nodo *Lista)
{

    while (Lista != NULL)
    {
        printf("\nID tarea:%d", Lista->T.tareaID);
        printf("\nDescripcion Tarea:%s", Lista->T.Descripcion);
        printf("\nDuracion:%d", Lista->T.duracion);

        Lista = Lista->siguiente;
        printf("\n");
    }
}
// buscamos nodo de tarea por id
Nodo *BuscarNodo(Nodo **Lista, int id)
{

    Nodo *nodoAux;
    nodoAux = (*Lista);

    while (nodoAux != NULL && nodoAux->T.tareaID != id)
    {
        nodoAux = nodoAux->siguiente;
    }
    return (nodoAux);
}
// quitar (aislar) nodo mediante algun parametro
Nodo *quitarNodo(Nodo **Lista, int id)
{

    Nodo *nodoAux = (*Lista);
    Nodo *nodoAnt = NULL;

    while (nodoAux != NULL && nodoAux->T.tareaID != id)
    {
        nodoAnt = nodoAux;
        nodoAux = nodoAux->siguiente;
    }

    if (nodoAux != NULL)
    {
        if (nodoAux == (*Lista))
        {
            (*Lista) = nodoAux->siguiente;
        }
        else
        {
            nodoAnt->siguiente = nodoAux->siguiente;
        }

        nodoAux->siguiente = NULL;
    }

    return (nodoAux);
}

// consultar tareas por id
void BuscarTareaPorID(Nodo **Lista1, Nodo **Lista2, int id)
{
    Nodo *aux1 = (*Lista1);
    Nodo *aux2 = (*Lista2);

    if (aux1 == NULL && aux2 == NULL)
    {

        printf("\nLas listas estan vacias");
    }
    else
    {
        if (aux1 != NULL)
        {
            while (aux1 != NULL)
            {
                if (aux1->T.tareaID == id)
                {
                    printf("\nTarea Buscada- Estado: PENDIENTE");
                    printf("\nID tarea:%d", aux1->T.tareaID);
                    printf("\nDescripcion:%s", aux1->T.Descripcion);
                    printf("\nDuracion:%d", aux1->T.duracion);
                }
                aux1 = aux1->siguiente;
            }
        }
    }

    if (aux2 != NULL)
    {
        while (aux2 != NULL)
        {
            if (aux2->T.tareaID == id)
            {
                printf("\nTarea Buscada- Estado: Realizado");
                printf("\nID tarea:%d", aux2->T.tareaID);
                printf("\nDescripcion:%s", aux2->T.Descripcion);
                printf("\nDuracion:%d", aux2->T.duracion);
            }
            aux2 = aux2->siguiente;
        }
    }
    else
    {
        printf("\nNo hay tareas con ese ID");
    }
}
// consultar tareas por Palabra clave
void buscarTareaPorPalabra(Nodo **Lista1, Nodo **Lista2, char *palabraClave)
{
    Nodo *aux1 = (*Lista1);
    Nodo *aux2 = (*Lista2);

    if (aux1 == NULL && aux2 == NULL)
    {
        puts("\nlas listas estan vacias");
    }
    else
    {
        if (aux1 != NULL)
        {
            while (aux1 != NULL)
            {
                if (strstr(aux1->T.Descripcion, palabraClave) != NULL)
                {
                    printf("\nTarea Buscada- Estado: Pendiente");
                    printf("\nID tarea:%d", aux1->T.tareaID);
                    printf("\nDescripcion:%s", aux1->T.Descripcion);
                    printf("\nDuracion:%d", aux1->T.duracion);
                }

                aux1 = aux1->siguiente;
            }
        }

        if (aux2 != NULL)
        {
            while (aux2 != NULL)
            {
                if (strstr(aux2->T.Descripcion, palabraClave) != NULL)
                {
                    printf("\nTarea Buscada- Estado: Realizado");
                    printf("\nID tarea:%d", aux2->T.tareaID);
                    printf("\nDescripcion:%s", aux2->T.Descripcion);
                    printf("\nDuracion:%d", aux2->T.duracion);
                }

                aux2 = aux2->siguiente;
            }
        }
    }
}


/*Funciones para liberar Memoria Nodos*/

/*Quitar el primer nodo de la lista*/
Nodo *quitarPrimerNodo(Nodo **Lista){

    Nodo *nodoAux = (*Lista);
    *Lista = (*Lista)->siguiente;
    nodoAux->siguiente = NULL;

    return nodoAux;
}
/*Libera la memoria del nodo*/
void liberarMemoriaUnNodo(Nodo *nodo){

    free(nodo->T.Descripcion);
    free(nodo);
}
/*Libera todos los nodos de la Lista*/
void LiberarMemoria (Nodo **Lista, int cantidad){

    Nodo *nodoAux = NULL;
    for (int i = 0; i < cantidad; i++){
        
        nodoAux = quitarPrimerNodo(Lista);
        liberarMemoriaUnNodo(nodoAux);
    }

}

int main()
{
    srand(time(NULL));

    int cantTareasPendiente = 4;

    Nodo *ListaTareaPendiente, *ListaTareaRealizada;

    ListaTareaPendiente = crearListaVacia();
    ListaTareaRealizada = crearListaVacia();

    cargarDatos(&ListaTareaPendiente, cantTareasPendiente);

    // mostrar(ListaTareaPendiente);

    Nodo *nodoBuscado = BuscarNodo(&ListaTareaPendiente, 1002);

    Nodo *nodoEliminado = quitarNodo(&ListaTareaPendiente, 1002);

    insertarNodoEnLista(&ListaTareaRealizada, nodoEliminado);

    printf("\nTareas Pendientes");
    mostrar(ListaTareaPendiente);

    printf("\nLista de tareas realizadas:\n");
    mostrar(ListaTareaRealizada);

    //BuscarTareaPorID(&ListaTareaPendiente,&ListaTareaRealizada,1002);
    
    buscarTareaPorPalabra(&ListaTareaPendiente, &ListaTareaRealizada, "cerrar");

    LiberarMemoria(&ListaTareaPendiente,cantTareasPendiente);


    return 0;
}