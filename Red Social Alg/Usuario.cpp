#include "Usuario.h"
#include <iostream>
#include <algorithm>  // Para find(), para set_interseccion y set_union
#include <iterator> //inserter?

//metodos
void Usuario::agregarInteres(string interes) {
    if (!interes.empty()){
        intereses.insert(interes); //diferencia entre: push_back, insert y set?
    }
}

void Usuario::agregarAmigo(int idAmigo) {
    if (idAmigo>0 && idAmigo!=id){ //id mayor a 0 y no considerarse a si mismo
        amigos.push_back(idAmigo); //pushear en el vector :)
    }
}

void Usuario::mostrarInfo() {
    cout<<"===Usuario: "<< nombre << "==="<<endl;
    cout<<"Intereses: ";
    bool primero = true; //al inicio el primer elemento aun no se ha impreso (flag?)
    for (const string& interes : intereses){
        if(!primero){cout<<", ";}//coma antes de cada elemento menos en el primero
            cout<<interes;
            primero = false; //a partir de ahora ya no es el primero (se ejecuta despues de imprimir el primer elemento)
    }cout<<endl;
    cout<<"Amigos: "<<amigos.size()<<endl;
}

float Usuario::calcularSimilitudCon(const Usuario& otroUsuario) { //Metodo Jaccard
    set<string> interseccion;
    set<string> uniones;
    // Interseccion
    set_intersection(
        intereses.begin(), intereses.end(),
        otroUsuario.intereses.begin(), otroUsuario.intereses.end(),
        inserter(interseccion, interseccion.begin())
    );

    // Union
    set_union(
        intereses.begin(), intereses.end(),
        otroUsuario.intereses.begin(), otroUsuario.intereses.end(),
        inserter(uniones, uniones.begin())
    );

    if (uniones.empty()) return 0.0;
    return (float) interseccion.size() / (float) uniones.size();
}

