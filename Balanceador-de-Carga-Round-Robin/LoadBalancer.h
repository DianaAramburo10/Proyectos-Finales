#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "Server.h"

// Crea la lista circular de servidores
Server* createCircularServerList(int numServers);

// Libera memoria de la lista
void freeCircularServerList(Server* head);

// Distribuye solicitudes con Round Robin
void distributeRequestsRoundRobin(Server* head, int totalRequests);

// Muestra tabla de carga
void printLoadTable(Server* head, int totalRequests);

// Grafica de barras en texto
void printBarChart(Server* head);

#endif
