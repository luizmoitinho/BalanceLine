int lengthClientes=0,lengthMaster=0,lengthTransacao=0,lengthLog=0;
typedef struct{
    char nome[50];
    char cpf[12];
    int numConta;
    int digitoConta;
    int agencia;
    int senha;
} BASE_CLIENTES;
typedef struct{
    int codigo;
    BASE_CLIENTES cliente;
    float valor;
} ARQUIVO_MESTRE;
typedef struct{
    int numContaR,numContaD;
    int digitoContaR,digitoContaD;
    int agencia;
    int codigo;
    float valor;
    char flag;
    char status[20];
} ARQUIVO_TRANSACAO;
typedef struct{
    char flag;
    int numContaR,numContaD;
    float valor;
    char status[20];
}ARQUIVO_LOG;
int menu();
int viewHome();
void setClientes();

void msgFalha();
void msgSucesso();
void setSaque(ARQUIVO_TRANSACAO *newTransacao, char tipo);

void  toStringCliente(BASE_CLIENTES aux);
void createAccount(BASE_CLIENTES *cliente);
void pushCliente(BASE_CLIENTES lista[], BASE_CLIENTES cliente);
void loadClientes(char name[],  BASE_CLIENTES lista[]);
void writeClientes(char nome[],BASE_CLIENTES clientes[]);

void loadTransacao(char name[],  ARQUIVO_TRANSACAO lista[]);
void writeTransacao(char nome[],ARQUIVO_MESTRE clientes[]);

void loadMaster(char name[],  ARQUIVO_MESTRE lista[]);
void writeMaster(char nome[],ARQUIVO_TRANSACAO clientes[]);

int searchCliente(BASE_CLIENTES lista[], BASE_CLIENTES cliente);
void insertSort(BASE_CLIENTES lista[]);

int menu(BASE_CLIENTES cliente[],int session){
    int opt;

    printf("\n\t MTI BANK | %5s -  %d/%d \n",cliente[session].nome,cliente[session].numConta,cliente[session].agencia);
    printf("\n\t[ 1 ] - SAQUE ");
    printf("\n\t[ 2 ] - DEPÓSITO ");
    printf("\n\t[ 3 ] - TRANSFERÊNCIA");
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
    printf("\n\tCPF   :  ");
    gets(aux->cpf);
    printf("\tSenha  :  ");
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
}

void pushCliente(BASE_CLIENTES lista[], BASE_CLIENTES cliente){
    lista[lengthClientes++]=cliente;
}
int searchCliente(BASE_CLIENTES lista[], BASE_CLIENTES cliente){
    int inicio=0, fim = lengthClientes;
    int meio;
    while(inicio<=fim){
        meio = (inicio+fim)/2;
        if( strcmp(lista[meio].cpf,cliente.cpf)==0)
            return meio;
        else if ( strcmp(lista[meio].cpf,cliente.cpf)<0)
            inicio = meio+1;
        else
            fim = meio-1;
    }
    return -1;
}
//================ MANIPULAÇÃO DE ARQUIVOS BINARIOS =================
void writeMaster(char nome[],ARQUIVO_TRANSACAO clientes[])
{
    FILE *arquivo = fopen(nome,"wb");
    if(arquivo!=NULL)
        fwrite(clientes,sizeof(ARQUIVO_TRANSACAO),lengthMaster,arquivo);
    fclose(arquivo);
}
void loadMaster(char name[],  ARQUIVO_MESTRE lista[])
{
    FILE * arquivo = fopen(name,"rb");
    if(arquivo!=NULL)
    {
        int counter=0;
        ARQUIVO_MESTRE aux;
        while(fread(&aux,sizeof(ARQUIVO_MESTRE),1,arquivo))
        {
            *(lista+counter) = aux;
            counter++;
        }
        lengthMaster=counter;
    }
    else
    {
        FILE *arquivo2 = fopen(name,"wb");
        fclose(arquivo2);
    }
    fclose(arquivo);

}
void writeTransacao(char nome[],ARQUIVO_MESTRE clientes[])
{
    FILE *arquivo = fopen(nome,"wb");
    if(arquivo!=NULL)
        fwrite(clientes,sizeof(ARQUIVO_MESTRE),lengthTransacao,arquivo);
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
            if(strcmp(lista[j].cpf,lista[j+1].cpf)>0){
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

//============================  SET DADOS =====================
void setSaque(ARQUIVO_TRANSACAO *newTransacao, char tipo,BASE_CLIENTES cliente)
{
    newTransacao->flag = tipo;
    printf("\n\t\tDADOS SAQUE\n\n");
    newTransacao->numContaD =  cliente.numConta;
    newTransacao->digitoContaD= cliente.digitoConta;
    printf("\n Valor       : ");
    scanf("%f",&newTransacao->valor);
    msgSucesso();
}
void setDeposito(ARQUIVO_TRANSACAO *newTransacao, char tipo,BASE_CLIENTES cliente){
    newTransacao->flag = tipo;
    printf("\n\t\tDADOS DEPÓSITO\n\n");
    newTransacao->numContaD=cliente.numConta;
    newTransacao->digitoContaD=cliente.digitoConta;
    printf("\n Valor       : ");
    scanf("%f",&newTransacao->valor);
    msgSucesso();
}
void setTransferencia(ARQUIVO_TRANSACAO *newTransacao, char tipo,BASE_CLIENTES cliente){
    newTransacao->flag = tipo;
    printf("\n\t\tDADOS TRANSFERÊNCIA\n\n");
    newTransacao->numContaR = cliente.numConta;
    newTransacao->digitoContaR = cliente.digitoContaD;
    printf("\n Numero Conta Destino: ");
    scanf("%d",&newTransacao->numContaD);
    printf("\n Digito Conta Destino: ");
    scanf("%d",&newTransacao->digitoContaD);
    printf("\n Valor       : ");
    scanf("%f",&newTransacao->valor);
    msgSucesso();
}
void pushTransacao(ARQUIVO_TRANSACAO transacoes, ARQUIVO_TRANSACAO aux){
   transacoes[lengthTransacao++] =aux;
}


void msgSucesso(){
    printf("\n\t\tOperação realizada com sucesso!");
}
void msgFalha(){
    printf("\n\t\tErro ao efetuar a operação!");
}
void msgLoginNegado(){
    printf("\n\t\tCliente não cadastrado no sistema!");
}
