#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./programa.h"
// Funcao compra, recebe como parâmetro a posiçao da matriz na qual está relacionada ao setor
void compra(int setor){
   int i, qtdIngressosCompra, qtdIdosos, qtdEstudantes, *idades, auxLugar, auxConf;
   float *valores, valorTotalIdoso = 0, valorTotalEstudante = 0, valorTotalNormal = 0, valorTotal;
   char responsavel[25];
   // Requisição de informações para a compra e verificação de quantidades
   printf("\nQuantidade de ingressos disponíveis nesse setor: %i", (numLugares[setor]-qtdIngressos[setor]));
   printf("\nDigite a quantidade de ingressos que deseja comprar: ");
   scanf("%i", &qtdIngressosCompra);
   if((qtdIngressosCompra > (numLugares[setor]-qtdIngressos[setor])) || qtdIngressosCompra < 1){
      printf("\nQuantidade não disponível!\n");
      return;
   }
   printf("\nDigite o nome do responsável pela compra: (sem acentuações) ");
   scanf(" %[^\n]", responsavel);
   printf("Algum idoso? Se sim, quantos? (0 se não houver): ");
   scanf("%i", &qtdIdosos);
   printf("Algum estudante? Se sim, quantos? (0 se não houver): ");
   scanf("%i", &qtdEstudantes);
   if((qtdEstudantes+qtdIdosos) > qtdIngressosCompra){
      printf("\nErro! Quantidade de pessoas informadas maior do que a quantidade de ingressos!\n");
      return;
   }
   // Alocação dos espacos de acordo com os dados informados
   valores = (float*) calloc(qtdIngressosCompra, sizeof(float));
   idades = (int*) calloc(qtdIngressosCompra, sizeof(int));
   // Leitura das idades das pessoas idosas, atribuição do valor do ingresso com desconto de 25% e soma ao valor total da compra
   if(qtdIdosos > 0){
      printf("Digite a idade das pessoas idosas: \n");
      for(i = 0; i < qtdIdosos; i++){
         while(idades[i] < 60){
            printf("%i - ", i+1);
            scanf("%i", &idades[i]);
            valores[i] = valoresIngressos[setor] - (valoresIngressos[setor]*0.25);
            if(idades[i] < 60){
               printf("Idade inválida! Digite novamente.\n");
            }
         }
         valorTotalIdoso += valores[i];
      }
   }
   // Leitura das idades dos estudantes, atribuição do valor do ingresso com desconto de 50% e soma ao valor total da compra
   if(qtdEstudantes > 0){
      printf("Digite a idade dos estudantes: \n");
      for(i = 0; i < qtdEstudantes; i++){
         printf("%i - ", i+1);
         scanf("%i", &idades[i+qtdIdosos]);
         valores[i+qtdIdosos] = valoresIngressos[setor] - (valoresIngressos[setor]*0.5);
         valorTotalEstudante += valores[i+qtdIdosos];
      }
   }
   // Leitura das idades das outras pessoas, atribuiçao do valor integral do ingressoe soma ao valor total da compra
   if((qtdIngressosCompra-qtdIdosos-qtdEstudantes) > 0){
      printf("Digite a idade dos pagantes regulares: \n");
      for(i = 0; i < qtdIngressosCompra-qtdIdosos-qtdEstudantes; i++){
         printf("%i - ", i+1);
         scanf("%i", &idades[i+qtdIdosos+qtdEstudantes]);
         valores[i+qtdIdosos+qtdEstudantes] = valoresIngressos[setor];
         valorTotalNormal += valores[i+qtdIdosos+qtdEstudantes];
      }
   }
   // Confirma a compra
   valorTotal = valorTotalNormal + valorTotalEstudante + valorTotalIdoso;
   system("cls");
   printf("\nValor Total: %.2f\nDeseja confirmar a compra? (1-sim/2-nao) ", valorTotal);
   scanf("%i", &auxConf);
   if(auxConf == 1){
      // Se for confirmada, realoca o espaco necessário para salvar, tendo o espaco alocado salva os dados
      // armazena tb informacoes de relatorio
      relatEstat.saldoPorCategoria[0] += valorTotalNormal;
      relatEstat.saldoPorCategoria[1] += valorTotalEstudante;
      relatEstat.saldoPorCategoria[2] += valorTotalIdoso;
      relatEstat.saldoArrecadado += valorTotal;
      ingressos[setor] = (struct Ingresso *) realloc(ingressos[setor], (qtdIngressos[setor]+qtdIngressosCompra)*sizeof(struct Ingresso));
      for(i = 0; i < qtdIngressosCompra; i++){
         ingressos[setor][i+qtdIngressos[setor]].lugar = qtdIngressos[setor]+i+1;
         ingressos[setor][i+qtdIngressos[setor]].idade = idades[i];
         ingressos[setor][i+qtdIngressos[setor]].preco = valores[i];
         strcpy(ingressos[setor][i+qtdIngressos[setor]].responsavel, responsavel);
      }
      qtdIngressos[setor] += qtdIngressosCompra;
      printf("Compra efetuada com sucesso!\n\n");
   }else{
      printf("Compra cancelada!\n\n");
   }
   // Limpa o espaço alocado na memória para os vetores de idades e valores
   free(idades);
   free(valores);
}

