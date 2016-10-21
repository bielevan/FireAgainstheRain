// Eventos do menu
void OnEventMenu(SDL_Event *event)
{
    switch(event->type)
    {
    case SDL_QUIT:
        on_game = 0;
        on_run = 6;
        break;
    case SDL_MOUSEBUTTONDOWN:
        coliderMouseMenuClick(event);
        coliderMouseExit(event);
        break;
    case SDL_MOUSEMOTION:
        coliderMouseMenu(event);
        break;
    }
}

// Eventos do Jogo
void OnEvent(SDL_Event *event)
{
    switch(event->type)
    {
    // Sair
    case SDL_QUIT:
        on_game = 0;
        on_run = 6;
        break;
    }
}

// Eventos do Game Over
void OnEventGameOver(SDL_Event *event)
{
    switch(event->type)
    {
        case SDL_QUIT:
            on_game = 0;
            on_run = 6;
            break;
        case SDL_MOUSEBUTTONDOWN:
            coliderMouseMenuClickGameOver(event);
            coliderMouseExit(event);
        break;
        case SDL_MOUSEMOTION:
            coliderMouseMenuGameOver(event);
        break;
    }
}

// Eventos da tela de instrucoes
void OnEventInstructions(SDL_Event *event)
{
    switch(event->type)
    {
        case SDL_QUIT:
            on_game = 0;
            on_run = 6;
            break;
        case SDL_MOUSEBUTTONDOWN:
            coliderMouseInstructions(event);
        break;
        case SDL_MOUSEMOTION:
            motionMouseInstructions(event);
        break;
    }
}

// Eventos da tela de pontuação
void OnEventScore(SDL_Event *event)
{
    switch(event->type)
    {
    case SDL_QUIT:
        on_run = 6;
        on_game = 0;
        break;
    case SDL_MOUSEBUTTONDOWN:
        coliderMouseScore(event);
        break;
    case SDL_MOUSEMOTION:
        motionMouseScore(event);
        break;
    }
}
