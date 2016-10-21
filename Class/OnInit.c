#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Reinicalizar Fundo
void OnRestartScreen()
{
    // Fundo
    SDL_Surface *surface_background = SDL_LoadBMP("Imagens/background.bmp");
    texture_screen = SDL_CreateTextureFromSurface(renderer, surface_background);

    // Texto
    pontuacao.rect.w = 160;
    pontuacao.rect.h = 50;
    pontuacao.rect.x = 590;
    pontuacao.rect.y = 50;
    pontuacao.colorText.r = 0;
    pontuacao.colorText.g = 0;
    pontuacao.colorText.b = 0;
    pontuacao.colorText.a = 255;

    //Texto da pontuacao
    SDL_Surface *textoPontuacaoSurface = TTF_RenderUTF8_Blended(text.font, "Pontuação: ", pontuacao.colorText);
    pontuacao.texture = SDL_CreateTextureFromSurface(renderer, textoPontuacaoSurface);
    
    // Carregar Imagens
    SDL_Surface *surface_heart = SDL_LoadBMP("Imagens/heart.bmp");

    // Vida
    lifes = 2;
    for (int i = 0; i < 3; ++i)
    {
        SDL_DestroyTexture(life[i].texture);
        life[i].texture = NULL;
        life[i].rect.w = 60;
        life[i].rect.h = 60;
        life[i].rect.y = 5;
        life[i].rect.x = SCREEN_WIDTH-55-(45 * i);
        life[i].texture = SDL_CreateTextureFromSurface(renderer, surface_heart);
    }

    // Vida
    vida.frame = 0;
        vida.visible = 0;

    frames = 0;

    // Excluir Surfaces
    SDL_FreeSurface(surface_heart);
    SDL_FreeSurface(surface_background);
    SDL_FreeSurface(textoPontuacaoSurface);
}

// Inializar ou reiniar posicao
void OnRestartPosition()
{
    int sort, i;
    /*Inicializacoes das nuvens, este vetor eh importante para evitar que, em um caso aleatorio,
    todas as nuvens inicializem juntas*/

    int c[10] = {0, 50, 100, 200, 350, 500, 520, 690, 490, 777};
    // Nuvem
    for(i = 0; i < 10; i++)
    {
        clouds[i].rect.x = c[i];
        if(i % 2 == 0)
            clouds[i].vel.x = rand() % 3 + 1;
        else
            clouds[i].vel.x = -1 * (rand() % 3 + 1);
        clouds[i].vel.y = 0;
    }

    // Chuva
    for (i = 0; i < 18; i++)
    {
        sort = rand() % 6 + 1;
        ball[i].rect.x = rand() % 192 + clouds[sort].rect.x;
        ball[   i].rect.y = rand() % 20 + 1;
        ball[i].vel.y = rand() % 3 + 1;
    }

    // Personagem
    square.vel.x = 2;
    square.rect.x = 300;
  
    // Pontuacao
    tempo = 0;
    memset(tempoChar, 5, 0x0);

    // Pocao
    poison.frame = 0;

    // Vida
    vida.frame = 0;
}

