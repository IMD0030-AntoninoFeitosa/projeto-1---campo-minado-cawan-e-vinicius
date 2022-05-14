#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <iostream>
#include <array>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>



enum Dificuldade { beginner, intermediary, advanced };



typedef struct{

int minas;
int colunas;
int linhas;

} quantidades ;

typedef struct {

std::vector<std::vector<char>> mapa;
quantidades quantidade;
int mostrou;
std::vector<std::vector<int>> marcou;

} jogo;


bool verifica_bomba(jogo & jogo, int l, int c);

#endif
