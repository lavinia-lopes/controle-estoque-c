#include<stdio.h>

struct Dados {
    char livro[50];
    char autor[50];
    float preco;
    int quantidade;
};

void limpa_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int Compara(char *s1, char *s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if(s1[i] != s2[i]){
            return 0;
        }
        i++;
    }
    if(s1[i] == '\0' && s2[i] == '\0'){
            return 1;
    }
    return 0;
}

void Entrada_Dados(struct Dados *pReg) {
    char nome_temp[50];
    FILE *arquivo;
    int existe = 0;
    int i;

    printf("\n\n------------------------------------------------------------------------------------------------------\n\n");
    printf("1. ENTRADA DE DADOS\n");
    printf("Nome do Livro: ");
    scanf(" %49[^\n]", nome_temp);
    limpa_buffer();


    if(existe){
        printf("\nERRO: Ja existe um livro com este nome!\n");
        printf("\nPressione <ENTER> para voltar ao menu");
        getchar();
        return;
    }

    arquivo = fopen("livros.dat", "ab");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para gravacao!\n");
        return;
    }


    i = 0;
    while(nome_temp[i] != '\0' && i < 49){
        pReg->livro[i] = nome_temp[i];
        i++;
    }
    pReg->livro[i] = '\0'; // Garante o terminador nulo

    for(int j = i + 1; j < 50; j++) {
        pReg->livro[j] = '\0';
    }

    printf("Nome do Autor: ");
    scanf(" %49[^\n]", pReg->autor);
    limpa_buffer();

    printf("Preco: ");
    scanf("%f", &pReg->preco);
    limpa_buffer();

    printf("Quantidade: ");
    scanf("%d", &pReg->quantidade);
    limpa_buffer();

    fwrite(pReg, sizeof(struct Dados), 1, arquivo);
    fclose(arquivo);

    printf("\nRegistro gravado com sucesso!\n");
    printf("\nPressione <ENTER> para voltar ao menu");
    getchar();
}

void Lista_Livros(struct Dados *pReg){
    FILE *arquivo;
    int cont = 0;

    printf("\n\n------------------------------------------------------------------------------------------------------\n\n");
    printf("2. LISTA TODOS OS LIVROS\n");

    arquivo = fopen("livros.dat", "rb");

    if (arquivo != NULL) {
        while (fread(pReg, sizeof(struct Dados), 1, arquivo)) {
            if (pReg->livro[0] != '*') {
                printf("\nLivro: %s", pReg->livro);
                printf("\nAutor: %s", pReg->autor);
                printf("\nPreco: R$ %.2f", pReg->preco);
                printf("\nQtd:   %d\n", pReg->quantidade);
                printf("\n------------------------------------------------------------------------------------------------------");
                cont++;
            }
        }
        fclose(arquivo);
    }
    if(cont == 0){
        printf("\nNenhum registro ativo encontrado.\n");
    }
    printf("\nPressione <ENTER> para voltar ao menu");
    getchar();
}

void Pesquisa_Livro(struct Dados *pReg){
    char busca[50];
    int achou = 0;
    FILE *arquivo;

    printf("\n\n------------------------------------------------------------------------------------------------------\n\n");
    printf("3. PESQUISAR POR NOME COMPLETO\n");

    printf("Digite o nome exato do livro: ");
    scanf(" %49[^\n]", busca);
    limpa_buffer();

    arquivo = fopen("livros.dat", "rb");

    if (arquivo != NULL) {
        while (fread(pReg, sizeof(struct Dados), 1, arquivo)) {
            if (pReg->livro[0] != '*' && Compara(pReg->livro, busca)) {
                printf("\n--- REGISTRO ENCONTRADO ---\n");
                printf("Livro: %s", pReg->livro);
                printf("\nAutor: %s", pReg->autor);
                printf("\nPreco: R$ %.2f", pReg->preco);
                printf("\nQtd:   %d\n", pReg->quantidade);
                achou = 1;
                break;
            }
        }
        fclose(arquivo);
    }

    if(!achou){
        printf("\nLivro nao encontrado.\n");
    }
    printf("\nPressione <ENTER> para voltar ao menu");
    getchar();
}

void Pesquisa_Autor(struct Dados *pReg) {
    char letra;
    int achou = 0;
    FILE *arquivo;

    printf("\n\n------------------------------------------------------------------------------------------------------\n\n");
    printf("4. PESQUISAR POR INICIAL DO AUTOR\n");

    printf("Digite a primeira letra do autor: ");
    scanf("%c", &letra);
    limpa_buffer();

    arquivo = fopen("livros.dat", "rb");

    if (arquivo != NULL) {
        printf("\n--- AUTORES ENCONTRADOS ---\n");
        while (fread(pReg, sizeof(struct Dados), 1, arquivo)) {
            if (pReg->livro[0] != '*' && pReg->autor[0] == letra) {
                printf("\nLivro: %s | Autor: %s", pReg->livro, pReg->autor);
                achou = 1;
            }
        }
        fclose(arquivo);
    }

    if(!achou){
    printf("\nNenhum autor com a letra '%c' encontrado.\n", letra);
    }
    printf("\nPressione <ENTER> para voltar ao menu");
    getchar();
}

