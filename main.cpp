#include "Game.h"


const std::string CONFIG_FILE = "config.cfg";



jogo InicializarJogo(Dificuldade level) {
  jogo jogo;
  if (level == 0) {
    jogo.quantidade.minas = 10;
    jogo.quantidade.linhas = 10;
    jogo.quantidade.colunas = 10;
    // 10 x 10 + 10 minas
  } else if (level == 1) {
    jogo.quantidade.minas = 40;
    jogo.quantidade.linhas = 15;
    jogo.quantidade.colunas = 15;
    // 15 x 15 + 40 minas
  } else if (level == 2) {
    jogo.quantidade.minas = 100;
    jogo.quantidade.linhas = 15;
    jogo.quantidade.colunas = 30;
    // 15 x 30 + 100 minas
  } else {
    //  armazenar_Dificuldade(CONFIG_FILE, level);
  }
  int l = jogo.quantidade.linhas;
  int c = jogo.quantidade.colunas;
  for (int i = 0; i < l; i++) {
    std::vector<char> temp;
    for (int j = 0; j < c; j++) {
      temp.push_back('X');
    }
    jogo.mapa.push_back(temp);
  }

  return jogo;
}

// procedimento para sortear n bombas
void sortearBombas(jogo &jogo) {
  srand(time(NULL));
  int conta_minas = 0;
  do {
    int l = rand() % jogo.quantidade.linhas;
    int c = rand() % jogo.quantidade.colunas;
    
    if (jogo.mapa[l][c] != '@') {
      jogo.mapa[l][c] = '@';
      conta_minas++;
    }
  } while (conta_minas < jogo.quantidade.minas);
}

// função que diz se um par de coordenadas é válido ou não//
// 1 - é válido//
// 0 - não é válido//

bool coordenadaEhValida(jogo &jogo, int l, int c) {
  
  if (l >= 0 && l < jogo.quantidade.linhas && c >= 0 && c < jogo.quantidade.colunas)
    return true;
  else
    return false;
}

// função que retorna a quantidade de bombas na vizinhança//

int quantBombasVizinhas(jogo &jogo, int l, int c) {

  int quantidade = 0;
  //REFAZER PARA VERIFICAR 8 CASAS
  if (coordenadaEhValida(jogo, l - 1, c) && jogo.mapa[l - 1][c] == '@')
    quantidade++;
  if (coordenadaEhValida(jogo, l + 1, c) && jogo.mapa[l + 1][c] == '@')
    quantidade++;
  if (coordenadaEhValida(jogo, l, c + 1) && jogo.mapa[l][c + 1] == '@')
    quantidade++;
  if (coordenadaEhValida(jogo, l, c - 1) && jogo.mapa[l][c - 1] == '@')
    quantidade++;
  return quantidade;
}

// procedimento para contar as bombas vizinhas
void contarBombas(jogo &jogo) {
  for ( int l = 0; l < jogo.quantidade.linhas; l++) {
    for (int c = 0; c < jogo.quantidade.colunas; c++)
      jogo.mapa[l][c] = (char)quantBombasVizinhas(jogo, l, c);
  }
}

bool verifica_bomba(jogo &jogo, int l, int c) {
  if (jogo.mapa[l][c] == '@') {
    return true;
  }
  return false;
}

// procedimento para imprimir o jogo
void imprimir(jogo &jogo) {
  std::cout << std::endl
       << std::endl
       << "\t"
       << "    ";
  for (int l = 0; l < jogo.quantidade.linhas; l++)
    std::cout << " " << l << "  "; // índices das colunas
  std::cout << std::endl
       << "\t"
       << "   -----------------------------------------" << std::endl;
  for (int l = 0; l < jogo.quantidade.linhas; l++) {
    std::cout << "\t" << l << "  |"; // índices das linhas
    for (int c = 0; c < jogo.quantidade.colunas; c++) {
      if (verifica_bomba(jogo, l, c)) {
        if (jogo.mapa[l][c])
          std::cout << " @ "; // se for bomba *
        else
          std::cout << " " << jogo.mapa[l][c]<< " "; // bombas vizinhas
      } else
        std::cout << "   "; // imprime três espaços quando está fechada
      std::cout << "|";     // barra verticais
    }
    std::cout << std::endl << "\t   -----------------------------------------" << std::endl;
  }
}

