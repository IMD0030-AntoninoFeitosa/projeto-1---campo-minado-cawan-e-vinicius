#include <iostream>
#include <fstream>
#include <array>
#include <ctime>
#include <cstdlib>

#include "Game.h"

using namespace std;

const std::string CONFIG_FILE = "config.cfg";







typedef struct{
    int eBomba;
    int estaAberta;
    int vizinhos;
}celula;

// variáveis globais//
celula jogo[10][10];
int l, c, tam = 10;

// procedimento para inicializar a matriz do jogo
void inicializarJogo(){
    for(l = 0; l < tam; l++){
        for(c = 0; c < tam; c++){
            jogo[l][c].eBomba = 0;
            jogo[l][c].estaAberta = 0;
            jogo[l][c].vizinhos = 0;
        }
    }
}

// procedimento para sortear n bombas
void sortearBombas(int x){
    int i, bombas = 0;
    srand(time(NULL));
    for(i = 1; i <= x; i++){
        l = rand() % tam;
        c = rand() % tam;
        if(jogo[l][c].eBomba == 0){
            jogo[l][c].eBomba = 1;
            bombas++;
        }
        else
            i--;
    }
}

//função que diz se um par de coordenadas é válido ou não//
//1 - é válido//
//0 - não é válido//

int coordenadaEhValida(int l, int c){
    if(l >= 0 && l < tam && c >= 0 && c < tam)
        return 1;
    else
        return 0;
}


//função que retorna a quantidade de bombas na vizinhança//

int quantBombasVizinhas(int l, int c){

    int quantidade = 0;

    if(coordenadaEhValida(l - 1, c) && jogo[l-1][c].eBomba)
        quantidade++;
    if(coordenadaEhValida(l + 1, c) && jogo[l+1][c].eBomba)
        quantidade++;
    if(coordenadaEhValida(l, c + 1) && jogo[l][c+1].eBomba)
        quantidade++;
    if(coordenadaEhValida(l, c - 1) && jogo[l][c-1].eBomba)
        quantidade++;
    return quantidade;
}

// procedimento para contar as bombas vizinhas
void contarBombas(){
    for(l = 0; l < tam; l++){
        for(c = 0; c < tam; c++)
            jogo[l][c].vizinhos = quantBombasVizinhas(l, c);
    }
}



// procedimento para imprimir o jogo
void imprimir(){
    cout<<"    ";
    for(l = 0; l < tam; l++)
        cout<<" "<<l<<"  "; // índices das colunas
    cout<<endl<<"   -----------------------------------------"<<endl;
    for(l = 0; l < tam; l++){
        cout<<l<<"  |"; // índices das linhas
        for(c = 0; c < tam; c++){
            if(jogo[l][c].estaAberta){
                if(jogo[l][c].eBomba)
                    cout<<" * ";// se for bomba *
                else
                    cout<<jogo[l][c].vizinhos; //bombas vizinhas
            }
            else
                cout<<"   "; // imprime três espaços quando está fechada
            cout<<"|";// barra verticais
        }
        cout<<endl<<"   -----------------------------------------"<<endl;
    }
}





void mostrar_instrucoes(void){
    std::cout << "Instruções Campo Minado" << std::endl;
    std::cout << "Opções:" << std::endl;
    std::cout << "-h ou --help" << std::endl;
    std::cout << "-d ou --Dificuldade + (dificuldade escolhida)" << std::endl;
    std::cout << "                               Dificuldades disponiveis:" << std::endl;
    std::cout << "                               -b ou --beginner" << std::endl;
    std::cout << "                               -i ou --intermediary" << std::endl;
    std::cout << "                               -a ou --advanced" << std::endl;

}

void armazenar_Dificuldade(const std::string config_file, Dificuldade level){
  std::ofstream file;
  file.open (config_file.c_str(), std::ifstream::out);
  if(file.is_open()){
    switch(level){
      case Dificuldade::beginner: file << 'b'; break;
      case Dificuldade::intermediary: file << 'i'; break;
      case Dificuldade::advanced: file << 'a'; break;
    }
    file.close();
  }
}


Dificuldade carregar_Dificuldade(const std::string config_file){
  Dificuldade level;
  std::ifstream file;
  file.open (config_file.c_str(), std::ifstream::in);
  if(file.is_open()){
    char c;
    file >> c;
    switch(c){
      case 'b': level = Dificuldade::beginner; break;
      case 'i': level = Dificuldade::intermediary; break;
      case 'a': level = Dificuldade::advanced; break;
    }
    file.close();
  } else {
    armazenar_Dificuldade(config_file, Dificuldade::beginner);
    level = Dificuldade::beginner;
  }
  return level;
}

void comecarJogo(string n){
  int x = 0;
  if (n == "beginner"){
    tam = 10;
    x = 10;
  }
  else if (n == "intermediary"){
    tam = 15;
    x = 40;

  }

  
  
  inicializarJogo();
  sortearBombas(x);
  contarBombas();
  imprimir();
}

int main(int argc, char ** argv){

  if(argc > 1){
    std::string arg = argv[1];
    if(arg == "-h" || arg == "--help"){
      mostrar_instrucoes();
    } else if(arg == "-d" || arg == "--Dificuldade"){
      
      if(argc > 2){
        std::string newlevel = argv[2];
        if(newlevel == "-b" || newlevel == "--beginner"){
          armazenar_Dificuldade(CONFIG_FILE, Dificuldade::beginner);
        } else if(newlevel == "-i" || newlevel == "--intermediary"){
          armazenar_Dificuldade(CONFIG_FILE, Dificuldade::intermediary);
        } else if(newlevel == "-a" || newlevel == "--advanced"){
          armazenar_Dificuldade(CONFIG_FILE, Dificuldade::advanced);
        } else {
          std::cout << "Dificuldade escolhida nao existe: " << newlevel << std::endl;
          mostrar_instrucoes();
        }
      } else {
        std::cout << "Esperando uma dificuldade para: " << argv[1] << std::endl;
        mostrar_instrucoes();
      }
    } else {
      std::cout << "Comando desconhecido: " << argv[1] << std::endl;
      mostrar_instrucoes();
    }
  } else {
    Dificuldade level = carregar_Dificuldade(CONFIG_FILE);
      comecarJogo(level);
  }
  return 0;
}
