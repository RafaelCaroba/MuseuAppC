/*arquivo para gravar dados do vendedor*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //manipular strings
#include <locale.h> //definir idioma
#include <time.h> //definir horário
#include <stdbool.h> //usar expressôes booleanas //usada para validar os tickets

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
    float numeroTicket;
    int horarioSessao;
    int tipoIngresso;
    int genero;
    int idade;
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

void escreverCSVCli(FILE *file2, struct clientes dados[], int numDados){
    for (int i = 0; i < numDados; i++){
        fprintf(file2, "%s,%s,%s,%s,%f,%d,%d,%d,%d\n",
        dados[i].nomeCli, dados[i].emailCli, dados[i].cidadeCli,
        dados[i].telefoneCli, dados[i].numeroTicket, dados[i].horarioSessao,
        dados[i].tipoIngresso, dados[i].genero,  dados[i].idade);
    }
}

void lerCSVCli(FILE *file2, struct clientes dados[], int *numDados){
    char linha[max_str_length * 9];
    sscanf(linha, "%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49[^,],%49s",
        dados[*numDados]. nomeCli, dados[*numDados].emailCli, dados[*numDados].cidadeCli,
        dados[*numDados].telefoneCli, dados[*numDados].numeroTicket, dados[*numDados].horarioSessao,
        dados[*numDados].tipoIngresso, dados[*numDados].genero, dados[*numDados].idade,

    (*numDados)++);
}

/*struct tm{
    int tm_sec; //representa os segundos de 0 a 59
    int tm_min; //representa os minutos de 0 a 59
    int tm_hour; //representa as horas de 0 a 24
    int tm_mday; //dia do mês de 1 a 31
    int tm_mon; //representa os meses do ano de 0 a 11
    int tm_year; //representa o ano a partir de 1900
    int tm_wday; //dia da semana de 0 (domingo) até 6 (sábado)
    int tm_yday; // dia do ano de 1 a 365
    int tm_isdst; //indica horário de verão se for diferente de zero
};*/

bool validacaoIngresso(struct clientes dados[], int numDados, int buscaTicket){
    for(int i = 0 ; i < numDados ; i++){
        if(dados[i].numeroTicket == buscaTicket){
            //printf("ok, ingresso validado com sucesso");
            return true; //retorna o número do registro se o cliente for encontrado
            int registroCliente = i; 
        }
        else{
            return false; //retorna -1 se  o ticket n for encontrado
            //printf("Ingresso ínvalido");
        }
    }
}

int gerarTicket(){
    // semente para rand em tempo real
    srand((unsigned int)time(NULL));

    int min = 1000000;
    int max = 9999999;

    return (rand() % (max - min + 1)) + min;
}

bool validacaoHorario(struct clientes cliente){
    time_t rawtime;
    struct tm *tempo;

    time(&rawtime);
    tempo = localtime(&rawtime); //armazena o horario atual na variavel

    int horaAtual = tempo->tm_hour * 100 + tempo->tm_min; //colocando no formato hr e min

    return cliente.horarioSessao >= horaAtual;

}

