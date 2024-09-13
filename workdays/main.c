#include <stdio.h>
#include "../input.c"

int main()
{
  const int juuni_keskmine_bruutopalk = 2113;

  int tp_algus = input_i("toopaeva algus: "); // I allow starting on previous days so -value
  if (tp_algus < 0)
  {
    printf("Ärgem alusta eile oma tööga\n");
    return 1;
  }

  int tp_lopp = input_i("toopaeva lopp: ");
  if (tp_lopp <= tp_algus)
  {
    printf("Ei saa toopaeva lopetada enne kui toopaev on alanud\n");
    return 1;
  }
  int tp_arv = input_i("toopaevade arv kalendrikuus: ");
  if (tp_arv < 1)
  {
    printf("Voiks moned paevad tool ka kaia\n");
    return 1;
  }
  int tunnipalk = input_i("sinu tunnipalk: ");
  if (tunnipalk <= 0)
  {
    printf("Kas see on heategevus?\n");
    return 1;
  }

  int tootunnid_paevas = tp_lopp - tp_algus;

  int paevapalk = tootunnid_paevas * tunnipalk;

  int nadalapalk = paevapalk * 7; // E-P

  int kuupalk = paevapalk * tp_arv;

  printf("Kuupalk: %d\n", kuupalk);
  printf("Nadalapalk: %d\n", nadalapalk);

  int erinevus = juuni_keskmine_bruutopalk - kuupalk;

  if (erinevus > 0)
  {
    printf("Sinu palk on %d eurot alla keskmise!\n", erinevus);
  }
  else if (erinevus < 0)
  {
    printf("Sinu palk on %d eurot ule keskmise!\n", -erinevus);
  }
  else
  {
    printf("Sinu palk on sama juuni keskmise bruutopalgaga!\n");
  }

  return 0;
}