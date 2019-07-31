#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include "MoitinhoLib.h"


int main() {
setlocale(LC_ALL,"portuguese");
    int opt,session=-1;
    char flag;
    char *name_arq_transacao = "arquivo_transacao.dat";
    char *name_arq_master = "arquivo_master.dat";
    char *name_arq_cliente = "arquivo_clientes.dat";
    char *name_arq_log = "arquivo_log.dat";
    BASE_CLIENTES listaClientes[10000],auxCliente;


    while(session==-1 && (opt = viewHome())){
        loadClientes(name_arq_cliente,listaClientes);
        switch(opt){
            case 1:
                system("cls");
                setClientes(&auxCliente);
                session = searchCliente(listaClientes,auxCliente);
                if(session==-1){
                    msgLoginNegado();
                    printf("\n\n");
                    system("pause");
                }
                break;
            case 2:
                system("cls");
                createAccount(&auxCliente);
                pushCliente(listaClientes,auxCliente);
                bubbleSort(listaClientes);
                writeClientes(name_arq_cliente,listaClientes);
                printf("\n\n");
                system("pause");
                break;
            default:
                msgFalha();
                printf("\n\n");
                system("pause");
        }

        system("cls");
    }
    ARQUIVO_MESTRE dados_master[10000],auxMaster;
    ARQUIVO_TRANSACAO dados_transation[1000],auxTransation;
    ARQUIVO_LOG dados_log[1000],auxLog;

    loadMaster(name_arq_master,dados_master);
    loadTransacao(name_arq_transacao,dados_transation);
    while((opt=menu(listaClientes,session)) && opt!=6){
        switch(opt){
            case 1://Transferências
                setSaque(&auxTransation,'S',listaClientes[session]);
                pushTransacao(dados_transation,auxTransation);
                writeTransacao(name_arq_transacao,dados_transation);
                break;
            case 2://Depósitos
                setDeposito(&auxTransation,'D',listaClientes[session]);
                pushTransacao(dados_transation,auxTransation);
                write(name_arq_transacao,dados_transation);
                break;
            case 3://Saques
                setTransferencia(&auxTransation,'T',listaClientes[session]);
                pushTransacao(dados_transation,auxTransation);
                write(name_arq_transacao,dados_transation);
                break;
            case 4:
                detalheConta(listaClientes[session]);
                break;
            default:
                msgFalha();
        }
    }
    printf("\n\t\t\t\tPrograma Finalizado -  MTI BANK\n");
    //atualização dos arquivos.
}
