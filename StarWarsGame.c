#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


typedef struct
{
    char look;
    char in;
}Cage;
typedef struct
{
    int direction;
    int cor1;
    int cor2;
}Stormtroopers;
void stormmove(Cage **arr,Stormtroopers *stormarr,int N,int M,int storm,int stormtrooperEncounters,int *nstormtrooperEncounters);
int checkWin(Cage **arr, int N, int M, int stormtrooperEncounters,int *nstormtrooperEncounters,int cor1,int cor2);
int act(Cage **arr,int N,int M,int cor1,int cor2,char move[20],int *ncor1,int *ncor2,int stormtrooperEncounters,int *nstormtrooperEncounters,int force ,int *nforce,int darth,int *ndarth,Stormtroopers *stormarr,int storm);
void print(Cage **arr,int N,int M,int cor1,int cor2,char move[20],char diff[20],int tempcor1,int tempcor2,int stormtrooperEncounters,int *nstormtrooperEncounters,int *ntempcor1,int *ntempcor2);
void enemyMovement(Cage **arr, int N, int M, int cor1, int cor2,int darth,int *ndarth);
void stormattack(Cage **arr,int stormtrooperEncounters,int *nstormtrooperEncounters,int cor1,int cor2);

int main()
{
    int N,M,i,j,storm,obj,a,b,h;
    Cage **arr;
    char diff[20];
    char move[20];
    do{
        printf("give dimensions for the game that are higher than 8*8\n");
       if((scanf("%d %d", &N, &M) != 2) || (M < 8) || (N < 8)){
            while (getchar() != '\n');
        }
    }while((M<8)||(N<8));   
    arr = (Cage**) malloc (N*sizeof(Cage*));
    while(1){
        printf("choose dificulty easy medium hard impossible\n");
        scanf("%s",diff);
        if(strcmp(diff,"easy")==0){
            storm = (0.02)*(M*N);
            obj = (0.13)*(M*N);
            break;
        }
        if(strcmp(diff,"medium")==0){
            storm = (0.05)*(M*N);
            obj = (0.10)*(M*N);
            break;
        }
        if(strcmp(diff,"hard")==0){
            storm = (0.10)*(M*N);
            obj = (0.05)*(M*N);
            break;
        }
        if(strcmp(diff,"impossible")==0){
            storm = (0.15)*(M*N);
            obj = 0;
            break;
        }
    }
    while((4<N)||(4<M))
    {
        if(strcmp(diff,"easy")==0){
            storm = (0.02)*(M*N);
            obj = (0.13)*(M*N);
        }
        if(strcmp(diff,"medium")==0){
            storm = (0.05)*(M*N);
            obj = (0.10)*(M*N);
        }
        if(strcmp(diff,"hard")==0){
            storm = (0.10)*(M*N);
            obj = (0.05)*(M*N);
        }
        if(strcmp(diff,"impossible")==0){
            storm = (0.15)*(M*N);
            obj = 0;
        }
        arr = (Cage**) malloc (N*sizeof(Cage*));
        for(i=0; i<N; i++)
        {
           arr[i] = (Cage *) malloc (M* sizeof(Cage));
        }
        printf("new level\n");
        int stormtrooperEncounters = 0;
        int force = 0;
        int darth = 0;
        for(i=0; i<N; i++){
            for(j=0; j<M; j++){
                arr[i][j].look = '#';
                arr[i][j].in = '.';
            }
        }
        srand(time(0));
        a = ((rand()%4)+1);
        if(a==1){
            arr[0][0].look = 'D';
            arr[0][0].in = 'D';
        }
        if(a==2){
            arr[0][M-1].look = 'D';
            arr[0][M-1].in = 'D';
        }
        if(a==3){
            arr[N-1][0].look = 'D';
            arr[N-1][0].in = 'D';
        }
        if(a==4){
            arr[N-1][M-1].look = 'D';
            arr[N-1][M-1].in = 'D';
        }
        Stormtroopers *stormarr = malloc(storm*sizeof(Stormtroopers));
        for (i=0; i<storm; i++){
            do{
                a = (rand()%N)+0;
                b = (rand()%M)+0;
            }while(arr[a][b].in!='.');
            arr[a][b].look = '#';
            arr[a][b].in = '@';
            stormarr[i].cor1=a;
            stormarr[i].cor2=b;
            int x = ((rand()%4)+1);
            stormarr[i].direction=x;
        }
        for (i=0; i<obj; i++){
            do{
                a = (rand()%N)+0;
                b = (rand()%M)+0;
            }while(arr[a][b].in!='.');
            arr[a][b].look = 'x';
            arr[a][b].in = 'x';
        }
        do{
            a = (rand()%N)+0;
            b = (rand()%M)+0;
        }while(arr[a][b].in!='.');
        arr[a][b].look = 'L';
        arr[a][b].in = 'L';
        int cor1 = a;
        int cor2 = b;
        int tempcor1 = a;
        int tempcor2 = b;
        do{
            a = (rand()%N)+0;
            b = (rand()%M)+0;
        }while(arr[a][b].in!='.');
        arr[a][b].look = '#';
        arr[a][b].in = 'R';
        printf("   ");
        for (i = 0; i < M; i++) {
            printf("%c ", 'A' + i);
        }
        for(h=0; h<N; h++){
            arr[h][cor2].look=arr[h][cor2].in;
        }
        for(h=0; h<M; h++){
            arr[cor1][h].look=arr[cor1][h].in;
        }
    /*emfanizei to in twn tetragwnwn poy prepei na anoijoyn*/
        printf("\n");
        for ( i = 0; i < N; i++) {
            printf("%2d ", i + 1);
            for ( j = 0; j < M; j++) {
                printf("%c ", arr[i][j].look);
            }
            printf("\n");
        }
        for(h=0; h<N; h++){
            if(arr[h][cor2].look=='.'){
                arr[h][cor2].look='#';
            }
            if(arr[h][cor2].look=='@'){
                arr[h][cor2].look='#';
            }
            if(arr[h][cor2].look=='R'){
                arr[h][cor2].look='#';
            }
        }
        for(h=0; h<M; h++){
            if(arr[cor1][h].look=='.'){
                arr[cor1][h].look='#';
            }
            if(arr[cor1][h].look=='@'){
                arr[cor1][h].look='#';
            }
            if(arr[h][cor2].look=='R'){
                arr[h][cor2].look='#';
            }
        }
    /*janakanei to look twn anoigmenwn tetragwnwn keli*/
        printf("Level %s \nmake your move(s)\n",diff);
        scanf("%s",move);
        while(1){
        if (2==(act(arr,N,M,cor1,cor2,move,&cor1,&cor2,stormtrooperEncounters,&stormtrooperEncounters,force,&force,darth,&darth,stormarr,storm)))
        {
            break;
        }
        print(arr,N,M,cor1,cor2,move,diff,tempcor1,tempcor2,stormtrooperEncounters,&stormtrooperEncounters,&tempcor1,&tempcor2);
        }
        for(i=0; i<N; i++)
        {
           free (arr[i]);
        }   
        free(arr);
        free(stormarr);
        M--;
        N--;
    }
    printf("jsegns");

    return 0;
}
int act(Cage **arr,int N,int M,int cor1,int cor2,char move[20],int *ncor1,int *ncor2,int stormtrooperEncounters,int *nstormtrooperEncounters,int force,int *nforce,int darth , int *ndarth,Stormtroopers *stormarr,int storm)
{
    int i=0,temp,j,k;
    while(move[i]!='\0')
    {
        if(((move[i]=='u')||(move[i]=='U'))&&(!isdigit(move[i+1]))){
            temp = cor1;
            temp--;
            if((temp<0)||(arr[temp][cor2].in=='x'))
            {
                printf("cannot go higher\n");
                break;
            }
            cor1 = temp;
            if(2==(checkWin(arr,N,M,stormtrooperEncounters,&stormtrooperEncounters,cor1,cor2)))
            {
                return 2;
            }
            enemyMovement(arr,N,M,cor1,cor2,darth,ndarth);
            stormmove(arr,stormarr,N,M,storm,stormtrooperEncounters,&stormtrooperEncounters);
            printf("up\n");
        }
        else if(((move[i]=='d')||(move[i]=='D'))&&(!isdigit(move[i+1]))){
            temp = cor1;
            temp++;
            if((N-1<temp)||(arr[temp][cor2].in=='x')){
                printf("cannot go any lower \n");
                break;
            }
            printf("down\n");
            cor1 = temp;
            if(2==(checkWin(arr,N,M,stormtrooperEncounters,&stormtrooperEncounters,cor1,cor2)))
            {
                return 2;
            }
            enemyMovement(arr,N,M,cor1,cor2,darth,ndarth);
            stormmove(arr,stormarr,N,M,storm,stormtrooperEncounters,&stormtrooperEncounters);
        }
        else if(((move[i]=='l')||(move[i]=='L'))&&(!isdigit(move[i+1]))){
            temp = cor2;
            temp--;
            if((temp<0)||(arr[cor1][temp].in=='x'))
            {
                printf("cannot go left\n");
                break;
            }
            printf("left\n");
            cor2= temp;
            if(2==(checkWin(arr,N,M,stormtrooperEncounters,&stormtrooperEncounters,cor1,cor2)))
            {
                return 2;
            }
            enemyMovement(arr,N,M,cor1,cor2,darth,ndarth);
            stormmove(arr,stormarr,N,M,storm,stormtrooperEncounters,&stormtrooperEncounters);
        }
        else if(((move[i]=='r')||(move[i]=='R'))&&(!isdigit(move[i+1]))){
            temp = cor2;
            temp++;
            if((M-1<temp)||(arr[cor1][temp].in=='x'))
            {
                printf("cannot go right\n");
                break;
            }
            printf("right\n");
            cor2 = temp;
            if(2==(checkWin(arr,N,M,stormtrooperEncounters,&stormtrooperEncounters,cor1,cor2)))
            {
                return 2;
            }
            enemyMovement(arr,N,M,cor1,cor2,darth,ndarth);
            stormmove(arr,stormarr,N,M,storm,stormtrooperEncounters,&stormtrooperEncounters);
        }
        else{
            printf("you can use a only a special ability per turn you wanna proceed by deleting yor previous moves press 1 to procced or enything else if you donot wanna use special ability\n");
            scanf("%d",&k);
            if(k==1){
                if(((move[i]=='h')||(move[i]=='H'))&&(!isdigit(move[i+1]))){
                    printf("\n   ");
                    for (i = 0; i < M; i++) {
                        printf("%c ", 'A' + i);
                    }
                    printf("\n");
                    for ( i = 0; i < N; i++) {
                        printf("%2d ", i + 1);
                        for ( j = 0; j < M; j++) {
                            printf("%c ", arr[i][j].in);
                        }
                        printf("\n");
                    }
                }
                if(((move[i]=='x')||(move[i]=='X'))&&(!isdigit(move[i+1]))){
                    printf("thanks for playing game terminated");
                    exit(0);
                }
                if(move[i+2]=='>'){
                    if((force==0)||(force==1)){
                        if(!isupper(move[i])){
                            move[i]=move[i]-32;
                        }
                        if(!isupper(move[i+3])){
                            move[i+3]=move[i+3]-32;
                        }
                        int ob1 = move[i]-'A';
                        int ob2 = move[i+1]-'0'-1;
                        int ob3 = move[i+3]-'A';
                        int ob4 = move[i+4]-'0'-1;
                        if((ob2>=0)&&(ob2<N)&&(ob1>=0)&&(ob1<M)&&(ob4>=0)&&(ob4<N)&&(ob3>=0)&&(ob3<M)){
                            if(arr[ob4][ob3].in=='.'){
                                Cage temp;
                                temp = arr[ob4][ob3];
                                arr[ob4][ob3] = arr[ob2][ob1];
                                arr[ob2][ob1] = temp;
                                force++;
                                *nforce=force;
                            }
                            else {
                                printf("the cage you want the object to move to is occupied try another one\n");
                            }
                        }
                        else{
                            printf("there is no such cage\n");
                        }
                    }
                    else{
                        printf("you can use the force to move objects 2 times only\n");
                    }
                    break;
                }
            }
        }
        i++;
    }
    if(k!=1){
       *ncor1 = cor1;
       *ncor2 = cor2;
    }   
  }
