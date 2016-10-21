// Laço do jogo
int OnExecute()
{
    // Verifica se conseguiu inicializar componentes do jogo
    if (OnInit() == -1)
    {
        return -1;
    }

    // Verifica se conseguiu inicializar componentes da tela de instrucoes 
    if (OnInitInstructions() == -1)
    {
        return -1;
    }

    // Verifica se conseguiu inicializar musica
    if (initializePlay() == -1)
    {
        return -1;
    }

    SDL_Event event;
    while (on_game == 1)
    {
        switch (on_run)
        {
        // Menu
        case 1:
            while(on_run == 1)
            {
                if (SDL_PollEvent(&event))
                {
                    OnEventMenu(&event);
                }
                OnLoopMenu();
                OnRenderMenu();
            }
            break;
            
        // Instrucoes
        case 2:
            // Inicializar tela de instrucoes
            while (on_run == 2)
            {
                if (SDL_PollEvent(&event))
                {
                    OnEventInstructions(&event);
                }
                OnRenderInstructions();
            }
            break;

        // Pontuação
        case 3:
            // Verifica se conseguiu inicializar componentes da tela de score
            if (OnInitScore() == -1)
            {
                return -1;
            }

            while (on_run == 3)
            {
                if (SDL_PollEvent(&event))
                {
                    OnEventScore(&event);
                }
                OnRenderScore();
            }

            // Excluir componentes
            OnCleanupScore();
            break;

        // Jogo
        case 4:
            // Reiniciar posicoes para o inicio da partida
            OnRestartPosition();
            
            // Inicio da partida
            while(on_run == 4)
            {
                if (SDL_PollEvent(&event))
                {
                    OnEvent(&event);
                }
                OnLoop();
                OnMovement();
                OnRender();
            }   
            break;
        
        // Game Over
        case 5:
             // Verifica se conseguiu inicializar componentes do gameOver     
            if (OnInitGameOver() == -1)
            {
                return -1;
            }

            // Game Over
            while(on_run == 5)
            {
                if (SDL_PollEvent(&event))
                {
                    OnEventGameOver(&event);
                }
                OnLoopGameOver();
                OnRenderGameOver();
            }

            // Exclui componentes
            OnGameOverCleanup();
            
            // Reiniciar componentes
            OnRestartScreen();
            break;
        }

    }

     // Fechar musica
    closePlay();

    // Fechar Componentes
    OnInstructionsCleanup();
    OnCleanup();
    
    return 0;
}   