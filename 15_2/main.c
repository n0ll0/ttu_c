#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINE_LENGTH 100
#define MEASUREMENT_UNCERTAINTY 4

// Seadistatavad vaikesätted
int fine_per_kmh = 5;
int max_fine = 300;
int general_proceeding_threshold = 50;

// Trahvi arvutamise funktsioon
int calculate_fine(int speed, int limit)
{
  int excess_speed = speed - limit;

  // Kui kiirus on alla menetluskünnise, pole trahvi vaja
  if (excess_speed < 3)
  {
    return 0;
  }

  // Trahvi arvutamine
  int fine = excess_speed * fine_per_kmh;
  return fine > max_fine ? max_fine : fine;
}

void print_usage(const char *program_name)
{
  printf("Usage: %s [options]\n", program_name);
  printf("Options:\n");
  printf("  -f <fine_per_kmh>          Set fine per km/h (default: 5)\n");
  printf("  -m <max_fine>              Set maximum fine (default: 300)\n");
  printf("  -t <general_threshold>     Set general proceeding threshold (default: 50)\n");
}

int main(int argc, char *argv[])
{
  const char *input_file = "14_2_speeds.txt";
  const char *fines_file = "hoiatustrahvid.txt";
  const char *general_proceedings_file = "uldmenetluse_teated.txt";

  // Argumentide parsimine
  for (int i = 1; i < argc; i++)
  {
    if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
    {
      fine_per_kmh = atoi(argv[++i]);
    }
    else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc)
    {
      max_fine = atoi(argv[++i]);
    }
    else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc)
    {
      general_proceeding_threshold = atoi(argv[++i]);
    }
    else
    {
      print_usage(argv[0]);
      return 1;
    }
  }

  FILE *infile = fopen(input_file, "r");
  FILE *fines_out = fopen(fines_file, "w");
  FILE *general_out = fopen(general_proceedings_file, "w");

  if (!infile || !fines_out || !general_out)
  {
    fprintf(stderr, "Error opening file\n");
    return 1;
  }

  char line[MAX_LINE_LENGTH];
  while (fgets(line, sizeof(line), infile))
  {
    char reg_nr[10];
    int measured_speed, speed_limit;

    if (sscanf(line, "%s %d %d", reg_nr, &measured_speed, &speed_limit) != 3)
    {
      continue; // Jäta väärad read vahele
    }

    int adjusted_speed = measured_speed - MEASUREMENT_UNCERTAINTY;
    int excess_speed = adjusted_speed - speed_limit;

    // Kontrolli, kas alustatakse üldmenetlust
    if (excess_speed >= general_proceeding_threshold)
    {
      fprintf(general_out, "%s\n", reg_nr);
      fprintf(general_out, "Piirkiirus: %d km/h\n", speed_limit);
      fprintf(general_out, "Mõõdetud kiirus: %d km/h\n", measured_speed);
      fprintf(general_out, "Ületus: %d km/h\n\n", excess_speed);
    }
    else if (excess_speed >= 3)
    {
      // Kui tegemist pole üldmenetlusega, arvuta trahv
      int fine = calculate_fine(adjusted_speed, speed_limit);
      fprintf(fines_out, "%s %d km/h %.2f EUR\n", reg_nr, excess_speed, (double)fine);
    }
  }

  fclose(infile);
  fclose(fines_out);
  fclose(general_out);

  return 0;
}
