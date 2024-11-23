class Avl{
    private:  
        struct No{
            int valor, contador, fb;
            No *dir,*esq;
        };
        typedef No* NoPointer;
        NoPointer raiz;

        //Métodos privados para proteger a raiz
        NoPointer Inserir(NoPointer &raiz, NoPointer novo, bool &h); // Função recursiva para inserir um nó na árvore
        void ImprimirOrdemCrescente(NoPointer raiz); // Função recursiva para exibir a árvore em ordem crescente
        void ImprimirOrdemDecrescente(NoPointer raiz); // Função recursiva para exibir a árvore em ordem decrescente
        void BuscarValor(int num,NoPointer raiz); // Função para buscar um valor na árvore e imprimir se encontrado
        NoPointer AuxiliarDelete(NoPointer raiz); // Função auxiliar para encontrar o nó de maior valor na subárvore esquerda
        NoPointer DeletarNo(NoPointer raiz, int num, bool &h); // Função recursiva para deletar um nó na árvore
        NoPointer BalancearNo(NoPointer raiz); // Função que balancea a arvore

    public:
        Avl(); // Construtor, inicializa a arvore com NULL
        ~Avl(); // Destrutor (não realiza nenhuma operação no momento)
        void CriaNo(int num); // Função que cria um novo nó para inserir na árvore
        void ExibeArvore(int num); // Função que exibe a arvore de acordo com o que usuário quer
        void PesquisaValor(int num); // Função que inicia a busca por um valor a partir da raiz
        void RemoverNo(int num); // Função para iniciar a exclusão de um nó a partir da raiz
        int AtualizaFB(int fb, char lado); // Função que atualiza o fator de balanceamento 
};