void print(Cage **arr,int N,int M,int cor1,int cor2,char move[20],char diff[20],int tempcor1,int tempcor2,int stormtrooperEncounters,int *nstormtrooperEncounters,int *ntempcor1,int *ntempcor2)
{
    int i,j,h;
    printf("\n   ");
    for (i = 0; i < M; i++) {
        printf("%c ", 'A' + i);
    }
    arr[tempcor1][tempcor2].look='#';
    arr[tempcor1][tempcor2].in='.';
    arr[cor1][cor2].look='L';
    arr[cor1][cor2].in='L';
    for(h=0; h<N; h++){
        arr[h][cor2].look=arr[h][cor2].in;
    }
    for(h=0; h<M; h++){
        arr[cor1][h].look=arr[cor1][h].in;
    }
    /*emfanizei to in twn tetragwnwn poy prepei na anoijoyn*/
    printf("\n");
    for ( i = 0; i < N; i++) {
        printf("%2d ", i + 1);
        for ( j = 0; j < M; j++) {
            printf("%c ", arr[i][j].look);
        }
        printf("\n");
    }
    for(h=0; h<N; h++){
        if(arr[h][cor2].look=='.'){
            arr[h][cor2].look='#';
        }
        if(arr[h][cor2].look=='@'){
            arr[h][cor2].look='#';
        }
        if(arr[h][cor2].look=='R'){
            arr[h][cor2].look='#';
        }
    }
    for(h=0; h<M; h++){
        if(arr[cor1][h].look=='.'){
            arr[cor1][h].look='#';
        }
        if(arr[cor1][h].look=='@'){
            arr[cor1][h].look='#';
        }
        if(arr[h][cor2].look=='R'){
            arr[h][cor2].look='#';
        }
        
    }
    /*janakanei to look twn anoigmenwn tetragwnwn keli*/
    printf("Level %s \nmake your move(s)\n",diff);
    scanf("%s",move);
    *ntempcor1=cor1;
    *ntempcor2=cor2;
}
int checkWin(Cage **arr, int N, int M, int stormtrooperEncounters,int *nstormtrooperEncounters,int cor1,int cor2) {
    if (arr[cor1][cor2].in == '@') {
// If it's the first time Leia encounters a stormtrooper
        if (stormtrooperEncounters==0) {
            printf("Leia defeated a stormtrooper! The stormtrooper (@) has been removed.\n");
            arr[cor1][cor2].in = '.'; // Remove the stormtrooper
            *nstormtrooperEncounters = 1; // Update encounter flag
            return 0; // Game continues
        } 
        else {
            printf("You lost! Leia encountered another stormtrooper (@).\n");
            exit (0);
        }
    } 
    else if (arr[cor1][cor2].in == 'D') {
        printf("You lost! You encountered Darth Vader (D).\n");
        exit (0);
        } 
    else if (arr[cor1][cor2].in == 'R') {
    printf("Congratulations! You have found R2D2 (R).\n");
    return 2; // Indicate win
    } 
    else {
    return 0; // Indicate game continues
    }
    return 0; // Indicate game continues
}
void enemyMovement(Cage **arr, int N, int M, int cor1, int cor2,int darth,int *ndarth) {
    int dvRow, dvCol,i,j;
    int tempr, tempc;
    if(*ndarth==0){
        darth++;
        *ndarth=darth;
    }
    else
    {
    // Find Darth Vader's position
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (arr[i][j].in == 'D') {
                dvRow = i;
                dvCol = j;
                tempr = i;
                tempc = j;
                break;
            }
        }
    }

    int dx = cor1 - dvRow;
    int dy = cor2 - dvCol;

    // Move Darth Vader in the direction of Leia
    if (dx != 0) {
        if (dx > 0) {
            dvRow += 1; // Move Darth Vader down
        } else {
            dvRow -= 1; // Move Darth Vader up
        }
    }
    if (dy != 0) {
        if (dy > 0) {
            dvCol += 1; // Move Darth Vader right
        } else {
            dvCol -= 1; // Move Darth Vader left
        }
    }
    if(arr[dvRow][dvCol].in == 'L'){
        printf("\nDARTH VADER HAVE FOUND YOU YOU LOST");
        exit(0);
    }

    // Check for obstacles and try to move around them
    while (dvRow >= 0 && dvRow < N && dvCol >= 0 && dvCol < M &&
           (arr[dvRow][dvCol].in == 'x' || arr[dvRow][dvCol].in == '@' || arr[dvRow][dvCol].in == 'R')) {
        if (dx != 0) {
            if (dx > 0) {
                if (arr[dvRow][dvCol + 1].in == '.') {
                    dvCol += 1; // Move Darth Vader right
                } else {
                    dvCol -= 1; // Move Darth Vader left
                }
            } else {
                if (arr[dvRow][dvCol - 1].in == '.') {
                    dvCol -= 1; // Move Darth Vader left
                } else {
                    dvCol += 1; // Move Darth Vader right
                }
            }
        }
        if (dy != 0) {
            if (dy > 0) {
                if (arr[dvRow + 1][dvCol].in == '.') {
                    dvRow += 1; // Move Darth Vader down
                } else {
                    dvRow -= 1; // Move Darth Vader up
                }
            } else {
                if (arr[dvRow - 1][dvCol].in == '.') {
                    dvRow -= 1; // Move Darth Vader up
                } else {
                    dvRow += 1; // Move Darth Vader down
                }
            }
        }
    }

    // Update Darth Vader's position
    arr[dvRow][dvCol].in = 'D';
    arr[dvRow][dvCol].look = 'D';

    // Clear previous position
    arr[tempr][tempc].look = '#';
    arr[tempr][tempc].in = '.';
    darth=0;
    *ndarth=darth;
    }
}
void stormmove(Cage **arr,Stormtroopers *stormarr,int N,int M,int storm,int stormtrooperEncounters,int *nstormtrooperEncounters)
{
    int i;
    for(i=0; i<storm; i++)
    {
        if(stormarr[i].cor1!=-2)
        {
           int temp;
           if(stormarr[i].direction==1)
           {
               temp = stormarr[i].cor1;
               temp--;
               if(temp>=0)
               {
                   if(arr[temp][stormarr[i].cor2].in=='.')
                   {
                      arr[temp][stormarr[i].cor2].in='@';
                      arr[stormarr[i].cor1][stormarr[i].cor2].in='.';
                      stormarr[i].cor1=temp;
                    }
                    if(arr[temp][stormarr[i].cor2].in=='L')
                    {
                        stormattack(arr,stormtrooperEncounters,&stormtrooperEncounters,temp,stormarr[i].cor2);
                        arr[stormarr[i].cor1][stormarr[i].cor2].in='.';
                        stormarr[i].cor1 = -2;
                    }
                }    
                else
                {
                    temp=temp+2;
                    if(temp<=N-1)
                    {
                       if(arr[temp][stormarr[i].cor2].in=='.')
                       {
                           arr[temp][stormarr[i].cor2].in='@';
                           arr[stormarr[i].cor1][stormarr[i].cor2].in='.';
                           stormarr[i].cor1=temp;
                           stormarr[i].direction = 2;
                        }
                        if(arr[temp][stormarr[i].cor2].in=='L')
                        {
                            stormattack(arr,stormtrooperEncounters,&stormtrooperEncounters,temp,stormarr[i].cor2);
                            arr[stormarr[i].cor1][stormarr[i].cor2].in='.';
                            stormarr[i].cor1 = -2;
                        }
                    }
                }
            }
            else if(stormarr[i].direction==2)
            {
                temp = stormarr[i].cor1;
                temp++;
                if(temp<=N-1)
                {
                    if(arr[temp][stormarr[i].cor2].in=='.')
                    {
                        arr[temp][stormarr[i].cor2].in='@';
                        arr[stormarr[i].cor1][stormarr[i].cor2].in='.';
                        stormarr[i].cor1=temp;
                    }
                    if(arr[temp][stormarr[i].cor2].in=='L')
                    {
                        stormattack(arr,stormtrooperEncounters,&stormtrooperEncounters,temp,stormarr[i].cor2);
                        arr[stormarr[i].cor1][stormarr[i].cor2].in='.';
                        stormarr[i].cor1 = -2;
                    }
                }    
                else
                {
                    temp=temp-2;
                    if(temp>=0)
                    {
                        if(arr[temp][stormarr[i].cor2].in=='.')
                        {
                            arr[temp][stormarr[i].cor2].in='@';
                            arr[stormarr[i].cor1][stormarr[i].cor2].in='.';
                            stormarr[i].cor1=temp;
                            stormarr[i].direction = 1;
                        }
                        if(arr[temp][stormarr[i].cor2].in=='L')
                        {
                            stormattack(arr,stormtrooperEncounters,&stormtrooperEncounters,temp,stormarr[i].cor2);
                            arr[stormarr[i].cor1][stormarr[i].cor2].in='.';
                            stormarr[i].cor1 = -2;
                        }
                    }
                }    
            }
            else if(stormarr[i].direction==3)
            {
                temp = stormarr[i].cor2;
                temp--;
                if(temp>=0)
                {
                    if(arr[stormarr[i].cor1][temp].in=='.')
                    {
                        arr[stormarr[i].cor1][temp].in='@';
                        arr[stormarr[i].cor1][stormarr[i].cor2].in='.';
                        stormarr[i].cor2=temp;
                    }
                    if(arr[stormarr[i].cor1][temp].in=='L')
                    {
                        stormattack(arr,stormtrooperEncounters,&stormtrooperEncounters,stormarr[i].cor1,temp);
                        arr[stormarr[i].cor1][stormarr[i].cor2].in='.';
                        stormarr[i].cor1 = -2;
                    }
                }
                else
                {
                    temp = temp+2;
                    if(temp<=M-1)
                    {
                        if(arr[stormarr[i].cor1][temp].in=='.')
                        {
                            arr[stormarr[i].cor1][temp].in='@';
                            arr[stormarr[i].cor1][stormarr[i].cor2].in='.';
                            stormarr[i].cor2=temp;
                            stormarr[i].direction = 4;
                        }
                        if(arr[stormarr[i].cor1][temp].in=='L')
                        {
                            stormattack(arr,stormtrooperEncounters,&stormtrooperEncounters,stormarr[i].cor1,temp);
                            arr[stormarr[i].cor1][stormarr[i].cor2].in='.';
                            stormarr[i].cor1 = -2;
                        }
                    }
                }
            }
            else
            {
                temp = stormarr[i].cor2;
                temp++;
                if(temp<=M-1)
                {
                    if(arr[stormarr[i].cor1][temp].in=='.')
                    {
                        arr[stormarr[i].cor1][temp].in='@';
                        arr[stormarr[i].cor1][stormarr[i].cor2].in='.';
                        stormarr[i].cor2=temp;
                    }
                    if(arr[stormarr[i].cor1][temp].in=='L')
                    {
                        stormattack(arr,stormtrooperEncounters,&stormtrooperEncounters,stormarr[i].cor1,temp);
                        arr[stormarr[i].cor1][stormarr[i].cor2].in='.';
                        stormarr[i].cor1 = -2;
                    }
                }
                else
                {
                    temp = temp-2;
                    if(temp>=0)
                    {
                        if(arr[stormarr[i].cor1][temp].in=='.')
                        {
                            arr[stormarr[i].cor1][temp].in=='@';
                            arr[stormarr[i].cor1][stormarr[i].cor2].in='.';
                            stormarr[i].cor2=temp;
                            stormarr[i].direction=4;
                        }
                        if(arr[stormarr[i].cor1][temp].in=='L')
                        {
                            stormattack(arr,stormtrooperEncounters,&stormtrooperEncounters,stormarr[i].cor1,temp);
                            arr[stormarr[i].cor1][stormarr[i].cor2].in='.';
                            stormarr[i].cor1 = -2;
                        }
                    }
                }
            }
        }
    }
}
void stormattack(Cage **arr,int stormtrooperEncounters,int *nstormtrooperEncounters,int cor1,int cor2)
{
// If it's the first time Leia encounters a stormtrooper
    if (stormtrooperEncounters==0) {
        printf("Leia defeated a stormtrooper! The stormtrooper (@) has been removed.\n");
        *nstormtrooperEncounters = 1; // Update encounter flag
    } 
    else {
        printf("You lost! Leia encountered another stormtrooper (@).\n");
        exit (0);
    }
}