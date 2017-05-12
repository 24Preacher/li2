#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "cgi.h"
#include "estado.h"
#include "escrever.c"


#define MAX_BUFFER		10240
#define TAM				10
#define ESCALA			50

int posicao_valida(int x, int y) {
	return x >= 0 && y >= 0 && x < TAM && y < TAM;
}
int posicao_igual(POSICAO p, int x, int y) {
	return p.x == x && p.y == y;
}

int tem_jogador (ESTADO e, int x, int y){
	return posicao_igual(e.jog, x, y);
}

int tem_inimigo (ESTADO e, int x, int y) {
	int i;
	for(i=0; i < e.num_inimigos; i++)
		if  (posicao_igual(e.inimigo[i], x, y))
			return 1;
		return 0;
}

int tem_obstaculo (ESTADO e, int x, int y) {
	int i;
	for(i = 0; i < e.num_obstaculos; i++)
		if  (posicao_igual(e.obstaculo[i], x, y))
			return 1;
		return 0;
}

int tem_porta (ESTADO e, int x, int y){
	return posicao_igual(e.porta, x, y);
}

int posicao_ocupada (ESTADO e, int x, int y){
	return tem_jogador(e, x, y) || tem_inimigo(e, x, y) || tem_obstaculo(e, x, y)|| tem_porta(e, x, y);
}

void imprime_casa_transparente(int x, int y) {
	QUADRADO_TRANSP(x, y,ESCALA);
}

ESTADO inicializar_inimigo (ESTADO e) {
    int x, y;

    do {
   		x = random() % TAM;
    	y = random() % TAM;
    } while (posicao_ocupada (e, x, y));

    e.inimigo[(int)e.num_inimigos].x = x;
    e.inimigo[(int)e.num_inimigos].y = y;
    e.num_inimigos++;
	return e;
}

ESTADO inicializar_inimigos (ESTADO e, int num) {
	int i;
	for (i = 0; i < num; i++)
		e = inicializar_inimigo (e);
	return e;
}

ESTADO inicializar_obstaculo (ESTADO e) {
    int x, y;
    do {
   		x = random() % TAM;
    	y = random() % TAM;
    } while (posicao_ocupada (e, x, y));
    e.obstaculo[(int)e.num_obstaculos].x = x;
    e.obstaculo[(int)e.num_obstaculos].y = y;
    e.num_obstaculos++;
	return e;
}

ESTADO inicializar_obstaculos (ESTADO e, int num){
	int i;
	for (i = 0; i < num; i++)
		e = inicializar_obstaculo (e);
	return e;
}


ESTADO inicializar() {
	ESTADO e = {{0}};
	e.jog.x = random() % TAM;
	e.jog.y = random() % TAM;
	e.porta.x = random() % TAM;
	e.porta.y = random() % TAM;
	e.hp = 100;
	e = inicializar_inimigos(e, 15);
	e = inicializar_obstaculos(e, 20);
	return e;
}



int returninimigo (ESTADO e, int x,int y){
	int i;
	for (i=0; i < e.num_inimigos; i++){
			if (e.inimigo[i].x == x && e.inimigo[i].y == y)
				return i;
	}
}


ESTADO ataca_inimigo (ESTADO e, int x, int y){
	int i;
	i = returninimigo(e,x,y);
	for (i; i < e.num_inimigos; i++){
			e.inimigo[i] = e.inimigo[i+1];
	}
	e.num_inimigos--;
	return e;

}

ESTADO morre_jogador(ESTADO e){
	int x = e.jog.x;
	int y = e.jog.y;
	int dx, dy;
	for (dx = -1; dx <= 1; dx++)
		for (dy = -1; dy <= 1; dy++)
			if (tem_inimigo (e, x + dx ,y + dy))
				e.hp -= 15;
	return e;
}


/* ESTADO moveinimigo (ESTADO e, int dx, int dy){
	int

	x = e.inimigo[i].x + dx;
	y = e.inimigo[i].y + dy;
	if (!posicao_valida(x,y))
		return e;

}*/


/*


ESTADO moveinimigo (ESTADO e) {
	int i, x, y;
	int dx, dy;
	for(i = 0; i < e.num_inimigos; i++) {
		dx = -1 + random() % 3;
		dy = -1 + random() % 3;
		x = e.inimigo[i].x + dx;
		y = e.inimigo[i].y + dy;
		if(!posicao_valida(x, y) || tem_obstaculo(e, x, y) || tem_porta(e,x,y) || tem_jogador(e, x,y))
			return e;
		e.inimigo[i].x = x;
		e.inimigo[i].y = y;
	}
	return e;
}



ESTADO moveinimigos (ESTADO e){
	int dx, dy;
		for (dx = -1 && dy=-1; dx <= 1 && dy <=1; dx++ && dy++){
			e = moveinimigo(e, dx, dy);
        }
	return e;
} */


