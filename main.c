#include <stdio.h>
#include <locale.h>
#include "./programa.h"

int main(int argc, char const *argv[]){
   setlocale(LC_ALL,"");
   int op = 0, op2 = 0, op3 = 0;
   carregaOuSalvaDados(1);
   printf("=-=-= Bem Vindo! =-=-=\n\n");
   while(op != 5){
      printf("1 - Compra\n");
      printf("2 - Devolução\n");
      printf("3 - Lista de lugares\n");
      printf("4 - Relatórios e estatísticas\n");
      printf("5 - Finalizar\n\n");
      printf("Digite o número correspondente a opção desejada: ");
      scanf( "%i", &op);
      system("cls");
      switch(op){
         case 1:
            printf("=-=-= Compras =-=-=\n\n");
            printf("1 - Setor 1 - VIP\n");
            printf("2 - Setor 2 - Verde\n");
            printf("3 - Setor 3 - Amarela\n");
            printf("4 - Setor 4 - Pista\n");
            printf("5 - Para voltar\n\n");
            printf("Digite o numero correspondente ao setor desejado: ");
            scanf( "%i", &op2);
            if((op2 > 0) && (op2 < 5)){
               compra(op2-1);
            }else if(op2 != 5){
               printf("\nSetor Inválido!\n");
            }
            break;
         case 2:
            printf("=-=-= Devolução =-=-=\n\n");
            if(devolucao()){
               printf("Devolução processada com sucesso!\n");
            }else{
               printf("Devolução não processada!\n");
            }
            break;
         case 3:
            printf("=-=-= Listagem =-=-=\n\n");
            printf("1 - Setor 1 - VIP\n");
            printf("2 - Setor 2 - Verde\n");
            printf("3 - Setor 3 - Amarela\n");
            printf("4 - Setor 4 - Pista\n");
            printf("5 - Para voltar\n\n");
            printf("Digite o número correspondente ao setor desejado: ");
            scanf( "%i", &op2);
            if((op2 > 0) && (op2 < 5)){
               listagem(op2-1);
            }else if(op2 != 5){
               printf("\nSetor Inválido!\n");
            }
            break;
         case 4: 
            printf("=-=-= Relatórios =-=-=\n\n");
            printf("1 - Ordem crescente e decrescente das idades\n");
            printf("2 - Maior e menor idade\n");
            printf("3 - Saldo Arrecadado\n");
            printf("4 - Saldo Devolvido\n");
            printf("5 - Saldo por categoria\n");
            printf("6 - Para voltar\n\n");
            printf("Digite o número correspondente a opção: ");
            scanf("%i", &op2);
            if((op2 > 0) && (op2 < 6)){
               switch(op2){
                  case 1:
                     printf("Digite 1 para crescente ou 2 para decrescente: ");
                     scanf("%i", &op3);
                     if((op3 > 0) && (op3 < 3)){
                        ordenacao(op3, NULL, 0);
                     }else{
                        printf("\nOpção inválida!\n");
                     }
                     break;
                  case 2:
                     printf("Digite 1 para maior idade ou 2 para menor: ");
                     scanf("%i", &op3);
                     if((op3 > 0) && (op3 < 3)){
                        maiorMenorIdade(op3);
                     }else{
                        printf("\nOpção inválida!\n");
                     }
                     break;
                  case 3:
                     getSaldo(1, 0);
                     break;
                  case 4:
                     getSaldo(2, 0);
                     break;
                  case 5:
                     printf("Escolha a categoria: (1 - normal, 2 - estudante, 3 - idoso) ");
                     scanf("%i", &op3);
                     if((op3 > 0) && (op3 < 4)){
                        getSaldo(3,op3-1);
                     }else{
                        printf("\nCategoria inválida!\n");
                     }
               }
            }else if(op2 != 6){
               printf("\nOpção inválida!\n");
            }
            break;
         case 5: 
            carregaOuSalvaDados(2);
            printf("Obrigado por utilizar nosso programa!\n\n");
            break;
         default:
            printf("Opcao inválida\n");
      }
   }
   system("pause");
   return 0;
}