int main() {

    setlocale(LC_ALL, "Portuguese");

    printf("localização atual: %s\n", setlocale(LC_ALL, "Portuguese"));

    int numRecord = 0;
    int numDados = 0;
    struct Record records[max_rec];
    struct clientes dados[max_rec];
    struct tm *data_hora_atual;

    time_t segundos; // armazena time_t em segundos
    time(&segundos); // obtem tempo em segundos

    data_hora_atual = localtime(&segundos);// converte segundos para hora atual

    printf("\nHora ........: %d:",data_hora_atual->tm_hour);//hora

    char buscaEmail[max_str_length];
    char buscaSenha[max_str_length];

    printf("/////////////////////////////////////////////////////////////\n\n");

    printf("Bem vindos ao museu multimidia sobre o centenario da disney!!\n\n");
    //imagem mickey Obs: necessita de ajustes
    //printf("                   .d88888888bo.\n                 .d8888888888888b.\n                 8888888888888888b\n                 888888888888888888\n                 888888888888888888\n                  Y8888888888888888\n            ,od888888888888888888P\n         .'`Y8P'```'Y8888888888P'\n       .'_   `  _     'Y88888888b\n      /  _`    _ `      Y88888888b   ____\n   _  | /  \  /  \      8888888888.d888888b.\n  d8b | | /|  | /|      8888888888d8888888888b\n 8888_\ \_|/  \_|/      d888888888888888888888b\n .Y8P  `'-.            d88888888888888888888888\n/          `          `      `Y8888888888888888\n|                        __    888888888888888P\n \                       / `   dPY8888888888P'\n  '._                  .'     .'  `Y888888P`\n     `''-.,__    ___.-'    .-'\n         `-._````  __..--'`\n             ``````" );



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
        printf("4. Entrar na apresentação\n");
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

                            printf("Cadastro do cliente:\n\n");

                            file2 = fopen("infoCli.csv", "w");
                            if(numDados < max_rec){
                                /*talez adicionar a solicitação de algum documento*/
                                printf("Digite o nome: ");
                                fgets(dados[numDados].nomeCli, sizeof(dados[numDados].nomeCli), stdin);
                                dados[numDados].nomeCli[strcspn(dados[numDados].nomeCli, "\n")] = '\0';/*remove quebra de linha // strcspn calcula tamanho do segmento inicial*/

                                printf("Digite o telefone:");
                                fgets(dados[numDados].telefoneCli, sizeof(dados[numDados].telefoneCli), stdin);
                                dados[numDados].telefoneCli[strcspn(dados[numDados].telefoneCli, "\n")] = '\0';

                                printf("Digite o email:");
                                fgets(dados[numDados].emailCli, sizeof(dados[numDados].emailCli), stdin);
                                dados[numDados].emailCli[strcspn(dados[numDados].emailCli, "\n")] = '\0';

                                printf("Digite a cidade de origem:");
                                fgets(dados[numDados].cidadeCli, sizeof(dados[numDados].cidadeCli), stdin);
                                dados[numDados].cidadeCli[strcspn(dados[numDados].cidadeCli, "\n")] = '\0';

                                printf("Qual o gênero?");
                                //colocar como opções onde a pessoa digita a letra //colocar um switch para gravar //ver como declarar parametro quando prof responder
                                printf("1. Mulher cis\n\n2. Homem cis\n\n3. Mulher trans\n\n4. Homem trans\n\n5. Não Binário\n\n6. Outro\n\n7. Prefiro não dizer\n\n");
                                
                                int generoVar;
                                scanf("%d", &generoVar);
                                dados[numDados].genero = generoVar;

                                printf("Digite a idade:\n");

                                int idadeVar;
                                scanf("%d", &idadeVar);
                                dados[numDados].idade = idadeVar;

                                printf("Deseja um ingresso para qual horário?\n");

                                printf("Sessões diponiveis: \n 1. 9hrs \n 2. 12 hrs \n 3. 16 hrs \n 4. 20 hrs\n");

                                int horario;
                                scanf("%d", &horario);
                                dados[numDados].horarioSessao = horario;
                                
                                fflush(stdin);

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

                                printf("Gostaria de uma entrada:\n 1. inteira\n 2. meia\n");

                                fflush(stdin);

                                int entrada;

                                scanf("%d", &entrada);
                                dados[numDados].tipoIngresso = entrada;

                                switch (entrada)
                                {
                                case 1:
                                    printf("Você escolheu entrada inteira\n");
                                break;
                                case 2:
                                    printf("Você escolheu entreda meia\n");
                                break;
                                default:
                                    printf("Opção inválida");
                                break;
                                }

                                float ticket = gerarTicket();

                                printf("Aqui esta o código do ticket %.7f\n", ticket);

                                numDados++;

                            }

                            fclose(file2);
                        }
                        else{
                            printf("Senha incorreta\n");
                        }
                    }
                    else{
                        printf("Email não cadastrado\n");
                    }
                }
                fclose(file);


            break;

            case 3:
                /*cadastro cliente*/

                fflush(stdin);

                file2 = fopen("infoCli.csv", "w");
                if(numDados < max_rec){
                    /*talez adicionar a solicitação de algum documento*/
                    printf("Digite seu nome: ");
                    fgets(dados[numDados].nomeCli, sizeof(dados[numDados].nomeCli), stdin);
                    dados[numDados].nomeCli[strcspn(dados[numDados].nomeCli, "\n")] = '\0';/*remove quebra de linha // strcspn calcula tamanho do segmento inicial*/

                    printf("Digite seu telefone: ");
                    fgets(dados[numDados].telefoneCli, sizeof(dados[numDados].telefoneCli), stdin);
                    dados[numDados].telefoneCli[strcspn(dados[numDados].telefoneCli, "\n")] = '\0';

                    printf("Digite seu email: ");
                    fgets(dados[numDados].emailCli, sizeof(dados[numDados].emailCli), stdin);
                    dados[numDados].emailCli[strcspn(dados[numDados].emailCli, "\n")] = '\0';

                    printf("Digite sua cidade: ");
                    fgets(dados[numDados].cidadeCli, sizeof(dados[numDados].cidadeCli), stdin);
                    dados[numDados].cidadeCli[strcspn(dados[numDados].cidadeCli, "\n")] = '\0';

                    fflush(stdin);

                    printf("Qual seu gênero?\n\n");
                    printf("1. Mulher cis\n2. Homem cis\n3. Mulher trans\n4. Homem trans\n5. Não Binário\n6. Outro\n7. Prefiro não dizer\n");

                    int generoVar;
                    scanf("%d", &generoVar);
                    dados[numDados].genero = generoVar;

                    fflush(stdin);

                    switch (generoVar)
                    {
                    case 1:
                        printf("Você selecionou mulher cis \n");
                    break;

                    case 2:
                        printf("Você selecionou homem cis \n");
                    break;

                    case 3:
                        printf("Você selecionou mulher trans \n");
                    break;

                    case 4:
                        printf("Você selecionou homem trans\n");
                    break;

                    case 5:
                        printf("Você selecionou não binário\n");
                    break;

                    case 6:
                        printf("Você selecionou outro\n");
                    break;

                    case 7:
                        printf("Você selecionou prefiro não dizer\n");
                    break;
                    
                    default:
                        printf("Opção inválida.\n");
                    break;
                    }

                    fflush(stdin);

                    printf("Digite sua idade:\n");

                    int idadeVar;
                    scanf("%d", &idadeVar);
                    dados[numDados].idade = idadeVar;

                    fflush(stdin);

                    printf("Deseja um ingresso para qual horário?\n");

                    printf("Sessões diponiveis: \n9hrs \n12 hrs \n16 hrs \n20 hrs\n");

                    printf("Digite o horário desejado (sem o hrs)");

                    int horario;
                    scanf("%d", &horario);
                    dados[numDados].horarioSessao = horario;
                    
                    fflush(stdin);

                    switch (horario)
                    {
                    case 9:
                        printf("Ingresso selecionado para as 9 hrs.\n");
                    break;

                    case 12:
                        printf("Ingresso selecionado para as 12 hrs.\n");
                    break;

                    case 16:
                        printf("Ingresso selecionado para as 16 hrs\n");
                    break;

                    case 20:
                        printf("Ingresso selecionado para as 20 hrs\n");
                    break;

                    default:
                        printf("Essa opção não esta dísponivel.\n");
                    break;
                    }

                    printf("Gostaria de uma entrada:\n 1. inteira\n 2. meia\n");

                    fflush(stdin);

                    int entrada;

                    scanf("%d", &entrada);
                    dados[numDados].tipoIngresso = entrada;

                    switch (entrada)
                    {
                    case 1:
                        printf("Você escolheu entrada inteira\n");
                    break;
                    case 2:
                        printf("Você escolheu entreda meia\n");
                    break;
                    default:
                        printf("Opção inválida");
                    break;
                    }

                    float ticket = gerarTicket();

                    printf("Aqui esta o código do seu ticket %7.f\n", ticket);

                    dados[numDados].numeroTicket = ticket;
                    printf("TO AQUI");

                    numDados++;
                }

                    fflush(stdin);
                
                fclose(file2);

                printf("agr aqui");

            break;
            case 4:

                fflush(stdin);

                float buscaTicket;

                printf("Digite o código do seu ticket:\n");
                scanf("%f", &buscaTicket);
                fopen("infoCli.csv", "r");

                if(validacaoIngresso(dados, numDados, buscaTicket)){
                    printf("Ingresso válidado com sucesso\n");
                        int registroCliente = validacaoIngresso(dados, numDados, buscaTicket);

                        /*if(registroCliente != -1){
                            if(validacaoHorario(dados[registroCliente])){
                                printf("Horário válido, entrada permitida\n");
                            }
                            else{
                                printf("Horário inválido, entrada recusada\n");
                            }
                        }
                        else{
                            printf("Cliente não encontrado\n");
                        }*/
                }
                else{
                    printf("Ingresso Inválido");

                    return 0;
                }


            
            
                fclose(file2);
                
                printf("Aproveite sua sessão.\n");

                printf("/////////////////////////////////////////////////////////////////\n");

                printf("  Bem-vindos às histórias dos museus e exposições da Disney! Aqui, você pode explorar a fascinante jornada da Disney na indústria do entretenimento. Desde os primeiros desenhos animados até os incríveis parques temáticos e os filmes contemporâneos, temos várias exposições para você se aprofundar cada vez mais nesse universo fantástico Disney, a história da Disney teve início no início de 1923, quando Walt Disney, originalmente de Kansas City, Missouri, criou um curta-metragem intitulado 'Alice's Wonderland.' Esse curta-metragem apresentou uma atriz infantil interagindo com personagens animados. Após esse feito, Walt Disney mudou-se para Hollywood e uniu forças com seu irmão.\n\n");
                printf("  Assim, em 16 de outubro de 1923, fundaram os Disney Brothers Cartoon Studios. Logo depois, a distribuidora MJ Winkler Production se aproximou deles com o interesse de distribuir uma série de curtas intitulada 'Alice Comedies' , oferecendo cerca de 1,5 mil dólares para essa finalidade. Isso resultou na produção de vários filmes animados de sucesso.\n\n");
                printf("  A empresa começou a prosperar com a criação de seu ícone mais emblemático, o mascote Mickey Mouse, que foi criado em 1928. Mickey estreou em um curta-metragem chamado 'Plane Crazy' e mais tarde em 'Steamboat Willie,' o primeiro desenho animado sonoro da empresa, que se tornou um grande sucesso.\n\n");
                printf("  Com o passar dos anos, a Disney continuou a crescer e lançou animações icônicas, incluindo 'Branca de Neve e os Sete Anões', 'Pinóquio', 'Fantasia', 'Dumbo', 'Bambi', 'Cinderela', e 'Alice no País das Maravilhas.' No entanto, com o início da Segunda Guerra Mundial, os lucros das bilheteiras diminuíram, e muitos dos animadores da Disney foram convocados para o serviço militar.\n\n");
                printf("  Durante a guerra, o estúdio produziu filmes de treinamento e propaganda militar sob encomenda dos governos dos Estados Unidos e Canadá. Em 1942, aproximadamente 90 porcento dos 550 funcionários da Disney estavam envolvidos na produção de filmes relacionados à guerra, como 'A Vitória Pela Força Aérea' e o curta 'Educação para a Morte.\n\n");
                printf("  Após tantos sucessos, a Disney expandiu seus horizontes a partir dos anos 1950, abraçando filmes de ação ao vivo, investindo em televisão e inaugurando parques temáticos.\n\n");
                printf("  Em 1954, Walt Disney usou sua série 'Disneyland' para revelar o conceito do parque temático Disneyland, que era uma realização de seu desejo de um lugar onde pais e filhos pudessem desfrutar juntos. A Disneyland foi aberta ao público em 18 de julho de 1955 e continuou a crescer e atrair visitantes de todo o mundo.\n\n");
                printf("  A Disney também anunciou a Disney World, um complexo de parques temáticos, hotéis e uma cidade planejada, em Orlando, Flórida, em novembro de 1965.\n\n");
                printf("  Os estúdios de cinema da Disney continuaram a produzir filmes populares, incluindo 'A Dama e o Vagabundo', 'A Bela Adormecida' e 'Os 101 Dálmatas.' Um destaque foi o sucesso do musical 'Mary Poppins', que se tornou uma das maiores bilheteiras da história e recebeu cinco prêmios da Academia, incluindo Melhor Atriz para Julie Andrews.\n\n");
                printf("  Em 15 de dezembro de 1966, Walt Disney faleceu devido a complicações relacionadas a um câncer de pulmão. Seu irmão, Roy O. Disney, assumiu como presidente e CEO da empresa, renomeando o Disney World como Walt Disney World em homenagem à visão de seu irmão.\n\n");
                printf("  Hoje, a Disney é uma empresa diversificada, englobando redes de televisão, parques temáticos, produtos colecionáveis e até mesmo roupas. Os estúdios de cinema da Disney também operam como subsidiárias, incluindo Lucasfilm, Marvel Entertainment, Pixar, 20th Century Studios e Searchlight Pictures. A empresa é responsável por canais de televisão como ESPN, Star e National Geographic, bem como canais de programação infantil, como o Disney Channel. Além disso, no exterior, a Disney é a controladora da rede de televisão ABC.\n\n");
                printf("  Agora que você já aprendeu como foi criada a disney hora de testar seu conhecimento:\n\n");

                printf("  Qual o nome do primeiro curta-metragem feita pelo Walt Disney?\n\n");
                printf("a) Plane Crazy\n\n");
                printf("b) Alice's Wonderland\n\n");
                printf("c) Branca de neve e os sete anões\n\n");
                printf("d) Steamboat Willie\n\n");

                fflush(stdin);

                char resposta1;

                scanf("%c", &resposta1);

                switch (resposta1)  
                {
                case 'b':
                    printf("Resposta Correta!!\n\n");

                    printf("Parabéns!!\n\n");

                break;

                default:
                    printf("Resposta errada\n\n");

                    printf("A resposta correta era: \n Alice's Wonderland, que após seu lançamento ganhou tanta fama que o Walt se mudou para Hollywood e juntou forças com seu irmão, assim criando a Disney Brothers Cartoon Studios em 1923.\n\n");
                break;
                }

                fflush(stdin);

                printf("  Agora vamos conhecer um pouco mais sobre o famoso Walt Disney!\n\n");
                printf("  Walter Elias Disney, mais conhecido como Walt Disney, nasceu em Chicago em 5 de dezembro de 1901 e passou grande parte de sua infância em uma fazenda em Marceline, no Missouri. Sua infância foi marcada por desafios devido aos castigos impostos por seu pai, Elias Disney. Aos 16 anos, ele iniciou seu estudo de arte e se envolveu na Ordem Demolay.\n\n");              
                printf("  Após seu retorno da Primeira Guerra Mundial (1914-1919), onde serviu como motorista de ambulância devido à sua idade, uma paixão pelo desenho que ele tinha desde a infância o levou a fundar sua primeira empresa. Inicialmente, ele vendia desenhos dos personagens que criava, mas dificuldades financeiras levaram à falência de sua empresa aos 22 anos.\n\n");
                printf("  Apesar do fracasso inicial e da pressão de sua família para encontrar um emprego convencional, Walt Disney permaneceu firme em sua crença em seus sonhos e em sua arte. Ele retornou a Hollywood e estabeleceu um novo estúdio em sua garagem. Durante esse período, ele conseguiu um contrato para uma série de animações chamada 'Alice comedies', mas ela não obteve o sucesso esperado.\n\n");
                printf("  Posteriormente, Disney teve a oportunidade de trabalhar com a Universal e criou Oswald - O Coelho Sortudo, que foi o primeiro personagem de destaque em sua carreira. No entanto, ele perdeu os direitos sobre esse personagem devido a questões contratuais.\n\n");
                printf("  Após essa reviravolta, Disney e seus sócios Roy e Iwerks recomeçaram do zero. Foi nesse momento que o camundongo Mortimer, posteriormente conhecido como Mickey Mouse (nome escolhido pela esposa de Walt, Lily), surgiu como uma representação do oposto da desonestidade que Walt havia encontrado em sua jornada. Mickey era gentil, honesto, educado e amoroso.\n\n");
                printf("  O sucesso finalmente bateu à porta de Walt Disney. No início, ele mesmo dublou o personagem, pois não podia pagar dubladores. Mickey ganhou uma companheira, Minnie Mouse, e, apesar do desinteresse inicial do mercado pelos três primeiros filmes, a persistência de Walt resultou no fenômeno americano Mickey Mouse.\n\n");
                printf("  Seguindo o sucesso de Mickey Mouse, Disney lançou a animação 'Branca de Neve e os Sete Anões'. Enfrentando novamente dificuldades financeiras durante a produção, ele persistiu e finalizou o filme, que agora é considerado um clássico da animação.\n\n");
                printf("  Após tudo isso, Disney passou a produzir longas-metragens, como Pinóquio, Fantasia e Bambi. Mas om a eclosão da Segunda Guerra Mundial em 1939, Disney se viu interrompido em sua produção de longas-metragens. Ele foi convidado pelas Forças Armadas dos Estados Unidos para criar desenhos animados de treinamento para os soldados e filmes de propaganda militar, nos quais usou principalmente seus personagens mais conhecidos. Após a guerra, ele decidiu produzir o filme 'Cinderela', que foi um sucesso e ajudou a empresa a se recuperar.\n\n");
                printf("  Além dos estúdios cinematográficos, o império Disney se expandiu para incluir parques temáticos, canais de televisão e direitos sobre personagens criados. Walt Disney tornou-se uma lenda, criando um universo de referências no imaginário infantil de várias gerações, com o auxílio de sua equipe.\n\n");
                printf("  Disney faleceu em 15 de dezembro de 1966, devido a um avançado câncer de pulmão. Seu corpo foi cremado dois dias depois, e suas cinzas foram enterradas no Forest Lawn Memorial Park em Glendale, Califórnia. Ele detém o recorde de maior número de indicações ao Oscar (cinquenta e nove) e número de Oscares ganhos (22), incluindo quatro Oscares honorários.\n\n");
                printf("  Hora de testar seus conhecimentos: ");

                printf("Qual foi o primeiro personagem animado de destaque da carreira de Walt?\n\n");
                printf("a) Oswald - O coelho sortudo\n\n");
                printf("b) Mickey Mouse\n\n");
                printf("c) Donald Duck\n\n");
                printf("d) Tio Patinhas\n\n");

                fflush(stdin);

                char resposta2;

                scanf("%c", &resposta2);

                fflush(stdin);

                switch (resposta2)
                {
                case 'a':
                    printf("Resposta Correta!!\n\n");
                    printf("Parabéns\n\n");
                break;

                default:
                    printf("Resposta errada\n\n");
                    printf("A resposta correta era: \nOswald - O coelho sortudo, que Disney criou em um trabalho com a Universal, porém devido a questões contratuais ele perdeu os direitos sobre o personagem.\n\n");
                break;
                }

                fflush(stdin);

                printf("  Agora vamos conhecer sobre os personagens mais icônicos da Disney:\n\n");

                printf("  A Disney, ao longo de seus 100 anos de história, criou uma galeria extraordinária de personagens que conquistaram o coração do público em todo o mundo. Essas figuras icônicas não são apenas animadas, mas também têm a capacidade de viver nos corações e mentes de crianças e adultos, atravessando gerações e culturas. Neste moemento, mergulharemos no fascinante mundo dos personagens mais emblemáticos da Disney, examinando o que os torna tão especiais, como eles evoluíram e o impacto duradouro que tiveram na cultura popular. Desde os heróis que personificam valores nobres até os vilões memoráveis que provocam fascinação, cada personagem da Disney tem uma história única para contar. Juntos, eles compõem um tesouro de narrativas e lições que transcendem as telas e enriquecem nossas vidas de maneiras surpreendentes e encantadoras.\n\n");
                printf("Mickey Mouse e sua turma:\n\n");
                printf("  Mickey Mouse é o ícone mais emblemático da Walt Disney Company, tendo sido concebido em 1928 por Walt Disney em colaboração com o destacado artista norte-americano Ub Iwerks. Mickey é amplamente reconhecido como o símbolo da empresa e figura proeminente em inúmeras produções de animação, quadrinhos e uma variedade de produtos. Acompanhado por sua parceira Minnie e seus leais amigos, Donald e Pateta, o grupo desfruta de uma imensa popularidade global, participando em uma série diversificada de aventuras conjuntas que cativam audiências de todas as idades\n\n");
                printf("Tio Patinhas:\n\n");
                printf("  Patinhas McPato, ou Tio Patinhas, é um personagem criado pelo cartunista Carl Barks, tendo feito sua estreia inicial no ano de 1947. Ao longo das décadas subsequentes, esse personagem evoluiu de uma posição secundária nas narrativas do cenário de Patópolis para protagonizar suas próprias aventuras, frequentemente acompanhado por seus sobrinhos, Huguinho, Zezinho e Luisinho.\n\n");
                printf("Cinderela\n\n");
                printf("  Cinderela, uma das princesas mais amadas e conhecidas da Disney desempenha o papel principal no filme da Disney intitulado 'Cinderela', lançado em 1950, bem como em suas duas sequências subsequentes. Ela foi originalmente dublada por Ilene Woods, que faleceu, no filme original, e posteriormente, nas continuações do filme, Jennifer Hale assumiu a dublagem do personagem. Cinderela ocupa a segunda posição no conjunto de princesas da Disney. A narrativa de Cinderela é uma fábula de conto de fadas que retrata a história de uma jovem órfã que reside com sua madrasta cruel e as duas enteadas invejosas.\n\n");
                printf("Branca de Neve:\n\n");
                printf("  Branca de Neve é a personagem principal do filme pioneiro da Disney, 'Branca de Neve e os Sete Anões', lançado em 1937. Ela é a primeira das icônicas Princesas da Disney. Baseada em um conto dos Irmãos Grimm, Branca de Neve é retratada como uma jovem princesa elogiada por sua beleza e bondade inocente, que a torna vulnerável à inveja de sua madrasta. No entanto, sua pureza inspira seus amigos, incluindo os animais da floresta e os Sete Anões, que a protegem. Ao longo do filme, Branca de Neve desempenha papéis de mãe protetora e criança inocente em suas relações com os habitantes da floresta e os Sete Anões.\n\n");
                printf("Ariel:\n\n");
                printf("  A Princesa Ariel, uma das princesas mais populares da disney, é uma sereia que fez sua primeira aparição como personagem principal na versão de 1989 do conto 'A Pequena Sereia' pela Disney. Ela posteriormente reprisou seu papel como protagonista em uma série de TV e no prequel intitulado 'A Pequena Sereia: A História de Ariel.'\n\n");
                printf("  Ariel, é retratada como uma sereia de dezesseis anos que experimenta insatisfação com sua vida no oceano e nutre uma curiosidade inquieta pelo mundo humano. Com seu fiel amigo Linguado, um peixe, Ariel coleciona objetos humanos e ousa aventurar-se até a superfície do mar. Lá, ela busca a orientação de Sabidão, uma gaivota, que fornece informações imprecisas sobre a cultura humana.\n\n");
                printf("Rapunzel:\n\n");
                printf("  Rapunzel é a personagem principal do filme de animação da Disney lançado em 2010, 'Enrolados', e em sua subsequente sequência. Ela é uma encantadora princesa dotada de cabelos loiros longos e mágicos. Com o auxílio de Flynn Rider, um aventureiro de bela aparência, Rapunzel decide deixar para trás a torre isolada onde viveu por tanto tempo e se aventurar pelo mundo exterior. Essa personagem tem suas origens vagamente inspiradas no conto de fadas clássico italiano 'Rapunzel', conforme narrado pelos Irmãos Grimm.\n\n");
                printf("Elsa, Anna e Olaf:\n\n");
                printf("  Anna e Elsa são princesas de Arendelle em 'Frozen - Uma Aventura Congelante1 (2013). Elsa tem o poder de criar gelo e cobre o reino em inverno eterno acidentalmente. Anna busca trazer sua irmã de volta e restaurar o reino, explorando o amor fraternal. Olaf é um boneco de neve animado por Elsa, conhecido por seu senso de humor e desejo de sentir o calor do verão. Eles são personagens principais que juntos trazem humor, emoção e lições de aceitação na história.\n\n");
                printf("Buzz Lightyear e Woody:\n\n");
                printf("  Buzz Lightyear é um brinquedo espacial que acredita ser um herói real, enquanto Woody é um caubói leal e o líder dos brinquedos de Andy. Eles são personagens centrais da franquia 'Toy Story' da Disney-Pixar e, ao longo dos filmes, desenvolvem uma forte amizade e trabalham juntos para superar desafios. A história explora temas de amizade, identidade e aceitação.\n\n");
                printf("Pumba e Timão:\n\n");
                printf("  Simba é o herdeiro do trono na selva e protagonista de 'O Rei Leão', enquanto Timão e Pumba são seus amigos. Simba lida com desafios em sua jornada para se tornar rei após a morte de seu pai, Mufasa. Timão e Pumba, um suricata e um javali, trazem humor e amizade à história, ajudando Simba a encontrar seu verdadeiro destino. A relação entre os três é um elemento fundamental na narrativa.\n\n");
                printf("Malévola:\n\n");
                printf("  Malévola é a vilã do filme 'A Bela Adormecida' da Disney, uma feiticeira poderosa que amaldiçoa a princesa Aurora a cair em um sono profundo. Sua aparência sinistra e motivação de vingança tornam-na uma personagem icônica que personifica o mal na história.\n\n");
                printf("Capitão Jack Sparrow:\n\n");
                printf("  O Capitão Jack Sparrow é o personagem central da franquia 'Piratas do Caribe', interpretado por Johnny Depp. Ele é um pirata excêntrico e astuto, conhecido por sua personalidade carismática e sua aparência desalinhada. Sparrow é muitas vezes movido por seu desejo de riquezas, aventuras e liberdade, e tem um jeito único de lidar com situações perigosas. Ele é notório por suas artimanhas, malabarismos e pela busca constante de tesouros lendários. Ao longo da franquia, Jack Sparrow enfrenta inúmeras reviravoltas e desafios, sempre com um toque de humor e sagacidade, o que o torna um personagem icônico e querido pelo público.\n\n");

                printf("Agora que já conheceu algum dos personagens hora do teste:\n\n");
                printf("Malévola é vilã de qual filme?\n\n");
                printf("a)Frozen - Uma aventura congelante\n\n");
                printf("b)A Pequena Sereia\n\n");
                printf("c)A Bela Adormecida\n\n");
                printf("d)Cinderela\n\n");

                fflush(stdin);

                char resposta3;

                scanf("%c", &resposta3);

                switch(resposta3)
                {
                    case 'c':
                        printf("Resposta Correta \n\nParabéns!!\n\n");
                    break;
                    default:
                        printf("Resposta errada\n\n A resposta correta era:\n A Bela Adormecida\n\n");
                    break;
                }

                fflush(stdin);

                printf("Agora vamos falar sobre alguns dos filmes mais marcantes da Disney:\n\n");

                printf("Ao longo das décadas, a Disney consolidou sua posição como um dos estúdios de cinema mais influentes do mundo, proporcionando ao público uma extensa lista de filmes que se tornaram verdadeiros marcos na história do entretenimento. Com um legado que abrange quase um século de produção cinematográfica, os filmes da Disney cativaram gerações de espectadores, transportando-os para mundos mágicos, repletos de contos de fadas, aventuras emocionantes e lições atemporais. A seguir, exploraremos os filmes mais marcantes da Disney, aqueles que não apenas cativaram o público, mas também moldaram a cultura popular, redefiniram a animação e continuam a encantar pessoas de todas as idades em todo o mundo. Cada filme é uma janela para a imaginação, repleta de personagens memoráveis, trilhas sonoras inesquecíveis e mensagens que transcendem o tempo, garantindo seu lugar duradouro na história do cinema.\n\n");
                printf("Plane Crazy:\n\n  Um curta-metragem animado mudo em preto e branco de 1928 estrelando Mickey Mouse. É notável por ser o primeiro desenho animado de Mickey produzido pelos estúdios Disney, embora 'Steamboat Willie' tenha sido lançado antes, porém Walt Disney e Ub Iwerks não foram creditados.\n\n  Inspirado pelo voo histórico de Charles Lindbergh, Mickey e seus amigos constroem um avião, mas o primeiro voo é desastroso. Mickey tenta novamente, convida Minnie para voar e a beija, mesmo contra sua vontade. Minnie pula de paraquedas, Mickey fica distraído, e o avião cai no chão no final.\n\n");
                printf("Branca de Neve e os sete anões:\n\n  Um filme de animação clássico da Disney lançado em 1937 e é notável por ser o primeiro longa-metragem de animação produzido pela Disney. A história segue a jornada da jovem princesa Branca de Neve, que foge da madrasta malvada, a Rainha Má, e encontra refúgio na casa de sete anões adoráveis. Lá, ela forma um laço com os anões e se torna alvo da inveja da Rainha Má, que quer ser a mais bela do reino.\n\n  O filme é amado por suas músicas cativantes, como 'Heigh-Ho' e 'Someday My Prince Will Come', bem como por seus personagens encantadores. 'Branca de Neve e os Sete Anões' continua a ser uma parte importante do legado da Disney, encantando gerações de espectadores com sua história atemporal e animação clássica.\n\n");
                printf("Fantasia:\n\n  Criado em 1940, quando o interesse pelo Mickey começou a diminuir, então para atrair o público novamente a Disney ínicou a criação a criação de vários curtas. Entretando era esperado uma animação capaz de superar o sucesso de “Branca de Neve e os sete anões”, então compilaram todos esses curtas juntos, transformando-os em um longa-metragem.\n\n  O filme traz elementos visuais cativantes e emocionantes, sendo composto de vários contos baseados em sinfonias criados para ele, como por exemplo 'Aprendiz de feiticeiro' e 'A suíte do Quebra Nozes'.\n\n");
                printf("O Rei Leão:\n\n  Um filme da Disney lançado em 1994, que se tornou um clássico da animação. A história segue a jornada de Simba, um jovem leão destinado a ser rei, que foge de suas responsabilidades após a morte de seu pai, Mufasa. Ele eventualmente retorna para restaurar a paz no reino e enfrentar seu passado. O filme é conhecido por suas mensagens poderosas, animação incrível e trilha sonora memorável, e continua a encantar públicos de todas as idades.\n\n");
                printf("Frozen 2:\n\n  A história segue as irmãs Elsa e Anna, juntamente com seus amigos, em uma jornada para descobrir a origem dos poderes mágicos de Elsa e desvendar o passado de sua família. O filme explora temas como identidade, amor e a relação entre irmãs.\n\n  Elsa, a rainha de Arendelle, é chamada por uma misteriosa voz que a leva a aventurar-se em direção a uma floresta encantada. Anna, Olaf, Kristoff e a rena Sven a acompanham nessa jornada. Eles descobrem segredos sobre o passado de seus pais e a verdade por trás da origem dos poderes de Elsa. Além disso, enfrentam desafios mágicos e tentam salvar Arendelle de um possível desastre.\n\n  O filme é notável por suas músicas cativantes e reviravoltas emocionantes, à medida que os personagens lutam para entender seu passado e forjar seu futuro. Além disso, ele ocupa atualmente a décima posição na lista das maiores bilheteiras do mundo, tornando-se um dos filmes de animação de maior sucesso comercial. 'Frozen 2' expande o mundo de 'Frozen' e explora questões mais profundas, tornando-se um conto de amadurecimento e autodescoberta.\n\n");
                printf("Toy Story:\n\n  Um filme inovador em animação 3D por computação gráfica (CGI) lançado em 1995, que marcou o início de uma nova era na indústria de animação. A história envolve brinquedos que ganham vida quando os humanos não estão por perto, e segue a jornada de amizade entre Woody e Buzz Lightyear. O filme é conhecido por sua tecnologia revolucionária e mensagens sobre amizade e aceitação. Ele deu início a uma franquia de sucesso e estabeleceu a Pixar como líder na animação CGI.\n\n");
                printf("Avatar:\n\n  um filme de ficção científica lançado em 2009, dirigido por James Cameron. O filme é conhecido por suas inovações técnicas e visuais, incluindo o uso pioneiro da tecnologia 3D estereoscópica. Atualmente, 'Avatar' mantém o recorde como o segundo filme de maior bilheteria de todos os tempos, atrás apenas de 'Vingadores: Ultimato'. O filme é uma produção da 20th Century Fox e se tornou uma das propriedades mais valiosas da empresa.\n\n  Após a compra da 21st Century Fox pela Disney, em 2019, a franquia 'Avatar' passou a fazer parte do portfólio da Disney. Isso inclui a produção de várias sequências do filme original, que estão programadas para serem lançadas nas próximas décadas. A aquisição da 21st Century Fox pela Disney trouxe 'Avatar' para o universo Disney, permitindo a exploração de novas oportunidades de entretenimento e expansão da história do filme.\n\n  O filme é ambientado em Pandora, um planeta alienígena exuberante. A história segue Jake Sully, um ex-fuzileiro paraplégico que assume um avatar Na'vi como parte de um programa de exploração humana. Conflitos surgem quando os interesses humanos colidem com a cultura e o meio ambiente dos Na'vi. O filme aborda temas como exploração de recursos, choque de culturas e conservação ambiental.\n\n");
                printf("Star Wars: o despertar da força:\n\n  Um filme de ficção científica lançado em 2015, dirigido por J.J. Abrams. Este é o sétimo filme da franquia Star Wars e serve como uma sequência da trilogia original. O filme marcou o retorno de personagens icônicos da série, como Han Solo, Leia Organa e Luke Skywalker, além de introduzir uma nova geração de heróis e vilões. O elenco inclui Daisy Ridley, John Boyega, Oscar Isaac e Adam Driver.\n\n  A história se passa aproximadamente 30 anos após os eventos de 'O Retorno de Jedi' e gira em torno da busca do misterioso Jedi Luke Skywalker, enquanto a Resistência luta contra a Primeira Ordem, uma organização que surgiu das cinzas do Império Galáctico.\n\n  'O Despertar da Força' recebeu críticas positivas da crítica e dos fãs, elogiando o retorno ao espírito da trilogia original. O filme também teve um grande sucesso comercial e atualmente esta classificado como o quarto filme de maior bilheteria de todos os tempos. Ele revitalizou a franquia Star Wars e preparou o terreno para as próximas sequências, incluindo 'Os Últimos Jedi' e 'A Ascensão Skywalker'.\n\n");
                printf("Vingadores: Ultimato:\n\n  Um filme de super-heróis lançado em 2019 e dirigido pelos irmãos Anthony e Joe Russo. Este épico da Marvel Cinematic Universe (MCU), Universo cininematográfico da Marvel, conquistou o título de maior venda de bilheteria da história do cinema. O filme é o quarto da série 'Vingadores' e encerra a saga dos Vingadores enfrentando o vilão Thanos.\n\n  No enredo, os heróis tentam reverter os efeitos catastróficos do estalo de dedos de Thanos, que dizimou metade da vida no universo. Para fazer isso, eles embarcam em uma jornada no tempo, revisitando eventos-chave do MCU. O filme apresenta um elenco impressionante de personagens, incluindo Homem de Ferro, Capitão América, Thor, Viúva Negra, Hulk, Gavião Arqueiro e muitos outros.\n\n  O filme é conhecido por suas cenas de ação emocionantes, desenvolvimento de personagens e o culminar de mais de uma década de narrativa do MCU. Sua capacidade de cativar os fãs e atrair audiências de todo o mundo o tornou um sucesso avassalador nas bilheteiras, tornando-o o filme com a maior venda de ingressos da história do cinema até setembro de 2021.\n\n");
              
                printf("Hora de testar seu conhecimento:\n\n");
                printf("Qual filme trouxe uma nova era para a história da animação?\n\n");
                printf("a) Avatar\n\n");
                printf("b) Toy Story\n\n");
                printf("c) Plane Crazy\n\n");
                printf("d) Frozen 2\n\n");

                fflush(stdin);

                char resposta4;

                scanf("%c", &resposta4);

                switch(resposta4)
                {
                    case 'b':
                        printf("Resposta Correta!\n\nParabéns!!!");
                    break;
                    default:
                        printf("Resposta Incorreta\n\nA resposta correta era:\nToy Story, um filme que inovou o nivel de qualidade da computação gráfica(CGI), em 1995.\n\n");
                    break;
                }

                fflush(stdin);

                printf("Agora vamos aprender mais sobre as incovações tecnológicas da disney ao longo dos anos:\n\n");
                printf("A Disney é conhecida por sua dedicação à criatividade e à inovação, e ao longo dos anos, a empresa tem introduzido uma série de avanços tecnológicos que revolucionaram a indústria do entretenimento. Vamos explorar algumas dessas inovações notáveis que moldaram o mundo da animação e dos parques temáticos.\n\n");
                printf("Animação:\n  Snow White and the Seven Dwarfs (Branca de Neve e os Sete Anões): Foi o primeiro longa-metragem animado da Disney, lançado em 1937, que introduziu inovações técnicas significativas na animação.\n\n");
                printf("Efeitos Especiais:\n  Pirates of the Caribbean (Piratas do Caribe): A atração introduziu técnicas inovadoras de animação e efeitos especiais em parques temáticos.\n\n");
                printf("Technicolor e Fantasia (1940):\n  Um dos primeiros marcos tecnológicos da Disney que combina música clássica com animação inovadora. O filme apresenta várias sequências animadas, cada uma definida por uma composição clássica. Foi um dos primeiros filmes a usar o sistema Technicolor, que trouxe cores vibrantes à tela. Embora inicialmente não tenha sido um sucesso comercial, ao longo dos anos, tornou-se uma obra-prima da animação, influenciando a forma como a animação é usada para contar histórias.\n\n");
                printf("Disneyland e a revolução dos parques temáticos (1955):\n  Com a abertura do Disneyland na Califórnia, a Disney transformou o conceito de parques de diversão, introduzindo a ideia de um mundo totalmente imersivo e temático, com atrações que utilizavam tecnologia de ponta para contar histórias cativantes.\n\n");
                printf("Áudio Animatronics (1963):\n  Walt Disney e sua equipe introduziram a tecnologia Audio-Animatronics na Feira Mundial de Nova York. Isso permitiu a criação de personagens robóticos que podiam interagir com o público, inaugurando uma nova era nos parques temáticos da Disney.\n\n");
                printf("Efeitos Visuais Revolucionários (1989):\n  O lançamento de 'A Pequena Sereia' marcou a transição da animação tradicional para a animação digital, que mais tarde culminaria com filmes como 'Toy Story' da Pixar, que incluem a combinação de live-action com animação, uso de CGI (Computer Generated Imagery) e tecnologia de motion capture, uma subsidiária da disney\n\n");
                printf("Disney MagicBand (2013):\n  A Disney introduziu o MagicBand, uma pulseira inteligente que permite aos visitantes dos parques temáticos acessar seus ingressos, comprar produtos, fazer reservas e até mesmo abrir seus quartos de hotel, proporcionando uma experiência mais conveniente e personalizada.\n\n");
                printf("Realidade Aumentada em Parques (2019):\n  A Disney começou a incorporar tecnologia de realidade aumentada em suas atrações, como 'Star Wars: Galaxy's Edge', com a introdução de atrações baseadas em realidade virtual e aumentada, uso de sistemas RFID (Identificação por Radiofrequência) para melhorar a experiência do visitante e a criação de sistemas de entretenimento interativo, proporcionando uma experiência imersiva e interativa para os visitantes.\n\n");
                printf("Tecnologia de Filmes em 3D:\n  A Disney foi uma das pioneiras na produção de filmes em 3D, proporcionando aos espectadores uma experiência de cinema mais imersiva. Utilizando a tecnologia de filmes em 3D para criar experiências cinematográficas imersivas que atraem o público de todas as idades. Eles produziram filmes em 3D notáveis, como 'O Rei Leão' e 'Frozen', que combinam imagens estereoscópicas com animação avançada para proporcionar uma experiência visual envolvente e emocionante. A Disney continua a explorar a tecnologia 3D para inovar em suas narrativas e aprimorar a magia do cinema.\n\n");
                printf("Inteligência Artificial e Análise de Dados:\n  A Disney usa IA e análise de dados para personalizar experiências em parques temáticos, recomendar conteúdo no Disney+, melhorar a eficiência operacional e muito mais.\n\n");
                printf("Robôs Autônomos (2020):\n  A Disney apresentou robôs autônomos em seus parques temáticos, como o robô Groot e o robô R2-D2, que interagem com os visitantes e criam uma experiência única.\n\n");
                printf("Tecnologia de Entretenimento Interativo:\n  A Disney incorpora uma variedade de tecnologias de entretenimento interativo em seus jogos para criar experiências envolventes que cativam fãs de todas as idades e fazem uso de suas propriedades intelectuais populares. Essas tecnologias proporcionam diversão e imersão, permitindo aos jogadores explorar mundos mágicos e interagir com personagens icônicos da Disney.\n\n");
                printf("  Estas são apenas algumas das muitas inovações tecnológicas que a Disney trouxe ao mundo do entretenimento e dos parques temáticos. A empresa continua a surpreender e encantar pessoas de todas as idades com seu compromisso em combinar a criatividade com a tecnologia de ponta. Esperamos que tenha desfrutado desta exposição sobre as inovações tecnológicas da Disney!\n\n");

                printf("Hora de testar seu conhecimento:\n\n");
                printf("A Disney MagicBand é uma:\n\n");
                printf("a) Banda mágica de robôs autônomos que fazem shows pelo parque\n\n");
                printf("b) Uma área de realidade aumentada nos parques\n\n");
                printf("c) Uma pulseira inteligente que agiliza os processos de entradas em brinquedos e compras dentro dos parques\n\n");
                printf("d) Uma área de jogos interativos no parque\n\n");

                fflush(stdin);

                char resposta5;

                scanf("%c", &resposta5);

                switch (resposta5)
                {
                case 'c':
                    printf("Resposta correta!\nParabéns!!\n\n");
                break;
                
                default:
                    printf("Resposta incorreta:\n A resposta correta era:\n Uma pulseira inteligente que agiliza os processos de entradas em brinquedos e compras dentro dos parques\n\n");
                break;
                }

                fflush(stdin);

                printf("Que tal aprendermos sobre o legado e o futuro da Disney?\n");
                printf("  Ao longo dos anos, a Disney construiu um legado notável que deixou uma marca indelével na cultura popular, e agora, vamos explorar como esse legado se entrelaça com o futuro da empresa.\n\n");
                printf("  A história da Disney remonta a 1923, quando Walt Disney e Roy O. Disney fundaram o estúdio que se tornaria o epicentro da criação de animações inovadoras. A exposição começa com as primeiras animações, como 'Branca de Neve e os Sete Anões' e 'Cinderela', que capturaram os corações de gerações inteiras. Esses filmes estabeleceram o padrão para a animação e se tornaram clássicos atemporais.\n\n");
                printf("  No entanto, a Disney não parou por aí. A empresa evoluiu para abraçar novas formas de contar histórias, expandindo seu alcance para a aquisição de franquias como a Marvel, Star Wars e a Pixar. A exposição destaca como essas aquisições ajudaram a Disney a se manter relevante no cenário do entretenimento, permitindo que novas histórias e experiências fossem criadas.\n\n");
                printf("  Olhando para o futuro, a Disney continua a inovar. A tecnologia desempenha um papel crucial em atrações de parques temáticos, como a realidade virtual e aumentada, que proporcionam experiências imersivas como nunca. Além disso, a Disney está investindo em streaming de vídeo, com o lançamento do Disney+ e a expansão de seu catálogo de conteúdo original.\n\n");
                printf("  Esta exposição é uma homenagem à imaginação, criatividade e à capacidade da Disney de criar mundos mágicos que cativam gerações. À medida que exploramos o legado e o futuro da Disney, lembramos que a magia continuará a crescer e a se adaptar às necessidades e expectativas do público. A Disney é uma empresa que nunca para de sonhar, e, assim como Walt Disney uma vez disse: 'Se podemos sonhar, também podemos torná-lo realidade.' O futuro promete mais encantamento, diversão e aventura à medida que a Disney continua a nos surpreender e inspirar.\n\n");

                printf("Hora de testar seus conhecimentos:\n\n");
                printf("Quais franquias a Disney adquiriu para expandir o seu alcance de público?\n");
                printf("a)Marvel, Dreamworks, e Star Wars\n");
                printf("b)Blue Sky, Pixar e Marvel\n");
                printf("c)Marvel, Star Wars e Pixar\n");
                printf("d)Pixar, Blue Sky e DreamWorks\n");

                fflush(stdin);

                char resposta6;

                scanf("%c", &resposta6);

                switch(resposta6)
                {
                    case 'c':
                        printf("Resposta correta!\nParabéns!!\n\n");
                    break;
                    default:
                        printf("Resposta incorreta\nA resposta era:\nAs franquias Marvel, Star Wars e Pixar.\n\n");
                }

                fflush(stdin);

                printf("  Vamos ver um pouco mais sobre as aquisições notáveis da Disney e como elas moldaram o incrível universo do entretenimento:\n\n");
                printf("Marvel:\n  Começando por uma que tenho quase certeza de que a maioria aqui presente já ouviu falar, a Marvel. Em 2009, a Disney adquiriu a Marvel Entertainmet. E isso nos trouxe super-heróis icônicos que todos nós amamos, como Homem de Ferro, Homem Aranha, Capitão América para o universo magico da Disney. Os filmes do Universo Cinematográfico Marvel (MCU) se tornaram um grande sucesso na cultura, combinando uma história divertida em um único universo só compartilhado.\n\n");
                printf("Pixar:\n  Logo em seguida temos ela, a Pixar! Em 2006 a Disney adquiriu um dos estúdios de animação mais renomados do mundo, isso nos trouxe histórias como “Toy Story”, “Os Incríveis”, “Ratatouille” e entre outros filmes que vieram pra família Disney. Essa colaboração resultou claramente uma longa série de filmes de sucesso e tecnologias de animações avançadas.\n\n");
                printf("Lucasfilm:\n  Quem aqui já ouviu falar no nome Darth Vader? Ou melhor, já escutou essa frase “Que a força esteja com você.” Então a criadora do personagem de “Star Wars” é a Lucasfilm que foi comprada pela Disney em 2012.E como todos já imaginavam isso resultou em uma nova geração de filmes da saga e séries de televisão, expandindo o alcance da franquia e introduzindo personagens memoráveis como o Rey e Kylo Ren.\n\n");
                printf("21st Century Fox:\n  Aposto que você já chegou da escola e se sentou em frente TV pra almoçar e logo em seguida começou adivinhar o nome de personagens, caso você não tenha decifrado este pequeno enigma eu estou falando da série de tv “X-Men” que foi criada pela 21st Century Fox que em 2019 a Disney adquiriu. Incluindo além de “X-men” também Avatar e outras propriedades de televisão, como os amarelinhos queridos da televisão “Os Simpsons”. A aquisição ampliou ainda mais o catálogo de conteúdo da Disney.\n\n");
                printf("  Com essas aquisições permitiram a Disney consolidar seu domínio no mundo do entretenimento. Além de filmes, também tiveram impacto significativo em jogo de vídeo game, parques, e é claro plataformas de streaming, como a Disney + onde você tem acesso a todos filmes desde os recém-lançados até mesmo aqueles que você achou que nunca mais iria ver de novo. Com essa fusão de diferentes universos em um único império, proporcionando aos fãs uma experiencia rica, diversificada e única.\n\n");
                printf("  Espero que vocês tenham gostado de mais uma exploração sobre as Aquisições da Disney e de como elas transformaram o mundo do entretenimento. Eai, estão prontos para continuar explorando este incrível museu?\n\n");

                printf("Hora de testar seus conhecimentos:\n\n");
                printf("Qual é uma das franquias mais famosas criada pela Lucasfilm?\n\n");
                printf("a)Star Wars\n");
                printf("b)X-Men\n");
                printf("c)Shrek\n");
                printf("d)Senhor dos aneis\n");

                fflush(stdin);

                char resposta7;

                scanf("%c", &resposta7);

                switch (resposta7)
                {
                case 'a':
                    printf("Resposta Correta\n Parabéns!!\n\n");
                break;
                
                default:
                    printf("Resposta incorreta\nA resposta era:\nStarWars\n\n");
                break;
                }

                fflush(stdin);

                printf("Vamos falar agora sobre o impacto cultural da Disney na sociedade\n\n");

                printf("  Acredito que maioria das pessoas hoje aqui sabem quem é a Disney e o que ela faz. O impacto da Disney é bem grande abrangendo diversas áreas incluindo entretenimento, globalização e obviamente a nossa deliciosa infância.\n\n");
                printf("  Pra começar de forma bem divertida vamos começar pelas incríveis histórias e os personagens cativantes, a Disney é famosa por suas histórias magicas que te fazem ficar vidrado na tela a cada segundo exibido. Acompanhado com personagens incríveis como o famoso Mickey Mouse e Cinderela por exemplo que tenho certeza de que vocês devem conhecer. Com essas histórias têm inspirado narrativas em filmes, programas de televisão e livros em todo mundo.\n\n");
                printf("  Aposto que muitas vezes você fechou seus olhos por uns segundos e se imaginou dentro daquele mundo magico, não é? Imagine você em um mundo de conto de fadas com princesas e outras criaturas magicas, o mais legal disso tudo é que Disney tornou isso em realidade com seus lindos parques temáticos. Eles estabeleceram um padrão para parques de diversões pelo mundo, proporcionando experiências únicas e é claro inesquecível!\n\n");
                printf("  Quem aqui cresceu assistindo a filmes da Disney? Aqueles dias chuvosos na frente da telinha vendo seu filme preferido, com um tempo foram surgindo series também que abraçaram um grande público. A Disney tem desempenhado um papel fundamental na infância de muitas gerações influenciando suas visões de mundo e valores por meio de suas animações.\n\n");
                printf(" Agora me responde uma pergunta, você já notou que os produtos da Disney estão em toda parte?");
                    //pensar em uma interação de sim ou não para fazer uma ligação com o próximo parágrafo
                printf("  Claro que com esse incrível mundo a gente sempre vai desejar algo, como por exemplo o Xerife Woody que em seu filme Toy Story ele realmente é um brinquedo e com isso a marca Disney criou o seu próprio Woddy para colecionadores e fãs apaixonados, legal né? Esse é só um dos exemplos de diversas coisas que tem desde brinquedos até roupas.\n\n");
                printf("  Não tem como a gente deixar de fora os avanços tecnológicos da Disney, como a animação e os efeitos especiais que crescem filme após filme, isso influenciou a indústria do entretenimento, tornando nossos filmes e programas favoritos e ainda mais emocionantes de serem assistidos.\n\n");
                printf("  Algo muito interessante é que nos últimos anos, a Disney tem feito esforços para promover a diversidade e a inclusão em suas produções, algo muito importantes atualmente e assim influenciando a conversa sobre a representação na mídia.\n\n");
                printf("  Em um resumo, a Disney é muito maior que apenas um estúdio de filmes. Ela é uma parte da nossa cultura, moldando nossas histórias e a pessoa que nos tornamos, memorias de infância do seu pai, seu filho e futuramente do seu neto. Espero que tenham gostado desta viagem pelo impacto cultural da Disney. Prontos para continuar a nossa jornada explorando o museu?\n\n");

                printf("Hora de testar seus conhecimentos:\n");
                printf("O quanto você gosta da disney?\n");
                printf("Digite um número de um a cinco\n");

                char resposta8;

                scanf("%c", &resposta8);

                switch (resposta8)
                {
                case 1:
                    printf("Só isso?!?\n");
                    break;
                case 2:
                    printf("Que pena.\n");
                break;
                case 3: 
                    printf("Mediano, ok\n");
                break;
                case 4:
                    printf("Que legal!!\n");
                break;
                case 5:
                    printf("Que íncrivel!! Você gosta muito da disney!!\n");
                default:
                    printf("Essa não foi uma resposta válida\n");
                break;
                }

                printf("Agora ver um um pouco sobre a história dos Parques temáticos da disney:\n\n  Eles são destinos de entretenimento mundialmente famosos que desempenham um papel significativo na história do turismo e do entretenimento.\n\n");
                printf("  O primeiro parque temático da Disney, a Disneyland na Califórnia, foi inaugurado em 17 de julho de 1955. Foi concebido por Walt Disney como um lugar onde famílias inteiras poderiam se divertir juntas, oferecendo uma experiência única e mágica. O parque original apresentava áreas temáticas, como Adventureland, Frontierland, Fantasyland e Tomorrowland, e rapidamente se tornou um sucesso.\n\n");
                printf("  Os parques temáticos da Disney desempenharam um papel importante na formação da cultura popular. Os personagens, histórias e temas da Disney são reconhecidos globalmente, tornando-se parte integrante da infância de muitas gerações. Os parques também influenciaram a forma como as pessoas se divertem e consomem entretenimento.\n\n  Eles também são destinos de alto impacto econômico. Atraindo milhões de visitantes de todo o mundo, contribuindo para o turismo local e regional. Esses visitantes gastam dinheiro em hotéis, restaurantes, lojas e outras atividades, gerando empregos e estimulando o desenvolvimento econômico nas áreas circundantes.\n\n");
                printf("  A Disney é conhecida por sua inovação em tecnologia e entretenimento. Os parques introduziram várias tecnologias e técnicas inovadoras, como áudio animatrônicos, sistemas de filas virtuais, realidade aumentada e aperfeiçoamento das experiências de realidade virtual, influenciando a indústria do entretenimento.\n\n  Os parques da Disney promovem a imaginação e a criatividade, transportando os visitantes para mundos mágicos e histórias emocionantes. Isso tem um impacto positivo na criatividade das crianças e adultos, inspirando-os a sonhar e acreditar no poder da imaginação.\n\n  Além disso, eles oferecem oportunidades educacionais, com exposições e atrações que ensinam sobre história, cultura, ciência e conservação ambiental. Essas experiências educativas ajudam a tornar o aprendizado mais envolvente e acessível.\n\n  A Disney enfatiza a experiência familiar, criando ambientes onde pessoas de todas as idades podem se divertir juntas. Isso reforça a importância do tempo de qualidade em família e da criação de memórias compartilhadas.\n\n  Promove valores como amizade, tolerância, coragem e a importância do trabalho em equipe, através das histórias e personagens que são incorporados nas atrações.\n\n  A Disney também tem mostrado preocupação com a conservação ambiental e promove a sustentabilidade em seus parques, ajudando a aumentar a conscientização sobre questões ambientais entre seus visitantes.\n\n");

                printf("Hora de testar seus conhecimentos:\n\n");
                printf("Qual são os valores que a Disney promove?\n\n");
                printf("a) Amizade, tolerância e coragem.\nb) Amizade, inveja e coragem.\nc)Coragem, desonestidade e inveja.\nd) Coragem, tolerância e inveja.");

                int resposta9;
                scanf("%d", resposta9);

                switch (resposta9)
                {
                case 'a':
                        printf("Resposta correta!\n Parabéns\n");
                break;
                
                default:
                    printf("Resposta incorreta\n A resposta correta era:\n  Amizade, tolerância e coragem.\n");
                    break;
                }

                printf("Vamos para o próximo tema: Museus e exposições da Disney.\n\n  A Disney possui vários museus e exposições dedicados a contar a história e celebrar a magia da empresa e seus personagens icônicos. Aqui estão alguns dos mais notáveis:\n\n");
                printf("1. Walt Disney Family Museum:\n\n  Localizado em San Francisco, Califórnia, este museu é dedicado a Walt Disney, o fundador da Disney. Ele conta a história de sua vida, sua carreira no cinema de animação e seus inúmeros feitos, incluindo a criação da Disneylândia. O museu inclui uma coleção impressionante de artefatos, fotografias e documentos relacionados à vida de Walt Disney. Anteriormente uma base ativa do Exército e a defesa costeira mais forte da costa do Pacífico de 1846 a 1994, o Presidio agora serve como parque nacional e abriga o Museu da Família Walt Disney. Construído em 1897, o Quartel 104 - como era chamado anteriormente - fazia parte de uma fileira de enormes quartéis do Exército de tijolos na Montgomery Street, construídos para abrigar soldados. Muito antes de o museu se mudar, o prédio foi despojado de todas as suas históricas paredes internas, tetos e acabamentos pelo Exército.\n\n");
                printf("2. Walt Disney Archive:\n\n  Os Arquivos Disney mantêm uma coleção extensa de artefatos, figurinos, memorabilia e documentos históricos relacionados à Disney. Embora não seja um museu público, os itens dos Arquivos frequentemente são emprestados para exposições temporárias em museus de todo o mundo.\n\n  Os Arquivos Walt Disney começaram em 1970, enquanto a Disney ainda se recuperava do falecimento de seu fundador, Walt Disney. Na época, o irmão de Walt e presidente do conselho, Roy O. Disney, queria garantir que, à medida que os principais imaginadores e animadores começassem a se aposentar, seu vasto conhecimento da história da Disney não fosse esquecido.\n\n  Quis o destino que Dave Smith, que na época pesquisava na biblioteca da UCLA, ouvisse executivos da Disney discutindo a criação de um arquivo da empresa. Dave decidiu dar um salto e apresentar-lhes um plano para colocar um em ação e, em 22 de junho de 1970, foi oficialmente contratado como o primeiro arquivista da Disney. Fale sobre estar no lugar certo na hora certa!\n\n");
                printf("3. Exposições itinerantes:\n\n  A Disney frequentemente realiza exposições itinerantes que viajam para diferentes cidades. Essas exposições apresentam uma variedade de itens relacionados à Disney, como trajes, arte conceitual, animações e muito mais.\n\n  'A The Walt Disney Company completa 100 anos este ano, criada em 1923, a empresa fará uma exposição itinerante que remonta a trajetória da marca por meio de objetos e tecnologias imersivas.\n\n  Com um século de existência, serão elaboradas 10 galerias que contarão com fotos, figurinos, adereços e outros objetos originais. Além disso, serão usados áudios e elementos interativos e imersivos para enriquecer a experiência. '\n\n");
                printf("4. Exposições em parques temáticos:\n\n  Os parques temáticos da Disney frequentemente apresentam exposições temporárias que celebram os filmes e personagens da Disney. Por exemplo, o em Orlando, Flórida, costuma sediar exposições relacionadas a filmes da Disney e da Pixar.\n\n  Lembre-se de que as exposições e museus da Disney podem variar ao longo do tempo e em diferentes específicos que você deseja visitar.\n\n");

                printf("E aí? Qual dos parques você mais gostaria de visitar?\n\n a) Walt Disney Family Museum\nb) Walt Disney Archive\nc) Exposições itinerantes\nd) Exposições em parques temáticos\n\n");

                int resposta10;
                scanf("%d", resposta10);
                switch (resposta10)
                {
                case 'a':
                    printf("Que legal!! O Walt Disney Family Museum é um museu muito interessante para conhecer a história de Walt.");
                    break;
                case 'b':
                    printf("Que escolha interessante! Esse museu tem muito sobre a história da disney nas telas, pena que não é aberto ao público, mas você ainda pode ter a oportunidade de ver os artefatos históricos nas exposições temporárias");
                break;
                case 'c':
                    printf("Que legal!! Só corra e fique de olho nas datas no site para saber onde a exposição irá estar.");
                break;
                case 'd':
                    printf("Que escolha interessante!! Nela você terá uma experiência única, pois a cada exposição trazem itens diferentes, inclusive alguns do Walt Disney Archive.");
                break;
                }

                printf("Agora vamos ver um pouco sobre o impacto da Disney na educação:\n\n");
                printf("  A Disney teve um impacto significativo no campo da educação de várias maneiras ao longo de muitos anos. Aqui estão algumas das principais contribuições e influências educacionais da Disney:\n\n");
                printf("Aprendizado lúdico:\n  A Disney é conhecida por suas histórias envol ventes e personagens cativantes, que muitas vezes incorporam lições morais e éticas.\n\n  Isso torna os filmes da Disney e programas de televisão atrativos para crianças, ajudando a transmitir valores importantes de uma maneira divertida.\n\n");
                printf("Parques temáticos educacionais:\n  A Disney opera parques temáticos em todo o mundo, como a Disneylândia e o Walt Disney World. Esses parques oferecem oportunidades educacionais em diversas áreas, desde ciência e tecnologia até história e cultura. Eles também promovem a criatividade e a imaginação, essenciais para o desenvolvimento da criança.\n\n");
                printf("Materiais educacionais:\n  A Disney produz uma variedade de materiais educacionais, desde livros até jogos interativos. Muitos desses materiais usam personagens e histórias da Disney para ensinar conceitos educacionais, como leitura, matemática e ciências.\n\n");
                printf("Programas de filmes educacionais na mídia:\n Além dos e programas de televisão, a Disney também produz conteúdo educacional direto, como o Disney Junior, que visa crianças pré-escolares e apresenta programas que ensinam habilidades sociais e emocionais, bem como conceitos educacionais básicos.\n");
                printf("Inovações tecnológicas:\n  A Disney tem investido em tecnologias educacionais, como realidade virtual e aumentada, para melhorar a experiência de aprendiz agem e torná-la mais envolvente. Essas tecnologias são usadas em parques temáticos e outros contextos educacionais.\n\n");
                printf("Programas de bolsas de estudo:\n  A Disney também oferece programas de bolsas de estudo e projetos para estudantes, apoiando a educação de jovens talentos em áreas relacionadas ao entretenimento, cinema, animação e muito mais.\n\n");
                printf("No entanto, é importante observar que, embora a Disney tenha um impacto educacional positivo em muitos aspectos, também há preocupações sobre o marketing de produtos relacionados à marca Disney e seu impacto nas crianças, bem como questões de diversidade e representação em seu conteúdo.\n\n");

                printf("Hora de testar seus conhecimentos:\n\n");
                printf("Qual desses não é um impacto educacional da Disney citado na apresentação?\n\na) Parques temáticos educacionais\nb) Inovações tecnológicas\nc) Programas de bolsas de estudo\n d) Luta contra desigualdade social\n\n");

                int resposta11;
                scanf("%d", resposta11);
                switch (resposta11)
                {
                case 'd':
                    printf("Resposta correta!!");
                break;
                default:
                    printf("Resposta errada\n A resposta correta era: \nA luta contra a desigualdade social\n\n");
                break;
                }

                printf("Por último mas não menos importante, vamos falar sobre a influência da Disney na indústria do entretenimento!\n\n");
                printf("  Há muito tempo, no início do século XX, um visionário chamado Walt Disney tinha um sonho extraordinário. Ele acreditava que o entretenimento podia ser uma  força poderosa para cativar e unir as pessoas. Com sua determinação e criatividade sem limites, ele lançou as bases para o império da Disney e, por conseguinte, sua influência duradoura na indústria do entretenimento.\n\n  Walt Disney nasceu em Chicago em 1901 e desenvolveu o seu interesse pelos desenhos muito cedo. Aos 4 anos, ele se mudou para uma fazenda, onde foi exposto à natureza, animais e a vida de uma pequena cidade. Isso fez com que a sua imaginação disparasse e pudesse expandir sem as limitações que uma cidade grande pode oferecer.\n\n  Walt Disney começou sua carreira desenhando cartuns e, posteriormente, fundou seu próprio estúdio de animação, o que viria a se tornar a Walt Disney Company. Em 1928, a criação de Mickey Mouse com Steamboat Willie marcou o início da revolução da animação, introduzindo som sincronizado em desenhos animados e estabelecendo um novo padrão de qualidade.\n\n  A primeira produção do Disney Brothers Cartoon Studio veio no ano da sua fundação. Era uma série chamada Alice Comedies (algo como 'Comédias da Alice'), que misturava motion picture de fotografia com animação. Foi a primeira de várias produções nesse estilo feitas pelo estúdio.\n\n  Ao longo dos anos, a Disney expandiu seus horizontes, entrando na televisão e abrindo o primeiro parque temático da Disney, a Disneyland, em 1955. A série 'O Mickey Mouse Club' e o programa “Walt Disney's Wonderful World of Color' conquistaram audiências na TV, enquanto os parques temáticos redefiniram o conceito de entretenimento familiar.");
                printf("A expansão na mídia americana:\n\n  Apesar de ter lançado inúmeros filmes, programas e conteúdos televisivos, a Disney sempre fez isso em canais de terceiros. Canais já estabelecidos no cenário americano e mundial, entretanto em 1983, a empresa lançou o primeiro canal de televisão e o usou para distribuir seus conteúdos, além de promover as próprias atividades e eventos, como a inauguração dos seus parques temáticos.\n\n");
                printf("Expansão midiática internacional: \n\n  Como visto, a Disney direcionou seus focos para a criação de um canal próprio em 1983. Pouco depois, a empresa expandiu o seu alcance, lançando canais em Taiwan, no Reino Unido e Malásia.\n\n  Havia um motivo específico para isso. Uma vez que tivesse cativado os fãs desses países, poderia divulgar e lucrar com os parques que seriam inaugurados nesses lugares.\n\n  A Disney soube muito bem como espalhar a sua influência para construir um império nos mais diferentes segmentos. Dito isso, mesmo com os parques sendo extremamente lucrativos, eles nunca tiraram o lugar que a mídia ocupa como principal fonte de receita da empresa.\n\n  Apesar do sucesso da empresa, o falecimento de Walt, em 1966, foi um baque do qual a Disney não se recuperou tão rápido. Principalmente na área criativa. Os filmes já não cativaram o público como anteriormente e a falta de personagens memoráveis começou a afetar até mesmo os parques temáticos.\n\n  Os parques da Disney utilizaram fortemente a população local para se manterem abertos. Entretanto, para atrair essa população, que visita o parque com frequência, mudanças pontuais são necessárias para manter o público interessado. A falta de grandes filmes ou personagens permitiu apenas algumas mudanças nos parques desde 1964.\n\n  Dessa forma, algumas das mais extraordinárias mudanças e expansões aconteceram durante a primeira década do mandato de Michael Eisner como CEO da Walt Disney Company. Mandato esse que durou 21 anos (1984-2005).\n\n  Como líder da companhia, ele foi ousado e calculista, realizando movimentos estratégicos que expandiram a Disney para mercados internacionais e mantiveram a empresa viva durante momentos difíceis.\n\n  A influência da Disney se estendeu ainda mais com a aquisição de outras marcas, como a Pixar, Marvel e Lucasfilm, permitindo a criação de franquias de sucesso como 'Toy Story', 'Os Vingadores' e 'Star Wars'.\n\n  Hoje,a Disney é um império global do entretenimento, influenciando a cultura popular, lançando tendências de mercado, e continuando a encantar o público com filmes de animação, parques temáticos e plataformas de streaming, como o Disney+.\n\n  Assim, a história de como a Disney desenvolveu sua influência na indústria do entretenimento é uma jornada extraordinária de inovação, criatividade e perseverança, que deixou um legado duradouro que continua a encantar e inspirar pessoas em todo o mundo.\n\n");
                printf("E assim chegamos ao fim de nossa apresentação sobre a história dessa grande empresa que conquista a muitos anos os corações de todos.\nEspero que todos tenham gostado.");

                //colocar algo que faça o ingresso não ser mais válido
            break;

            case 5:
                /*lista de clientes*/
                /*talvez adicionar uma forma de login de administrador para acesso deste caso*/
            file2 = fopen("infoCli.csv", "r");
            if (numDados > 0)
            {
                int i;
                for (i = 1; i < numDados; i++)
                {
                    printf("Cadastro %d:\n", i);
                    printf("Nome: %s\n", dados[i].nomeCli);
                    printf("Telefone: %s\n", dados[i].telefoneCli);
                    printf("Email: %s\n", dados[i].emailCli);
                    printf("Cidade: %s\n", dados[i].cidadeCli);
                    printf("Ticket: %7.f\n", dados[i].numeroTicket);
                    printf("Tipo do Ingresso: %d\n", dados[i].tipoIngresso);
                    printf("Horário da sessão: %d\n", dados[i].horarioSessao);
                    printf("genero: %d\n", dados[i].genero);
                    printf("idade: %d\n", dados[i].idade);
                    printf("\n");
                }
            }
            else
            {
                printf("Nenhum registro encontrado.\n");
            }
            fclose(file2);
            break;

            case 6:
                /*lista funcionários*/
                /*talvez adicionar uma forma de login de administrador para acesso deste caso*/
                file = fopen("info.csv", "r");
                if(numRecord > 0){
                    for(int i = 1; i < numRecord; i++){
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
                fclose(file);
            break;
            case 7:
                /*editar dados funcionários*/
                /*talvez adicionar uma forma de login de administrador para acesso deste caso*/
                printf("Digite o número do registro que deseja acessar 1-%d: \n", numRecord);
                int registroEdicaoF;
                scanf("%d", &registroEdicaoF);

                fflush(stdin);

                if (registroEdicaoF >= 1 && registroEdicaoF <= numRecord){ //verifica se o numero dado esta dentro da lista de registros disponiveis
                    printf("Editando registro %d:\n", registroEdicaoF);

                    printf("Digite o novo nome: \n");
                    fgets(records[registroEdicaoF - 1].nome, sizeof(records[registroEdicaoF - 1].nome), stdin);
                    records[registroEdicaoF - 1].nome[strcspn(records[registroEdicaoF - 1].nome, "\n")] = '\0';

                    printf("Digite o novo telefone: \n");
                    fgets(records[registroEdicaoF - 1].telefone, sizeof(records[registroEdicaoF - 1].telefone), stdin);
                    records[registroEdicaoF - 1].telefone[strcspn(records[registroEdicaoF - 1].telefone, "\n")] = '\0';

                    printf("Digite o novo email: \n");
                    fgets(records[registroEdicaoF - 1].email, sizeof(records[registroEdicaoF - 1].email), stdin);
                    records[registroEdicaoF - 1].email[strcspn(records[registroEdicaoF - 1].email, "\n")] = '\0';

                    printf("Digite o novo bairro: \n");
                    fgets(records[registroEdicaoF - 1].bairro, sizeof(records[registroEdicaoF - 1].bairro), stdin);
                    records[registroEdicaoF - 1].bairro[strcspn(records[registroEdicaoF - 1].bairro, "\n")] = '\0';

                    printf("Digite a nova cidade: \n");
                    fgets(records[registroEdicaoF - 1].cidade, sizeof(records[registroEdicaoF - 1].cidade), stdin);
                    records[registroEdicaoF - 1].cidade[strcspn(records[registroEdicaoF - 1].cidade, "\n")] = '\0';

                    printf("Digite o novo pais: \n");
                    fgets(records[registroEdicaoF - 1].pais, sizeof(records[registroEdicaoF - 1].pais), stdin);
                    records[registroEdicaoF - 1].pais[strcspn(records[registroEdicaoF - 1].pais, "\n")] = '\0';

                    printf("Digite a nova senha: \n");
                    fgets(records[registroEdicaoF - 1].senha, sizeof(records[registroEdicaoF - 1].senha), stdin);
                    records[registroEdicaoF - 1].senha[strcspn(records[registroEdicaoF - 1].senha, "\n")] = '\0';
                   }
                else{
                        printf("Número de registro ínvalido.\n");
                }

            break;
            case 8:

                /*editar dados clientes*/
                /*talvez adicionar uma forma de login de administrador para acesso deste caso*/
                printf("Digite o número do registro a ser acessado 1-%d", numDados);

                int registroEdicaoC;
                scanf("%d", registroEdicaoC);

                fflush(stdin);

                printf("Digite o novo nome: ");
                fgets(dados[registroEdicaoC - 1].nomeCli, sizeof(dados[registroEdicaoC - 1].nomeCli), stdin);
                dados[registroEdicaoC - 1].nomeCli[strcspn(dados[registroEdicaoC - 1].nomeCli, "\n")] = '\0';

                printf("Digite o novo telefone: ");
                fgets(dados[registroEdicaoC - 1].telefoneCli, sizeof(dados[registroEdicaoC - 1].telefoneCli), stdin);
                dados[registroEdicaoC - 1].telefoneCli[strcspn(dados[registroEdicaoC - 1].telefoneCli, "\n")] = '\0';

                printf("Digite o novo email: ");
                fgets(dados[registroEdicaoC - 1].emailCli, sizeof(dados[registroEdicaoC - 1].emailCli), stdin);
                dados[registroEdicaoC - 1].emailCli[strcspn(dados[registroEdicaoC - 1].emailCli, "\n")] = '\0';

                printf("Digite a nova cidade: ");
                fgets(dados[registroEdicaoC - 1].cidadeCli, sizeof(dados[registroEdicaoC - 1].cidadeCli), stdin);
                dados[registroEdicaoC - 1].cidadeCli[strcspn(dados[registroEdicaoC - 1].cidadeCli, "\n")] = '\0';

                printf("Digite o novo gênero: \n");
                printf("1. Mulher cis\n\n2. Homem cis\n\n3. Mulher trans\n\n4. Homem trans\n\n5. Não Binário\n\n6. Outro\n\n7. Prefiro não dizer\n\n");    
                int generoVar;
                scanf("%d", &generoVar);
                dados[registroEdicaoC - 1].genero = generoVar;

                printf("Digite a nova idade: ");
                int idadeVar;
                scanf("%d", &idadeVar);
                dados[numDados-1].idade = idadeVar;

                printf("Deseja mudar informações do ingresso também?\n");

                printf("1. Sim\n2. Não\n");

                int EdicaoIngresso;

                scanf("%d", EdicaoIngresso);

                if(EdicaoIngresso = 1){
                    printf("Digite o novo horário da sessao: \n");
                    printf("Sessões diponiveis: \n 1. 9hrs \n 2. 12 hrs \n 3. 16 hrs \n 4. 20 hrs\n");
                    int horario;
                    scanf("%d", &horario);
                    dados[registroEdicaoC-1].horarioSessao = horario;

                    
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
                    
                    printf("Digite o novo horario: \n");
                    int entrada;
                    scanf("%d", &entrada);
                    dados[registroEdicaoC-1].tipoIngresso = entrada;

                    switch (entrada)
                    {
                    case 1:
                        printf("Você escolheu entrada inteira\n");
                    break;
                    case 2:
                        printf("Você escolheu entreda meia\n");
                    break;
                    default:
                        printf("Opção inválida");
                    break;
                    }

                    float ticket = rand()%10000;

                    printf("Aqui esta o novo código do ticket %.7f\n", ticket);
                    dados[registroEdicaoC - 1].numeroTicket = ticket;

                }
                else{
                    printf("Edição de cadastro e ingressos concluída com sucesso!");
                }

                printf("Edição de cadastro concluída com sucesso!");
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
                    printf("Erro ao abrir o arquivo para salvar os dados de funcionarios.\n");
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
    system("PAUSE");
    return 0;
}

