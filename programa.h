struct Ingresso{
   int lugar, idade;
   float preco;
   char responsavel[25];
};
// Vetores onde a posição 0 se refere a area vip, 1 a area verde, 2 a area amarela e 3 a pista
struct Ingresso *ingressos[4]; // vetor de ponteiros o que forma uma matriz na qual a segunda dimensão é alocada dinamicamente
int qtdIngressos[4], numLugares[4]; 
float valoresIngressos[4];

struct RelatoriosEstatisticas{
   float saldoArrecadado, saldoDevolvido, saldoPorCategoria[3]; //categoria: 0 = normal, 1 = estudante, 2 = idoso
   char responsavelMenorIdade[25], responsavelMaiorIdade[25];
   int *ordCrescente, *ordDecrescente, maiorIdade, menorIdade;
};
struct RelatoriosEstatisticas relatEstat;

void compra(int setor);
int devolucao();
void listagem(int setor);
void ordenacao(int tipo, char **nomes, int op);
void getSaldo(int op, int categoria);
void maiorMenorIdade(int op);
void carregaOuSalvaDados(int op);