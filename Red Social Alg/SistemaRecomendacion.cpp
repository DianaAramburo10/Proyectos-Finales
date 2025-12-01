#include "SistemaRecomendacion.h"
#include <algorithm>
#include <iostream>
#include <map> 
using namespace std;

//FUNCION 1:agregar usuario al sistema
void SistemaRecomendacion::agregarUsuario(const Usuario& u) {
    usuarios.push_back(u);
}

//FUNCION 2:buscar usuario por id(auxiliar)
Usuario* SistemaRecomendacion::buscarUsuario(int idUsuario) {
    for (int i=0; i<usuarios.size(); i++){
        if (usuarios[i].getId()==idUsuario){
            return &usuarios[i]; //Retorna la direccion del usuario encontrado
        }
    }
    return nullptr; //No se encontro
}

//FUNCION 3:Mostrar todos los usuarios
void SistemaRecomendacion::mostrarTodosUsuarios() {
    cout << "\n========== RED SOCIAL ==========" << endl;
    for (Usuario& u : usuarios){
        u.mostrarInfo();
        cout<<endl;
    }
    // TODO: Recorrer 'usuarios' y llamar mostrarInfo() de cada uno
    cout << "================================\n" << endl;
}

vector<string> SistemaRecomendacion::generarRecomendaciones(int idUsuario, int topN) {
    vector<string> recomendaciones;
    
    //1.Buscar usuario
    Usuario* usuario = buscarUsuario(idUsuario);
    if (usuario == nullptr) {
        return recomendaciones;
    }
    
    //2.obtener amigos
    vector<int> idsAmigos = usuario->getAmigos();
    if (idsAmigos.empty()) {
        return recomendaciones;
    }
    
    //3.calcular similitud con cada amigo
    vector<pair<Usuario*, float>> amigosSimilitud;
    for (int idAmigo : idsAmigos) {
        Usuario* amigo = buscarUsuario(idAmigo);
        if (amigo != nullptr) {
            float similitud = usuario->calcularSimilitudCon(*amigo);
            amigosSimilitud.push_back({amigo, similitud});
        }
    }
    
    //4.ordenar por similitud
    sort(amigosSimilitud.begin(), amigosSimilitud.end(),
         [](const pair<Usuario*, float>& a, const pair<Usuario*, float>& b) {
             return a.second > b.second;
         });
    
    //5.recopilar intereses y calcular scores
    map<string, float> scoreIntereses;
    set<string> interesesUsuario = usuario->getIntereses();
    
    for (const auto& [amigo, similitud] : amigosSimilitud) {
        set<string> interesesAmigo = amigo->getIntereses();
        for (const string& interes : interesesAmigo) {
            if (interesesUsuario.find(interes) == interesesUsuario.end()) {
                scoreIntereses[interes] += similitud;
            }
        }
    }
    
    //6.rankear intereses por score
    vector<pair<string, float>> interesesRankeados;
    for (const auto& [interes, score] : scoreIntereses) {
        interesesRankeados.push_back(pair<string, float>(interes, score));
    }
    
    sort(interesesRankeados.begin(), interesesRankeados.end(),
         [](const pair<string, float>& a, const pair<string, float>& b) {
             return a.second > b.second;
         });
    
    //7.retornar top N
    for (int i = 0; i < min(topN, (int)interesesRankeados.size()); i++) {
        recomendaciones.push_back(interesesRankeados[i].first);
    }
    
    return recomendaciones;
}


void SistemaRecomendacion::mostrarRecomendaciones(int idUsuario, int topN) {
    Usuario* usuario = buscarUsuario(idUsuario);
    if (usuario == nullptr) {
        cout << "Usuario no encontrado" << endl;
        return;
    }
    
    cout << "\n----------------------------------------" << endl;
    cout << "RECOMENDACIONES PARA: " << usuario->getNombre() << endl;
    cout << "----------------------------------------" << endl;
    
    // Mostrar intereses actuales
    cout << "\n Tus intereses actuales: ";
    bool primero = true;
    for (const string& i : usuario->getIntereses()) {
        if (!primero) cout << ", ";
        cout << i;
        primero = false;
    }
    cout << "\n" << endl;
    
    // Mostrar similitud con amigos
    vector<int> idsAmigos = usuario->getAmigos();
    if (!idsAmigos.empty()) {
        cout << "Similitud con tus amigos:\n" << endl;
        for (int idAmigo : idsAmigos) {
            Usuario* amigo = buscarUsuario(idAmigo);
            if (amigo != nullptr) {
                float sim = usuario->calcularSimilitudCon(*amigo);
                int barras = (int)(sim * 10);
                cout << "   " << amigo->getNombre() << ": ";
                for (int i = 0; i < 10; i++) {
                    cout << (i < barras ? "#" : "-");
                }
                cout << " " << (int)(sim * 100) << "%" << endl;
            }
        }
        cout << endl;
    }
    
    // Recomendaciones
    vector<string> recs = generarRecomendaciones(idUsuario, topN);
    
    if (recs.empty()) {
        cout <<  "No hay recomendaciones disponibles" << endl;
    } else {
        cout << "Intereses recomendados:\n" << endl;
        for (int i = 0; i < recs.size(); i++) {
            cout << "   " << (i+1) << ". " << recs[i] << endl;
        }
    }
    
    cout << "\n----------------------------------------\n" << endl;
}