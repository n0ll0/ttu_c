#include <stdio.h>

/* Number of age groups in total */
#define GROUPS 11
/* Array position for minors group */
#define GROUP_MINOR (GROUPS - 2)
/* Array position for elders group */
#define GROUP_ELDER (GROUPS - 1)
/* Group size*/
#define GROUP_STEP 5
/* Upper bound for minors */
#define MINOR_UPPER_BOUND 17
/* Calculates lower bound for elders */
#define ELDER_LOWER_BOUND (MINOR_UPPER_BOUND + (GROUP_STEP * (GROUPS - 2)))

int validate_input(int age);
int find_age_group_index(int age);
void display_results(int ageGroups[]);

int main(void)
{
  int ageGroups[GROUPS] = {0};
  int age, idx;

  /* Infinite loop for input */
  while (1)
  {
    printf("Enter age (0 to stop): ");
    scanf("%d", &age);

    /* Check for break condition (age 0) */
    if (age == 0)
      break;

    /* Validate input */
    if (validate_input(age))
    {
      /* Determine the index */
      idx = find_age_group_index(age);

      /* Add to the age group counter */
      ageGroups[idx]++;
    }
  }

  /* Print the results */
  display_results(ageGroups);

  return 0;
}

int validate_input(int age)
{
  return age >= 0;
}

int find_age_group_index(int age)
{
  if (age <= MINOR_UPPER_BOUND)
  {
    return GROUP_MINOR;
  }
  else if (age >= ELDER_LOWER_BOUND)
  {
    return GROUP_ELDER;
  }
  else
  {
    return (age - MINOR_UPPER_BOUND - 1) / GROUP_STEP;
  }
}

void display_results(int ageGroups[])
{
  printf("Minors: %d\n", ageGroups[GROUP_MINOR]);
  for (int i = 0; i < GROUPS - 2; i++)
  {
    printf("Group %d (%d-%d): %d\n", i + 1, MINOR_UPPER_BOUND + 1 + i * GROUP_STEP, MINOR_UPPER_BOUND + (i + 1) * GROUP_STEP, ageGroups[i]);
  }
  printf("Elders: %d\n", ageGroups[GROUP_ELDER]);
}
