#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "MoitinhoLib.h"


int main() {
setlocale(LC_ALL,"portuguese");
    int opt,session=-1;
    char *name_arq_transacao = "arquivo_transacao.dat";
    char *name_arq_master = "arquivo_master.dat";
   //char *name_arq_cliente = "arquivo_clientes.dat";
    char *name_arq_log = "arquivo_log.dat";
    BASE_CLIENTES listaClientes[10000],auxCliente;
    while(session==-1){
        opt = viewHome();
        loadClientes(name_arq_master,listaClientes);
        bubbleSort(listaClientes);
        switch(opt){
            case 1:
                system("cls");
                setClientes(&auxCliente);
                session = searchCliente(listaClientes,auxCliente.numConta);
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
                writeClientes(name_arq_master,listaClientes);
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

    ARQUIVO_TRANSACAO dados_transation[1000],auxTransation;
    ARQUIVO_TRANSACAO dados_log[1000],auxLog;
    loadTransacao(name_arq_transacao,dados_transation);
    while((opt=menu(listaClientes,session)) && opt!=6){
        switch(opt){
            case 1://Transferências
                setSaque(&auxTransation,'S',listaClientes[session]);
                pushTransacao(dados_transation,auxTransation);
                break;
            case 2://Depósitos
                setDeposito(&auxTransation,'D',listaClientes[session]);
                pushTransacao(dados_transation,auxTransation);
                break;
            case 3://Saques
                setTransferencia(&auxTransation,'T',listaClientes[session]);
                break;
            case 4:
                detalheConta(listaClientes[session]);
                break;
            default:
                msgFalha();
        }
        system("pause");
        system("cls");
    }
    writeTransacao(name_arq_transacao,dados_transation); // transacao
    writeTransacao(name_arq_log,dados_transation);       // log
    wormTransacoes(name_arq_transacao,name_arq_master,name_arq_log,listaClientes,dados_transation,dados_log);

    printf("\n\t\t\t\tSessão Encerrada - Obrigado por usar o MTI BANK\n");
    system("pause");
    //atualização dos arquivos.
}
