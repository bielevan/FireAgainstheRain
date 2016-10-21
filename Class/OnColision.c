// Detecta colisao botao intrucoes
void coliderMouseInstructions(SDL_Event *event)
{
    SDL_Point point;
    point.x = menuInstrucoes.rect.x;
    point.y = menuInstrucoes.rect.y;
    if (SDL_EnclosePoints(&point, 1, &menuInstrucoes.rect, NULL))
    {
        on_run = 1;
    }
}

// Detecta se o mouse passou no botao do menu
void motionMouseInstructions(SDL_Event *event)
{
    SDL_Point point;
    point.x = event->motion.x;
    point.y = event->motion.y;
    if (SDL_EnclosePoints(&point, 1, &menuInstrucoes.rect, NULL))
        menuInstrucoes.cor = 1;
    else
        menuInstrucoes.cor = 0;
}

// Detecta colisao botao intrucoes
void coliderMouseScore(SDL_Event *event)
{
    SDL_Point point;
    point.x = menuScore.rect.x;
    point.y = menuScore.rect.y;
    if (SDL_EnclosePoints(&point, 1, &menuScore.rect, NULL))
    {
        on_run = 1;
    }
}

// Detecta se o mouse passou no botao do menu
void motionMouseScore(SDL_Event *event)
{
    SDL_Point point;
    point.x = event->motion.x;
    point.y = event->motion.y;
    if (SDL_EnclosePoints(&point, 1, &menuScore.rect, NULL))
        menuScore.cor = 1;
    else
        menuScore.cor = 0;
}

// Detecta se o mouse passou no botao de menu
void coliderMouseMenu(SDL_Event *event)
{
    SDL_Point point;
    point.x = event->motion.x;
    point.y = event->motion.y;
    for(int i = 0; i < 3; i++)
    {
        if (SDL_EnclosePoints(&point, 1, &menu[i].rect, NULL))
            menu[i].cor = 1;
        else
            menu[i].cor = 0;
    }
}

// Botoes do menu
void coliderMouseMenuClick(SDL_Event *event)
{
    SDL_Point point;
    point.x = event->button.x;
    point.y = event->button.y;
    for (int i = 0; i < 3; i++)
    {
        if (SDL_EnclosePoints(&point, 1, &menu[i].rect, NULL))
        {
            if (i == 0)
            {
                on_run = 4;
            }
            else if (i == 1)
            {
                on_run = 2;
            }
            else
            {
                on_run = 3;
            }
        }
    }
}

// Detecta se clicou no botao de sair
void coliderMouseExit(SDL_Event *event)
{
    SDL_Point point;
    point.x = event->button.x;
    point.y = event->button.y;
    if (SDL_EnclosePoints(&point, 1, &sair.rect, NULL))
    {
        on_game = 0;
        on_run = 6;
    }
}

// Detecta colisao entre personagem e chuva
void coliderRainSquare()
{
    int i, sort;
    for(i = 0; i < 18; i++)
    {
        SDL_Point point;
        point.x = ball[i].rect.x;
        point.y = ball[i].rect.y;
        // Verifica colisao
        if (SDL_EnclosePoints(&point, 1, &square.rect, NULL))
        {
            // Redefine chuva
            sort = rand() % 10;
            ball[i].rect.x = rand() % 192 + clouds[sort].rect.x;
            ball[i].rect.y = 40;
            ball[i].vel.y = rand() % 3 + 1;

            // Retira um coracao
            if (lifes > -1)
            {
                SDL_DestroyTexture(life[lifes].texture);
                life[lifes].texture = NULL;
                SDL_Surface *surface = SDL_LoadBMP("Imagens/heart2.bmp");
                if (surface == NULL)
                {
                    SDL_Log("Não encontrou a imagem do coração");
                }
                SDL_SetColorKey(surface, 1, SDL_MapRGB(surface->format, 255, 255, 255));
                life[lifes].texture = SDL_CreateTextureFromSurface(renderer, surface);
                life[lifes].rect.h = 39;
                life[lifes].rect.w = 40;
                life[lifes].rect.y += 10;
                life[lifes].rect.x += 6;
                SDL_FreeSurface(surface);
                lifes--;
            }
            else
            {
                on_run = 5;
            }
        }
    }
}

// Detecta colisao entre personagem e gelo
void coliderIceSquare()
{
    SDL_Point point;
    point.x = ice.rect.x;
    point.y = ice.rect.y;
    if (SDL_EnclosePoints(&point, 1, &square.rect, NULL))
    {
        square_moviment = 0;
        ice_moviment = 0;
        ice.rect.y = 20;
        frames = 0;
    }
}

// Detecta colisao entre personagem e pocao para diminuir velocidade
void coliderPoisonSquare()
{
    SDL_Point point;
    point.x = poison.rect.x;
    point.y = poison.rect.y;
    if (SDL_EnclosePoints(&point, 1, &square.rect, NULL))
    {
        poison.rect.y = 20;
        square.vel.x = square.vel.x/2;
        poison.frame = 0;
        poison_moviment = 0;
    }
}

// Detecta colisao entre coracao e personagem
void coliderHeartSquare()
{
    SDL_Point point;
    point.x = vida.rect.x;
    point.y = vida.rect.y;
    if (SDL_EnclosePoints(&point, 1, &square.rect, NULL))
    {
        vida.frame = 0;
        vida.visible = 0;
        if (lifes < 2)
        {
            lifes++;
        }
        SDL_Surface *surface = SDL_LoadBMP("Imagens/heart.bmp");
        life[lifes].texture = SDL_CreateTextureFromSurface(renderer, surface);
        life[lifes].rect.w = 60;
        life[lifes].rect.h = 60;
        life[lifes].rect.y = 5;
        life[lifes].rect.x -= 6;
        SDL_FreeSurface(surface);
    }
}

// Detecta colisão entre estrela e personagem
void coliderStarSquare()
{
	SDL_Point point;
	point.x = star.SCREENrect.x;
	point.y = star.SCREENrect.y;
	if (SDL_EnclosePoints(&point, 1, &square.rect, NULL))
	{
		star.SCREENrect.y = 10;
		star.frames = 0;
		star.star_moviment = 0;
		rain_moviment = 0;
	}
}

// Detecta se o mouse passou no botao de menu
void coliderMouseMenuGameOver(SDL_Event *event)
{
    SDL_Point point;
    point.x = event->motion.x;
    point.y = event->motion.y;
    if (SDL_EnclosePoints(&point, 1, &menuGameOver.rect, NULL))
    {
        menuGameOver.cor = 1;       
    }
    else
    {
        menuGameOver.cor = 0;
    }
}

// Volta ao menu apartir da tela de game over
void coliderMouseMenuClickGameOver(SDL_Event *event)
{
    SDL_Point point;
    point.x = event->button.x;
    point.y = event->button.y;
    if (SDL_EnclosePoints(&point, 1, &menuGameOver.rect, NULL))
    {
        on_run = 1;
    }
}