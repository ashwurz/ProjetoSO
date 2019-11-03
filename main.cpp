//FEITO EM C++ 17

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

//Variaveis globais - Inicio

ofstream fp; //File em modo de write
ifstream fr; // File em modo de read
char comando[200];
char nome[200]; //nome do HD Virtual
char hdtxt[200]; //nome do HD com estensao txt
char nomeArquivo[16]; // nome do Arquivo
char nomePasta[16]; //nome da pasta
char nomePastaNavegacao[16]; // nome da pasta para navegação
int posNavegacao;
char nomeCaminho[200];
char nomeCaminhoCopy[200];
char nomeHashtag[16];
string pastas; //string com os nomes das pastas;
int estadoDoComando = 0; //Variavel que diz em qual comando o usuario se encontra
char HD[1024][32];
char proximo[200];
char conteudo[1000];
/*
 * 0 - nao esta em nenhum estado
 * 1 - createhd
 * 2 - create
 * 3 - cd
 * 4 - mkdir
 * 5 - delete
 * 6 - dir
 * 7 - type
 * 8 - copy
 * 9 - copydir
 */

// Fim das Variveis globais

//Metodos - Inicio

void imprimeHashtag();
void recebeComando();
void verificadorDeComando();
void leHD();
void criaHD();
void criaTabela();
void criaPasta(int i);
void criaArquivo(int i);
void criaProximo(int i);
void escreveHD();
void escreveArquivo();
void deleteArquivo();
int iguais(char v[], char d[]);
string nomeHDComTxt();
void listaPastasArquivos(bool print, bool printArquivo);
void printLista(char lista[], int i);
void printFile(int i);
string posicaoAtual();
string posicaoNova(char nomeTeste[], char tempPosHD[]);
void copiaSeExiste(int tipo);
string copyPathSeExiste(int tipo);
void copy(char nomeCopy[],bool pasta, int o);
void copyTudoDentro(int i, string temp_str_origem);
void criaArquivoCopiado(int i, string temp_str);
void criaPastaCopy(int i, string temp_str, char nomeCopy[]);
void confirmaDisponibilidadeP();
void confirmaDisponibilidadeD();
int * confirmaDisponibilidadeA(int n);
void aPartirDaRaiz();
void posPastaAtual();
void doispontos();
void saiPrograma();
//Fim dos Metodos

int main(int argc, char *argv[])
{
    posNavegacao = -1;
    memset(comando, 0 , 200);
    memset(nome, 0 , 200);
    memset(hdtxt, 0 , 200);
    memset(nomeArquivo, 0 , 16);
    memset(nomePasta, 0 , 16);
    memset(nomePastaNavegacao, 0 , 16);
    memset(nomeCaminho, 0 , 200);
    memset(nomeCaminhoCopy, 0 , 200);
    memset(nomeHashtag, 0 , 16);
    memset(proximo, 0 , 200);
    memset(conteudo, 0 , 1000);
    while(true){
        recebeComando();
    }
}

void imprimeHashtag(){
    if(strlen(nome) == 0){
        cout << "# ";
    }
    else if(estadoDoComando == 3){
        string nomeDoComando = nome;
        string nomeDaPasta = nomeHashtag;
        pastas = pastas +  "\\" + nomeDaPasta;
        string comandoComNome = "# " + nomeDoComando + pastas + "> ";
        cout << comandoComNome;
    }
    else{
        string nomeDoComando = nome;
        string comandoComNome = "# " + nomeDoComando + pastas + "> ";
        cout << comandoComNome;
    }
}

void aPartirDaRaiz(){
    int i = 0;
    int j = 3;
    for(j; j < strlen(comando);j++){
        nomeCaminhoCopy[i] = comando[j];
        i++;
    }
    char tempNomePasta[16];
    char tempPosHD[4];
    char nomeCopy[16];
    bool achou = false;
    bool arquivo = false;
    string pos;
    tempPosHD[0] = '0';
    tempPosHD[1] = '0';
    tempPosHD[2] = '0';
    tempPosHD[3] = '0';
    memset(tempNomePasta, 0 , 16);
    memset(nomeCopy, 0 , 16);
    char temp[16];
    j = 1;
    while(true){
        int l = 0;
        for(j; j <= strlen(nomeCaminhoCopy);j++){
            if(nomeCaminhoCopy[j] == '\\'){
                j++;
                break;
            }
            else if (nomeCaminhoCopy[j] == '\0'){
                arquivo = true;
                break;
            }
            nomeCopy[l] = nomeCaminhoCopy[j];
            l++;
        }
        string temp_str = posicaoNova(nomeCopy, tempPosHD);
        if(strlen(temp_str.c_str()) == 1){
            tempPosHD[2] = '0';
            tempPosHD[3] = (char) temp_str.c_str()[0];
        }
        else if(strlen(temp_str.c_str()) == 2){
            tempPosHD[2] = (char) temp_str.c_str()[0];
            tempPosHD[3] = (char) temp_str.c_str()[1];
        }
        else if(strlen(temp_str.c_str()) == 3){
            tempPosHD[1] = (char) temp_str.c_str()[0];
            tempPosHD[2] = (char) temp_str.c_str()[1];
            tempPosHD[3] = (char) temp_str.c_str()[2];
        }
        else if(strlen(temp_str.c_str()) == 4){
            tempPosHD[0] = (char) temp_str.c_str()[0];
            tempPosHD[1] = (char) temp_str.c_str()[1];
            tempPosHD[2] = (char) temp_str.c_str()[2];
            tempPosHD[3] = (char) temp_str.c_str()[3];
        }
        else {
            break;
        }
        memset(nomeCopy, 0 , 16);
        if(arquivo){
            break;
        }
    }
    pastas = nomeCaminhoCopy;
    for(i = strlen(nomeCaminhoCopy); i >= 0; i--){
        if(nomeCaminhoCopy[i] == '\\'){
            break;
        }
    }
    memset(nomePastaNavegacao,'\0', 200);
    i++;
    j = i;
    for(j ; j < strlen(nomeCaminhoCopy); j++){
        nomePastaNavegacao[j-i] = nomeCaminhoCopy[j];
    }
    memset(nomeCaminhoCopy,'\0', 200);

    posNavegacao = ((tempPosHD[0] - '0')*1000) + ((tempPosHD[1] - '0')*100) + ((tempPosHD[2] - '0')*10) + ((tempPosHD[3] - '0')*1) - 1;
    estadoDoComando = 1;
}

