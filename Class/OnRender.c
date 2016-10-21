// Desenhar menu
void OnRenderMenu()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_screen, NULL, NULL);
    int i;
    for (i = 0; i < 18; i++)
    {
        SDL_RenderCopy(renderer, ball[i].texture, NULL, &ball[i].rect);
    }
    for (i = 0; i < 8; i++)
    {
        SDL_RenderCopy(renderer, clouds[i].texture, NULL, &clouds[i].rect);
    }
    // SDL_RenderCopy(renderer, square.texture, NULL, &square.rect);
    SDL_RenderCopy(renderer, texture_title, NULL, &rect_title);
    for (i = 0; i < 3; i++)
    {
        if(menu[i].cor == 0)
            SDL_RenderCopy(renderer, menu[i].texture1, NULL, &menu[i].rect);
        else
            SDL_RenderCopy(renderer, menu[i].texture2, NULL, &menu[i].rect);
    }
    SDL_RenderCopy(renderer, sair.texture, NULL, &sair.rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
}

// Intrucoes
void OnRenderInstructions()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture_screen, NULL, NULL);
    if (menuInstrucoes.cor == 0)
        SDL_RenderCopy(renderer, menuInstrucoes.texture1, NULL, &menuInstrucoes.rect);
    else
        SDL_RenderCopy(renderer, menuInstrucoes.texture2, NULL, &menuInstrucoes.rect);
    SDL_RenderCopy(renderer, informacao.texture, NULL, &informacao.rect);
    SDL_RenderPresent(renderer);
    SDL_Delay(18);
}

// Desenha game over
void OnRenderGameOver()
{
    SDL_RenderClear(renderer);
    // Fundo
    SDL_RenderCopy(renderer, texture_screen, NULL, NULL);
    int i;
    // Chuva
    for (i = 0; i < 18; i++)
    {
            SDL_RenderCopy(renderer, ball[i].texture, NULL, &ball[i].rect);
    }
    // Nuvem
    for (i = 0; i < 10; i++)
    {
        SDL_RenderCopy(renderer, clouds[i].texture, NULL, &clouds[i].rect);
    }
    SDL_RenderCopy(renderer, sair.texture, NULL, &sair.rect);
    SDL_RenderCopy(renderer, informacao_game_over.texture, NULL, &informacao_game_over.rect);
    SDL_RenderCopy(renderer, pontuacao.texture, NULL, &pontuacao.rect);
    SDL_RenderCopy(renderer, game_over_pontuacao_total.texture, NULL, &game_over_pontuacao_total.rect);
    SDL_RenderCopy(renderer, game_over_pontuacao.texture, NULL, &game_over_pontuacao.rect);
    SDL_RenderCopy(renderer, game_over_tempo.texture, NULL, &game_over_tempo.rect);
    SDL_RenderCopy(renderer, game_over_tempo_total.texture, NULL, &game_over_tempo_total.rect);
    if (menuGameOver.cor == 0)
    {
        SDL_RenderCopy(renderer, menuGameOver.texture1, NULL, &menuGameOver.rect);
    }
    else
    {
        SDL_RenderCopy(renderer, menuGameOver.texture2, NULL, &menuGameOver.rect);
    }
    SDL_RenderPresent(renderer);
    SDL_Delay(18);
}

// Pontuação
void OnRenderScore()
{
    SDL_RenderClear(renderer);
    
    // Fundo
    SDL_RenderCopy(renderer, texture_screen, NULL, NULL);
    
    // Botao
    if (menuScore.cor == 0)
    {
        SDL_RenderCopy(renderer, menuScore.texture1, NULL, &menuScore.rect);
    }
    else
    {
        SDL_RenderCopy(renderer, menuScore.texture2, NULL, &menuScore.rect);
    }

    // Texto
    if (len_score > 0)
    {
        for (int i = 0; i < len_score; ++i)
        {
            char texto[50];
            sprintf(texto, "Pontuação: %d     Tempo: %d     Data: %d / %d / %d", player[i].pontuacao, player[i].tempo, player[i].data.tm_mday, 
                             player[i].data.tm_mon, player[i].data.tm_year + 1900);
            pontuacao_inf.textSurface = TTF_RenderUTF8_Blended(text.font, texto, pontuacao_inf.colorText);
            pontuacao_inf.texture = SDL_CreateTextureFromSurface(renderer, pontuacao_inf.textSurface);
            SDL_RenderCopy(renderer, pontuacao_inf.texture, NULL, &pontuacao_inf.rect);
            SDL_FreeSurface(pontuacao_inf.textSurface);
            SDL_DestroyTexture(pontuacao_inf.texture);
            pontuacao_inf.rect.y += 45;
        }
        if (len_score > 6)
            pontuacao_inf.rect.y = 80;
        else
            pontuacao_inf.rect.y = 160;
    }
    else
    {
        char texto[50] = { "Não há histórico de partidas." };
        pontuacao_inf.textSurface = TTF_RenderUTF8_Blended(text.font, texto, pontuacao_inf.colorText);
        pontuacao_inf.texture = SDL_CreateTextureFromSurface(renderer, pontuacao_inf.textSurface);
        SDL_RenderCopy(renderer, pontuacao_inf.texture, NULL, &pontuacao_inf.rect);
        SDL_FreeSurface(pontuacao_inf.textSurface);
        SDL_DestroyTexture(pontuacao_inf.texture);
    }
    
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
}

// Desenhar jogo
void OnRender()
{
    SDL_RenderClear(renderer);
    // Fundo
    SDL_RenderCopy(renderer, texture_screen, NULL, NULL);
    int i;
    
    // Chuva
    for(i = 0; i < 18; i++)
    {
        SDL_RenderCopy(renderer, ball[i].texture, NULL, &ball[i].rect);
    }
    
    // Gelo
    if (ice_moviment == 1)
    {
        SDL_RenderCopy(renderer, ice.texture, NULL, &ice.rect);
    }
    
    // Pocao
    if (poison_moviment == 1)
    {
        SDL_RenderCopy(renderer, poison.texture, NULL, &poison.rect);
    }
    
    // Coracao
    if (vida.visible == 1)
    {
        SDL_RenderCopy(renderer, vida.texture, NULL, &vida.rect);
    }
    
    // Estrela
    if (star.star_moviment == 1)
    {
		SDL_RenderCopy(renderer, star.texture, &star.IMGrect, &star.SCREENrect);
	}
    
    // Nuvem
    for(i = 0; i < 10; i++)
    {
        SDL_RenderCopy(renderer, clouds[i].texture, NULL, &clouds[i].rect);
    }
    
    // Vida
    for(i = 0; i < 3; i++)
    {
		SDL_RenderCopy(renderer, life[i].texture, NULL, &life[i].rect);
	}
    
    // Personagem
    SDL_RenderCopy(renderer, square.texture, NULL, &square.rect);
    
    // Pontuacao
    sprintf(tempoChar, "%d", tempo/100);
    text.textSurface = TTF_RenderUTF8_Blended(text.font, tempoChar, text.colorText);
    text.texture = SDL_CreateTextureFromSurface(renderer, text.textSurface);
    tempo++;
    SDL_RenderCopy(renderer, text.texture, NULL, &text.rect);
    
    // Texto
    SDL_RenderCopy(renderer, pontuacao.texture, NULL, &pontuacao.rect);
    SDL_FreeSurface(text.textSurface);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
}