int calculadist (ESTADO e, int dx, int dy){
	int x = e.jog.x;
	int y = e.jog.y;
	int dist;

	dist = ((dx - x)^2) + ((dy - y)^2);

	return dist;
}



// funçao que faz array com posiçoes para as quais os inimigos podem ir

ESTADO pospossiveis (ESTADO e,int i){
	int dx , dy;
	int x = 0, y = 0;
	int dist = 240000;
	int dist2;
	for (dx = -1; dx <= 1; dx++)
		for(dy = -1; dy <= 1; dy++) {
				if(dx != 0 || dy != 0) {
					dist2 = calculadist(e,e.inimigo[i].x + dx, e.inimigo[i].y + dy);
					if(!posicao_ocupada(e, e.inimigo[i].x + dx, e.inimigo[i].y + dy) && posicao_valida(e.inimigo[i].x + dx, e.inimigo[i].y + dy)) {
						if (dist2 < dist){
							dist = dist2;
							x = e.inimigo[i].x + dx;
							y = e.inimigo[i].y + dy;
						}
				}
			}
		}

	e.inimigo[i].x = x;
	e.inimigo[i].y = y;
	return e;
}


ESTADO loopmove (ESTADO e) {
	int i;

	for (i = 0; i < e.num_inimigos; i++)
		e = pospossiveis(e,i);
	return e;
}

// funcao que calcula a posicao a menor distancia do jogador


// realizar o movimento


void imprime_movimento(ESTADO e, int dx, int dy) {
	ESTADO novo = e;
	int x = e.jog.x + dx;
	int y = e.jog.y + dy;
	char link[MAX_BUFFER];
	if(!posicao_valida(x, y))
		return;
	if(tem_obstaculo(e, x, y) && !tem_porta(e, x, y))
		return;
	if(tem_inimigo (e, x ,y))
		novo = ataca_inimigo (e,x,y);
	novo.jog.x = x;
	novo.jog.y = y;
	novo = loopmove(novo);
	novo = morre_jogador(novo);

	sprintf(link, "http://localhost/cgi-bin/exemplo?%s", estado2str(novo));
	ABRIR_LINK(link);
	imprime_casa_transparente(x, y);
	FECHAR_LINK;
}

void imprime_movimentos(ESTADO e) {
	int dx, dy;
	for (dx = -1; dx <= 1; dx++)
		for (dy = -1; dy <= 1; dy++)
			if (dx != 0 || dy != 0)
			imprime_movimento(e, dx, dy);
}

void imprime_jogador(ESTADO e) {
	IMAGEM(e.jog.x, e.jog.y, ESCALA, "foguetao.png");
	imprime_movimentos(e);
}

void imprime_porta (ESTADO e) {
	IMAGEM(e.porta.x, e.porta.y, ESCALA, "earth.png");
}


ESTADO ler_estado(char *args) {
	if(strlen(args) == 0)
		return inicializar();

	ESTADO e = str2estado(args);
	if (e.jog.x == e.porta.x && e.jog.y == e.porta.y)
		e = inicializar();

	return e;
}

void imprime_inimigos(ESTADO e) {
	int i;
	for(i = 0; i < e.num_inimigos; i++)
		IMAGEM(e.inimigo[i].x, e.inimigo[i].y, ESCALA, "alien1.png");
}

void imprime_obstaculos(ESTADO e) {
	int i;
	for(i = 0; i < e.num_obstaculos; i++)
		IMAGEM(e.obstaculo[i].x, e.obstaculo[i].y, ESCALA, "rock1.png");
}

void imprime_gameover(ESTADO e) {
	IMAGEM(e.jog.x, e.jog.y, ESCALA, "gameover.png");
}
int main() {
	srandom (time(NULL));
	int x, y;

	ESTADO e = ler_estado(getenv("QUERY_STRING"));


	COMECAR_HTML;
	ABRIR_SVG(700, 700);
    BACKGROUND;

	for(y = 0; y < 10; y++)
		for(x = 0; x < 10; x++)
			imprime_casa_transparente(x, y);

	imprime_inimigos(e);
	imprime_obstaculos(e);
    imprime_porta(e);
    imprime_jogador(e);
			if (e.hp <= 0){
				e.hp = 0;
				GAME_OVER;
			}
    char linha[1024] = {0};

	sprintf(linha, "%s %d/100 (%f)", e.nome, e.hp, e.escala);
	TEXTO(11, 1, ESCALA, linha);


	FECHAR_SVG;

	return 0;
}
