#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>

enum Dificuldade { beginner, intermediary, advanced };


struct{

int minas;
int colunas;
int linhas;
} typedef quantidades ;

struct {

std::vector<std::vector<char>> mapa;
quantidades quantidade;

} typedef jogo;








#endif