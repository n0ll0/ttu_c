#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M22RAMATUS 4
#define FLAG_COUNT 3

#define INPUT_FILE "14_2_speeds.txt"
#define OUT_FINE "trahvid"
#define OUT_PROCEEDING "menetlused"
#define CONFIG_FILE "config.toml"

int main(int argc, char **argv)
{
	float fpkmph = 5.0;
	float maxFine = 300.0;
	float yldmenetlusePiir = 50;
	float finePiir = 3;

	FILE *kiirused = fopen(INPUT_FILE, "r");
	if (kiirused == NULL)
		return 1;
	FILE *trahvid = fopen(OUT_FINE, "w");
	if (trahvid == NULL)
		return 1;
	FILE *menetlused = fopen(OUT_PROCEEDING, "w");
	if (menetlused == NULL)
		return 1;
	FILE *config = fopen(CONFIG_FILE, "r");
	if (config == NULL)
		return 1;

	char *flagname = calloc(40, sizeof(char));
	while (fscanf(config, "%s = ", flagname) == 1)
	{
		if (strcmp(flagname, "general_proceeding_threshold")==0) {
			fscanf(config, "%f", &yldmenetlusePiir);
			continue;
		}
		if (strcmp(flagname, "fine_threshold")==0) {
			fscanf(config, "%f", &finePiir);
			continue;
		}
		if (strcmp(flagname, "max_fine")==0) {
			fscanf(config, "%f", &maxFine);
			continue;
		}
		if (strcmp(flagname, "fine_per_kmph")==0) {
			fscanf(config, "%f", &fpkmph);
			continue;
		}
	}

	fclose(config);

	char *reg = calloc(100, sizeof(char));
	float moot;
	float piir;
	while (fscanf(kiirused, "%s %f %f", reg, &moot, &piir) == 3)
	{
		float diff = moot - piir - M22RAMATUS;
		if (diff >= yldmenetlusePiir)
		{
			fprintf(menetlused, "%s\nPiirkiirus: %.0f\nM66detud kiirus: %.0f\nYletus: %.0f\n\n",
							reg, piir, moot, diff);
		}
		else if (diff >= finePiir)
		{
			fprintf(trahvid, "%s %.1f km/h %.2f EUR\n",
							reg, diff, (float)(diff)*fpkmph <= maxFine ? (float)(diff)*fpkmph : maxFine);
		}
	}

	fclose(kiirused);
	fclose(trahvid);
	fclose(menetlused);

	return 0;
}