// Inicializar componetes da instrucoes
int OnInitInstructions()
{
    // Carregar surfaces
    SDL_Surface *surface_informacao = SDL_LoadBMP("Imagens/FundoGameOver.bmp");
    if (surface_informacao == NULL)
    {
        SDL_Log("Não foi possível encontrar fundo\n");
        return -1;
    }
    SDL_Surface *surface_menu = SDL_LoadBMP("Imagens/menu1.bmp");
    if (surface_menu == NULL)
    {
        SDL_Log("Imagem do menu não encontrado\n");
        return -1;
    }
    SDL_Surface *surface_menu2 = SDL_LoadBMP("Imagens/menu2.bmp");
    if (surface_menu2 == NULL)
    {
        SDL_Log("Imagem do menu 2 não encontrado\n");
        return -1;
    }
    SDL_Surface *surface_instrucoes = SDL_LoadBMP("Imagens/instrucoes.bmp");
    if (surface_instrucoes == NULL)
    {
        SDL_Log("Imagem da insrucoes não foi localizada\n");
        return -1;
    }

    // Botao
    menuInstrucoes.cor = 0;
    menuInstrucoes.rect.h = 50;
    menuInstrucoes.rect.w = 130;
    menuInstrucoes.rect.y = 475;
    menuInstrucoes.rect.x = 340;
    menuInstrucoes.texture2 = SDL_CreateTextureFromSurface(renderer, surface_menu);
    menuInstrucoes.texture1 = SDL_CreateTextureFromSurface(renderer, surface_menu2);
    
    // Instrucoes
    informacao.rect.w = 700;
    informacao.rect.h = 394;
    informacao.rect.x = 60;
    informacao.rect.y = 70;
    informacao.texture = SDL_CreateTextureFromSurface(renderer, surface_instrucoes);

    // Excluir Surfaces
    SDL_FreeSurface(surface_menu);
    SDL_FreeSurface(surface_menu2);
    SDL_FreeSurface(surface_instrucoes);
    return 1;
}

// Inicializar componentes do Game Over
int OnInitGameOver()
{
    // Salvar dados
    struct Player player;
    player.pontuacao = (tempo / 100) * 15;
    player.tempo = tempo / 100;
    time_t t;
    t = time(NULL);
    player.data = *(localtime(&t));
    SDL_Log("Salvando dados....\n");
    printf("%d / %d / %d \n", player.data.tm_mday, player.data.tm_mon, player.data.tm_year+1900);
    saveFile(&player);

    // Carregar imagens
    SDL_Surface *surface_background = SDL_LoadBMP("Imagens/background2.bmp");
    if (surface_background == NULL)
    {
        SDL_Log("Nao foi possível encontrar background 2\n");
        return -1;
    }
    SDL_Surface *surface_informacao = SDL_LoadBMP("Imagens/FundoGameOver.bmp");
    if (surface_informacao == NULL)
    {
        SDL_Log("Não foi possível encontrar fundo\n");
        return -1;
    }
    SDL_Surface *surface_menu = SDL_LoadBMP("Imagens/menu1.bmp");
    if (surface_menu == NULL)
    {
        SDL_Log("Imagem do menu não encontrado\n");
        return -1;
    }
    SDL_Surface *surface_menu2 = SDL_LoadBMP("Imagens/menu2.bmp");
    if (surface_menu2 == NULL)
    {
        SDL_Log("Image do menu 2 não encontrado\n");
        return -1;
    }

    // Background
    texture_screen = SDL_CreateTextureFromSurface(renderer, surface_background);
    
    // Informacao
    informacao_game_over.rect.w = 600;
    informacao_game_over.rect.h = 400;
    informacao_game_over.rect.x = 100;
    informacao_game_over.rect.y = 100;
    informacao_game_over.texture = SDL_CreateTextureFromSurface(renderer, surface_informacao);

    // Texto
    TTF_CloseFont(text.font);
    text.font = TTF_OpenFont("Font/Lobster-Regular.ttf", 120);
    if (!text.font)
    {
        SDL_Log("Erro na fonte: %s", TTF_GetError());
        return -1;
    }
    // Texto do game over
    pontuacao.rect.w = 320;
    pontuacao.rect.h = 100;
    pontuacao.rect.x = 240;
    pontuacao.rect.y = 110;
    pontuacao.colorText.r = 52;
    pontuacao.colorText.g = 73;
    pontuacao.colorText.b = 94;
    pontuacao.colorText.a = 255;
    SDL_Surface *textoPontuacaoSurface = TTF_RenderUTF8_Blended(text.font, "Fim do Jogo", pontuacao.colorText);
    pontuacao.texture = SDL_CreateTextureFromSurface(renderer, textoPontuacaoSurface);
    
    game_over_pontuacao.rect.w = 200;
    game_over_pontuacao.rect.h = 80;
    game_over_pontuacao.rect.x = 310;
    game_over_pontuacao.rect.y = 220;
    textoPontuacaoSurface = TTF_RenderUTF8_Blended(text.font, "Pontuacao", pontuacao.colorText);
    game_over_pontuacao.texture = SDL_CreateTextureFromSurface(renderer, textoPontuacaoSurface);

    game_over_pontuacao_total.rect.h = 40;
    game_over_pontuacao_total.rect.y = 300;
    game_over_pontuacao_total.rect.x = 360;
    game_over_pontuacao_total.rect.w = 90;
    char texto[20];
    sprintf(texto, "%d", player.pontuacao);
    textoPontuacaoSurface = TTF_RenderUTF8_Blended(text.font, texto, pontuacao.colorText);
    game_over_pontuacao_total.texture = SDL_CreateTextureFromSurface(renderer, textoPontuacaoSurface);
    
    game_over_tempo.rect.w = 120;
    game_over_tempo.rect.h = 70;
    game_over_tempo.rect.y = 340;
    game_over_tempo.rect.x = 350;
    textoPontuacaoSurface = TTF_RenderUTF8_Blended(text.font, "Tempo", pontuacao.colorText);
    game_over_tempo.texture = SDL_CreateTextureFromSurface(renderer, textoPontuacaoSurface);

    game_over_tempo_total.rect.h = 30;
    game_over_tempo_total.rect.y = 410;
    game_over_tempo_total.rect.x = 390;
    game_over_tempo_total.rect.w = 40;
    sprintf(texto, "%d", player.tempo);
    textoPontuacaoSurface = TTF_RenderUTF8_Blended(text.font, texto, pontuacao.colorText);
    game_over_tempo_total.texture = SDL_CreateTextureFromSurface(renderer, textoPontuacaoSurface);

    // Botao
    menuGameOver.rect.h = 50;
    menuGameOver.rect.w = 130;
    menuGameOver.rect.y = 475;
    menuGameOver.rect.x = 340;
    menuGameOver.texture1 = SDL_CreateTextureFromSurface(renderer, surface_menu);
    menuGameOver.texture2 = SDL_CreateTextureFromSurface(renderer, surface_menu2);
    menuGameOver.cor = 0;

    // Excluir surfaces
    SDL_FreeSurface(surface_menu);
    SDL_FreeSurface(surface_menu2);
    SDL_FreeSurface(surface_background);   
    SDL_FreeSurface(surface_informacao);
    SDL_FreeSurface(textoPontuacaoSurface);
    return 1;
}

