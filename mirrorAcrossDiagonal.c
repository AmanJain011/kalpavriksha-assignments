#include <stdio.h>

int main()
{
    int rowLength;
    int colLength;
    
    printf("Enter row Length: ");
    scanf("%d", &rowLength);
    
    printf("Enter column Length: ");
    scanf("%d", &colLength);
    
    int matrix[100][100];
    int newMatrix[100][100];
    
    for(int i=0; i<rowLength; i++){
        for(int j=0; j<colLength; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    
    for(int i=0; i<rowLength; i++){
        for(int j=0; j<colLength; j++){
            newMatrix[j][i] = matrix[i][j];
        }
    }
    
    printf("<<----------------------------------->>\n");
    
    for(int i=0; i<rowLength; i++){
        for(int j=0; j<colLength; j++){
            printf("%d ", newMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