// Funcao devoluçao, envia com parametro o setor e retorna 0 ou 1
int devolucao(){
   char responsavel[25];
   int i, j, setor = -1;
   // Faz a procura pelo nome entre os setores, se encontra armazena na variavel setor
   printf("\nDigite o nome do responsável pela compra: (sem acentuações) ");
   scanf(" %[^\n]", responsavel);
   for(i = 0; i < 4; i++){
      for(j = 0; j < qtdIngressos[i]; j++){
         if(!strcmp(ingressos[i][j].responsavel, responsavel)){
            setor = i;
         }
      }
   }
   // Confirmando que foi encontrado o setor, o mesmo é enviado junto com o nome para a funçao que processa a devolucao
   if(setor >= 0){
      return processaDevolucao(setor, responsavel);
   }else{
      printf("\nNome não encontrado\n");
      return 0;
   }
}

// Funcao que faz o processamento da devolucao
int processaDevolucao(int setor, char responsavel[25]){
   struct Ingresso *auxIngressosQueFicarao;
   int i, j = 0, auxConf;
   float saldoADevolver = 0, saldoADevolverCategorias[3], valoresCategorias[3], aux;

   saldoADevolverCategorias[0] = 0;
   saldoADevolverCategorias[1] = 0;
   saldoADevolverCategorias[2] = 0;
   valoresCategorias[0] = valoresIngressos[setor];
   valoresCategorias[1] = valoresIngressos[setor] - (valoresIngressos[setor]*0.5);
   valoresCategorias[2] = valoresIngressos[setor] - (valoresIngressos[setor]*0.25);
   // Para o processamento é criado um vetor auxilar de ingressos que armazenará os ingressos que permanecerão 
   auxIngressosQueFicarao = (struct Ingresso *) malloc(sizeof(struct Ingresso));
   printf("\nConfirma a devolução desses ingressos?\n");
   // Imprime os ingressos a serem devolvidos e armazena o que ficarão na variavel auxiliar
   // manipulacao das variaveis auxiliares a estatisticas
   for(i = 0; i < qtdIngressos[setor]; i++){
      if(!strcmp(ingressos[setor][i].responsavel, responsavel)){
         printf("%i %i %.2f %s\n", ingressos[setor][i].lugar, ingressos[setor][i].idade, ingressos[setor][i].preco, ingressos[setor][i].responsavel);
         aux = ingressos[setor][i].preco;
         saldoADevolver += aux;
         if(aux == valoresCategorias[0]){
            saldoADevolverCategorias[0] += aux;
         }
         else if(aux == valoresCategorias[1]){
            saldoADevolverCategorias[1] += aux;
         }else if(aux == valoresCategorias[2]){
            saldoADevolverCategorias[2] += aux;
         }
      }
      else{
         j++;
         auxIngressosQueFicarao[j-1].lugar = ingressos[setor][i].lugar;
         auxIngressosQueFicarao[j-1].idade = ingressos[setor][i].idade;
         auxIngressosQueFicarao[j-1].preco = ingressos[setor][i].preco;
         strcpy(auxIngressosQueFicarao[j-1].responsavel, ingressos[setor][i].responsavel);
         auxIngressosQueFicarao = (struct Ingresso *) realloc(auxIngressosQueFicarao, (j+1) * sizeof(struct Ingresso));
      }

   }
   // Confirma a devolucão de todos os ingressos relacionados ao nome do responsavel indicado
   printf("1 - sim / 2 - não: ");
   scanf("%i", &auxConf);
   if(auxConf != 1){
      return 0;
   }
   // Se confirmado, o vetor do setor é realocada com a quantidade de ingressos que ficarão
   // a variavel j que é incrementada no laço 'for' acima armazena essa quantidade
   // o nova vetor do setor recebe as informaçoes dos ingressos a NÃO serem devolvidos
   // atualizao informacoes estatisticas
   ingressos[setor] = (struct Ingresso *) realloc(ingressos[setor], j * sizeof(struct Ingresso));
   for(i = 0; i < j; i++){
      ingressos[setor][i].lugar = i+1;
      ingressos[setor][i].idade = auxIngressosQueFicarao[i].idade;
      ingressos[setor][i].preco = auxIngressosQueFicarao[i].preco;
      strcpy(ingressos[setor][i].responsavel, auxIngressosQueFicarao[i].responsavel);
   }
   relatEstat.saldoArrecadado -= saldoADevolver;
   relatEstat.saldoDevolvido += saldoADevolver;
   relatEstat.saldoPorCategoria[0] -= saldoADevolverCategorias[0];
   relatEstat.saldoPorCategoria[1] -= saldoADevolverCategorias[1];
   relatEstat.saldoPorCategoria[2] -= saldoADevolverCategorias[2];
   qtdIngressos[setor] = j;
   free(auxIngressosQueFicarao);
   return 1;
}