void posPastaAtual(){
    string temp_str = posicaoAtual();
    char tempPosHD[4];
    tempPosHD[0] = '0';
    tempPosHD[1] = '0';
    tempPosHD[2] = '0';
    tempPosHD[3] = '0';
    if(strlen(temp_str.c_str()) == 1){
        tempPosHD[0] = '0';
        tempPosHD[1] = '0';
        tempPosHD[2] = '0';
        tempPosHD[3] = (char) temp_str.c_str()[0];
    }
    if(strlen(temp_str.c_str()) == 2){
        tempPosHD[0] = '0';
        tempPosHD[1] = '0';
        tempPosHD[2] = (char) temp_str.c_str()[0];
        tempPosHD[3] = (char) temp_str.c_str()[1];
    }
    if(strlen(temp_str.c_str()) == 3){
        tempPosHD[0] = '0';
        tempPosHD[1] = (char) temp_str.c_str()[0];
        tempPosHD[2] = (char) temp_str.c_str()[1];
        tempPosHD[3] = (char) temp_str.c_str()[2];
    }
    if(strlen(temp_str.c_str()) == 4){
        tempPosHD[0] = (char) temp_str.c_str()[0];
        tempPosHD[1] = (char) temp_str.c_str()[1];
        tempPosHD[2] = (char) temp_str.c_str()[2];
        tempPosHD[3] = (char) temp_str.c_str()[3];
    }
    posNavegacao = ((tempPosHD[0] - '0')*1000) + ((tempPosHD[1] - '0')*100) + ((tempPosHD[2] - '0')*10) + ((tempPosHD[3] - '0')*1) - 1;
}

void doispontos(){
    char temp[pastas.size()];
    strcpy(temp, pastas.c_str());
    int i;
    for(i = strlen(temp); i >= 0; i--){
        if(temp[i] == '\\'){
            break;
        }
    }
    for(int j = i; j < strlen(temp); j++){
        temp[j] = 0;
    }
    /*int k;
    for(k = i; k >= 0 ; k--){
        if(temp[k] == '\\'){
            break;
        }
    }
    memset(nomePastaNavegacao,'\0', 16);
    k++;
    int a = k;
    for(k ; k < strlen(temp); k++){
        nomePastaNavegacao[k-a] = temp[k];
    }
    pastas = temp;*/
    int k = 3;
    for(i = 0 ; i <= strlen(temp); i++){
        comando[k] = temp[i];
        k++;
    }
    aPartirDaRaiz();
    //estadoDoComando = 1;
}

void recebeComando(){
    imprimeHashtag();
    memset(comando, 0 , 200);
    gets(comando);
    fflush(stdin);
    verificadorDeComando();
}

void criaHD(){
    string temp;
    temp = nomeHDComTxt();
    strcpy(hdtxt, temp.c_str());
    fp.open(hdtxt);
    criaTabela();
    fp.close();
}

void escreveArquivo(){
    leHD();
    cout << "Digite o conteudo do arquivo:\n";
    gets(conteudo);
    fflush(stdin);
    confirmaDisponibilidadeD();
    memset(nomeArquivo,0, 16);
}

void deleteArquivo(){
    leHD();
    char tempNomeArquivo[16];
    char tempPosConteudo[4];
    char tempPosHD[4];
    int posicaoConteudo = 0;
    tempPosHD[0] = '0';
    tempPosHD[1] = '0';
    tempPosHD[2] = '0';
    tempPosHD[3] = '0';
    int corrigi = posNavegacao + 1;
    stringstream strs;
    strs  << corrigi;
    string temp_str = strs.str();
    if(strlen(temp_str.c_str()) == 1){
        tempPosHD[2] = '0';
        tempPosHD[3] = (char) temp_str.c_str()[0];
    }
    if(strlen(temp_str.c_str()) == 2){
        tempPosHD[2] = (char) temp_str.c_str()[0];
        tempPosHD[3] = (char) temp_str.c_str()[1];
    }
    for(int i = 0; i < 20; i++){
        for(int j = 16; j < 32; j++){
            if(HD[i][j] != 0) {
                tempNomeArquivo[j - 16] = HD[i][j];
            }
        }
        if(iguais(nomeArquivo, tempNomeArquivo) && HD[i][4] == tempPosHD[0] && HD[i][5] == tempPosHD[1] && HD[i][6] == tempPosHD[2] && HD[i][7] == tempPosHD[3]){
            HD[i][0] = '0';
            posicaoConteudo = ((HD[i][8] - '0')*1000) + ((HD[i][9] - '0')*100) + ((HD[i][10] - '0')*10) + ((HD[i][11] - '0')*1);
            break;
        }
    }
    int i = posicaoConteudo;
    HD[i][0] = '0';
    while ( i != 0){
        HD[i][0] = '0';
        i = ((HD[i][4] - '0')*1000) + ((HD[i][5] - '0')*100) + ((HD[i][6] - '0')*10) + ((HD[i][7] - '0')*1);
    }
    cout << "arquivo " << nomeArquivo << " foi removido" << endl;
    escreveHD();
}