void mostrar_instrucoes() {
  std::cout << "Instruções Campo Minado" << std::endl;
  std::cout << "Opções:" << std::endl;
  std::cout << "-h ou --help" << std::endl;
  std::cout << "-d ou --Dificuldade + (dificuldade escolhida)" << std::endl;
  std::cout << "                               Dificuldades disponiveis:"
            << std::endl;
  std::cout << "                               -b ou --beginner" << std::endl;
  std::cout << "                               -i ou --intermediary"
            << std::endl;
  std::cout << "                               -a ou --advanced" << std::endl;
}

void armazenar_Dificuldade(const std::string config_file, Dificuldade level) {
  std::ofstream file;
  file.open(config_file.c_str(), std::ifstream::out);
  if (file.is_open()) {
    switch (level) {
    case Dificuldade::beginner:
      file << 'b';
      break;
    case Dificuldade::intermediary:
      file << 'i';
      break;
    case Dificuldade::advanced:
      file << 'a';
      break;
    }
    file.close();
  }
}

Dificuldade carregar_Dificuldade(const std::string config_file) {
  Dificuldade level;
  std::ifstream file;
  file.open(config_file.c_str(), std::ifstream::in);
  if (file.is_open()) {
    char c;
    file >> c;
    switch (c) {
    case 'b':
      level = Dificuldade::beginner;
      break;
    case 'i':
      level = Dificuldade::intermediary;
      break;
    case 'a':
      level = Dificuldade::advanced;
      break;
    }
    file.close();
  } else {
    armazenar_Dificuldade(config_file, Dificuldade::beginner);
    level = Dificuldade::beginner;
  }
  return level;
}

// abrir coordenadas
void abrirCelula(jogo &jogo, int l, int c) {
  if (coordenadaEhValida(jogo, l, c) && jogo.mapa[l][c] == false) {
    std::cout << " ";
    jogo.mapa[l][c] = 1;
    if (jogo.mapa[l][c] == 0) {

      abrirCelula(jogo, l - 1, c);
      abrirCelula(jogo, l + 1, c);
      abrirCelula(jogo, l, c + 1);
      abrirCelula(jogo, l, c - 1);
    }
  }
}

// verificar vitoria n > 0 ainda n ganhou, n = 0 ganhou
int ganhou(jogo &jogo) {
  int quantidade = 0;

  for (int l = 0; l < jogo.quantidade.linhas; l++) {
    for (int c = 0; c < jogo.quantidade.colunas; c++) {
      if (jogo.mapa[l][c] == 0 && jogo.mapa[l][c] == 0)
        quantidade++;
    }
  }
  return quantidade;
}

// ler coordenadas
void jogar(jogo &jogo) {
  int l, c;
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  do {
    imprimir(jogo);
    do {
      std::cout << std::endl << "Digite as coordenadas de linha e coluna:";
      std::cin >> l >> c;
      if (coordenadaEhValida(jogo, l, c) == 0 ||
          jogo.mapa[l][c] == 1)
        std::cout << "Coordenada invalida ou ja aberta!";
    } while (coordenadaEhValida(jogo, l, c) == 0 ||
             jogo.mapa[l][c] == 1);

    abrirCelula(jogo, l, c);
  } while (ganhou != 0);

  if (verifica_bomba(jogo,l,c))
    std::cout << std::endl << "Que pena! Voce perdeu!!!" << std::endl;
  else
    std::cout << std::endl << "PARABENS! VOCE GANHOU!!!" << std::endl;
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "DURACAO DA PARTIDA: "<< elapsed_seconds.count() << "s\n";
  imprimir(jogo);
}

void comecarJogo(Dificuldade level) {
  jogo jogo = InicializarJogo(level);
  sortearBombas(jogo);
  contarBombas(jogo);

  jogar(jogo);
}


int main(int argc, char **argv) {

  if (argc > 1) {
    std::string arg = argv[1];
    if (arg == "-h" || arg == "--help") {
      mostrar_instrucoes();
    } else if (arg == "-d" || arg == "--Dificuldade") {

      if (argc > 2) {
        std::string newlevel = argv[2];
        if (newlevel == "-b" || newlevel == "--beginner") {
          armazenar_Dificuldade(CONFIG_FILE, Dificuldade::beginner);
        } else if (newlevel == "-i" || newlevel == "--intermediary") {
          armazenar_Dificuldade(CONFIG_FILE, Dificuldade::intermediary);
        } else if (newlevel == "-a" || newlevel == "--advanced") {
          armazenar_Dificuldade(CONFIG_FILE, Dificuldade::advanced);
        } else {
          std::cout << "Dificuldade escolhida nao existe: " << newlevel
                    << std::endl;
          mostrar_instrucoes();
        }
      } else {
        std::cout << "Esperando uma dificuldade para: " << argv[1] << std
          ::endl;
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
