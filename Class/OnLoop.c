// Loop do menu
void OnLoopMenu()
{
    int i, sort;
    
    // Atualiza da posicao da chuva
    for(i = 0; i < 10; i++)
    {
        if (clouds[i].rect.x < -200 || clouds[i].rect.x - clouds[i].rect.w >= SCREEN_WIDTH)
        {
            if (clouds[i].vel.x > 0)
                clouds[i].vel.x = -(rand() % 3 + 1);
            else
                clouds[i].vel.x = rand() % 3 + 1;
        }
        clouds[i].rect.x += clouds[i].vel.x;
    }

    // Atualiza a posicao da chuva
    for(i = 0; i < 30; i++)
    {
        if (ball[i].rect.y > SCREEN_HEIGHT)
        {
            sort = rand() % 6 + 1;
            ball[i].rect.x = rand() % 192 + clouds[sort].rect.x;
            ball[i].rect.y = 40;
            ball[i].vel.y = rand() % 3 + 1;
        }
        ball[i].rect.y += ball[i].vel.y;
    }
}

// Loop do Jogo
void OnLoop()
{
    int i, sort;
    // Frame geral
    frames++;
    poison.frame++;
    star.frames++;
    
    // Verifica se pode soltar gelo
    if (frames == 300 && ice_moviment == 0)
    {
        ice_moviment = 1;
        ice.vel.y = rand() % 3 + 1;
        sort = rand() % 10;
        ice.rect.x = rand() % 192 + clouds[sort].rect.x;
    }
	
    // Verifica se pode movimentar estrela
	if (star.frames == 800)
	{
		star.star_moviment = 1;
		star.SCREENrect.x = rand() % SCREEN_WIDTH;
	}
	
    // Verifica se pode atualizar a chuva depois de pegar a estrela
	if (star.frames == 300 && rain_moviment == 0)
	{
		rain_moviment = 1;
	}
    
    // Verifica se pode soltar pocao de diminuir velocidade
    if (poison.frame == 600 && poison_moviment == 0)
    {
        poison_moviment = 1;
        sort = rand() % 6;
        poison.vel.y = rand() % 2 + 1;
        poison.rect.x = rand() % 192 + clouds[sort].rect.x;
    }
    
    // Se perder uma vida ela começa a aparecer
    if (lifes < 2)
    {
        vida.frame++;
        // Verifica se pode mostrar vida
        if (vida.frame == 300 && vida.visible == 0)
        {
            vida.visible = 1;
            vida.rect.x = rand() % SCREEN_WIDTH;
        }
    }

    // Atualiza posicao da nuvem
    if (rain_moviment == 1)
    {
		for(i = 0; i < 10; i++)
		{
			if (clouds[i].rect.x < -200 || clouds[i].rect.x >= SCREEN_WIDTH)
			{
				if (clouds[i].vel.x > 0)
					clouds[i].vel.x = -(rand() % 3 + 1);
				else
					clouds[i].vel.x = rand() % 3 + 1;
			}
			clouds[i].rect.x += clouds[i].vel.x;
		}
        
        // Nuvens
        int c[10] = { 0 };
        // Quantidade de gotas por chuvas
        int qtn = 5;

		for(i = 0; i < 18; i++)
		{
            if (ball[i].rect.y > SCREEN_HEIGHT)
            {
                ball[i].rect.y = 20;
                ball[i].vel.y = rand() % 3 + 1;
                if (i >= 15)
                {   
                    ball[i].rect.x = square.rect.x;
                }
                else
                {
                    sort = rand() % 9 + 1;
                    while (c[sort] > qtn)
                    {
                        sort = rand() % 9 + 1;
                    } 
                    c[sort] += 1;
                    ball[i].rect.x = rand() % 192 + clouds[sort].rect.x;
                }
			}
			ball[i].rect.y += ball[i].vel.y;
		}
	}
    
    // Atualiza posicao do gelo
    if (ice_moviment == 1)
    {
        ice.rect.y += ice.vel.y;
        if (ice.rect.y >= SCREEN_HEIGHT)
        {
            ice_moviment = 0;
            ice.rect.y = 20;
            frames = 0;
        }
        else
        {
            coliderIceSquare();
        }
    }
    
    // Atualiza posicao da pocao
    if (poison_moviment == 1)
    {
        poison.rect.y += poison.vel.y;
        if (poison.rect.y >= SCREEN_HEIGHT + poison.rect.h)
        {
            poison_moviment = 0;
            poison.rect.y = 20;
            poison.frame= 0;
        }
        else
        {
            coliderPoisonSquare();
        }
    }
    
    // Atualiza vida
    if (vida.visible == 1)
    {
        coliderHeartSquare();
        if (vida.frame == 600 && vida.visible == 1)
        {
            vida.frame = 0;
            vida.visible = 0;
        }
    }
    
    // Atualiza posição da estrela
    if (star.star_moviment == 1)
    {
		star.SCREENrect.y += star.vel.y;
        star.ticks = SDL_GetTicks(); //conta em ms desde que o jogo comecou
        star.seconds = star.ticks/100; //Divide para que nao fique tao rapido
        star.sprite = star.seconds % 8; //8 sprites
        star.IMGrect.x = star.sprite * 64; //+- 64 pixels cada sprite

        if (star.SCREENrect.y > SCREEN_HEIGHT + star.SCREENrect.h)
		{
			star.star_moviment = 0;
			star.SCREENrect.y = 10;
			star.frames = 0;
		}
        coliderStarSquare();
	}
    
    // Altera velocidade do jogador
    if (square_moviment == 0 && frames > 180)
    {
        square_moviment = 1;
    }
    else if (square.vel.x == 1 && poison.frame > 600)
    {
        square.vel.x = 2;
        poison.frame = 0;
    }
    
    // Verifica se colidiu
    coliderRainSquare();
}

// Loop do game over
void OnLoopGameOver()
{
    int i, sort;
    
    // Atualiza da posicao da nuvem
    for(i = 0; i < 10; i++)
    {
        if (clouds[i].rect.x < -200 || clouds[i].rect.x - clouds[i].rect.w >= SCREEN_WIDTH)
        {
            if (clouds[i].vel.x > 0)
                clouds[i].vel.x = -(rand() % 3 + 1);
            else
                clouds[i].vel.x = rand() % 3 + 1;
        }
        clouds[i].rect.x += clouds[i].vel.x;
    }
    
    // Atualiza a posicao da chuva
    for(i = 0; i < 18; i++)
    {
        if (ball[i].rect.y > SCREEN_HEIGHT)
        {
            sort = rand() % 6 + 1;
            ball[i].rect.x = rand() % 192 + clouds[sort].rect.x;
            ball[i].rect.y = 40;
            ball[i].vel.y = rand() % 3 + 1;
        }
        ball[i].rect.y += ball[i].vel.y;
    }   
}