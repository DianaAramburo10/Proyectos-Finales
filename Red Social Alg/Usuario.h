#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>
#include <vector>
#include <set> //No permite elementos duplicados y los mantiene ordenados automaticamente (alfabeticamente)
using namespace std;

class Usuario {
    private:
        int id;
        string nombre;
        set <string> intereses;
        vector <int> amigos; //IDs de amigos
    public:
        //Constructor, getters, setters
        //constructur
        Usuario (int _id, string _nombre) : id(_id) , nombre (_nombre) {}
        //atributo = paramentro (por eso el guion bajo, tambien se puede usar "this ->" o usar nombres diferentes)
        //este formato de inicializacion se llama "lista de inicializacion" es la forma mas eficiente de inicializar en c++

        //getters (paea leer valores privados)
        int getId() {return id;}
        string getNombre() {return nombre;}
        const set<string>& getIntereses() const{return intereses;}
        vector<int> getAmigos() {return amigos;}

        //metodos
        void agregarInteres(string interes);
        void agregarAmigo(int idAmigo);
        void mostrarInfo();
        float calcularSimilitudCon(const Usuario& otroUsuario);
};


#endif