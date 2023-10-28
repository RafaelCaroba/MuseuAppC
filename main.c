/*arquivo para gravar dados do vendedor*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define max_rec 100
#define max_str_length 50

/*dados que serão solicitados no cadastro*/
struct Record {
    char nome[max_str_length];
    char telefone[max_str_length];
    char email[max_str_length];
    char bairro[max_str_length];
    char cidade[max_str_length];
    char pais[max_str_length];
    char senha[max_str_length];
    /*clientes*/
    char nomeCli[max_str_length];
    char telefoneCli[max_str_length];
    char emailCli[max_str_length];
    char cidadeCli[max_str_length];
};

/*escrever os dados no csv*/
void escreverCSV(FILE *file, struct Record records[], int numRecord){

    int i;
    for (i = 0; i < numRecord; i++){
        fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n",
            records[i].nome,
            records[i].telefone,
            records[i].email,
            records[i].bairro,
            records[i].cidade,
            records[i].pais,
            records[i].senha);

            // records[i].nomeCli,
            // records[i].telefoneCli,
            // records[i].emailCli,
            // records[i].cidadeCli);
    }
}

/*ler dados do csv*/
void lerCSV(FILE *file, struct Record records[], int *numRecord){
    char line[max_str_length * 7]; /*tamanho maximo de uma linha*/
    sscanf(line, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49s",
            records[*numRecord].nome, records[*numRecord].telefone,
            records[*numRecord].email,records[*numRecord].bairro,
            records[*numRecord].cidade, records[*numRecord].pais,
            records[*numRecord].senha, records[*numRecord].nomeCli,
            records[*numRecord].telefoneCli, records[*numRecord].emailCli,
            records[*numRecord].cidadeCli);
    (*numRecord)++;
}


