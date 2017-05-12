/**
@file cgi.h
Macros úteis para gerar CGIs
*/

#include <stdio.h>

/**
* Caminho para as imagens
*/
#define IMAGE_PATH							"http://localhost/images/"

/**
\brief Macro para começar o html
*/
#define COMECAR_HTML						printf("Content-Type: text/html\n\n")

/**
\brief Macro para abrir um svg
@param tamx O comprimento do svg
@param tamy A altura do svg
*/
#define ABRIR_SVG(tamx, tamy)				printf("<svg width=%d height=%d>\n", tamx, tamy)

#define BACKGROUND             printf("<image width=500 height=500 xlink:href=http://localhost/images/space1.png />\n")

#define GAME_OVER							printf("<image width=500 height=500 xlink:href=http://localhost/images/gameover.png />\n")
/**
\brief Macro para fechar um svg
*/
#define FECHAR_SVG							printf("</svg>\n")


/**
\brief Macro para criar uma imagem
@param X A coordenada X do canto superior esquerdo
@param Y A coordenada Y do canto superior esquerdo
@param ESCALA A escala da imagem
@param FICHEIRO O caminho para o link do ficheiro
*/
#define IMAGEM(X, Y, ESCALA, FICHEIRO)		printf("<image x=%d y=%d width=%d height=%d xlink:href=%s />\n", \
												ESCALA * X, ESCALA* Y, ESCALA, ESCALA, IMAGE_PATH FICHEIRO)

#define TEXTO(X, Y, ESCALA, TXT)						printf("<text x=%d y=%d>\n%s\n</text>\n", \
															ESCALA * X, ESCALA * Y, TXT)


/**
\brief Macro para criar um quadrado
@param X A coordenada X do canto superior esquerdo
@param Y A coordenada Y do canto superior esquerdo
@param ESCALA A escala do quadrado
@param COR A cor de preenchimento do quadrado
*/

#define QUADRADO_TRANSP(X, Y, ESCALA)			printf("<rect x=%d y=%d width=%d height=%d opacity=0 />\n", \
												ESCALA * X, ESCALA* Y, ESCALA, ESCALA)

/**
\brief Macro para abrir um link
@param link O caminho para o link
*/
#define ABRIR_LINK(link)					printf("<a xlink:href=%s>\n", link)

/**
\brief Macro para fechar o link
*/
#define FECHAR_LINK							printf("</a>\n")