// Listagem, funcão que recebe com parametro o setor
void listagem(int setor){
   int i;
   system("cls");
   printf("**************   ");
   switch(setor){
      case 0:
         printf("LISTAGEM SETOR 1 - VIP");
         break;
      case 1:
         printf("LISTAGEM SETOR 2 - Verde");
         break;
      case 2:
         printf("LISTAGEM SETOR 3 - Amarela");
         break;
      case 3:
         printf("LISTAGEM SETOR 4 - Pista");
   }
   printf("   **************\n\n");
   printf("LUGAR\t\tIDADE\t\tPREÇO\t\tRESPONSÁVEL\n");
   for(i = 0; i < qtdIngressos[setor]; i++){
      printf("%i\t\t%i\t\t%.2f\t\t%s\n", ingressos[setor][i].lugar, ingressos[setor][i].idade, ingressos[setor][i].preco, ingressos[setor][i].responsavel);
   }
   printf("\n");
   system("pause");
   system("cls");
}

// funcao para ordenacao da idade e auxiliar na visualizao da maior e menor idade
void ordenacao(int tipo, char **nomes, int op){
   int qtdIdades, i, j, k = 0, houveMudanca = 1, aux, *idades;
   char auxNomes[25];
   // aloca espaco para as variaveis da estrutura de estatisticas e soma a quantidade total de idades
   qtdIdades = qtdIngressos[0] + qtdIngressos[1] + qtdIngressos[2] + qtdIngressos[3];
   idades = (int *) malloc(qtdIdades * sizeof(int));
   // adiciona todas as idades nas variaveis de ordem para serem ordenadas dps
   for(i = 0; i < 4; i++){
      for(j = 0; j < qtdIngressos[i]; j++){
         idades[k] = ingressos[i][j].idade;
         k++;
      }
   }
   // tipo 1 para crescente e tipo 2 para decrescente
   if(tipo == 1){
      // algoritmo padrao de ordenagem
      relatEstat.ordCrescente = (int *) realloc(relatEstat.ordCrescente, qtdIdades * sizeof(int));
      while(houveMudanca){
         houveMudanca = 0;
         for(i = 0; i < qtdIdades-1; i++){
            if(idades[i] > idades[i+1]){
               aux = idades[i];
               idades[i] = idades[i+1];
               idades[i+1] = aux;
               if(nomes){
                  strcpy(auxNomes, nomes[i]);
                  strcpy(nomes[i], nomes[i+1]);
                  strcpy(nomes[i+1], auxNomes);
               }
               houveMudanca = 1;
            }
         }
      }
      for(i = 0; i < qtdIdades; i++){
         relatEstat.ordCrescente[i] = idades[i];
      }
      // se a funcao foi chamada a partir da funcao de maior ou menor idade, exibe a idade respectiva e o nome do responsavel
      if(nomes){
         if(op == 1){
            strcpy(relatEstat.responsavelMaiorIdade, nomes[qtdIdades-1]);
            relatEstat.maiorIdade = relatEstat.ordCrescente[qtdIdades-1];
            printf("\nMaior idade:\n");
            printf("Idade: %i, Responsável: %s\n", relatEstat.maiorIdade, relatEstat.responsavelMaiorIdade);
         }else if(op == 2){
            strcpy(relatEstat.responsavelMenorIdade, nomes[0]);
            relatEstat.menorIdade = relatEstat.ordCrescente[0];
            printf("\nMenor idade:\n");
            printf("Idade: %i, Responsável: %s\n", relatEstat.menorIdade, relatEstat.responsavelMenorIdade);
         }
      }else{
         printf("\nIdades em ordem crescente:\n");
         for(i = 0; i < qtdIdades; i++){
            printf("idade: %i\n", relatEstat.ordCrescente[i]);
         }
      }
   }else if(tipo == 2){
      relatEstat.ordDecrescente = (int *) realloc(relatEstat.ordDecrescente, qtdIdades * sizeof(int));
      while(houveMudanca){
         houveMudanca = 0;
         for(i = 0; i < qtdIdades-1; i++){
            if(idades[i] < idades[i+1]){
               aux = idades[i];
               idades[i] = idades[i+1];
               idades[i+1] = aux;
               houveMudanca = 1;
            }
         }
      }
      printf("\nIdades em ordem descrescente:\n");
      for(i = 0; i < qtdIdades; i++){
         relatEstat.ordDecrescente[i] = idades[i];
         printf("idade: %i\n", relatEstat.ordDecrescente[i]);
      }
   }
   free(idades);
}

