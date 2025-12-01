#ifndef SISTEMA_RECOMENDACION_H
#define SISTEMA_RECOMENDACION_H

#include "Usuario.h"  //incluye Usuario porque lo usa
#include <vector>
#include <string>
using namespace std;

class SistemaRecomendacion {
private:
    vector<Usuario> usuarios;  //usa la clase usuario ; todos los usuarios de la red

    //funcion auxiliar para buscar un usuario por ID. Retorna un puntero para poder modificar al usuario o retornar nullptr si no existe.
    Usuario* buscarUsuario(int idUsuario);
public:
    //agregar un usuario al sistema
    void agregarUsuario(const Usuario& u);
    //generar recomendaciones para un usuario
    vector<string> generarRecomendaciones(int idUsuario, int TopN = 5);
    //cambiar formato de recomendaciones
    void mostrarRecomendaciones(int idUsuario,int TopN = 5);
    //mostrar todos los usuarios (util para debugging)
    void mostrarTodosUsuarios();
};

#endif