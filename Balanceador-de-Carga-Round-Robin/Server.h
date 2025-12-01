#ifndef SERVER_H
#define SERVER_H

struct Server {
    int id;                 // Identificador del servidor
    int handledRequests;    // Requests atendidas
    Server* next;           // Apunta al siguiente (lista circular)
};

#endif