// funcao utilitario relatorios
void getSaldo(int op, int categoria){
   switch(op){
      case 1:
         printf("\nSaldo Arrecadado: %.2f\n", relatEstat.saldoArrecadado);
         break;
      case 2:
         printf("\nSaldo Devolvido: %.2f\n", relatEstat.saldoDevolvido);
         break;
      case 3:
         printf("\nSaldo nessa categoria: %.2f\n", relatEstat.saldoPorCategoria[categoria]);
   }
}

// funcao para exibi a maior ou menor idade, chama a funcao crescente e printa
void maiorMenorIdade(int op){
   char **nomes;
   int i, j, k = 0, qtdNomes;
   // quantidade de nomes e aloca espaco na matriz char
   qtdNomes = qtdIngressos[0] + qtdIngressos[1] + qtdIngressos[2] + qtdIngressos[3];
   if(qtdNomes == 0){
     printf("\nNenhum cadastro encontrado!\n");
     return;
   }
   nomes = (char **) malloc(qtdNomes * sizeof(char));
   // armazena todos os nomes na matriz
   for(i = 0; i < 4; i++){
      for(j = 0; j < qtdIngressos[i]; j++){
         nomes[k] = (char *) malloc(25 * sizeof(char));
         strcpy(nomes[k], ingressos[i][j].responsavel);
         k++;
      }
   }
   // chama a funcao ordenacao crescente, passa os nomes e a opcao
   ordenacao(1, nomes, op);
   // limpa o espaco alocado para os nomes
   for(i = 0; i < qtdNomes; i++){
      free(nomes[i]);
   }
   free(nomes);
}

