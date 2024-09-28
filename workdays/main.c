#include <stdio.h>
#include "../input.c"

int main()
{
  int tp_algus;
  int tp_lopp;
  int tp_arv;
  int tunnipalk;
  const int juuni_keskmine_bruutopalk = 2113;

  printf("Tööpäeva algus: ");
  scanf("%d", &tp_algus);
  if (tp_algus < 0)
  {
    printf("Ärgem alusta eile oma tööga\n");
    return 1;
  }

  printf("Tööpäeva lõpp: ");
  scanf("%d", &tp_lopp);
  if (tp_lopp <= tp_algus)
  {
    printf("Ei saa toopaeva lopetada enne kui toopaev on alanud\n");
    return 1;
  }
  printf("toopaevade arv kalendrikuus: ");
  scanf("%d", &tp_arv);
  if (tp_arv < 1)
  {
    printf("Voiks moned paevad tool ka kaia\n");
    return 1;
  }
  printf("sinu tunnipalk: ");
  scanf("%d", &tunnipalk);
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