// Pontuação
int OnInitScore()
{
    // Inicializar surfaces
    SDL_Surface *surface_menu = SDL_LoadBMP("Imagens/menu1.bmp");
    if (surface_menu == NULL)
    {
        SDL_Log("Imagem do botão não encontrado na tela de pontuações\n");
        return -1;
    }
    SDL_Surface *surface_menu2 = SDL_LoadBMP("Imagens/menu2.bmp");
    if (surface_menu2 == NULL)
    {
        SDL_Log("Imagem do botão 2 não encontrado na tela de pontuações\n");
        return -1;
    }

    // Botao
    menuScore.rect.h = 50;
    menuScore.rect.w = 130;
    menuScore.rect.y = 450;
    menuScore.rect.x = 340;
    menuScore.cor = 0;
    menuScore.texture2 = SDL_CreateTextureFromSurface(renderer, surface_menu);
    menuScore.texture1 = SDL_CreateTextureFromSurface(renderer, surface_menu2);
    
    // Texto
    pontuacao_inf.rect.w = 480;
    pontuacao_inf.rect.h = 40;
    pontuacao_inf.rect.x = 162;
    pontuacao_inf.rect.y = 160;
    pontuacao_inf.colorText.r = 0;
    pontuacao_inf.colorText.g = 0;
    pontuacao_inf.colorText.b = 0;
    pontuacao_inf.colorText.a = 255;
    
    // Obter pontucao
    player = readFile(&len_score);

    // Ordenar lista
    if (player != NULL)
    {
        PLAYER aux;
        int j;
        for (int i = 1; i < len_score; i++)
        {
            aux = player[i];
            for (j = i-1; j > -1; j--)
            {
               if (player[j].pontuacao < aux.pontuacao)
               {
                   player[j+1] = player[j];
               }
               else
               {
                    break;
               }
            }
            player[j+1] = aux;
        }
        
        if (len_score > 6)
        {
            menuScore.rect.y = 530;
            pontuacao_inf.rect.y = 80;
        }

        if (len_score > 10)
        {
            len_score = 10;
        }
    }
    else
    {
        SDL_Log("Não existe lista d pontuação\n");
        len_score = 0;
    }

    // Excluir Surfaces
    SDL_FreeSurface(surface_menu);   
    SDL_FreeSurface(surface_menu2);
    return 1; 
}

