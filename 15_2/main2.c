#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define m22ramatus 4
#define FLAG_COUNT 3

int main(int argc, char **argv)
{
	float fpkmph = 5.0;
	float maxFine = 300.0;
	int yldmenetlusePiir = 50;
	int finePiir = 3;

	FILE *kiirused = fopen("14_2_speeds.txt", "r");
	if (kiirused == NULL)
		return 1;
	FILE *trahvid = fopen("trahvid", "w");
	if (trahvid == NULL)
		return 1;
	FILE *menetlused = fopen("menetlused", "w");
	if (menetlused == NULL)
		return 1;
	FILE *flags = fopen(".flags", "w");
	if (flags == NULL)
		return 1;

	while (fscanf(flags, "%s", flagname) == 3)
	{
		if (strcmp(flagname, "-t")==0) {
			fscanf(flags, "")
		};
		if (diff >= yldmenetlusePiir)
		{
			fprintf(menetlused, "%s\nPiirkiirus: %d\nM66detud kiirus: %d\nYletus: %d\n\n",
							reg, piir, moot, diff);
		}
		else if (diff >= finePiir)
		{
			fprintf(trahvid, "%s %d km/h %.2f EUR\n",
							reg, diff, (float)(diff)*fpkmph <= maxFine ? (float)(diff)*fpkmph : maxFine);
		}
	}

	for (int i = 1; i < argc; i++)
	{
		printf("%s\n", argv[i]);
		printf("%s\n", argv[i+1]);
		if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
		{
			fpkmph = atof(argv[++i]);
			fprintf(flags, "%f\n", fpkmph);
		}
		else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc)
		{
			maxFine = atof(argv[++i]);
			fprintf(flags, "%f\n", maxFine);
		}
		else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc)
		{
			yldmenetlusePiir = atoi(argv[++i]);
			fprintf(flags, "%d\n", yldmenetlusePiir);
		}
		else
		{
			printf("Usage:\n");
			printf("Options:\n");
			printf("\t-f <fine per km/h>       Set fine per km/h (default: 5)\n");
			printf("\t-m <max trahv>           Set maximum fine (default: 300)\n");
			printf("\t-t <Yldmenetluse piir>   (default: 50)\n");

			return 0;
		}
	}

	char *reg = calloc(100, sizeof(char));
	int moot;
	int piir;
	while (fscanf(kiirused, "%s %d %d", reg, &moot, &piir) == 3)
	{
		int diff = moot - piir - m22ramatus;
		if (diff >= yldmenetlusePiir)
		{
			fprintf(menetlused, "%s\nPiirkiirus: %d\nM66detud kiirus: %d\nYletus: %d\n\n",
							reg, piir, moot, diff);
		}
		else if (diff >= finePiir)
		{
			fprintf(trahvid, "%s %d km/h %.2f EUR\n",
							reg, diff, (float)(diff)*fpkmph <= maxFine ? (float)(diff)*fpkmph : maxFine);
		}
	}

	fclose(kiirused);
	fclose(trahvid);
	fclose(menetlused);

	return 0;
}
