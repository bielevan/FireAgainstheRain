// Geral
struct Overall {
    SDL_Rect rect;
    SDL_Point vel;
    SDL_Texture *texture;
};

// Life
struct Life {
    SDL_Rect rect;
    SDL_Texture *texture;
};

// Pocao
struct Poison {
    SDL_Rect rect;
    SDL_Point vel;
    int frame;
    SDL_Texture *texture;
};

// Aumenta vida
struct Vida {
    SDL_Rect rect;
    SDL_Texture *texture;
	int frame;
    int visible;
};

// Estrela
struct Star {
    /*Para a animacao da estrela, precisamos de dois retangulos: um para pritar na tela
    e o outro para ler diferentes posicoes da imagem que, com o tempo, sera trocada para
    fazer a animacao*/
    SDL_Rect SCREENrect;
    SDL_Rect IMGrect;
    SDL_Point vel;
    SDL_Texture *texture;
	int star_moviment;
	int frames;
    Uint32 ticks; // Funcao que conta o tempo para formar a animacao
    Uint32 seconds; //Assim passamos de ms >>> s
    Uint32 sprite; //Numero de sprites da animacao
};

// Images
struct Imagem {
    SDL_Rect rect;
    SDL_Texture *texture;
};

// Menu
struct Menu {
    SDL_Rect rect;
    SDL_Texture *texture2;
    SDL_Texture *texture1;
    int cor;
};

// Texto
struct Font {
    SDL_Rect rect;
    TTF_Font *font;
    SDL_Color colorText;
    SDL_Texture *texture;
    SDL_Surface *textSurface;
};

struct WriteScreen {
    SDL_Rect rect;
    SDL_Color colorText;
    SDL_Texture *texture;
};

typedef struct Player {
    int pontuacao;
    int tempo;
    struct tm data;
}PLAYER;

// Tela
SDL_Window *window;
SDL_Surface *screen;
SDL_Rect rect_title;
SDL_Renderer *renderer;
SDL_Texture *texture_title;
SDL_Texture *texture_screen;

struct Vida vida;
struct Star star;
struct Overall ice;
struct Life life[3];
struct Menu menu[3];
struct Poison poison;
struct Overall square;
struct Overall ball[18];
struct Overall clouds[10];
struct Font text, pontuacao_inf;
struct Menu menuGameOver, menuScore, menuInstrucoes;
struct Imagem informacao_game_over, sair, informacao;
struct WriteScreen pontuacao, game_over_pontuacao, game_over_tempo, game_over_pontuacao_total, game_over_tempo_total;

int frames;
int lifes = 2;

// Verifica movimentos
int ice_moviment;
int rain_moviment;
int poison_moviment;
int square_moviment;

// Controla Telas
int on_game;
int on_run;

//Timer
int tempo = 0;
char tempoChar[5] = "";

// Pontuação
int len_score;
struct Player *player;

Mix_Chunk *musica;