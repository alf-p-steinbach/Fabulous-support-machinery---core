//#include <cs50.h>
#include <stdio.h>

int main(void)
{   
    char answer;
    do
    {
        char answer = 'y'; //get_char("are you okay Y/N ");
        if (answer == 'y' || answer == 'Y')
        {
            printf("you are okay");
        }
            else if (answer == 'n' || answer == 'N')
        {
            printf("you are not okay ");
        }

    }
    while (answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N');
}
