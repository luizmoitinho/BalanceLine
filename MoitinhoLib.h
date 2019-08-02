int lengthClientes=0,lengthMaster=0,lengthTransacao=0,lengthLog=0;
typedef struct{
    char nome[50];
    char cpf[12];
    int numConta;
    int digitoConta;
    int agencia;
    int senha;
    float saldo;
} BASE_CLIENTES;
typedef struct{
    int numContaR,numContaD;
    int digitoContaR,digitoContaD;
    int agencia;
    int codigo;
    float valor;
    char flag;
    char status[20];
} ARQUIVO_TRANSACAO;
int menu();
int viewHome();
void setClientes();
void msgFalha();
void msgSucesso();
void msgLoginNegado();
void toStringCliente(BASE_CLIENTES aux);
void createAccount(BASE_CLIENTES *cliente);
void pushCliente(BASE_CLIENTES lista[], BASE_CLIENTES cliente);
void loadClientes(char name[],  BASE_CLIENTES lista[]);
void writeClientes(char nome[],BASE_CLIENTES clientes[]);
void loadTransacao(char name[],  ARQUIVO_TRANSACAO lista[]);
void writeTransacao(char nome[],ARQUIVO_TRANSACAO clientes[]);
void toStringTransacao(ARQUIVO_TRANSACAO transacao);
void detalheConta(BASE_CLIENTES cliente);
int searchCliente(BASE_CLIENTES lista[], int cliente);
void insertSort(BASE_CLIENTES lista[]);
void toStringCliente(BASE_CLIENTES aux);
void setSaque(ARQUIVO_TRANSACAO *newTransacao, char tipo,BASE_CLIENTES cliente);
void setDeposito(ARQUIVO_TRANSACAO *newTransacao, char tipo,BASE_CLIENTES cliente);
void setTransferencia(ARQUIVO_TRANSACAO *newTransacao, char tipo,BASE_CLIENTES cliente);
void pushTransacao(ARQUIVO_TRANSACAO transacoes[], ARQUIVO_TRANSACAO aux);



int menu(BASE_CLIENTES cliente[],int session){
    int opt;
    printf("\n\t MTI BANK | %5s -  %d/%d \n",cliente[session].nome,cliente[session].numConta,cliente[session].agencia);
    printf("\n\t[ 1 ] - SAQUE ");
    printf("\n\t[ 2 ] - DEPÓSITO ");
    printf("\n\t[ 3 ] - TRANSFERÊNCIA");
    printf("\n\t[ 4 ] - MINHA CONTA");
    printf("\n\t[ 6 ] - SAIR");
    printf("\n\n\t\t#OPERACAO: ");
    scanf("%d",&opt);
    return opt;
}
int viewHome(){
    int opt;
    printf("\n\t\t MTI BANK\n");
    printf("\n\t[ 1 ] - ENTRA ");
    printf("\n\t[ 2 ] - CRIAR CONTA ");
    printf("\n\n\t\t#OPERACAO: ");
    scanf("%d",&opt);
    return opt;
}
void setClientes(BASE_CLIENTES *aux){
    fflush(stdin);
    printf("\n\t\tMTI BANK - ENTRAR\n");
    printf("\n\tNº Conta   :  ");
    scanf("%d",&aux->numConta);
    printf("\tSenha   :  ");
    scanf("%d",&aux->senha);
}
void createAccount(BASE_CLIENTES *cliente){
    fflush(stdin);
    printf("\n\t\t MTI BANK - CRIAR CONTA\n");
    printf("\n\t\tDADOS PESSOAIS");
    printf("\n\tnome :");
    gets(cliente->nome);
    printf("\n\tCPF :");
    gets(cliente->cpf);
    printf("\n\t\tDADOS DA CONTA");
    printf("\n\tNúmero:");
    scanf("%d",&cliente->numConta);
    printf("\n\tDigito:");
    scanf("%d",&cliente->digitoConta);
    printf("\n\tAgência:");
    scanf("%d",&cliente->agencia);
    printf("\n\tSenha:");
    scanf("%d",&cliente->senha);
    cliente->senha=0;
}

void pushCliente(BASE_CLIENTES lista[], BASE_CLIENTES cliente){
    lista[lengthClientes++]=cliente;
}
int searchCliente(BASE_CLIENTES lista[], int cliente){
    int inicio=0, fim = lengthClientes;
    int meio;
    while(inicio<=fim){
        meio = (inicio+fim)/2;
        if(lista[meio].numConta == cliente)
            return meio;
        else if(lista[meio].numConta < cliente)
            inicio = meio+1;
        else
            fim = meio-1;
    }
    return -1;
}

