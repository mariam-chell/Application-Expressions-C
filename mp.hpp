 #ifndef MP_HPP
#define MP_HPP

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// Maillon = élément de la pile
class Maillon {
private:
    char info;
    Maillon* suivant;

    friend class Pile;

public:
    Maillon(char v, Maillon* s);
};

// Pile = liste chaînée
class Pile {
private:
    Maillon* sommet;

public:
    Pile();
    ~Pile();
    void empiler(int x);
    int depiler();
    bool estVide();
};

// Fonction d’évaluation postfixée
int evaluer(string e);

// Fonction pour vérifier si un caractère est un opérande (chiffre)
bool estOperande(char c);

// Fonction pour obtenir la priorité d'un opérateur
int priorite(char op);

// Fonction pour transformer une expression infixée en une expression postfixée
string Postfix(string infix);


// à ajouter dans mp.hpp

class noeud {
    public:
        char type; // 'o' pour opérateur, 'f' pour valeur
        char ope;
        double val;
        noeud* fg;
        noeud* fd;
    
        noeud();
        ~noeud();
    };
    
class Arbre {
    private:
        noeud* racine;
    
    public:
        Arbre(); // constructeur vide
        Arbre(string infix); // constructeur à partir d'expression infixée
        ~Arbre();
    
        double evaluer();
        double evaluer(noeud* n);
        void afficherInfixe();
        void afficherInfixe(noeud* n);
    };
    

#endif                     