#include <stdio.h>
/**/
int  ConvToPos(int nums[], int len)
{
    int count = 0;

    for (size_t i = 0; i < len; i++)
    {
        if (nums[i] < 0)
        {
            nums[i] = -nums[i];
            ++count;
        }
    }

    return count;
}

/**/