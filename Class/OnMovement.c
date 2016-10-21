void OnMovement()
{
    const Uint8 *keyState;
    keyState = SDL_GetKeyboardState(NULL);

    if(square_moviment == 1)
    {
        if(keyState[SDL_SCANCODE_RIGHT])
        {
            if(square.rect.x + square.rect.w <= SCREEN_WIDTH)
            {
                square.rect.x += square.vel.x;
            }
        }
        if(keyState[SDL_SCANCODE_LEFT])
        {
            if(square.rect.x >= 0)
            {
                square.rect.x -= square.vel.x;
            }
        }
    }
    else if (square_moviment == 0 && frames > 180)
    {
        square_moviment = 1;
    }
    if (square.vel.x == 1 && poison.frame > 540)
    {
        square.vel.x = 2;
        poison.frame = 0;
    }
}
