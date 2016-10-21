// Exclui componentes do jogo
void OnCleanup()
{
    // Exclui surfaces
    int i = 0;
    for (i = 0; i < 18; i++)
    {
        SDL_DestroyTexture(ball[i].texture);
    }
    for (i = 0; i < 10; i++)
    {
        SDL_DestroyTexture(clouds[i].texture);
    }
    for (i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(life[i].texture);
    }
     for (i = 0; i < 3; i++)
    {
        SDL_DestroyTexture(menu[i].texture1);
        SDL_DestroyTexture(menu[i].texture2);
    }
    
    // Excluir componentes da tela
    SDL_DestroyTexture(ice.texture);
    SDL_DestroyTexture(sair.texture);
    SDL_DestroyTexture(star.texture);
    SDL_DestroyTexture(vida.texture);
    SDL_DestroyTexture(text.texture);
    SDL_DestroyTexture(texture_title);
    SDL_DestroyTexture(poison.texture);
    SDL_DestroyTexture(texture_screen);
    SDL_DestroyTexture(square.texture);
    SDL_DestroyTexture(pontuacao.texture);
    SDL_DestroyTexture(informacao_game_over.texture);

    // Excluir Fonte
    TTF_CloseFont(text.font);
    TTF_Quit();
    
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Excluir Componentes do Game Over
void OnGameOverCleanup()
{
    SDL_DestroyTexture(texture_screen);
    SDL_DestroyTexture(pontuacao.texture);
    SDL_DestroyTexture(menuGameOver.texture1);
    SDL_DestroyTexture(menuGameOver.texture2);
    SDL_DestroyTexture(game_over_pontuacao.texture);
    SDL_DestroyTexture(informacao_game_over.texture);   
    SDL_DestroyTexture(game_over_tempo_total.texture);
    SDL_DestroyTexture(game_over_pontuacao_total.texture);
}

// Excluir Componentes da tela de Instrucoes
void OnInstructionsCleanup()
{
    SDL_DestroyTexture(informacao.texture);
    SDL_DestroyTexture(menuInstrucoes.texture1);
    SDL_DestroyTexture(menuInstrucoes.texture2);
}

// Excluir componentes da tela de põntuações
void OnCleanupScore()
{
    if (player != NULL)
        free(player);
    SDL_DestroyTexture(menuScore.texture1);
    SDL_DestroyTexture(menuScore.texture2);
}