int main() {
    struct Record records[max_rec];

    int numRecord = 0;
    char buscaEmail[max_str_length];
    char buscaSenha[max_str_length];

    printf("/////////////////////////////////////////////////////////////\n\n");

    printf("Bem vindos ao museu multimidia sobre o centenario da disney!!\n\n");

    printf("////////////////////////////////////////////////////////////////\n\n");
    printf("Como deseja proseguir?\n\n");



    /*carrega os dados do csv ao iniciar o código*/
    FILE *file = fopen("info.csv" , "r");
    if (file != NULL){/*basicamente pra ver se o csv esta funciondo, onde ai diz se diferente de 0/null/negativo/desligado*/
        lerCSV(file, records, &numRecord);
        fclose(file);
    }

    while(1){
        printf("Escolha uma opção:\n");
        printf("1. Quero me tornar vendedor\n");
        printf("2. Já sou vendedor cadastrado\n");
        printf("3. Comprar ingresso\n");
        printf("4. Entrar na apresentação");
        printf("5. Listar clientes cadastrados\n");
        printf("6. Listar funcionários cadastrados\n");
        printf("7. Editar registro funcionário\n");
        printf("8. Editar registro cliente\n");
        printf("9. Salvar dados no arquivo\n");
        printf("10. Sair\n");

        int escolha;
        scanf("%d", &escolha);

        /*fflush(stdin);*/ /*verificar diferença*/
        while(getchar() != '\n'); /*limpa buffer do teclado*/

        switch (escolha){
            case 1:
            /*Fazer cadastro funcionário*/
                // file = fopen("info.csv", "w");
                // escreverCSV("info.csv", records, numRecord);
                if(numRecord < max_rec){
                    /*talez adicionar a solicitação de algum documento*/
                    printf("Digite seu nome: ");
                    fgets(records[numRecord].nome, sizeof(records[numRecord].nome), stdin);
                    records[numRecord].nome[strcspn(records[numRecord].nome, "\n")] = '\0';/*remove quebra de linha // strcspn calcula tamanho do segmento inicial*/

                    printf("Digite seu telefone:");
                    fgets(records[numRecord].telefone, sizeof(records[numRecord].telefone), stdin);
                    records[numRecord].telefone[strcspn(records[numRecord].telefone, "\n")] = '\0';

                    printf("Digite seu email:");
                    fgets(records[numRecord].email, sizeof(records[numRecord].email), stdin);
                    records[numRecord].email[strcspn(records[numRecord].email, "\n")] = '\0';

                    printf("Digite seu bairro:");
                    fgets(records[numRecord].bairro, sizeof(records[numRecord].bairro), stdin);
                    records[numRecord].bairro[strcspn(records[numRecord].bairro, "\n")] = '\0';

                    printf("Digite sua cidade:");
                    fgets(records[numRecord].cidade, sizeof(records[numRecord].cidade), stdin);
                    records[numRecord].cidade[strcspn(records[numRecord].cidade, "\n")] = '\0';

                    printf("Digite seu país:");
                    fgets(records[numRecord].pais, sizeof(records[numRecord].pais), stdin);
                    records[numRecord].pais[strcspn(records[numRecord].pais, "\n")] = '\0';

                    printf("Digite sua senha:");
                    fgets(records[numRecord].senha, sizeof(records[numRecord].senha), stdin);
                    records[numRecord].senha[strcspn(records[numRecord].senha, "\n")] = '\0';

                    puts("\n\n");

                    numRecord ++;
                }
                else{
                    printf("numero de cadastros máximo atingido");
                }
            break;

            case 2:
                /*fazer login*/
                file = fopen("info.csv", "r");
                printf("Digite seu email:");
                fgets(buscaEmail, sizeof(buscaEmail), stdin);
                buscaEmail[strspn(buscaEmail, "\n")] = '\0';
                printf(buscaEmail);
                printf("Digite sua senha:");
                fgets(buscaSenha, sizeof(buscaSenha), stdin);
                buscaSenha[strspn(buscaSenha, "\n")] = '\0';

                int i;
                for (i = 0; i < numRecord; i++) {
                    if(strcmp(records[i].email, buscaEmail) == 0){
                        printf(buscaEmail);
                        if(strcmp(records[i].senha, buscaSenha) == 0){
                            /*ir para pagina de cadastro de cliente*/
                            printf("ok, FUNCIONA!!!\n\n");
                            break;
                        }
                        else{
                            printf("Senha incorreta\n");

                        }
                    }
                    else{
                        printf("Email não cadastrado\n\n\n");
                    }
                }
            break;

            case 3:
                /*cadastro cliente*/
                /*duvida se precisaria criar outra base struct ou se melhor linkar com outro
                codigo essa parte ou somente criar outra base csv*/
                file = fopen("info.csv", "w");
                if(numRecord < max_rec){
                    /*talez adicionar a solicitação de algum documento*/
                    printf("Digite seu nome: ");
                    fgets(records[numRecord].nomeCli, sizeof(records[numRecord].nomeCli), stdin);
                    records[numRecord].nomeCli[strcspn(records[numRecord].nomeCli, "\n")] = '\0';/*remove quebra de linha // strcspn calcula tamanho do segmento inicial*/

                    printf("Digite seu telefone:");
                    fgets(records[numRecord].telefoneCli, sizeof(records[numRecord].telefoneCli), stdin);
                    records[numRecord].telefoneCli[strcspn(records[numRecord].telefoneCli, "\n")] = '\0';

                    printf("Digite seu email:");
                    fgets(records[numRecord].emailCli, sizeof(records[numRecord].emailCli), stdin);
                    records[numRecord].emailCli[strcspn(records[numRecord].emailCli, "\n")] = '\0';

                    printf("Digite sua cidade:");
                    fgets(records[numRecord].cidadeCli, sizeof(records[numRecord].cidadeCli), stdin);
                    records[numRecord].cidadeCli[strcspn(records[numRecord].cidadeCli, "\n")] = '\0';

                    numRecord ++;
                }

                printf("Deseja um ingresso para qual horário?\n");

                int horario;

                printf("Sessões diponiveis: \n 1. 9hrs \n 2. 12 hrs \n 3. 16 hrs \n 4. 20 hrs\n");
                scanf("%d", &horario);

                switch (horario)
                {
                case 1:
                    printf("Ingresso selecionado para as 9 hrs.\n");
                    break;

                case 2:
                    printf("Ingresso selecionado para as 12 hrs.\n");
                break;

                case 3:
                    printf("Ingresso selecionado para as 16 hrs\n");
                break;

                case 4:
                    printf("Ingresso selecionado para as 20 hrs\n");
                break;

                default:
                    printf("Essa opção não esta dísponivel.\n");
                break;
                }

                int entrada;

                printf("Gostaria de uma entrada:\n 1. inteira\n 2. meia\n");
                scanf("%d", &entrada);

                printf("Aqui esta o código do seu ticket %d\n", rand());
            break;
           case 4:

                printf("Digite o código do seu ticket:\n");

                float ticket;

                scanf("%f", &ticket);

                printf("ok, ingresso validado\n");
                printf("Aproveite sua sessão.\n");

                printf("//////////////////////////////////////////////////////////////\n");

                printf("Bem vindo(a) a nossa exposição sobre o centenário da Disney!!\n");

                printf("////////////////////////////////////////////////////////////////");

            break;

            case 5:
                /*lista de clientes*/
                /*talvez adicionar uma forma de login de administrador para acesso deste caso*/
            break;

            case 6:
                /*lista funcionários*/
                /*talvez adicionar uma forma de login de administrador para acesso deste caso*/

                if(numRecord > 0){
                    int i;
                    for(i = 1; i < numRecord; i++){
                        printf("Cadastro %d:\n", i);
                        printf("Nome: %s\n", records[i].nome);
                        printf("Telefone: %s\n", records[i].telefone);
                        printf("Email: %s\n", records[i].email);
                        printf("Bairro: %s\n", records[i].bairro);
                        printf("Cidade: %s\n", records[i].cidade);
                        printf("Pais: %s\n", records[i].pais);
                        printf("Senha: %s\n", records[i].senha);
                        printf("\n");
                    }
                }
                else{
                    printf("Nenhum registro encontrado.\n");
                }
            case 7:

                /*editar dados funcionários*/
                /*talvez adicionar uma forma de login de administrador para acesso deste caso*/

            break;
            case 8:

                /*editar dados clientes*/
                /*talvez adicionar uma forma de login de administrador para acesso deste caso*/

            break;

            case 9:
                /*salvar arquivo*/
                printf("Estou aqui!");
                file = fopen("info.csv", "w");
                if (file != NULL){
                    printf("Agora aqui!");
                    escreverCSV(file, records, numRecord);
                    fclose(file);
                    printf("Dados salvos no arquivo 'info.csv'.\n");
                }
                else{
                    printf("Erro ao abrir o arquivo para salvar os dados.");
                }

            break;

            case 10:

                /*sair sem salvar*/
                return 0;

            break;

            default:

            break;
        }

    }

    return 0;
}

