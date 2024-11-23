#include "avl.h"
#include <iostream>
using namespace std;

Avl::Avl(){
    raiz = NULL;
}

Avl::~Avl(){

}

// Função que cria um novo nó para inserir na árvore
void Avl::CriaNo(int num){

    NoPointer novo = new No;
    if(novo == NULL){
        cout << "ERRO" <<endl;
        return;
    }
    novo->valor = num;
    novo->contador = 1;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->fb = 0;
    bool h = true;
    raiz = Inserir(raiz, novo, h);
    cout << "--------  A RAIZ E: " <<raiz->valor<<endl;
}

// Função recursiva para inserir um nó na árvore
Avl::NoPointer Avl::Inserir(NoPointer &raiz, NoPointer novo, bool &h){
    if(raiz == NULL){
        h = true;
        return novo;
    }
    if(novo->valor < raiz->valor){
        raiz->esq = Inserir(raiz->esq, novo, h);
        // Verifica se a altura 'h' cresceu, se cresceu atualiza o fb
        if(h){
            raiz->fb = AtualizaFB(raiz->fb, 'E');
            if(raiz->fb == 2 || raiz->fb == -2){
                raiz = BalancearNo(raiz);
            }
            h = (raiz->fb != 0);
        }
    }
    else if(novo->valor > raiz->valor){
        raiz->dir = Inserir(raiz->dir, novo, h);
        // Verifica se a altura 'h' cresceu, se cresceu atualiza o fb
        if(h){
            raiz->fb = AtualizaFB(raiz->fb, 'D');
            if(raiz->fb == 2 || raiz->fb == -2){
                raiz = BalancearNo(raiz);
            }
            h = (raiz->fb != 0);
        }
    }
    else{
        // Caso ao contrario, o valor novo é igual ao valor da caixinha existente
        raiz->contador = raiz->contador + 1; // Incrementa o contador da caixinha existente
        delete novo; // Deleta o novo pois já existe caixinha com esse valor criado
    }
    return raiz;
}

int Avl::AtualizaFB(int fb, char lado){
    // Se o FB = 0 então os dois lados tem o mesmo tamanho
    if(fb == 0){
        return lado == 'D' ? 1 : -1;
    }
    // Se o FB = 1 então o lado direito é maior
    else if(fb == 1){
        return lado == 'D' ? 2 : 0;
    }
    // Se o FB = -1 então o lado esquerdo é maior
    else {
        return lado == 'D' ? 0 : -2;
    }
}

Avl::NoPointer Avl::BalancearNo(NoPointer raiz){
    // ROTAÇÃO A ESQUERDA: FB = 2 é o lado direito que está desbalanceado
    if(raiz->fb == 2){
        NoPointer filho = raiz->dir;

        // ROTAÇÃO SIMPLES A ESQUERDA: FB do filho >= 0 
        if(filho->fb >= 0){
            raiz->dir = filho->esq;
            filho->esq = raiz;
            // Atualiza os fatores de balanceamento.
            if (filho->fb == 0) {
                raiz->fb = 1;
                filho->fb = -1;
            } else {
                raiz->fb = 0;
                filho->fb = 0;
            }
            return filho;
        }

        // ROTAÇÃO DUPLA A ESQUERDA: FB do filho = 1
        else {
            NoPointer novoPai = filho->esq;

            filho->esq = novoPai->dir;
            raiz->dir = novoPai->esq;

            novoPai->dir = filho;
            novoPai->esq = raiz;

            // Atualiza os fatores de balanceamento
            if (novoPai->fb == 1) {
                raiz->fb = -1;
                filho->fb = 0;
            } else if (novoPai->fb == -1) {
                raiz->fb = 0;
                filho->fb = 1;
            } else {
                raiz->fb = 0;
                filho->fb = 0;
            }
            novoPai->fb = 0;
            return novoPai;
        }
    }
    
    // ROTAÇÃO A DIREITA: FB = -2  então o lado esquerdo está desbalanceado
    else{
        NoPointer filho = raiz->esq;

        // ROTAÇÃO SIMPLES A DIREITA: FB do filho <= 0
        if(filho->fb <= 0){
            raiz->esq = filho->dir;
            filho->dir = raiz;

            if (filho->fb == 0) {
                raiz->fb = -1;
                filho->fb = 1;
            } else {
                raiz->fb = 0;
                filho->fb = 0;
            }
            return filho;
        }
        
        // ROTAÇÃO DUPLA A DIREITA: FB do filho = 1 
        else{
            NoPointer novoPai = filho->dir;

            raiz->esq = novoPai->dir;
            filho->dir = novoPai->esq;

            novoPai->dir = raiz;
            novoPai->esq = filho;

            if (novoPai->fb == 1) {
                raiz->fb = 0;
                filho->fb = -1;
            } else if (novoPai->fb == -1) {
                raiz->fb = 1;
                filho->fb = 0;
            } else {
                raiz->fb = 0;
                filho->fb = 0;
            }
            novoPai->fb = 0;
            return novoPai;
        }
    }
}

