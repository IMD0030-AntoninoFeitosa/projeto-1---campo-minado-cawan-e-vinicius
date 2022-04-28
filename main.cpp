#include <iostream>
#include <fstream>

#include "Game.h"


const std::string CONFIG_FILE = "config.cfg";

void mostrar_instruções(void){
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

int main(int argc, char ** argv){

  if(argc > 1){
    std::string arg = argv[1];
    if(arg == "-h" || arg == "--help"){
      mostrar_instruções();
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
          mostrar_instruções();
        }
      } else {
        std::cout << "Esperando uma dificuldade para: " << argv[1] << std::endl;
        mostrar_instruções();
      }
    } else {
      std::cout << "Comando desconhecido: " << argv[1] << std::endl;
      mostrar_instruções();
    }
  } else {
    Dificuldade level = carregar_Dificuldade(CONFIG_FILE);
    start_game(level);
  }
  return 0;
}
