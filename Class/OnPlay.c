int initializePlay()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4046))
    {
        SDL_Log("Não foi possível inicializar o som");
        return -1;
    }
    // Carregando musica
    musica = Mix_LoadWAV("Music/musica.wav");
    if (musica == NULL)
    {
        SDL_Log("Não foi possível encontrar arquivo .wav");
        return -1;
    }
    Mix_VolumeChunk(musica, 50);
    Mix_PlayChannel(5, musica, -1);
    Mix_FadeInChannel(5, musica, -1, 10);
}

void closePlay()
{
    Mix_CloseAudio();
    Mix_FreeChunk(musica);
}