void detalheConta(BASE_CLIENTES cliente){
    printf("\n\t\tDETALHES DA CONTA\n");
    printf("\n\tNúmero     : %d",cliente.numConta);
    printf("\n\tDígito     : %d",cliente.digitoConta);
    printf("\n\tAgência    : %d",cliente.agencia);
    printf("\n\tTitular    : %s",cliente.nome);
    printf("\n\tCPF        : %s",cliente.cpf);
    printf("\n\tSaldo      : %.2f\n",cliente.saldo);
    printf("\n\n");
    //Criar o método que percorre os dados que estão no arquivo mestre e achar o saldo atual do cliente.
}
//================ MANIPULAÇÃO DE ARQUIVOS BINARIOS =================
void writeTransacao(char nome[],ARQUIVO_TRANSACAO clientes[]){
    FILE *arquivo = fopen(nome,"wb");
    if(arquivo!=NULL)
        fwrite(clientes,sizeof(ARQUIVO_TRANSACAO),lengthTransacao,arquivo);
    fclose(arquivo);
}
void loadTransacao(char name[],  ARQUIVO_TRANSACAO lista[])
{
    FILE * arquivo = fopen(name,"rb");
    if(arquivo!=NULL)
    {
        int counter=0;
        ARQUIVO_TRANSACAO aux;
        while(fread(&aux,sizeof(ARQUIVO_TRANSACAO),1,arquivo))
        {
            *(lista+counter) = aux;
            counter++;
        }
        lengthTransacao=counter;
    }
    else
    {
        FILE *arquivo2 = fopen(name,"wb");
        fclose(arquivo2);
    }
    fclose(arquivo);

}

void loadLog(char name[],  ARQUIVO_TRANSACAO lista[])
{
    FILE * arquivo = fopen(name,"rb");
    if(arquivo!=NULL)
    {
        int counter=0;
        ARQUIVO_TRANSACAO aux;
        while(fread(&aux,sizeof(ARQUIVO_TRANSACAO),1,arquivo))
        {
            *(lista+counter) = aux;
            counter++;
        }
        lengthLog=counter;
    }
    else
    {
        FILE *arquivo2 = fopen(name,"wb");
        fclose(arquivo2);
    }
    fclose(arquivo);

}
void writeClientes(char nome[],BASE_CLIENTES clientes[])
{
    FILE *arquivo = fopen(nome,"wb");
    if(arquivo!=NULL)
        fwrite(clientes,sizeof(BASE_CLIENTES),lengthClientes,arquivo);
    fclose(arquivo);
}
void loadClientes(char name[],  BASE_CLIENTES lista[])
{
    FILE * arquivo = fopen(name,"rb");
    if(arquivo!=NULL)
    {
        int counter=0;
        BASE_CLIENTES aux;
        while(fread(&aux,sizeof(BASE_CLIENTES),1,arquivo))
        {
            *(lista+counter) = aux;
            counter++;
        }
        lengthClientes=counter;
    }
    else
    {
        FILE *arquivo2 = fopen(name,"wb");
        fclose(arquivo2);
    }
    fclose(arquivo);
}

//=========================== MÉTODO DE ORDENAÇÃO ================
void insertSort(BASE_CLIENTES lista[]){
    int i,j;
    BASE_CLIENTES aux;
    for(i = 1;i<lengthClientes;i++){
        aux = lista[i];
        j=i-1;
        while(j>=0 && strcmp(lista[j].cpf,aux.cpf)>0){
            lista[j+1] =  lista[j];
            j--;
        }
        lista[j+1]=aux;
    }
}


void bubbleSort(BASE_CLIENTES lista[]){
    BASE_CLIENTES aux;
    for(int i=0;i<lengthClientes-1;i++){
        for(int j=0;j<lengthClientes-1;j++){
            if(lista[j].numConta>lista[j+1].numConta){
                aux=lista[j];
                lista[j]=lista[j+1];
                lista[j+1]=aux;
            }
        }
    }
}
void  toStringCliente(BASE_CLIENTES aux){
    printf("%s,%s - %d-%d-%d (%d)",aux.nome,aux.cpf,aux.numConta,aux.digitoConta,aux.agencia,aux.senha);
}
void toStringTransacao(ARQUIVO_TRANSACAO transacao){
    printf("Nº ContaD: %d | Nº DigitoContaD: %d | Nº ContaR: %d | Nº DigitoContaR: %d \n",transacao.numContaD,transacao.digitoContaD,transacao.numContaR,transacao.digitoContaR);
    printf("Agência: %d | Código: %d | valor: %.2f | flag:%c | status: %s\n\n",transacao.agencia,transacao.codigo,transacao.valor,transacao.flag,transacao.status);
}
//============================  SET DADOS =====================
void setSaque(ARQUIVO_TRANSACAO *newTransacao, char tipo,BASE_CLIENTES cliente){
    printf("\n\t\tDADOS SAQUE\n\n");
    printf("\n Valor       : ");
    scanf("%f",&newTransacao->valor);
    newTransacao->codigo =  lengthTransacao;
    newTransacao->flag = tipo;
    newTransacao->numContaD =  cliente.numConta;
    newTransacao->digitoContaD= cliente.digitoConta;
    strcpy(newTransacao->status,"ANALISE");
    msgSucesso();
}
void setDeposito(ARQUIVO_TRANSACAO *newTransacao, char tipo,BASE_CLIENTES cliente){
    printf("\n\t\tDADOS DEPÓSITO\n\n");
    printf("\n Valor       : ");
    scanf("%f",&newTransacao->valor);
    newTransacao->codigo =  lengthTransacao;
    newTransacao->flag = tipo;
    newTransacao->numContaD=cliente.numConta;
    newTransacao->digitoContaD=cliente.digitoConta;
    strcpy(newTransacao->status,"ANALISE");
    msgSucesso();
}
void setTransferencia(ARQUIVO_TRANSACAO *newTransacao, char tipo,BASE_CLIENTES cliente){
    printf("\n\t\tDADOS TRANSFERÊNCIA\n\n");
    printf("\n Numero Conta Destino: ");
    scanf("%d",&newTransacao->numContaD);
    printf("\n Digito Conta Destino: ");
    scanf("%d",&newTransacao->digitoContaD);
    printf("\n Valor       : ");
    scanf("%f",&newTransacao->valor);
    newTransacao->codigo=lengthTransacao;
    newTransacao->flag = tipo;
    newTransacao->numContaR = cliente.numConta;
    newTransacao->digitoContaR = cliente.numConta;
    strcpy(newTransacao->status,"ANALISE");
    msgSucesso();
}