void Faixa_de_Preco(struct Dados *pReg) {
    float min, max;
    int achou = 0;
    FILE *arquivo;

    printf("\n\n------------------------------------------------------------------------------------------------------\n\n");
    printf("5. PESQUISAR POR FAIXA DE PRECO\n");

    printf("Preco Minimo: ");
    scanf("%f", &min);
    limpa_buffer();

    printf("Preco Maximo: ");
    scanf("%f", &max);
    limpa_buffer();

    arquivo = fopen("livros.dat", "rb");

    if(arquivo != NULL){
        printf("\n--- LIVROS NA FAIXA DE R$ %.2f a R$ %.2f ---\n", min, max);
        while(fread(pReg, sizeof(struct Dados), 1, arquivo)){
            if(pReg->livro[0] != '*' && pReg->preco >= min && pReg->preco <= max){
                printf("\nLivro: %s | Preco: R$ %.2f", pReg->livro, pReg->preco);
                achou = 1;
            }
        }
        fclose(arquivo);
    }

    if(!achou){
    printf("\nNenhum livro nesta faixa de preco.\n");
    }
    printf("\nPressione <ENTER> para voltar ao menu");
    getchar();
}

void Altera_Quantidade(struct Dados *pReg, FILE *fp){
    char busca[50];
    char op;
    int valor, achou = 0;

    printf("\n\n------------------------------------------------------------------------------------------------------\n\n");
    printf("6. ALTERAR QUANTIDADE\n");

    printf("Nome do livro: ");
    scanf(" %49[^\n]", busca);
    limpa_buffer();

    fseek(fp, 0, SEEK_SET);

    while(fread(pReg, sizeof(struct Dados), 1, fp)){
        if(pReg->livro[0] != '*' && Compara(pReg->livro, busca)){
            achou = 1;
            printf("\nAtual: %d unidades.", pReg->quantidade);
            printf("\nDigite (+) para entrada ou (-) para saida: ");
            scanf(" %c", &op);
            limpa_buffer();
            printf("Digite a quantidade: ");
            scanf("%d", &valor);
            limpa_buffer();

            if(op == '+'){
                pReg->quantidade += valor;
            }else if(op == '-'){
                pReg->quantidade -= valor;
                if (pReg->quantidade < 0) pReg->quantidade = 0;
            }

            fseek(fp, -((long)sizeof(struct Dados)), SEEK_CUR);
            fwrite(pReg, sizeof(struct Dados), 1, fp);
            printf("\nEstoque atualizado!\n");
            break;
        }
    }
    if(!achou){
    printf("\nLivro nao encontrado.\n");
    }
    printf("\nPressione <ENTER> para voltar ao menu");
    getchar();
}

void Altera_Preco(struct Dados *pReg, FILE *fp) {
    char busca[50];
    int achou = 0;

    printf("\n\n------------------------------------------------------------------------------------------------------\n\n");
    printf("7. ALTERAR PRECO\n");

    printf("Nome do livro: ");
    scanf(" %49[^\n]", busca);
    limpa_buffer();
    fseek(fp, 0, SEEK_SET);

    while(fread(pReg, sizeof(struct Dados), 1, fp)) {
        if(pReg->livro[0] != '*' && Compara(pReg->livro, busca)){
            achou = 1;
            printf("\nPreco Atual: R$ %.2f", pReg->preco);
            printf("\nNovo Preco: ");
            scanf("%f", &pReg->preco);
            limpa_buffer();

            fseek(fp, -((long)sizeof(struct Dados)), SEEK_CUR);
            fwrite(pReg, sizeof(struct Dados), 1, fp);
            printf("\nPreco atualizado!\n");
            break;
        }
    }
    if(!achou){
    printf("\nLivro nao encontrado.\n");
    }
    printf("\nPressione <ENTER> para voltar ao menu");
    getchar();
}

void Altera_Tudo(struct Dados *pReg, FILE *fp) {
    char busca[50];
    int achou = 0;

    printf("\n\n------------------------------------------------------------------------------------------------------\n\n");
    printf("8. ALTERAR TODOS OS DADOS\n");

    printf("Nome do livro a ser alterado: ");
    scanf(" %49[^\n]", busca);
    limpa_buffer();

    fseek(fp, 0, SEEK_SET);

    while(fread(pReg, sizeof(struct Dados), 1, fp)){
        if(pReg->livro[0] != '*' && Compara(pReg->livro, busca)){
            achou = 1;

            printf("\n-- Novos Dados --\n");

            printf("Novo Nome do Livro: ");
            scanf(" %49[^\n]", pReg->livro);
            limpa_buffer();

            printf("Novo Autor: ");
            scanf(" %49[^\n]", pReg->autor);
            limpa_buffer();

            printf("Novo Preco: ");
            scanf("%f", &pReg->preco);
            limpa_buffer();

            printf("Nova Quantidade: ");
            scanf("%d", &pReg->quantidade);
            limpa_buffer();

            fseek(fp, -((long)sizeof(struct Dados)), SEEK_CUR);
            fwrite(pReg, sizeof(struct Dados), 1, fp);
            printf("\nRegistro atualizado completamente!\n");
            break;
        }
    }
    if (!achou){
    printf("\nLivro nao encontrado.\n");
    }
    printf("\nPressione <ENTER> para voltar ao menu");
    getchar();
}