void escreveHD(){
    fp.open(hdtxt);
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
}

string nomeHDComTxt(){
    string nomeString = nome;
    nomeString += ".txt";
    return nomeString;
}

void verificadorDeComando(){
    int i;
    int k = 0;

    if (iguais("createhd ", comando)){
        if(estadoDoComando >= 1){
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
        estadoDoComando = 2;
        escreveArquivo();
    }
    else if(iguais("remove ", comando)){
        if(estadoDoComando == 0){
            cout << "Comando nao permitido";
            return;
        }
        for(i = 7; comando[i] != 0; i++){
            nomeArquivo[k] = comando[i];
            k++;
        }
        estadoDoComando = 5;
        deleteArquivo();
        memset(nomeArquivo, 0 , 16);
    }
    else if(iguais("cd ", comando)){
        if(estadoDoComando == 0){
            cout << "Comando nao permitido";
            return;
        }
        estadoDoComando = 7;
        memset(nomeHashtag,'\0', 16);
        if (comando[3] == '\\'){
            aPartirDaRaiz();
        }
        else{
            for(i = 3; comando[i] != 0; i++){
                nomeHashtag[k] = comando[i];
                k++;
            }
            if(iguais("..", nomeHashtag)){
                memset(nomeHashtag,'\0', 16);
                doispontos();
            }
            else{
                for(i = 0; i < 16; i++){
                    nomePastaNavegacao[i] = nomeHashtag[i];
                }
                posPastaAtual();
                estadoDoComando = 3;
            }
        }
    }
    else if(iguais("mkdir ", comando)){
        if(estadoDoComando == 0){
            cout << "Comando nao permitido" << endl;
            return;
        }
        for(i = 6; comando[i] != 0; i++){
            nomePasta[k] = comando[i];
            k++;
        }
        estadoDoComando = 4;
        confirmaDisponibilidadeP();
    }
    else if(iguais("dir", comando)){
        if(estadoDoComando == 0){
            cout << "Comando nao permitido" << endl;
            return;
        }
        estadoDoComando = 6;
        listaPastasArquivos(true, false);
    }
    else if(iguais("type ", comando)){
        if(estadoDoComando == 0){
            cout << "Comando nao permitido" << endl;
            return;
        }
        for(i = 5; comando[i] != 0; i++){
            nomeArquivo[k] = comando[i];
            k++;
        }
        estadoDoComando = 7;
        listaPastasArquivos(false, true);

    }
    else if(iguais("copy ", comando)){
        if(estadoDoComando == 0){
            cout << "Comando nao permitido" << endl;
            return;
        }
        for(i = 5; comando[i] != ' ' && comando[i] != 0; i++){
            nomeCaminho[k] = comando[i];
            k++;
        }
        nomeCaminho[k] = '\0';
        i++;
        k = 0;
        if(comando[i] != 0){
            for(i; comando[i] != 0; i++){
                nomeCaminhoCopy[k] = comando[i];
                k++;
            }
            nomeCaminhoCopy[k] = '\0';
        }
        else{
            cout << "Caminho invalido" << endl;
            return;
        }
        estadoDoComando = 8;
        copiaSeExiste(1);
        memset(nomeCaminho, 0 , 200);
        memset(nomeCaminhoCopy, 0 , 200);
    }
    else if(iguais("copydir ", comando)){
        if(estadoDoComando == 0){
            cout << "Comando nao permitido" << endl;
            return;
        }
        for(i = 8; comando[i] != ' ' && comando[i] != 0; i++){
            nomeCaminho[k] = comando[i];
            k++;
        }
        nomeCaminho[k] = '\0';
        i++;
        k = 0;
        if(comando[i] != 0){
            for(i; comando[i] != 0; i++){
                nomeCaminhoCopy[k] = comando[i];
                k++;
            }
            nomeCaminhoCopy[k] = '\0';
        }
        else{
            cout << "Caminho invalido" << endl;
            return;
        }
        estadoDoComando = 9;
        copiaSeExiste(2);
        memset(nomeCaminho, 0 , 200);
        memset(nomeCaminhoCopy, 0 , 200);
    }
    else if(iguais("exit",comando)){
        saiPrograma();
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

void listaPastasArquivos(bool print, bool printArquivo){
    leHD();
    char tempNomePasta[16];
    char tempPosHD[4];
    char lista[16];
    tempPosHD[0] = '0';
    tempPosHD[1] = '0';
    tempPosHD[2] = '0';
    tempPosHD[3] = '0';
    int corrigi = posNavegacao + 1;
    stringstream strs;
    strs  << corrigi;
    string temp_str = strs.str();
    if(strlen(temp_str.c_str()) == 1){
        tempPosHD[2] = '0';
        tempPosHD[3] = (char) temp_str.c_str()[0];
    }
    if(strlen(temp_str.c_str()) == 2){
        tempPosHD[2] = (char) temp_str.c_str()[0];
        tempPosHD[3] = (char) temp_str.c_str()[1];
    }
    bool printou = false;
    for(int i = 0; i < 20; i++){
        if(HD[i][0] == '1' && HD[i][4] == tempPosHD[0] && HD[i][5] == tempPosHD[1] && HD[i][6] == tempPosHD[2] && HD[i][7] == tempPosHD[3]){
            for(int j = 16; j < 32; j++){
                if(HD[i][j] != 0){
                    lista[j - 16] = HD[i][j];
                }
                else{
                    lista[j - 16] = 0;
                }
            }
            if(print){
                printLista(lista, i);
                printou = true;
            }
            if(printArquivo && iguais(nomeArquivo,lista) && HD[i][2] == '0'){
                printFile(i);
                printou = true;
            }
        }
        memset(lista, 0 , 16);
    }
    if (!printou){
        cout << "Arquivo nao existe neste diretorio" << endl;
    }
}

void printLista(char lista[], int i){
    if(HD[i][2] == '0'){
        int bytes = ((HD[i][12] - '0')*1000) + ((HD[i][13] - '0')*100) + ((HD[i][14] - '0')*10) + ((HD[i][15] - '0')*1);
        cout << lista << " " << bytes << " bytes" << endl;
    }
    else{
        cout << lista << endl;
    }
}

void printFile(int i){
    int bytes = ((HD[i][12] - '0')*1000) + ((HD[i][13] - '0')*100) + ((HD[i][14] - '0')*10) + ((HD[i][15] - '0')*1);
    int j;
    i = ((HD[i][8] - '0')*1000) + ((HD[i][9] - '0')*100) + ((HD[i][10] - '0')*10) + ((HD[i][11] - '0')*1);
    for (j = 0; j < bytes; j++){
        cout << HD[i][(j%24)+8];
        if((j+1)%20 == 0){
            cout << endl;
        }
        if((j+1)%24 == 0){
            i = ((HD[i][4] - '0')*1000) + ((HD[i][5] - '0')*100) + ((HD[i][6] - '0')*10) + ((HD[i][7] - '0')*1);
        }
    }
    if(j%20 != 0){
        cout << endl;
    }
}

string posicaoAtual(){
    leHD();
    char tempPosHD[4];
    tempPosHD[0] = '0';
    tempPosHD[1] = '0';
    tempPosHD[2] = '0';
    tempPosHD[3] = '0';
    int corrigi = posNavegacao + 1;
    stringstream strs;
    strs  << corrigi;
    string temp_str = strs.str();
    if(strlen(temp_str.c_str()) == 1){
        tempPosHD[2] = '0';
        tempPosHD[3] = (char) temp_str.c_str()[0];
    }
    if(strlen(temp_str.c_str()) == 2){
        tempPosHD[2] = (char) temp_str.c_str()[0];
        tempPosHD[3] = (char) temp_str.c_str()[1];
    }
    char tempNomePasta[16];
    for(int i = 0; i < 20; i++){
        if(HD[i][0] == '1' && HD[i][2] == '1' && HD[i][4] == tempPosHD[0] && HD[i][5] == tempPosHD[1] && HD[i][6] == tempPosHD[2] && HD[i][7] == tempPosHD[3]){
            for(int j = 16; j < 32 && HD[i][j] != 0; j++){
                tempNomePasta[j - 16] = HD[i][j];
            }
            if(iguais(nomePastaNavegacao, tempNomePasta) && (nomePastaNavegacao[0] != 0)){
                corrigi = i + 1;
                stringstream strs2;
                strs2  << corrigi;
                string temp_str2 = strs2.str();
                return temp_str2;
            }
        }
    }
    return "0000";
}

string posicaoNova(char nomeTeste[], char tempPosHD[]){
    leHD();
    char tempNomePasta[16];
    for(int i = 0; i < 20; i++){
        if(HD[i][0] == '1' && HD[i][4] == tempPosHD[0] && HD[i][5] == tempPosHD[1] && HD[i][6] == tempPosHD[2] && HD[i][7] == tempPosHD[3]){
            for(int j = 16; j < 32 && HD[i][j] != 0; j++){
                tempNomePasta[j - 16] = HD[i][j];
            }
            if(iguais(nomeTeste, tempNomePasta) && (nomeTeste[0] != 0)){
                int corrigi = i + 1;
                stringstream strs;
                strs  << corrigi;
                string temp_str = strs.str();
                return temp_str;
            }
            memset(tempNomePasta, 0 , 16);
        }
    }
    return "Pasta ou Arquivo nao existe neste Diretorio";
}

void copiaSeExiste(int tipo){
    leHD();
    char tempNomePasta[16];
    char tempPosHD[4];
    char tempCopy[16];
    char nomeCopy[16];
    bool achou = false;
    bool arquivo = false;
    tempPosHD[0] = '0';
    tempPosHD[1] = '0';
    tempPosHD[2] = '0';
    tempPosHD[3] = '0';
    memset(tempNomePasta, 0 , 16);
    memset(tempCopy, 0 , 16);
    memset(nomeCopy, 0 , 16);
    int corrigi = posNavegacao + 1;
    stringstream strs;
    strs  << corrigi;
    string temp_str = strs.str();
    if(strlen(temp_str.c_str()) == 1){
        tempPosHD[2] = '0';
        tempPosHD[3] = (char) temp_str.c_str()[0];
    }
    if(strlen(temp_str.c_str()) == 2){
        tempPosHD[2] = (char) temp_str.c_str()[0];
        tempPosHD[3] = (char) temp_str.c_str()[1];
    }
    int j = 0;
    if (nomeCaminho[j] == '\\'){
        j++;
    }
    for(j; j <= strlen(nomeCaminho);j++){
        if(nomeCaminho[j] == '\\'){
            break;
        }
        else if (nomeCaminho[j] == '\0'){
            break;
        }
        nomeCopy[j] = nomeCaminho[j];
    }
    for(int i = 0; i < 20; i++){
        if(HD[i][0] == '1' && HD[i][4] == tempPosHD[0] && HD[i][5] == tempPosHD[1] && HD[i][6] == tempPosHD[2] && HD[i][7] == tempPosHD[3]){
            for(int k = 16; k < 32 && HD[i][k] != 0; k++){
                tempCopy[k - 16] = HD[i][k];
            }
            if(iguais(nomeCopy, tempCopy) && (nomeCopy[0] != 0)){
                achou = true;
                break;
            }
            memset(tempCopy, 0 , 16);
        }
    }
    memset(nomeCopy, 0 , 16);
    if(!achou){
        tempPosHD[0] = '0';
        tempPosHD[1] = '0';
        tempPosHD[2] = '0';
        tempPosHD[3] = '0';
    }
    achou = false;
    char temp[16];
    memset(nomeCopy, 0 , 16);
    j = 0;
    if (nomeCaminho[j] == '\\'){
        j++;
    }
    while(true){
        int l = 0;
        for(j; j <= strlen(nomeCaminho);j++){
            if(nomeCaminho[j] == '\\'){
                j++;
                break;
            }
            else if (nomeCaminho[j] == '\0'){
                arquivo = true;
                break;
            }
            nomeCopy[l] = nomeCaminho[j];
            l++;
        }
        string temp_str = posicaoNova(nomeCopy, tempPosHD);
        if(strlen(temp_str.c_str()) == 1){
            tempPosHD[2] = '0';
            tempPosHD[3] = (char) temp_str.c_str()[0];
        }
        else if(strlen(temp_str.c_str()) == 2){
            tempPosHD[2] = (char) temp_str.c_str()[0];
            tempPosHD[3] = (char) temp_str.c_str()[1];
        }
        else if(strlen(temp_str.c_str()) == 3){
            tempPosHD[1] = (char) temp_str.c_str()[0];
            tempPosHD[2] = (char) temp_str.c_str()[1];
            tempPosHD[3] = (char) temp_str.c_str()[2];
        }
        else if(strlen(temp_str.c_str()) == 4){
            tempPosHD[0] = (char) temp_str.c_str()[0];
            tempPosHD[1] = (char) temp_str.c_str()[1];
            tempPosHD[2] = (char) temp_str.c_str()[2];
            tempPosHD[3] = (char) temp_str.c_str()[3];
        }
        else {
            cout << temp_str << endl;
            break;
        }
        if(arquivo){
            achou = true;
            break;
        }
        memset(nomeCopy, 0 , 16);
    }
    if (achou){
        if(tipo == 1){
            memset(conteudo, 0 , 1000);
            int i;
            i = ((tempPosHD[0] - '0')*1000) + ((tempPosHD[1] - '0')*100) + ((tempPosHD[2] - '0')*10) + ((tempPosHD[3] - '0')*1) - 1;
            int bytes = ((HD[i][12] - '0')*1000) + ((HD[i][13] - '0')*100) + ((HD[i][14] - '0')*10) + ((HD[i][15] - '0')*1);
            int j;
            i = ((HD[i][8] - '0')*1000) + ((HD[i][9] - '0')*100) + ((HD[i][10] - '0')*10) + ((HD[i][11] - '0')*1);
            for (j = 0; j < bytes; j++){
                conteudo[j] = HD[i][(j%24)+8];
                if((j+1)%24 == 0){
                    i = ((HD[i][4] - '0')*1000) + ((HD[i][5] - '0')*100) + ((HD[i][6] - '0')*10) + ((HD[i][7] - '0')*1);
                }
            }
            copy(nomeCopy, false, i);
        }
        else if(tipo == 2){
            int i;
            i = ((tempPosHD[0] - '0')*1000) + ((tempPosHD[1] - '0')*100) + ((tempPosHD[2] - '0')*10) + ((tempPosHD[3] - '0')*1);
            copy(nomeCopy, true, i);
        }

    }
}

string copyPathSeExiste(int tipo){
    char tempNomePasta[16];
    char tempPosHD[4];
    char tempCopy[16];
    char nomeCopy[16];
    bool achou = false;
    bool arquivo = false;
    string pos;
    tempPosHD[0] = '0';
    tempPosHD[1] = '0';
    tempPosHD[2] = '0';
    tempPosHD[3] = '0';
    memset(tempNomePasta, 0 , 16);
    memset(nomeCopy, 0 , 16);
    memset(tempCopy, 0 , 16);
    int corrigi = posNavegacao + 1;
    stringstream strs;
    strs  << corrigi;
    string temp_str = strs.str();
    if(strlen(temp_str.c_str()) == 1){
        tempPosHD[2] = '0';
        tempPosHD[3] = (char) temp_str.c_str()[0];
    }
    if(strlen(temp_str.c_str()) == 2){
        tempPosHD[2] = (char) temp_str.c_str()[0];
        tempPosHD[3] = (char) temp_str.c_str()[1];
    }
    int j = 0;
    if (nomeCaminhoCopy[j] == '\\'){
        j++;
    }
    for(j ; j <= strlen(nomeCaminhoCopy);j++){
        if(nomeCaminhoCopy[j] == '\\'){
            break;
        }
        else if (nomeCaminhoCopy[j] == '\0'){
            break;
        }
        nomeCopy[j] = nomeCaminhoCopy[j];
    }
    for(int i = 0; i < 20; i++){
        if(HD[i][0] == '1' && HD[i][4] == tempPosHD[0] && HD[i][5] == tempPosHD[1] && HD[i][6] == tempPosHD[2] && HD[i][7] == tempPosHD[3]){
            for(int k = 16; k < 32 && HD[i][k] != 0; k++){
                tempCopy[k - 16] = HD[i][k];
            }
            if(iguais(nomeCopy, tempCopy) && (nomeCopy[0] != 0)){
                achou = true;
                break;
            }
            memset(tempCopy, 0 , 16);
        }
    }
    memset(nomeCopy, 0 , 16);
    if(!achou){
        tempPosHD[0] = '0';
        tempPosHD[1] = '0';
        tempPosHD[2] = '0';
        tempPosHD[3] = '0';
    }
    achou = false;
    char temp[16];
    memset(nomeCopy, 0 , 16);
    j = 0;
    if (nomeCaminho[j] == '\\'){
        j++;
    }
    while(true){
        int l = 0;
        for(j; j <= strlen(nomeCaminhoCopy);j++){
            if(nomeCaminhoCopy[j] == '\\'){
                j++;
                break;
            }
            else if (nomeCaminhoCopy[j] == '\0'){
                arquivo = true;
                break;
            }
            nomeCopy[l] = nomeCaminhoCopy[j];
            if(tipo == 1){
                nomeArquivo[l] = nomeCaminhoCopy[j];
            }
            else if(tipo == 2){
                nomePasta[l] = nomeCaminhoCopy[j];
            }
            l++;
        }
        if(arquivo && tipo == 1){
            break;
        }
        temp_str = posicaoNova(nomeCopy, tempPosHD);
        if(arquivo && tipo == 2){
            break;
        }
        if(strlen(temp_str.c_str()) == 1){
            tempPosHD[2] = '0';
            tempPosHD[3] = (char) temp_str.c_str()[0];
        }
        else if(strlen(temp_str.c_str()) == 2){
            tempPosHD[2] = (char) temp_str.c_str()[0];
            tempPosHD[3] = (char) temp_str.c_str()[1];
        }
        else if(strlen(temp_str.c_str()) == 3){
            tempPosHD[1] = (char) temp_str.c_str()[0];
            tempPosHD[2] = (char) temp_str.c_str()[1];
            tempPosHD[3] = (char) temp_str.c_str()[2];
        }
        else if(strlen(temp_str.c_str()) == 4){
            tempPosHD[0] = (char) temp_str.c_str()[0];
            tempPosHD[1] = (char) temp_str.c_str()[1];
            tempPosHD[2] = (char) temp_str.c_str()[2];
            tempPosHD[3] = (char) temp_str.c_str()[3];
        }
        else {
            break;
        }
        memset(nomeCopy, 0 , 16);
        memset(nomeArquivo,'\0', 16);
    }
    return temp_str;
}

void copy(char nomeCopy[], bool pasta, int o){
    char tempPosHD[4];
    tempPosHD[0] = '0';
    tempPosHD[1] = '0';
    tempPosHD[2] = '0';
    tempPosHD[3] = '0';
    if(!pasta){
        string temp_str = copyPathSeExiste(1);
        if(strlen(temp_str.c_str()) == 1){
            tempPosHD[0] = '0';
            tempPosHD[1] = '0';
            tempPosHD[2] = '0';
            tempPosHD[3] = (char) temp_str.c_str()[0];
        }
        else if(strlen(temp_str.c_str()) == 2){
            tempPosHD[0] = '0';
            tempPosHD[1] = '0';
            tempPosHD[2] = (char) temp_str.c_str()[0];
            tempPosHD[3] = (char) temp_str.c_str()[1];
        }
        else if(strlen(temp_str.c_str()) == 3){
            tempPosHD[0] = '0';
            tempPosHD[1] = (char) temp_str.c_str()[0];
            tempPosHD[2] = (char) temp_str.c_str()[1];
            tempPosHD[3] = (char) temp_str.c_str()[2];
        }
        else if(strlen(temp_str.c_str()) == 4){
            tempPosHD[0] = (char) temp_str.c_str()[0];
            tempPosHD[1] = (char) temp_str.c_str()[1];
            tempPosHD[2] = (char) temp_str.c_str()[2];
            tempPosHD[3] = (char) temp_str.c_str()[3];
        }
        else {
            cout << temp_str;
            return;
        }
        for (int i = 0; i<=20; i++){
            if(HD[i][0] == '0'){
                criaArquivoCopiado(i, temp_str);
                memset(nomeArquivo,'\0', 16);
                memset(conteudo,'\0', 1000);
                escreveHD();
                cout << nomeCopy << " copiado" << endl;
                return;
            }
        }
    }
    else{
        string temp_str = copyPathSeExiste(2);
        if(strlen(temp_str.c_str()) == 1){
            tempPosHD[0] = '0';
            tempPosHD[1] = '0';
            tempPosHD[2] = '0';
            tempPosHD[3] = (char) temp_str.c_str()[0];
        }
        else if(strlen(temp_str.c_str()) == 2){
            tempPosHD[0] = '0';
            tempPosHD[1] = '0';
            tempPosHD[2] = (char) temp_str.c_str()[0];
            tempPosHD[3] = (char) temp_str.c_str()[1];
        }
        else if(strlen(temp_str.c_str()) == 3){
            tempPosHD[0] = '0';
            tempPosHD[1] = (char) temp_str.c_str()[0];
            tempPosHD[2] = (char) temp_str.c_str()[1];
            tempPosHD[3] = (char) temp_str.c_str()[2];
        }
        else if(strlen(temp_str.c_str()) == 4){
            tempPosHD[0] = (char) temp_str.c_str()[0];
            tempPosHD[1] = (char) temp_str.c_str()[1];
            tempPosHD[2] = (char) temp_str.c_str()[2];
            tempPosHD[3] = (char) temp_str.c_str()[3];
        }
        else {
            cout << temp_str;
            return;
        }
        stringstream strs;
        strs  << o;
        string temp_str_origem = strs.str();
        for (int i = 0; i<=20; i++){
            if(HD[i][0] == '0'){
                criaPastaCopy(i, temp_str, nomeCopy);
                copyTudoDentro(i, temp_str_origem);
                escreveHD();
                cout << nomeCopy << " copiada para dentro da " <<  nomePasta << endl;
                memset(nomePasta,'\0', 16);
                return;
            }
        }
    }
}

void copyTudoDentro(int i, string temp_str_origem){
    char nomeCopy[16];
    char tempPosHD[4];
    memset(nomeCopy, 0 , 16);
    if(strlen(temp_str_origem.c_str()) == 1){
        tempPosHD[0] = '0';
        tempPosHD[1] = '0';
        tempPosHD[2] = '0';
        tempPosHD[3] = (char) temp_str_origem.c_str()[0];
    }
    else if(strlen(temp_str_origem.c_str()) == 2){
        tempPosHD[0] = '0';
        tempPosHD[1] = '0';
        tempPosHD[2] = (char) temp_str_origem.c_str()[0];
        tempPosHD[3] = (char) temp_str_origem.c_str()[1];
    }
    else if(strlen(temp_str_origem.c_str()) == 3){
        tempPosHD[0] = '0';
        tempPosHD[1] = (char) temp_str_origem.c_str()[0];
        tempPosHD[2] = (char) temp_str_origem.c_str()[1];
        tempPosHD[3] = (char) temp_str_origem.c_str()[2];
    }
    else if(strlen(temp_str_origem.c_str()) == 4){
        tempPosHD[0] = (char) temp_str_origem.c_str()[0];
        tempPosHD[1] = (char) temp_str_origem.c_str()[1];
        tempPosHD[2] = (char) temp_str_origem.c_str()[2];
        tempPosHD[3] = (char) temp_str_origem.c_str()[3];
    }
    int corrigi = i + 1;
    stringstream strs;
    strs  << corrigi;
    string temp_str = strs.str();
    for (int j = 0; j<=20; j++){
        if(HD[j][0] == '1' && HD[j][4] == tempPosHD[0] && HD[j][5] == tempPosHD[1] && HD[j][6] == tempPosHD[2] && HD[j][7] == tempPosHD[3]){
            for(int l = 16; l < 32 && HD[j][l] != 0; l++){
                nomeCopy[l - 16] = HD[j][l];
            }
            corrigi = j+1;
            stringstream strs2;
            strs2  << corrigi;
            temp_str_origem = strs2.str();
            for (int k = 0; k<=20; k++){
                if(HD[k][0] == '0'){
                    if (HD[j][2] == '1'){
                        criaPastaCopy(k, temp_str, nomeCopy);
                        copyTudoDentro(k, temp_str_origem);
                        break;
                    }
                    if (HD[j][2] == '0'){
                        memset(conteudo, 0 , 1000);
                        int bytes = ((HD[j][12] - '0')*1000) + ((HD[j][13] - '0')*100) + ((HD[j][14] - '0')*10) + ((HD[j][15] - '0')*1);
                        int z = ((HD[j][8] - '0')*1000) + ((HD[j][9] - '0')*100) + ((HD[j][10] - '0')*10) + ((HD[j][11] - '0')*1);
                        for (int y = 0; y < bytes; y++){
                            conteudo[y] = HD[z][(y%24)+8];
                            if((y+1)%24 == 0){
                                z = ((HD[z][4] - '0')*1000) + ((HD[z][5] - '0')*100) + ((HD[z][6] - '0')*10) + ((HD[z][7] - '0')*1);
                            }
                        }
                        for(int m = 0; m < 16; m++){
                            nomeArquivo[m] = nomeCopy[m];
                        }
                        criaArquivoCopiado(k, temp_str);
                        memset(nomeArquivo,'\0', 16);
                        memset(conteudo,'\0', 1000);
                        break;
                    }
                }
            }
            memset(nomeCopy, '\0', 16);
        }
    }
    return;
}

void confirmaDisponibilidadeP(){
    leHD();
    for (int i = 0; i<=20; i++){
        if(HD[i][0] == '0'){
            criaPasta(i);
            escreveHD();
            cout << nomePasta <<" criada" << endl;
            memset(nomePasta,'\0', 16);
            return;
        }
    }
}

void criaPasta(int i){
    int l;
    l = posNavegacao;
    l++;
    for (int k = 0; k < 32; k++){
        if ( k == 0){
            HD[i][k] = '1';
        }
        else if ( k == 2){
            HD[i][k] = '1';
        }
        else if ( k >= 4 & k <= 7){
            if(l !=0){
                char tempPosHD[4];
                tempPosHD[0] = '0';
                tempPosHD[1] = '0';
                tempPosHD[2] = '0';
                tempPosHD[3] = '0';
                stringstream strs;
                strs  << l;
                string temp_str = strs.str();
                if(strlen(temp_str.c_str()) == 1){
                    tempPosHD[2] = '0';
                    tempPosHD[3] = (char) temp_str.c_str()[0];
                }
                if(strlen(temp_str.c_str()) == 2){
                    tempPosHD[2] = (char) temp_str.c_str()[0];
                    tempPosHD[3] = (char) temp_str.c_str()[1];
                }
                HD[i][k] = tempPosHD[k-4];
            }
            else{
                HD[i][k] = '0';
            }
        }
        else if ( k >= 8 & k <= 11){
            HD[i][k] = '0';
        }
        else if ( k >= 12 & k <= 15){
            HD[i][k] = '0';
        }
        else if ( k >= 16 & k <= 31){
            HD[i][k] = nomePasta[k-16];
        }
    }
}

void criaPastaCopy(int i, string temp_str, char nomeCopy[]){
    for (int k = 0; k < 32; k++){
        if ( k == 0){
            HD[i][k] = '1';
        }
        else if ( k == 2){
            HD[i][k] = '1';
        }
        else if ( k >= 4 & k <= 7){
            char tempPosHD[4];
            tempPosHD[0] = '0';
            tempPosHD[1] = '0';
            tempPosHD[2] = '0';
            tempPosHD[3] = '0';
            if(strlen(temp_str.c_str()) == 1){
                tempPosHD[2] = '0';
                tempPosHD[3] = (char) temp_str.c_str()[0];
            }
            if(strlen(temp_str.c_str()) == 2){
                tempPosHD[2] = (char) temp_str.c_str()[0];
                tempPosHD[3] = (char) temp_str.c_str()[1];
            }
            HD[i][k] = tempPosHD[k-4];
        }
        else if ( k >= 8 & k <= 11){
            HD[i][k] = '0';
        }
        else if ( k >= 12 & k <= 15){
            HD[i][k] = '0';
        }
        else if ( k >= 16 & k <= 31){
            HD[i][k] = nomeCopy[k-16];
        }
    }
}

void confirmaDisponibilidadeD(){
    for (int i = 0; i<=20; i++){
        if(HD[i][0] == '0'){
            criaArquivo(i);
            escreveHD();
            memset(nomeArquivo, 0 , 16);
            return;
        }
    }
}

int * confirmaDisponibilidadeA(int n){
    int *disponiveis = new int[n];
    int m;
    int i;
    for(m = 0; m < n;m++){
        for (i= 20; i<1024; i++){
            if(HD[i][0] == '0'){
                disponiveis[m] = i;
                HD[i][0] = '1';
                break;
            }
        }
    }
    return disponiveis;
}

void criaArquivo(int i){
    int tamanho = strlen(conteudo);
    int nLinhas = (tamanho/24) + 1;
    int *a;
    a = confirmaDisponibilidadeA(nLinhas);
    criaProximo(a[0]);
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

    int l;
    l = posNavegacao;
    l++;
    int atual = 0;

    for (int k = 0; k < 32; k++){
        if ( k == 0){
            HD[i][k] = '1';
        }
        else if ( k == 2){
            HD[i][k] = '0';
        }
        else if ( k >= 4 & k <= 7){
            if(l !=0){
                char tempPosHD[4];
                tempPosHD[0] = '0';
                tempPosHD[1] = '0';
                tempPosHD[2] = '0';
                tempPosHD[3] = '0';
                stringstream strs;
                strs  << l;
                string temp_str = strs.str();
                if(strlen(temp_str.c_str()) == 1){
                    tempPosHD[2] = '0';
                    tempPosHD[3] = (char) temp_str.c_str()[0];
                }
                if(strlen(temp_str.c_str()) == 2){
                    tempPosHD[2] = (char) temp_str.c_str()[0];
                    tempPosHD[3] = (char) temp_str.c_str()[1];
                }
                HD[i][k] = tempPosHD[k-4];
            }
            else{
                HD[i][k] = '0';
            }
        }
        else if ( k >= 8 & k <= 11){
            HD[i][k] = proximo[k-8];
        }
        else if ( k >= 12 & k <= 15){
            HD[i][k] = tamanhoConteudo[k-12];
        }
        else if ( k >= 16 & k <= 31){
            HD[i][k] = nomeArquivo[k-16];
        }
    }
    for (int j = 0; j <= (nLinhas - 1);j++){
        if(j != (nLinhas - 1)){
            criaProximo(a[(j+1)]);
        }
        for (int k = 0; k < 32; k++){
            if ( k >= 4 & k <= 7){
                if(j == (nLinhas-1)){
                    HD[(a[j])][k] = '0';
                }
                else{
                    HD[(a[j])][k] = proximo[k-4];
                }
            }
            else if ( k >= 8 & k <= 31){
                if (conteudo[atual] != 0){
                    HD[a[j]][k] = conteudo[atual];
                    atual++;
                }
            }
        }
    }
    cout << "arquivo " << nomeArquivo <<" criado com "<< tamanho << " bytes" << endl;
}

void criaArquivoCopiado(int i, string temp_str2){
    int tamanho = strlen(conteudo);
    int nLinhas = (tamanho/24) + 1;
    int *a;
    a = confirmaDisponibilidadeA(nLinhas);
    criaProximo(a[0]);
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
            char tempPosHD[4];
            tempPosHD[0] = '0';
            tempPosHD[1] = '0';
            tempPosHD[2] = '0';
            tempPosHD[3] = '0';
            if(strlen(temp_str2.c_str()) == 1){
                tempPosHD[2] = '0';
                tempPosHD[3] = (char) temp_str2.c_str()[0];
            }
            if(strlen(temp_str2.c_str()) == 2){
                tempPosHD[2] = (char) temp_str2.c_str()[0];
                tempPosHD[3] = (char) temp_str2.c_str()[1];
            }
            HD[i][k] = tempPosHD[k-4];
        }
        else if ( k >= 8 & k <= 11){
            HD[i][k] = proximo[k-8];
        }
        else if ( k >= 12 & k <= 15){
            HD[i][k] = tamanhoConteudo[k-12];
        }
        else if ( k >= 16 & k <= 31){
            HD[i][k] = nomeArquivo[k-16];
        }
    }
    for (int j = 0; j <= (nLinhas - 1);j++){
        if(j != (nLinhas - 1)){
            criaProximo(a[(j+1)]);
        }
        for (int k = 0; k < 32; k++){
            if ( k >= 4 & k <= 7){
                if(j == (nLinhas-1)){
                    HD[(a[j])][k] = '0';
                }
                else{
                    HD[(a[j])][k] = proximo[k-4];
                }
            }
            else if ( k >= 8 & k <= 31){
                if (conteudo[atual] != 0){
                    HD[a[j]][k] = conteudo[atual];
                    atual++;
                }
            }
        }
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

void leHD(){
    fr.open(hdtxt);

    for(int i = 0; i< 1024; i++){
        for(int j = 0; j<32;j++){
            fr >> HD[i][j];
        }
    }

    fr.close();
}

void saiPrograma(){
    exit(0);
}