// Função recursiva para deletar um nó na árvore
Avl::NoPointer Avl::DeletarNo(NoPointer raiz, int num, bool &h){
    if(raiz == NULL){
        h = false; // Árvore não modificada
        return raiz;
    }
    if(num < raiz->valor){
        raiz->esq = DeletarNo(raiz->esq, num, h);
        // Verifica se a altura diminuiu, se sim atualiza fator de balanceamento
        if (h) {
            raiz->fb = AtualizaFB(raiz->fb, 'D'); // Subárvore esquerda diminuiu
            if (raiz->fb == 2 || raiz->fb == -2) {
                raiz = BalancearNo(raiz);
            }
            h = (raiz->fb == 0); // Se o nó está balanceado, a altura diminuiu
        }
    }
    else if(num > raiz->valor){
        raiz->dir = DeletarNo(raiz->dir, num, h);
         // Verifica se a altura diminuiu, se sim atualiza fator de balanceamento
        if (h) {
            raiz->fb = AtualizaFB(raiz->fb, 'E'); // Subárvore direita diminuiu
            if (raiz->fb == 2 || raiz->fb == -2) {
                raiz = BalancearNo(raiz);
            }
            h = (raiz->fb == 0); // Se o nó está balanceado, a altura diminuiu
        }
    }
    else{
        h = true;
        // CASO 1: Verifica se é um nó folha
        if(raiz->dir == NULL && raiz->esq == NULL){
            delete raiz;
            return NULL;
        }

        // CASO 2 e CASO 3: Nó com apenas um filho ou dois filhos que um é folha
        NoPointer filhoDir = raiz->dir;
        NoPointer filhoEsq = raiz->esq;
        if(filhoDir != NULL){
            if(filhoDir->dir == NULL && filhoDir->esq == NULL){
                filhoDir->esq = raiz->esq;
                delete raiz;
                return filhoDir;
            }
        }

        if(filhoEsq != NULL){
            if(filhoEsq->dir == NULL && filhoEsq->esq == NULL){
                filhoEsq->dir = raiz->dir;
                delete raiz;
                return filhoEsq;
            }
        }

        // CASO 4 e CASO 5: O nó tem dois filhos e ambos possuem filhos
        NoPointer substituto = AuxiliarDelete(raiz->esq); // Encontra o nó mais a direita na subAvl esquerda
        raiz->valor = substituto->valor;
        raiz->contador = substituto->contador;
        substituto->valor = num;
        raiz->esq = DeletarNo(raiz->esq, num, h);
    }
    return raiz;    
}

// Função auxiliar para encontrar o nó de maior valor na subárvore esquerda
Avl::NoPointer Avl::AuxiliarDelete(NoPointer raiz){
    while((raiz->dir != NULL)){
        raiz = raiz->dir;
    }
    return raiz;
}

// Função para iniciar a exclusão de um nó a partir da raiz
void Avl::RemoverNo(int num){
    bool h;
    raiz = DeletarNo(raiz, num, h);
    cout << "--------  A RAIZ E: " <<raiz->valor<<endl;
}



// Função que exibe a Avl de acordo com o que usuário quer
void Avl::ExibeArvore(int opcao){
    if(opcao == 2){
        cout << endl << "Ordem crescente: ";
        ImprimirOrdemCrescente(raiz);
    }
    else{
        cout << endl << "Ordem decrescente: ";
        ImprimirOrdemDecrescente(raiz);
    }
    cout << endl;
}

// Função recursiva para exibir a árvore em ordem decrescente
void Avl::ImprimirOrdemDecrescente(NoPointer raiz){
    if(raiz==NULL){
        return;
    }
    ImprimirOrdemDecrescente(raiz->dir);
    cout << raiz->valor << " - ";
    ImprimirOrdemDecrescente(raiz->esq);
}

// Função recursiva para exibir a árvore em ordem crescente
void Avl::ImprimirOrdemCrescente(NoPointer raiz){
    if(raiz==NULL){
        return;
    }
    ImprimirOrdemCrescente(raiz->esq);
    cout << raiz->valor <<" - ";
    ImprimirOrdemCrescente(raiz->dir);
}

// Função para buscar um valor na árvore e imprimir se encontrado
void Avl::BuscarValor(int num,NoPointer raiz){
    if(raiz == NULL){
        return;
    }

    BuscarValor(num, raiz->esq);
    if(raiz->valor == num){
        cout << "Valor " << raiz->valor << " encontrado, ocorrencia: " << raiz->contador <<endl;
        cout << "FB: " << raiz->fb<<endl;
    }
    BuscarValor(num,raiz->dir);
}

// Função que inicia a busca por um valor a partir da raiz
void Avl::PesquisaValor(int num){
    BuscarValor(num, raiz);
}