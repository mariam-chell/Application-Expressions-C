#include "mp.hpp"



int main() {
  /*  //////////////////////////
    // Question 1 : évaluer une expression postfixée
    //////////////////////////

    string expPostfixee;
    cout << "Entrez une expression postfixée (ex: 23+5*): ";
    cin >> expPostfixee;

    int resultat = evaluer(expPostfixee);
    cout << "Résultat de l'évaluation : " << resultat << endl;



 //////////////////////////
 /*   // Question 2 : convertir infixée → postfixée
    //////////////////////////

    string expInfixee;
    cout << "\nEntrez une expression infixée (ex: 2+3*5) : ";
    cin >> expInfixee;

    string conversion = Postfix(expInfixee);
    cout << "Expression convertie en postfixée : " << conversion << endl;

   */ //////////////qst3////////////////

    string exp;
    cout << "Entrez une expression infixée : ";
    cin >> exp;

    Arbre arbre(exp);

    cout << "Expression reconstruite : ";
    arbre.afficherInfixe();

    cout << "Résultat de l'évaluation : " << arbre.evaluer() << endl;


    //////////////qst4////////////////

    return 0;
}
