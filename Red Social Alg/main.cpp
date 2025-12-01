#include "Usuario.h"
#include "SistemaRecomendacion.h"
#include <iostream>
using namespace std;

int main() {
    cout << "=== SISTEMA DE RECOMENDACIONES - RED SOCIAL ===" << endl;
    
    // 1.CREAR USUARIOS
    Usuario ana(1, "Ana Garcia");
    ana.agregarInteres("musica");
    ana.agregarInteres("fitness");
    ana.agregarInteres("tecnologia");
    ana.agregarInteres("viajes");
    
    Usuario carlos(2, "Carlos Lopez");
    carlos.agregarInteres("tecnologia");
    carlos.agregarInteres("gaming");
    carlos.agregarInteres("musica");
    carlos.agregarInteres("programacion");
    
    Usuario maria(3, "Maria Rodriguez");
    maria.agregarInteres("fitness");
    maria.agregarInteres("cocina");
    maria.agregarInteres("viajes");
    maria.agregarInteres("yoga");
    maria.agregarInteres("fotografia");
    
    Usuario juan(4, "Juan Martinez");
    juan.agregarInteres("gaming");
    juan.agregarInteres("tecnologia");
    juan.agregarInteres("anime");
    juan.agregarInteres("programacion");
    
    Usuario laura(5, "Laura Sanchez");
    laura.agregarInteres("musica");
    laura.agregarInteres("arte");
    laura.agregarInteres("fotografia");
    laura.agregarInteres("viajes");
    laura.agregarInteres("moda");
    
    Usuario pedro(6, "Pedro Hernandez");
    pedro.agregarInteres("deportes");
    pedro.agregarInteres("fitness");
    pedro.agregarInteres("cocina");
    pedro.agregarInteres("naturaleza");
    
    //2.ESTABLECER CONEXIONES (AMIGOS)
    ana.agregarAmigo(2); //ana es amiga de carlos
    ana.agregarAmigo(3); //ana es amiga de maria
    ana.agregarAmigo(5); //ana es amiga de laura
    
    carlos.agregarAmigo(1); //carlos es amigo de ana
    carlos.agregarAmigo(3); //carlos es amigo de maria
    carlos.agregarAmigo(4); //carlos es amigo de juan
    
    maria.agregarAmigo(1); //maria es amiga de ana
    maria.agregarAmigo(2); //maria es amiga de carlos
    maria.agregarAmigo(5); //maria es amiga de laura
    
    juan.agregarAmigo(2); //juan es amigo de carlos
    juan.agregarAmigo(5); //juan es amigo de laura
    
    laura.agregarAmigo(1); //laura es amiga de ana
    laura.agregarAmigo(3); //laura es amiga de maria
    laura.agregarAmigo(4); //laura es amiga de juan
    
    pedro.agregarAmigo(3); //pedro es amigo de maria
    
    //3.CREAR SISTEMA Y AGREGAR USUARIOS
    SistemaRecomendacion sistema;
    sistema.agregarUsuario(ana);
    sistema.agregarUsuario(carlos);
    sistema.agregarUsuario(maria);
    sistema.agregarUsuario(juan);
    sistema.agregarUsuario(laura);
    sistema.agregarUsuario(pedro);
    
    //4.MOSTRAR TODOS LOS USUARIOS
    sistema.mostrarTodosUsuarios();
    
    //5.GENERAR RECOMENDACIONES
    cout << "\n========== GENERANDO RECOMENDACIONES ==========\n" << endl;
    
    sistema.mostrarRecomendaciones(1, 5); //para ana
    sistema.mostrarRecomendaciones(2, 5); //para carlos
    sistema.mostrarRecomendaciones(6, 5); //para pedro
    
    return 0;
}