// Inicilizar componentes
int OnInit()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        SDL_Log("Não foi possível inicializar sdl\n");
        return -1;
    }

    // Tela
    window = SDL_CreateWindow("Fire Against the Rain", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    screen = SDL_GetWindowSurface(window);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Carrega Imagens
    SDL_Surface *surface_square = SDL_LoadBMP("Imagens/player.bmp");
    if (surface_square == NULL)
    {
        SDL_Log("Imagem do jogador nao encontrada\n");
        return -1;
    }
    SDL_Surface *surface_ball = SDL_LoadBMP("Imagens/raindrop.bmp");
    if (surface_ball == NULL)
    {
        SDL_Log("Imagem da chuva nao encontrada\n");
        return -1;
    }
    SDL_Surface *surface_screen = SDL_LoadBMP("Imagens/background.bmp");
    if (surface_screen == NULL)
    {
        SDL_Log("Imagem de fundo nao encontrada\n");
        return -1;
    }
    SDL_Surface *surface_cloud = SDL_LoadBMP("Imagens/nuvem.bmp");
    if (surface_cloud == NULL)
    {
        SDL_Log("Imagem da nuvem nao encontrada\n");
        return -1;
    }
    SDL_Surface *surface_life = SDL_LoadBMP("Imagens/heart.bmp");
    if (surface_life == NULL)
    {
        SDL_Log("Imagem da vida nao encontrada\n");
        return -1;
    }
    SDL_Surface *surface_ice = SDL_LoadBMP("Imagens/gelo.bmp");
    if (surface_ice == NULL)
    {
        SDL_Log("Imagem do gelo não encontrado\n");
        return -1;
    }
    SDL_Surface *surface_poison = SDL_LoadBMP("Imagens/poison.bmp");
    if (surface_poison == NULL)
    {
        SDL_Log("Imagem do veneno nao encontrada\n");
        return -1;
    }
    SDL_Surface *surface_heart = SDL_LoadBMP("Imagens/life.bmp");
    if (surface_heart == NULL)
    {
        SDL_Log("Imagem do coração nao encontrada\n");
        return -1;
    }
    SDL_Surface *surface_star = SDL_LoadBMP("Imagens/starcoin.bmp");
    if (surface_star == NULL)
    {
        SDL_Log("Imagem da estrela não encontrado\n");
        return -1;
    }
    SDL_Surface *surface_title = SDL_LoadBMP("Imagens/title.bmp");
    if (surface_title == NULL)
    {
        SDL_Log("Imagem do inicio não encontrado\n");
        return -1;
    }
    SDL_Surface *surface_menu = SDL_LoadBMP("Imagens/iniciar1.bmp");
    if (surface_menu == NULL)
    {
        SDL_Log("Imagem do menu não encontrado\n");
        return -1;
    }
    SDL_Surface *surface_menu2 = SDL_LoadBMP("Imagens/iniciar2.bmp");
    if (surface_menu2 == NULL)
    {
        SDL_Log("Image do menu 2 não encontrado\n");
        return -1;
    }
    SDL_Surface *surface_exit = SDL_LoadBMP("Imagens/exit.bmp");
    if (surface_exit == NULL)
    {
        SDL_Log("Imagem de sair não encontrado\n");
        return -1;
    }
    SDL_Surface *surface_instrucoes1 = SDL_LoadBMP("Imagens/instrucoes1.bmp");
    if (surface_instrucoes1 == NULL)
    {
        SDL_Log("Imagem do botao de instrucoes não foi encontrado\n");
        return -1;
    }
    SDL_Surface *surface_instrucoes2 = SDL_LoadBMP("Imagens/instrucoes2.bmp");
    if (surface_instrucoes2 == NULL)
    {
        SDL_Log("Imagem do botão de instrucoes 2 não foi encontado");
        return -1;
    }
    SDL_Surface *surface_pontuacao1 = SDL_LoadBMP("Imagens/pontuacao1.bmp");
    if (surface_pontuacao1 == NULL)
    {
        SDL_Log("IMagem do botão de pontuação não foi encontrado");
        return -1;
    }
    SDL_Surface *surface_pontuacao2 =  SDL_LoadBMP("Imagens/pontuacao2.bmp");
    if (surface_pontuacao2 == NULL)
    {
        SDL_Log("Imagem do botão de pontuação 2 não foi encontrado");
        return -1;
    }
    int i, sort;

     // Texto
    if (TTF_Init())
    {
        SDL_Log("Erro no ttf_init");
        return -1;
    }
    text.font = TTF_OpenFont("Font/Lobster-Regular.ttf", 90);
    if (!text.font)
    {
        SDL_Log("Erro na fonte: %s", TTF_GetError());
        return -1;
    }

    // Tamanho do texto
    text.rect.w = 20;
    text.rect.h = 30;
    text.rect.x = 760;
    text.rect.y = 65;
    pontuacao.rect.w = 160;
    pontuacao.rect.h = 50;
    pontuacao.rect.x = 590;
    pontuacao.rect.y = 50;

    //Cor do texto
    text.colorText.r = 0;
    text.colorText.g = 0;
    text.colorText.b = 0;
    text.colorText.a = 255;
    pontuacao.colorText.r = 0;
    pontuacao.colorText.g = 0;
    pontuacao.colorText.b = 0;
    pontuacao.colorText.a = 255;

    //Texto da pontuacao
    SDL_Surface *textoPontuacaoSurface = TTF_RenderUTF8_Blended(text.font, "Pontuação: ", pontuacao.colorText);
    pontuacao.texture = SDL_CreateTextureFromSurface(renderer, textoPontuacaoSurface);

    //Inicializacao das nuvens
    int c[10] = {0, 50, 100, 200, 350, 500, 520, 690, 490, 777};

    // Nuvem
    for (i = 0; i < 18; i++)
    {
        clouds[i].rect.w = 192;
        clouds[i].rect.h = 86;
        clouds[i].rect.x = c[i];
        clouds[i].rect.y = 0;
        if(i % 2 == 0)
            clouds[i].vel.x = rand() % 3 + 1;
        else
            clouds[i].vel.x = -1 * (rand() % 3 + 1);
        clouds[i].vel.y = 0;
        clouds[i].texture = SDL_CreateTextureFromSurface(renderer, surface_cloud);
    }
    
    for (i = 0; i < 18; i++)
    {
        ball[i].rect.w = 15;
        ball[i].rect.h = 15;
        sort = rand() % 10 + 1;
        ball[i].rect.x = rand() % 192 + clouds[sort].rect.x;
        ball[i].rect.y = rand() % 20 + 1;
        ball[i].vel.x = 0;
        ball[i].vel.y = rand() % 3 + 1;
        ball[i].texture = SDL_CreateTextureFromSurface(renderer, surface_ball);
    }
    rain_moviment = 1;

    // Menu
    texture_title = SDL_CreateTextureFromSurface(renderer, surface_title);
    rect_title.h = 400;
    rect_title.w = 600;
    rect_title.x = 100;
    rect_title.y = 100;

    /// Botoes menu
    for(i = 0; i < 3; i++)
    {
        menu[i].rect.h = 50;
        menu[i].rect.w = 130;
        menu[i].rect.y = 450;
        menu[i].cor = 0;
    }
    menu[0].rect.x = 180;
    menu[0].texture2 = SDL_CreateTextureFromSurface(renderer, surface_menu);
    menu[0].texture1 = SDL_CreateTextureFromSurface(renderer, surface_menu2);
    menu[1].rect.x = 340;
    menu[1].texture2 = SDL_CreateTextureFromSurface(renderer, surface_instrucoes1);
    menu[1].texture1 = SDL_CreateTextureFromSurface(renderer, surface_instrucoes2);
    menu[2].rect.x = 500;
    menu[2].texture2 = SDL_CreateTextureFromSurface(renderer, surface_pontuacao1);
    menu[2].texture1 = SDL_CreateTextureFromSurface(renderer, surface_pontuacao2);

    // Botao de sair
    sair.rect.h = 40;
    sair.rect.w = 40;
    sair.rect.y = 20;
    sair.rect.x = SCREEN_WIDTH - 70;
    sair.texture = SDL_CreateTextureFromSurface(renderer, surface_exit);
    
    // Fundo
    texture_screen = SDL_CreateTextureFromSurface(renderer, surface_screen);
    
    // Personagem
    square.vel.x = 2;
    square.vel.y = 0;
    square.rect.w = 70;
    square.rect.h = 70;
    square.rect.x = 300;
    square.rect.y = 500;
    square_moviment = 1;
    square.texture = SDL_CreateTextureFromSurface(renderer, surface_square);
    
    // Vida
    for(i = 0; i < 3; i++)
    {
        life[i].rect.w = 60;
        life[i].rect.h = 60;
        life[i].rect.y = 5;
        life[i].rect.x = SCREEN_WIDTH-55-(45 * i);
        life[i].texture = SDL_CreateTextureFromSurface(renderer, surface_life);
    }

    //Gelo
    ice.rect.h = 50;
    ice.rect.w = 50;
    ice.rect.y = 20;
    ice.vel.x = 0;
    ice.texture = SDL_CreateTextureFromSurface(renderer, surface_ice);
    ice_moviment = 0;

    // Pocao de diminuir velocidade
    poison.rect.h = 60;
    poison.rect.w = 60;
    poison.rect.y = 20;
    poison.vel.x = 0;
    poison.texture = SDL_CreateTextureFromSurface(renderer, surface_poison);
    poison_moviment = 0;
    
    // Vida
    vida.rect.h = 50;
    vida.rect.w = 50;
    vida.rect.y = 500;
    vida.texture = SDL_CreateTextureFromSurface(renderer, surface_heart);
    vida.frame = 0;
    vida.visible = 0;
    
    // Star
    star.SCREENrect.w = 62;
    star.SCREENrect.h = 63;
    star.SCREENrect.y = 10;
    star.IMGrect.w = 62;
    star.IMGrect.h = 63;
    star.IMGrect.y = 0;
    star.vel.x = 1;
    star.vel.y = 1;
    SDL_SetColorKey(surface_star, 1, SDL_MapRGB(surface_star->format, 255, 255, 255));
    star.texture = SDL_CreateTextureFromSurface(renderer, surface_star);
    star.star_moviment = 0;
    star.frames = 0;

    // Excluir surface
    SDL_FreeSurface(surface_ice);
    SDL_FreeSurface(surface_ball);
    SDL_FreeSurface(surface_exit);
    SDL_FreeSurface(surface_life);
    SDL_FreeSurface(surface_star);
    SDL_FreeSurface(surface_menu);
    SDL_FreeSurface(surface_title);
    SDL_FreeSurface(surface_heart);
    SDL_FreeSurface(surface_cloud);
    SDL_FreeSurface(surface_menu2);
    SDL_FreeSurface(surface_poison);
    SDL_FreeSurface(surface_square);
    SDL_FreeSurface(surface_screen);
    SDL_FreeSurface(surface_instrucoes1);
    SDL_FreeSurface(surface_instrucoes2);
    SDL_FreeSurface(surface_pontuacao1);
    SDL_FreeSurface(surface_pontuacao2);
    SDL_FreeSurface(textoPontuacaoSurface);

    // Verifica se inicializo a tela
    if (screen == NULL)
    {
        SDL_Log("Não foi possível inicilizar tela\n");
        return -1;
    }

    on_run = 1;
    on_game = 1;
    return 0;
}
