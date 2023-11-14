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
};

struct clientes {
    char nomeCli[max_str_length];
    char telefoneCli[max_str_length];
    char emailCli[max_str_length];
    char cidadeCli[max_str_length];
    int numeroTicket[max_str_length];
    int horarioSessao[max_str_length];
    int tipoIngresso[max_str_length];
};

/*escrever os dados no csv*/
void escreverCSV(FILE *file, struct Record records[], int numRecord){
    for (int i = 0; i < numRecord; i++){
        fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n",
            records[i].nome, records[i].telefone,
            records[i].email, records[i].bairro,
            records[i].cidade, records[i].pais,
            records[i].senha);
    }
}

/*ler dados do csv*/
void lerCSV(FILE *file, struct Record records[], int *numRecord){
    char line[max_str_length * 7]; /*tamanho maximo de uma linha*/
    sscanf(line, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,]%49[^,],%49s",
            records[*numRecord].nome, records[*numRecord].telefone,
            records[*numRecord].email,records[*numRecord].bairro, 
            records[*numRecord].cidade, records[*numRecord].pais, 
            records[*numRecord].senha,

    (*numRecord)++);
}

void escreverCSVCli(FILE *file2, struct clientes dados[], int *numDados){
    for (int i = 0; i < numDados; i++){
        fprintf(file2, "%s,%s,%s,%s,%s,%s,%s\n", 
        dados[i].nomeCli, dados[i].emailCli, dados[i].cidadeCli,
        dados[i].telefoneCli, dados[i].numeroTicket, dados[i].horarioSessao,
        dados[i].tipoIngresso);
    }
}

void lerCSVCli(FILE *file2, struct clientes dados[], int *numDados){
    char linha[max_str_length * 7];
    sscanf(linha, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49s", 
        dados[*numDados]. nomeCli, dados[*numDados].emailCli, dados[*numDados].cidadeCli,
        dados[*numDados].telefoneCli, dados[*numDados].numeroTicket, dados[*numDados].horarioSessao,
        dados[*numDados].tipoIngresso,
        
    (*numDados)++);
}


int main() {
    struct Record records[max_rec];
    struct clientes dados[max_rec];
    
    int numRecord = 0;
    int numDados = 0;
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

    FILE *file2 = fopen("infoCli.csv" , "r");
    if(file2 != NULL){
        lerCSVCli(file2, dados, &numDados);
        fclose(file2);
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
                file = fopen("info.csv", "w"); 
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

                    numRecord ++;
                }
                else{
                    printf("numero de cadastros máximo atingido");
                }
                fclose(file);
            break;

            case 2:
                /*fazer login*/
                file = fopen("info.csv", "r");
                printf("Digite seu email:");
                fgets(buscaEmail, sizeof(buscaEmail), stdin);
                buscaEmail[strspn(buscaEmail, "\n")] = '\0';

                printf("Digite sua senha:");
                fgets(buscaSenha, sizeof(buscaSenha), stdin);
                buscaSenha[strspn(buscaSenha, "\n")] = '\0';

                for (int i = 0; i < numRecord; i++) {
                    if(strcmp(records[i].email, buscaEmail) == 0){
                        printf(buscaEmail);
                        if(strcmp(records[i].senha, buscaSenha) == 0){
                            /*ir para pagina de cadastro de cliente*/
                            printf("ok");
                        }
                        else{
                            printf("Senha incorreta\n");
                        }
                    }
                    else{
                        printf("Email não cadastrado\n");
                    }
                }
            break;

            case 3:
                /*cadastro cliente*/
                /*duvida se precisaria criar outra base struct ou se melhor linkar com outro
                codigo essa parte ou somente criar outra base csv*/

                file = fopen("infoCli.csv", "w"); 
                if(numDados < max_rec){
                    /*talez adicionar a solicitação de algum documento*/
                    printf("Digite seu nome: ");
                    fgets(dados[numDados].nomeCli, sizeof(dados[numDados].nomeCli), stdin);
                    dados[numDados].nomeCli[strcspn(dados[numDados].nomeCli, "\n")] = '\0';/*remove quebra de linha // strcspn calcula tamanho do segmento inicial*/

                    printf("Digite seu telefone:");
                    fgets(dados[numDados].telefoneCli, sizeof(dados[numDados].telefoneCli), stdin);
                    dados[numDados].telefoneCli[strcspn(dados[numDados].telefoneCli, "\n")] = '\0';

                    printf("Digite seu email:");
                    fgets(dados[numDados].emailCli, sizeof(dados[numDados].emailCli), stdin);
                    dados[numDados].emailCli[strcspn(dados[numDados].emailCli, "\n")] = '\0';

                    printf("Digite sua cidade:");
                    fgets(dados[numDados].cidadeCli, sizeof(dados[numDados].cidadeCli), stdin);
                    dados[numDados].cidadeCli[strcspn(dados[numDados].cidadeCli, "\n")] = '\0';

                    numDados++;
                }

                printf("Deseja um ingresso para qual horário?\n");

                printf("Sessões diponiveis: \n 1. 9hrs \n 2. 12 hrs \n 3. 16 hrs \n 4. 20 hrs\n");
                fgets(dados[numDados].horarioSessao, sizeof(dados[numDados].horarioSessao), stdin);
                    dados[numDados].horarioSessao[strcspn(dados[numDados].horarioSessao, "\n")] = '\0';

                int horario;

                horario = horarioSessao; //pensei em de alguma forma colocar um ponteiro para poder usar de parametro

                switch (horario) //descobrir forma de puxar o dado do fgets
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
                fgets(dados[numDados].tipoIngresso, sizeof(dados[numDados].tipoIngresso), stdin);
                    dados[numDados].tipoIngresso[strcspn(dados[numDados].tipoIngresso, "\n")] = '\0';

                switch ()
                {
                case 1:
                    printf("Você escolheu entrada inteira");
                break;
                case 2:
                    printf("Você escolheu entreda meia");
                break;
                }

                printf("Aqui esta o código do seu ticket %d\n", rand());

                fclose("infoCli.csv");

            break;
           case 4:               

                printf("Digite o código do seu ticket:\n");

                float ticket;
                
                scanf("%f", &ticket);

                printf("ok, ingresso validado\n");
                printf("Aproveite sua sessão.\n");

                printf("/////////////////////////////////////////////////////////////////\n");

                printf("Bem vindo(a) a nossa exposição sobre o centenário da Disney!!\n");

                printf("/////////////////////////////////////////////////////////////////");

            break;

            case 5:     
                /*lista de clientes*/
                /*talvez adicionar uma forma de login de administrador para acesso deste caso*/
            break;

            case 6:
                /*lista funcionários*/
                /*talvez adicionar uma forma de login de administrador para acesso deste caso*/
                file = fopen("info.csv", "r");
                if(numRecord > 0){
                    for(int i = 1; i < numRecord; i++){
                        printf("Cadastro %d:\n", i + 1);
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
                file = fopen("info.csv", "w");
                if (file != NULL){
                    escreverCSV(file, records, numRecord);
                    fclose(file);
                    printf("Dados salvos no arquivo 'info.csv'.\n");
                }
                else{
                    printf("Erro ao abrir o arquivo para salvar os dados de funcionarios.");
                }

                file2 = fopen("infoCli.csv", "w");
                if (file2 != NULL){
                    escreverCSVCli(file2, dados, numDados);
                    fclose(file2);
                    printf("Dados salvos no arquivo 'infoCli.csv'.\n");
                }
                else{
                    printf("Erro em salvar dados de clientes");
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