void Excluir(struct Dados *pReg, FILE *fp) {
    char busca[50];
    char confirmacao;
    int achou = 0;

    printf("\n\n------------------------------------------------------------------------------------------------------\n\n");
    printf("9. EXCLUSAO LOGICA\n");

    printf("Nome do livro a excluir: ");
    scanf(" %49[^\n]", busca);
    limpa_buffer();
    fseek(fp, 0, SEEK_SET);

    while(fread(pReg, sizeof(struct Dados), 1, fp)){
        if(pReg->livro[0] != '*' && Compara(pReg->livro, busca)){
            achou = 1;
            printf("\nLivro encontrado: %s", pReg->livro);
            printf("\nTem certeza? (S/N): ");
            scanf(" %c", &confirmacao);
            limpa_buffer();

            if(confirmacao == 'S' || confirmacao == 's'){
                pReg->livro[0] = '*';
                fseek(fp, -((long)sizeof(struct Dados)), SEEK_CUR);
                fwrite(pReg, sizeof(struct Dados), 1, fp);
                printf("\nLivro excluido logicamente.\n");
            }else{
                printf("\nOperacao cancelada.\n");
            }
            break;
        }
    }
    if(!achou){
    printf("\nLivro nao encontrado.\n");
    }
    printf("\nPressione <ENTER> para voltar ao menu");
    getchar();
}

int main() {
  struct Dados registro;
  FILE *arquivo = NULL;
  int op;

    arquivo = fopen("livros.dat", "rb+");
    if(arquivo == NULL){
        arquivo = fopen("livros.dat", "wb+");
        if(arquivo == NULL){
            printf("Erro ao abrir arquivo.\n");
            return 1;
        }
    }

    do{
        printf("\n\n------------------------------------------------------------------------------------------------------\n\n");
        printf("CONTROLE DE ESTOQUE DE LIVROS\n");
        printf("1. ENTRADA DE DADOS\n");
        printf("2. LISTA TODOS OS LIVROS\n");
        printf("3. PESQUISAR POR NOME COMPLETO\n");
        printf("4. PESQUISAR POR INICIAL DO AUTOR\n");
        printf("5. PESQUISAR POR FAIXA DE PRECO\n");
        printf("6. ALTERAR QUANTIDADE\n");
        printf("7. ALTERAR PRECO\n");
        printf("8. ALTERAR TODOS OS DADOS\n");
        printf("9. EXCLUSAO LOGICA\n");
        printf("10. SAIR\n");
        printf("Opcao: ");
        scanf("%d", &op);
        limpa_buffer();

        switch (op) {
            case 1:
                Entrada_Dados(&registro);
                break;
            case 2:
                Lista_Livros(&registro);
                break;
            case 3:
                Pesquisa_Livro(&registro);
                break;
            case 4:
                Pesquisa_Autor(&registro);
                break;
            case 5:
                Faixa_de_Preco(&registro);
                break;
            case 6:
                Altera_Quantidade(&registro, arquivo);
                fclose(arquivo);
                arquivo = fopen("livros.dat", "rb+");
                if(arquivo == NULL){
                printf("Erro de reabertura!");
                return 1;
                }
                break;
            case 7:
                Altera_Preco(&registro, arquivo);
                fclose(arquivo);
                arquivo = fopen("livros.dat", "rb+");
                if(arquivo == NULL){
                printf("Erro de reabertura!");
                return 1;
                }
                break;
            case 8:
                Altera_Tudo(&registro, arquivo);
                fclose(arquivo);
                arquivo = fopen("livros.dat", "rb+");
                if(arquivo == NULL){
                printf("Erro de reabertura!");
                return 1;
                }
                break;
            case 9:
                Excluir(&registro, arquivo);
                fclose(arquivo);
                arquivo = fopen("livros.dat", "rb+");
                if(arquivo == NULL){
                printf("Erro de reabertura!");
                return 1;
                }
                break;
            case 10:
                printf("\nPrograma Finalizado\n");
                break;
            default:
                printf("\nOpcao invalida!\n");

        printf("\nPressione <ENTER> para voltar ao menu");
        getchar();
        }

    }while(op != 10);

    if (arquivo != NULL) {
        fclose(arquivo);
    }
    return 0;
}
