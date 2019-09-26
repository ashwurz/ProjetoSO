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
int estadoDoComando = 0; //Variavel que diz em qual comando o usuario se encontra
char HD[1024][32];
char proximo[200];
char conteudo[1000];
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
void escreveHD();
void escreveArquivo();
void deleteArquivo();
int iguais(char v[], char d[]);
string nomeHDComTxt();
void confirmaDisponibilidadeD();
int * confirmaDisponibilidadeA(int n);
void criaArquivo(int i);
void criaProximo(int i);
void saiPrograma();
void leHD();


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
    memset(nomeArquivo,'\0', 16);

}

void deleteArquivo(){
    leHD();
    char tempNomeArquivo[16];
    char tempPosConteudo[4];
    int posicaoConteudo = 0;
    for(int i = 0; i < 20; i++){
        for(int j = 16; j < 32; j++){
            if(HD[i][j] != 0) {
                tempNomeArquivo[j - 16] = HD[i][j];
            }
        }
        if(iguais(nomeArquivo, tempNomeArquivo)){
            HD[i][0] = '0';
            for(int k = 8; k < 12; k++){
                tempPosConteudo[k - 8] = HD[i][k];
            }
            posicaoConteudo = atoi(tempPosConteudo);
        }
    }
    HD[posicaoConteudo][0] = '0';
    while ( posicaoConteudo != 0){
        HD[posicaoConteudo][0] = '0';
	    for(int k = 4; k < 8; k++){
	        tempPosConteudo[k - 4] = HD[posicaoConteudo][k];
	    }
	    posicaoConteudo = atoi(tempPosConteudo);
	}
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
        escreveArquivo();
    }
    else if(iguais("delete ", comando)){
        if(estadoDoComando == 0){
            cout << "Comando nao permitido";
            return;
        }
        for(i = 7; comando[i] != 0; i++){
            nomeArquivo[k] = comando[i];
            k++;
        }
        deleteArquivo();
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

void confirmaDisponibilidadeD(){
    for (int i = 0; i<=20; i++){
        if(HD[i][0] == '0'){
            criaArquivo(i);
            escreveHD();
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