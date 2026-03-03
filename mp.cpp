 #include "mp.hpp"
  ////////////////qst1////////////////
Maillon::Maillon(char v, Maillon* s) {
    info = v;
    suivant = s;
}

Pile::Pile() {
    sommet = nullptr;
}

Pile::~Pile() {
    while (sommet != nullptr) {
        Maillon* temp = sommet;
        sommet = sommet->suivant;
        delete temp;
    }
}

void Pile::empiler(int x) {
    sommet = new Maillon(x, sommet);
}

int Pile::depiler() {
    if (sommet == nullptr) {
        exit(1); // pile vide
    }

    int x = sommet->info;
    Maillon* temp = sommet;
    sommet = sommet->suivant;
    delete temp;
    return x;
}

bool Pile::estVide() {
    return sommet == nullptr;
}

int evaluer(string e) {
    Pile p;

    for (int i = 0; e[i]; i++) {
        char c = e[i];

        if (c >= '0' && c <= '9') {
            int val = c - '0';
            p.empiler(val);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            int b = p.depiler();
            int a = p.depiler();
            int res;

            if (c == '+') {
                res = a + b;
            }
            else if (c == '-') {
                res = a - b;
            }
            else if (c == '*') {
                res = a * b;
            }
            else if (c == '/') {
                if (b == 0) {
                    exit(1);
                }
                res = a / b;
            }

            p.empiler(res);
        }
    }

    int r = p.depiler();

    if (!p.estVide()) {
        exit(1); 
    }

    return r;
}
////////////////qst2////////////////
bool estOperande(char c) {
    return c >= '0' && c <= '9';
}

int priorite(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

string Postfix(string infix) {
    Pile pile;
    string postfix = "";

    for (int i = 0; infix[i] != '\0'; ++i) {
        char c = infix[i];

        if (estOperande(c)) {
            postfix += c;
        }
        else if (c == '(') {
            pile.empiler(c);
        }
        else if (c == ')') {
            while (!pile.estVide() && pile.depiler() != '(') {
                postfix += pile.depiler();
            }
            pile.depiler();
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!pile.estVide()) {
                int top = pile.depiler();
                if (priorite(c) > priorite(top)) {
                    pile.empiler(top);
                    break;
                }
                postfix += top;
            }

            pile.empiler(c);
        }
    }

    while (!pile.estVide()) {
        int top = pile.depiler();
        if (top == '(') break;
        postfix += top;
    }

    return postfix;
}


//////////////////////// QST3 ////////////////////////

noeud::noeud() {
    type = 'f';
    ope = '\0';
    val = 0;
    fg = nullptr;
    fd = nullptr;
}

noeud::~noeud() {
    if (fg) delete fg;
    if (fd) delete fd;
}

Arbre::Arbre() {
    racine = nullptr;
}

Arbre::~Arbre() {
    if (racine) delete racine;
}


Arbre::Arbre(string infix) {
    racine = nullptr;
    string post = Postfix(infix);
    Pile pile;
    const int MAX = 100;
    noeud* tab[MAX];
    int nb = 0;

    for (int i = 0; i < post.length(); ++i) {
        char c = post[i];

        if (estOperande(c)) {
            tab[nb] = new noeud();
            tab[nb]->type = 'f';
            tab[nb]->val = c - '0';
            tab[nb]->fg = nullptr;
            tab[nb]->fd = nullptr;

            pile.empiler(nb);
            nb++;
        } else {
            int idx2 = pile.depiler();
            int idx1 = pile.depiler();

            tab[nb] = new noeud();
            tab[nb]->type = 'o';
            tab[nb]->ope = c;
            tab[nb]->fg = tab[idx1];
            tab[nb]->fd = tab[idx2];

            pile.empiler(nb);
            nb++;
        }
    }

    int racineIdx = pile.depiler();
    racine = tab[racineIdx];
}


double Arbre::evaluer() {
    return evaluer(racine);
}

double Arbre::evaluer(noeud* n) {
    if (n == nullptr) return 0;

    if (n->type == 'f') return n->val;

    double g = evaluer(n->fg);
    double d = evaluer(n->fd);

    switch (n->ope) {
        case '+': return g + d;
        case '-': return g - d;
        case '*': return g * d;
        case '/': return d != 0 ? g / d : 0; // ou exit(1)
        default: return 0;
    }
}

void Arbre::afficherInfixe() {
    afficherInfixe(racine);
    cout << endl;
}

void Arbre::afficherInfixe(noeud* n) {
    if (n == nullptr) return;

    if (n->type == 'f') {
        cout << (int)n->val;
    } else {
        cout << "(";
        afficherInfixe(n->fg);
        cout << n->ope;
        afficherInfixe(n->fd);
        cout << ")";
    }
}
