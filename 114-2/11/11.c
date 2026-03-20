    #include <stdio.h>
    #include <string.h>

    int str2Int(char str[], int startIndex, int endIndex)
    {
        int result = 0;
        for(int i = startIndex; i < endIndex; i++)
        {
            result *= 10;
            result += str[i] - '0';
        }
        return result;
    }

    int getFraction(char operand[], int *up, int *down,int *isNagitive, int len)
    {   
        int indexOfDevide = -1, indexOfBraket = -1, _int = 0; 
        if(operand[0] == '-')
        {
            *isNagitive = 1;
        }
        for(int i = 0; i < len; i++)
        {
            if(operand[i] == '(')
                indexOfBraket = i;
            if(operand[i] == '/')
                indexOfDevide = i;
        }
        if(indexOfBraket != -1)
        {
            _int = str2Int(operand, *isNagitive, indexOfBraket);
        }
        *down = str2Int(operand, indexOfDevide + 1, (indexOfBraket == -1 ? len : len -1));
        *up = str2Int(operand, indexOfBraket + 1 + (indexOfBraket == -1 ? *isNagitive : 0), indexOfDevide) + _int * *down;
        return (*down == 0 ? 0 : 1);
    }

    int main()
    {
        char operand1[50], operand2[50];
        char operator, yorn = 'y';

        do
        {
            int up1, up2, upResult, down1, down2, downResult, intResult = 0, isNagitive1 = 0, isNagitive2 = 0, isNagitiveResult = 0;
            int indexOfBraket = -1, indexOfDevide = -1;
            scanf("%s %c%s", operand1, &operator, operand2);
            if(!getFraction(operand1, &up1, &down1, &isNagitive1, strlen(operand1)) || !getFraction(operand2, &up2, &down2, &isNagitive2, strlen(operand2)))
            {
                printf("error\n");
                scanf(" %c", &yorn);
                continue;
            }    
            switch (operator)
            {
            case '+':
                if(isNagitive1)
                    up1 = -up1;
                if(isNagitive2)
                    up2 = -up2;
                upResult = up1 * down2 + up2 * down1;
                downResult = down1 * down2;
                if(upResult < 0)
                {
                    upResult = -upResult;
                    isNagitiveResult = 1;
                } 
                break;
            case '-':
                if(isNagitive1)
                    up1 = -up1;
                if(isNagitive2)
                    up2 = -up2;
                upResult = up1 * down2 - up2 * down1;
                downResult = down1 * down2;
                if(upResult < 0)
                {
                    upResult = -upResult;
                    isNagitiveResult = 1;
                } 
                break;
            case '*':
                upResult = up1 * up2;
                downResult = down1 * down2;
                isNagitiveResult = isNagitive1 ^ isNagitive2;
                break;
            case '/':
                upResult = up1 * down2;
                downResult = up2 * down1;
                isNagitiveResult = isNagitive1 ^ isNagitive2;
                break;
            }
            scanf(" %c", &yorn);
        } while(yorn == 'y');
        
        return 0;
    }