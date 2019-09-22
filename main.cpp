//FEITO EM C++ 17

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#include <csignal>
#include <windows.h>

using namespace std;

//Variáveis globais - Início
ofstream fp; //File em modo de write
ifstream fr; // File em modo de read
//char caminho[200] = "";
char comando[200];
char nome[200]; //nome do HD Virtual
char nomeArquivo[200]; // nome do Arquivo
int estadoDoComando = 0; //Variável que diz em qual comando o usuário se encontra
static volatile bool g_exit = false;
/*
 * 0 - não esta em nenhum estado
 * 1 - createhd
 * 2 - create
 */


// Fim das Variáveis globais

//Metodos - Início
void imprimeHashtag();
void imprimeHashtagComando(char hdNome[200]);
void recebeComando();
void verificadorDeComando();
void criaHD();
void escreveArquivo();
void criaTabela();
void saiHD();
void criaArquivo();
void escreveArquivo(char nomeArquivo[200]);
int iguais(char v[], char d[]);
string nomeHDComTxt(char* nomeHd);

//Fim dos Métodos

int main(int argc, char *argv[])
{
    while(true){
        recebeComando();
    }
}

void imprimeHashtag(){
    if(strlen(nome) == 0){
        cout << "# ";
    }
    else{
        string nomeDoComando = nome;
        string comandoComNome = "# " + nomeDoComando + "> ";
        cout << comandoComNome;
    }
}

void recebeComando(){
    imprimeHashtag();
    gets(comando);
    fflush(stdin);
    verificadorDeComando();
}

void criaHD(){
    string nomeString = nomeHDComTxt(nome);

    fp.open(nomeString);
    criaTabela();
    fp.close();
}

void escreveArquivo(char nomeArquivo[200]){

    char conteudo[200];

    string nomeString = nomeHDComTxt(nomeArquivo);
    fr.open(nomeString);
    char teste[1024][32];

    for(int i = 0; i< 1024; i++){
        for(int j = 0; j<32;j++){
            fr >> teste[i][j];
        }
    }

    cout << "Digite o conteudo do arquivo:\n";
    gets(conteudo);
    fflush(stdin);
}

string nomeHDComTxt(char* nomeHd){
    string nomeString = nomeHd;
    nomeString += ".txt";
    return nomeString;
}

void verificadorDeComando(){
    int i;
    int k = 0;

    if (iguais("createhd ", comando)){
        if(estadoDoComando == 1){
            cout << "Não é permitido realizar este comando\n";
            return;
        }
        for (i = 9 ;comando[i] != 0 ; i++){
            nome[k] = comando[i];
            k++;
        }
        estadoDoComando = 1;
        criaHD();
    }
    else if (iguais("create ", comando)){
        if(estadoDoComando == 0){
            cout << "Não é permitido realizar este comando sem um HD criado\n";
            return;
        }
        for (i = 7 ;comando[i] != 0 ; i++){
            nomeArquivo[k] = comando[i];
            k++;
        }
        escreveArquivo(nomeArquivo);
    }
    else{
        cout << "Comando invalido\n";
    }
}

int iguais(char v[], char d[]){
    int c = 0;
    while(v[c] != 0 ){
        if(v[c] != d[c]){
            return 0;
        }
        c++;
    }
    //if (v[c] != d[c]){
    //	return 0;
    //}
    return 1;
}

void criaTabela(){
    for (int i = 0; i<1024; i++){
        for (int j = 0; j< 33 ;j++){
            if (j == 0 || (j == 1 && i>=0 && i<=19)){
                fp << "0";
            }
            else if(j == 1 && i>=20){
                fp << "1";
            }
            else if(j == 32){
                fp << endl;
            }
            else{
                fp << "-";
            }
        }
    }
}