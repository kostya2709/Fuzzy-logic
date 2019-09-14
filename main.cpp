#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <math.h>

float Not (float a);

float And (float a, float b);

float Or (float num1, float num2);

void Binary (char* my_str, char* sign, float *number1, float *number2);

float Negation (char* my_str);

void Exit (void);

long ReadFileLength (const char* file);

int Is_Digit (char a);

int main()
{
    const char file_name[] = "input.txt";

    FILE* input = fopen (file_name, "r");

    long size = ReadFileLength (file_name);

    char* my_str = (char*) calloc (size + 1, 1);
    assert (my_str);

    fread (my_str, 1, size + 1, input);
    if (*(my_str + size) == '\n')
        *(my_str + size) = '\0';
    else *(my_str + ++size) = '\0';
    fclose (input);

    float answer = 0;

    //printf ("size = %d, %s, %c\n", size, my_str, *my_str);

    float number1 = 0;
    float number2 = 0;
    char sign = NULL;

    if (*my_str == '~')
        answer = Not (Negation (my_str));
    else if (Is_Digit (*my_str))
        Binary (my_str, &sign, &number1, &number2);
    else
        Exit ();

    if (!answer)
            if (sign == '+')
                answer = Or (number1, number2);
            else answer = And (number1, number2);


    const char* file_name1 = "output.txt";
    FILE* output = fopen (file_name1, "w");
    fprintf (output, "%.2f", answer);
    fclose (output);

    free (my_str);
    //printf ("Your answer is %.2f\n", answer);

    return 0;
}

long ReadFileLength (const char* file)
{
    assert (file);

    FILE* f = fopen (file, "r");

    fseek (f, 0, SEEK_END);
    long pointer2 = ftell (f);

    fclose (f);
    return (pointer2);

}

int Is_Digit (char a)
{
    if (a >= '0' && a <= '9')
        return 1;
    else return 0;
}

float Negation (char* my_str)
{
    //printf ("Hello, I am in Negation!\n");
    assert (my_str);

    my_str++;

    int step = 0;
    float num = 0;


    for (; *my_str; my_str++)
        if (*my_str == ' ')
            continue;

        else if (Is_Digit (*my_str))
        {
            num = num * 10 + *my_str - '0';
            //printf ("num = %f\n", num);
            step *= 10;
        }

        else if (*my_str == '.' || *my_str == ',')
            if (step == 0)
                step += 1;
            else Exit;
        else Exit;


        if (step > 0)
            num = num / step;

        if (num > 1)
            Exit;

        else

                    return num;


}

void Binary (char* my_str, char* sign, float *number1, float *number2)
{
    float num1 = 0;
    float num2 = 0;

    short done = 0;

    short step = 0;

    for (; *my_str; my_str++)
    {
        if (*my_str == ' ')
            continue;
        else if (Is_Digit (*my_str))
        {
            if (done == 0)
                num1 = num1 * 10 + *my_str - '0';
            else num2 = num2 * 10 + *my_str - '0';
            step *= 10;
        }

        else if (*my_str == '*' && done == 0)
        {
           done += 1;
           if (step > 0)
                num1 /= step;
           step = 0;
           *sign = '*';
        }

        else if (*my_str == '+' && done == 0)
        {
            done += 1;
            *sign = '+';
            if (step > 0)
                num1 /= step;
            step = 0;
        }

        else if (*my_str == '.' && step == 0)
           step = 1;

        else Exit();
    }

        if (step > 0)
            num2 /= step;

        if (num1 < 0 || num1 > 1 || num2 < 0 || num2 > 1)
        {
            printf ("Invalid numbers!\n");
            Exit();
        }

        *number1 = num1;
        *number2 = num2;

}

float Not (float a)
{
    assert (isfinite(a));
    assert (a >= 0);
    assert (a <= 1);

    //printf ("Hello! Not is here!");
    return 1 - a;
}

float Or (float a, float b)
{
    assert (isfinite(a));
    assert (a >= 0);
    assert (a <= 1);

    assert (isfinite(b));
    assert (b >= 0);
    assert (b <= 1);

    //printf ("Hello! I am in Or!\n");
    return a + b - a * b;
}

float And (float a, float b)
{
    assert (isfinite(a));
    assert (a >= 0);
    assert (a <= 1);

    assert (isfinite(b));
    assert (b >= 0);
    assert (b <= 1);

    //printf ("I am in And! a = %f, b = %f\n", a, b);
    return a * b;
}

void Exit (void)
{
    printf ("Unexpected expression!\n");
    abort ();
}
