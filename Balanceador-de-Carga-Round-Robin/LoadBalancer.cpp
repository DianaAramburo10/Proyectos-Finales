#include <iostream>   
#include <iomanip>  // Para std::setw, std::setprecision
#include <string>   
#include "LoadBalancer.h" //Incluye las declaraciones de las funciones y la estructura Server
using namespace std;  


// Crea una lista circular de servidores
Server* createCircularServerList(int numServers) {

    // Si el número de servidores es inválido, no se crea nada
    if (numServers <= 0) return nullptr;

    Server* head = nullptr;  //"head" apuntará al primer servidor de la lista

    Server* prev = nullptr;  // "prev" guarda el nodo anterior para poder enlazarlo con el nuevo

    // Se crea cada servidor
    for (int i = 0; i < numServers; ++i) {

        // Reservamos memoria dinámica para un nuevo servidor
        Server* node = new Server;

        node->id = i + 1;              
        // Asignamos un identificador único al servidor (1,2,3...)

        node->handledRequests = 0;     
        // Inicializa en 0 porque aún no ha atendido solicitudes

        node->next = nullptr;          
        // Aún no apunta a ningún servidor

        if (!head) {                   
            // Si la cabeza está vacía, este es el primer servidor
            head = node;
        } else {
            // Si ya hay al menos uno, el anterior apunta a este nuevo
            prev->next = node;
        }

        prev = node;  // "prev" se actualiza para el siguiente ciclo
    }

    // Se completa la circularidad:
    prev->next = head;  
    // El último servidor apunta al primero

    return head;        
    // Se regresa el inicio de la lista
}


// Libera memoria de la lista circular
void freeCircularServerList(Server* head) {

    if (!head) return;  
    // Si la lista está vacía, no hay nada que liberar

    Server* current = head->next;

    // Recorremos todos los nodos excepto el primero
    while (current != head) {
        Server* tmp = current;         
        current = current->next;       
        delete tmp;                    
        // Se libera memoria del nodo
    }

    delete head;  
    // Finalmente se elimina la cabeza
}


// Distribuye solicitudes usando Round Robin
void distributeRequestsRoundRobin(Server* head, int totalRequests) {

    if (!head || totalRequests <= 0) return;
    // Si no hay servidores o solicitudes, no se hace nada

    Server* current = head;  
    // Comenzamos desde el primer servidor

    for (int i = 0; i < totalRequests; ++i) {

        current->handledRequests++;  
        // Se asigna una request al servidor actual

        current = current->next;     
        // Se avanza al siguiente servidor (Round Robin)
    }
}


// Imprime tabla de resultados
void printLoadTable(Server* head, int totalRequests) {

    if (!head) return;

    cout << "\n=== Tabla de Distribucion de Carga ===\n";

    cout << left << setw(10) << "Servidor"
         << setw(15) << "Requests"
         << setw(15) << "Porcentaje" << "\n";
    // Encabezados de la tabla

    cout << string(40, '-') << "\n";
    // Línea separadora

    Server* current = head;

    do {
        // Calcula el porcentaje de carga de este servidor
        double percentage = (100.0 * current->handledRequests) / totalRequests;

        cout << left << setw(10) << current->id  //fija el ANCHO del espacio que se reserva para ese dato
             << setw(15) << current->handledRequests
             << fixed << setprecision(2)
             << setw(14) << percentage << "%" << "\n";

        current = current->next;  
        //Avanzamos al siguiente servidor
    } while (current != head);
}


// Genera gráfica de barras en consola
void printBarChart(Server* head) {

    if (!head) return;

    const int maxBarLength = 50;  
    // Ancho máximo de la barra

    int maxRequests = 0;

    Server* current = head;

    // Encuentra el servidor con más solicitudes
    do {
        if (current->handledRequests > maxRequests)
            maxRequests = current->handledRequests;

        current = current->next;
    } while (current != head);

    cout << "\n=== Grafica de Barras ===\n";

    current = head;

    do {
        // Escala la barra proporcionalmente
        int barLength = 
            (current->handledRequests * maxBarLength) / maxRequests;

        // Garantiza barra visible si tuvo al menos 1 request
        if (barLength == 0 && current->handledRequests > 0)
            barLength = 1;

        // Crea la barra con '#'
        string bar(barLength, '#');

        cout << "Servidor " << current->id << " | "
             << bar << " (" << current->handledRequests << ")\n";

        current = current->next;
    } while (current != head);
}
