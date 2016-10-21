// Salvar pontuação no arquivo
void saveFile(struct Player* player)
{
	FILE *file;
	if ((file = fopen("pontuacao.txt", "ab")) == NULL)
	{
		SDL_Log("Não foi possível abrir arquivo");
		return;
	}
	fwrite(player, sizeof(PLAYER), 1, file);
 	if (ferror(file))
	{
		SDL_Log("Erro ao salvar dados");
	}
	fclose(file);
}

// Ler pontuacao do arquivo
struct Player* readFile(int *len)
{
	FILE *file;
	if ((file = fopen("pontuacao.txt", "rb")) == NULL)
	{
		SDL_Log("Não foi possível abrir arquivo ou ainda não existe !\n");
		return NULL;
	}
	struct Player* player = (struct Player *) malloc (0);
	int cont = 0;
	while (!feof(file))
	{
		player = (struct Player *) realloc (player, (cont + 1) * sizeof(struct Player));
		if (fread(&player[cont], sizeof(PLAYER), 1, file) != 1)
			break;
		cont++;
	}
	*len = cont;
	fclose(file);
	if (cont == 0)
	{
		printf("Não existe pontuação salva !\n");
		free(player);
		return NULL;
	}
	else
	{
		return player;
	}
}