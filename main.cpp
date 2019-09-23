//FEITO EM C++ 17

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <string>
#include <fstream>

using namespace std;

//Variaveis globais - Inicio
ofstream fp; //File em modo de write
ifstream fr; // File em modo de read
char comando[200];
char nome[200]; //nome do HD Virtual
char nomeArquivo[16]; // nome do Arquivo
int estadoDoComando = 0; //Variavel que diz em qual comando o usuario se encontra
char HD[1024][32];
char proximo[200];
/*
 * 0 - nao esta em nenhum estado
 * 1 - createhd
 * 2 - create
 */


// Fim das Variveis globais

//Metodos - Inicio
void imprimeHashtag();
void recebeComando();
void verificadorDeComando();
void criaHD();
void criaTabela();
void escreveArquivo(char nomeArquivo[200]);
int iguais(char v[], char d[]);
string nomeHDComTxt(char* nomeHd);
void confirmaDisponibilidadeD(char conteudo[200]);
int confirmaDisponibilidadeA();
void criaArquivo(int i, char conteudo[200]);
void criaProximo(int i);
void incrementaProximo();


//Fim dos Metodos

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
    fp.open(nome);
    criaTabela();
    fp.close();
}

void escreveArquivo(char nomeArquivo[16]){
    char conteudo[1000];

    fr.open(nome);

    for(int i = 0; i< 1024; i++){
        for(int j = 0; j<32;j++){
            fr >> HD[i][j];
        }
    }

    fr.close();

    cout << "Digite o conteudo do arquivo:\n";
    gets(conteudo);
    fflush(stdin);
    confirmaDisponibilidadeD(conteudo);
    memset(nomeArquivo,'\0', 16);

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
            cout << "Nao e permitido realizar este comando\n";
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
            cout << "Nao e permitido realizar este comando sem um HD criado\n";
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

void confirmaDisponibilidadeD(char conteudo[200]){
    for (int i = 0; i<20; i++){
        if(HD[i][0] == '0'){
            criaArquivo(i, conteudo);
            fp.open(nome);
            for (int i = 0; i<1024; i++){
                for (int j = 0; j< 33 ;j++){
                    if(j == 32){
                        fp << endl;
                    }
                    else{
                        fp << HD[i][j];
                    }
                }
            }
            fp.close();
            return;
        }
    }
}

int confirmaDisponibilidadeA(){
    for (int i = 20; i<1024; i++){
        if(HD[i][0] == '0'){
            return i;
        }
    }
}

void criaArquivo(int i, char conteudo[200]){
    int tamanho = strlen(conteudo);
    int nLinhas = tamanho/24;
    int a = confirmaDisponibilidadeA();
    criaProximo(a+1);
    stringstream strs;
    strs  << tamanho;
    string temp_str = strs.str();
    char tamanhoConteudo[4];
    if(strlen(temp_str.c_str()) == 1){
        tamanhoConteudo[0] = '0';
        tamanhoConteudo[1] = '0';
        tamanhoConteudo[2] = '0';
        tamanhoConteudo[3] = (char) temp_str.c_str()[0];
    }
    if(strlen(temp_str.c_str()) == 2){
        tamanhoConteudo[0] = '0';
        tamanhoConteudo[1] = '0';
        tamanhoConteudo[2] = (char) temp_str.c_str()[0];
        tamanhoConteudo[3] = (char) temp_str.c_str()[1];
    }
    if(strlen(temp_str.c_str()) == 3){
        tamanhoConteudo[0] = '0';
        tamanhoConteudo[1] = (char) temp_str.c_str()[0];
        tamanhoConteudo[2] = (char) temp_str.c_str()[1];
        tamanhoConteudo[3] = (char) temp_str.c_str()[2];
    }
    if(strlen(temp_str.c_str()) == 4){
        tamanhoConteudo[0] = (char) temp_str.c_str()[0];
        tamanhoConteudo[1] = (char) temp_str.c_str()[1];
        tamanhoConteudo[2] = (char) temp_str.c_str()[2];
        tamanhoConteudo[3] = (char) temp_str.c_str()[3];
    }

    int atual = 0;

    for (int k = 0; k < 32; k++){
        if ( k == 0){
            HD[i][k] = '1';
        }
        else if ( k == 2){
            HD[i][k] = '0';
        }
        else if ( k >= 4 & k <= 7){
            //if(pasta){
            //teste[i][k] = pasta[k-4];
            //}
            //else{
            HD[i][k] = '0';
            //}
        }
        else if ( k >= 8 & k <= 11){
            //if(pasta){
            //teste[i][k] = "0";
            //}
            //else{
            HD[i][k] = proximo[k-8];
            //}
        }
        else if ( k >= 12 & k <= 15){
            HD[i][k] = tamanhoConteudo[k-12];
        }
        else if ( k >= 16 & k <= 31){
            HD[i][k] = nomeArquivo[k-16];
        }
    }
    if ((a + nLinhas) <= 1024){
        for (int j = a; j <= a + nLinhas;j++){
            for (int k = 0; k < 32; k++){
                if ( k == 0){
                    HD[j][k] = '1';
                }
                else if ( k >= 4 & k <= 7){
                    if(nLinhas > 0 && j != (a +nLinhas)){
                        HD[j][k] = proximo[k-4];
                    }
                    else{
                        HD[j][k] = '0';
                    }
                }
                else if ( k >= 8 & k <= 31){
                    if (conteudo[atual] != 0){
                        HD[j][k] = conteudo[atual];
                        atual++;
                    }
                }
            }
            incrementaProximo();
        }
    }
    else{
        cout << "overflow de memoria";
    }
}

void criaProximo(int i){
    stringstream strs;
    strs  << i;
    string temp_str = strs.str();
    if(strlen(temp_str.c_str()) == 1){
        proximo[0] = '0';
        proximo[1] = '0';
        proximo[2] = '0';
        proximo[3] = (char) temp_str.c_str()[0];
    }
    if(strlen(temp_str.c_str()) == 2){
        proximo[0] = '0';
        proximo[1] = '0';
        proximo[2] = (char) temp_str.c_str()[0];
        proximo[3] = (char) temp_str.c_str()[1];
    }
    if(strlen(temp_str.c_str()) == 3){
        proximo[0] = '0';
        proximo[1] = (char) temp_str.c_str()[0];
        proximo[2] = (char) temp_str.c_str()[1];
        proximo[3] = (char) temp_str.c_str()[2];
    }
    if(strlen(temp_str.c_str()) == 4){
        proximo[0] = (char) temp_str.c_str()[0];
        proximo[1] = (char) temp_str.c_str()[1];
        proximo[2] = (char) temp_str.c_str()[2];
        proximo[3] = (char) temp_str.c_str()[3];
    }
    return;
}

void incrementaProximo(){
    int k = 3;
    int valor;
    int estourou = 0;
    valor = proximo[k] - '0';
    if (valor >=0 && valor <= 8){
        proximo[k] = proximo[k] + 1;
    }
    else{
        proximo[k] = '0';
        estourou = 1;
    }
    k = 2;
    if (estourou == 1){
        while(estourou == 1 || k == 0){
            valor = proximo[k] - '0';
            if (valor >=0 && valor <= 7){
                proximo[k] = proximo[k] + 1;
                estourou = 0;
            }
            else if(valor == 8){
                proximo[k] = '0';
            }
            else{
                proximo[k] = '1';
            }
        }
    }
}