void wormTransacoes(char name_arq_transacao[],char name_arq_master[],char name_arq_log [],BASE_CLIENTES clientes[],ARQUIVO_TRANSACAO transacoes[],ARQUIVO_TRANSACAO logs[]){
    int pos_destino,pos_remetente;
    for(int i=0; i<lengthTransacao ;i++){
        pos_destino=-1;
        switch(transacoes[i].flag){
            case 'S':
                 pos_destino =  searchCliente(clientes,transacoes[i].numContaD);
                 if(clientes[pos_destino].saldo - transacoes[i].valor >=0){
                    clientes[pos_destino].saldo = clientes[pos_destino].saldo - transacoes[i].valor;
                    //modifyLog(name_arq_log,logs,transacoes[i].codigo,'SUCESSO');
                 }
               // else
                   // modifyLog(name_arq_log,logs,transacoes[i].codigo,'SALDO INSUFICIENTE');
                break;
            case 'D':
                pos_destino =  searchCliente(clientes,transacoes[i].numContaD);
                if(pos_destino!=-1){
                    clientes[pos_destino].saldo = transacoes[i].valor + clientes[pos_destino].saldo;
                   // modifyLog(name_arq_log,logs,transacoes[i].codigo,'SUCESSO');
                }
                //else
                   // modifyLog(name_arq_log,logs,transacoes[i].codigo,'CONTA NAO ENCONTRADA');
                break;
            case 'T':
                //busca a posicao da pessoa que será transferido o dinheiro
                pos_destino =  searchCliente(clientes,transacoes[i].numContaD);
                if(pos_destino!=-1){
                    pos_remetente = searchCliente(clientes,transacoes[i].numContaR);
                    if(clientes[pos_remetente].saldo  - transacoes[i].valor >=0){
                        clientes[pos_remetente].saldo = clientes[pos_remetente].saldo - transacoes[i].valor;
                        clientes[pos_destino].saldo   = clientes[pos_destino].saldo   + transacoes[i].valor;
                        //modifyLog(name_arq_log,transacoes[i].codigo,'SUCESSO');
                    }
                    //else
                       // modifyLog(name_arq_log,logs,transacoes[i].codigo,'SALDO INSUFICIENTE');
                }
              //  else
                   // modifyLog(name_arq_log,logs,transacoes[i].codigo,'CONTA DESTINO INCORRETA');
                break;
        }
    }
    writeClientes(name_arq_master,clientes);
    FILE *limpa_arquivo = fopen(name_arq_transacao,"wb");
    fclose(limpa_arquivo);
}
void modifyLog(char nome[],ARQUIVO_TRANSACAO logs[],int codigo,char erroLog[]){
    loadLog(nome,logs);

    for(int i=0; i<lengthLog;i++){
        if(codigo == logs[i].codigo){
            strcpy(logs[i].status,erroLog);
            break;
        }
    }
}

void pushTransacao(ARQUIVO_TRANSACAO transacoes[], ARQUIVO_TRANSACAO aux){
   transacoes[lengthTransacao++] = aux;
}

void msgSucesso(){
    printf("\n\t\tOperação realizada com sucesso!\n\n");
}
void msgFalha(){
    printf("\n\t\tErro ao efetuar a operação!\n\n");
}
void msgLoginNegado(){
    printf("\n\t\tCliente não cadastrado no sistema!\n\n");
}