// Funcão que carrega os dados das lista qnd inicia o programa, e salva nelas quando o programa é finalizado
void carregaOuSalvaDados(int op){
   FILE *listagens[4], *relatoriosEstatisticas;
   int i, j, qtdIdades;
   // opcao de carregamento, chamada no inicio do programa
   if(op == 1){
      listagens[0] = fopen("data/LISTAGEM SETOR 1 – VIP.txt", "r");
      listagens[1] = fopen("data/LISTAGEM SETOR 2 – Verde.txt", "r");
      listagens[2] = fopen("data/LISTAGEM SETOR 3 – Amarela.txt", "r");
      listagens[3] = fopen("data/LISTAGEM SETOR 4 – Pista.txt", "r"); 
      valoresIngressos[0] = 100;
      valoresIngressos[1] = 70; 
      valoresIngressos[2] = 70;
      valoresIngressos[3] = 50;
      numLugares[0] = 10; 
      numLugares[1] = 20;
      numLugares[2] = 20;  
      numLugares[3] = 30;
      // leitura dos dados dos arquivos
      for(i = 0; i < 4; i++){
         if(listagens[i] == NULL){
            printf("Não foi possível carregar os arquivos das listas!\n");
            system("pause");
            exit(1);
         }
         qtdIngressos[i] = 0;
         ingressos[i] = (struct Ingresso *) malloc(sizeof(struct Ingresso));
         while(fscanf(listagens[i], "%i %i %f %[^\n]", &ingressos[i][qtdIngressos[i]].lugar, &ingressos[i][qtdIngressos[i]].idade, &ingressos[i][qtdIngressos[i]].preco, &ingressos[i][qtdIngressos[i]].responsavel) != EOF){
            qtdIngressos[i]++;
            ingressos[i] = (struct Ingresso *) realloc(ingressos[i], (qtdIngressos[i]+1) * sizeof(struct Ingresso));
         }
         fclose(listagens[i]);
      }
      // ler as informacoes de saldo no arquivo de relatorio
      // é preciso carregar esses dados especificamente pois eles sao alterados no decorrer da execucao
      relatoriosEstatisticas = fopen("data/Relatorio e Estatisticas.txt", "r");
      relatEstat.saldoArrecadado = 0;
      relatEstat.saldoDevolvido = 0;
      relatEstat.saldoPorCategoria[0] = 0;
      relatEstat.saldoPorCategoria[1] = 0;
      relatEstat.saldoPorCategoria[2] = 0;
      relatEstat.ordCrescente = (int *) malloc(sizeof(int));
      relatEstat.ordDecrescente = (int *) malloc(sizeof(int));
      if(relatoriosEstatisticas == NULL){
         printf("Não foi possível carregar o arquivo de relatório!\n");
         system("pause");
         exit(1);
      }
      while(fscanf(relatoriosEstatisticas, "%f %f %f %f %f", &relatEstat.saldoArrecadado, &relatEstat.saldoDevolvido, &relatEstat.saldoPorCategoria[0], &relatEstat.saldoPorCategoria[1], &relatEstat.saldoPorCategoria[2]) != EOF){
         break;
      }
      fclose(relatoriosEstatisticas);
   }else if(op == 2){ // opcao de salvar os dados, chamada na finalizacao do programa
      // chama as funcoes relacionadas a relatorio para atualizar os dados, dps salva tudo
      qtdIdades = qtdIngressos[0] + qtdIngressos[1] + qtdIngressos[2] + qtdIngressos[3];
      relatoriosEstatisticas = fopen("data/Relatorio e Estatisticas.txt", "w");
      ordenacao(1, NULL, 0);
      ordenacao(2, NULL, 0);
      maiorMenorIdade(1);
      maiorMenorIdade(2);
      system("cls");
      fprintf(relatoriosEstatisticas, "%f %f %f %f %f\n", relatEstat.saldoArrecadado, relatEstat.saldoDevolvido, relatEstat.saldoPorCategoria[0], relatEstat.saldoPorCategoria[1], relatEstat.saldoPorCategoria[2]);
      fprintf(relatoriosEstatisticas, "%s\n\n", "linha acima se encontra respectivamente, o saldo arrecadado, saldo devolvido, saldo ingressos normal, saldo ingressos estudantes, saldo ingressos idosos");
      fprintf(relatoriosEstatisticas, "%s\n", "idade ordem crescente");
      for(i = 0; i < qtdIdades; i++){
         fprintf(relatoriosEstatisticas, "%i\n", relatEstat.ordCrescente[i]);
      }
      fprintf(relatoriosEstatisticas, "%s\n", "idade ordem decrescente");
      for(i = 0; i < qtdIdades; i++){
         fprintf(relatoriosEstatisticas, "%i\n", relatEstat.ordDecrescente[i]);
      }
      fprintf(relatoriosEstatisticas, "%s\n%i %s\n", "maior idade nome responsavel", relatEstat.maiorIdade, relatEstat.responsavelMaiorIdade);
      fprintf(relatoriosEstatisticas, "%s\n%i %s\n", "menor idade nome responsavel", relatEstat.menorIdade, relatEstat.responsavelMenorIdade);
      fclose(relatoriosEstatisticas);
      free(relatEstat.ordCrescente);
      free(relatEstat.ordDecrescente);
      // salvando informacoes dos ingressos
      listagens[0] = fopen("data/LISTAGEM SETOR 1 – VIP.txt", "w");
      listagens[1] = fopen("data/LISTAGEM SETOR 2 – Verde.txt", "w");
      listagens[2] = fopen("data/LISTAGEM SETOR 3 – Amarela.txt", "w");
      listagens[3] = fopen("data/LISTAGEM SETOR 4 – Pista.txt", "w");
      for(i = 0; i < 4; i++){
         for(j = 0; j < qtdIngressos[i]; j++){
            fprintf(listagens[i], "%i %i %f %s\n", ingressos[i][j].lugar, ingressos[i][j].idade, ingressos[i][j].preco, ingressos[i][j].responsavel);
         }
         fclose(listagens[i]);
         free(ingressos[i]);
      }
   }
}
