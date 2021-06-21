# Bem vindo!

## Como instalar
Para rodar esse programa é necessário ter o compilador c instalado e configurado em sua máquina!<br>
Extraia os arquivos em uma pasta, abra o terminal dentro da mesma e digite o comando "gcc main.c programa.c -o programa", será gerado um arquivo executável "programa.exe".<br>
Um outra forma de executar é configurando um projeto em uma ide como o devc++.<br>
**Não tente compilar o arquivo "main.c" ou "programa.c" isoladamente, os dois precisam ser compilados simultaneamente!**

## Funcionalidades
* Compra<br>
Será solicitado o setor, a quantidade de ingressos, se a quantidade estiver disponível prossegue a solicitação. Logo depois de verificada a disponibilidade, é solicitado ao usuario a informação de quantos desses ingressos serão para idosos e estudantes, os mesmos terão desconto de 25% e 50% respectivamente.
* Devolução<br>
Será solicitado o nome do responsável pela compra, todos os ingressos comprados por esse responsável será devolvido.
* Listagem de lugares<br>
Será solicitado o setor, irá mostrar a lista de ingressos vendidos nesse setor.
* Relatorio e Estatisticas<br>
Um menu será exibido com as opção, são elas: impressão em ordem crescente ou decrescente das idades, maior ou menor idade e nome do responsável pela compra, saldo total arrecadado, saldo devolvido, saldo por categoria (normal, idoso, estudante).

Quando solicitada a finalização do programa, todas informação são salvas em arquivos .txt, essas mesmos arquivos são carregados na inicialização do programa para que os dados possam ser recuperados.
