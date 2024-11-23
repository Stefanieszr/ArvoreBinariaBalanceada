#include "avl.h"
#include <iostream>

using namespace std;

int main(){
    Avl a1;

    int opcao;
    while(opcao != 6){
        cout << endl << "#########################################################"<<endl;
        cout << "Inserir um numero na arvore, digite 1" << endl;
        cout << "Exibir os elementos em ordem crescente, digite 2" << endl;
        cout << "Exibir os elementos em ordem decrescente, digite 3" << endl;
        cout << "Buscar por uma valor especifico, digite 4" << endl;
        cout << "Remover um valor, digite 5" << endl;
        cout << "Encerrar, digite 6" << endl;
        cout << "#########################################################"<<endl;
        cin >> opcao;

        switch (opcao){
        case 1:
            int numero;
            cout << "Digite o numero que deseja inserir"<<endl;
            cin >> numero;
            a1.CriaNo(numero);
            break;
        case 2:
            a1.ExibeArvore(opcao);
            break;
        case 3:
            a1.ExibeArvore(opcao);
            break;
        case 4:
            int valor;
            cout << "Qual valor deseja encontrar" << endl;
            cin >> valor;
            a1.PesquisaValor(valor);
            break;
        case 5:
            int valorRemover;
            cout << "Qual valor deseja remover" << endl;
            cin >> valorRemover;
            a1.RemoverNo(valorRemover);
            break;
        case 6:
            break;
        default:
            cout << "Escolha invalida, tente novamente!"<<endl;
            break;
        }
    }
}