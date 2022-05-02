
#include <stdio.h>
#include <stdlib.h>


int tracks = 0;
int sequenceSize = 0;
int * sequence = NULL;

void release(){
    if(tracks > 0){
        tracks = 0;
        sequenceSize = 0;
        free(sequence);
    }
}//release

void enter(){
    int i;
    int j;
    release();
    printf("Enter number of concentric tracks (2 or more): ");
    scanf("%d", &tracks);
    if(tracks <= 1){
        printf("Invalid number of tracks. \n");
        return;
    }
    
    printf("Enter size of sequence(1 - %d): ", tracks-1);
    scanf("%d", &sequenceSize);
    if(sequenceSize <= 0){
        printf("Invalid size of sequence, too low. \n");
        tracks = 0;
        return;
    }else if(sequenceSize >= tracks){
        printf("Invalid size of sequence, too high. \n");
        tracks = 0;
        return;
    }
    
    sequence = (int *)malloc(sequenceSize*sizeof(int));
    for(i = 0; i < sequenceSize; i++){
        int track = -1;
        printf("Enter track (1 - %d) for sequence index %d:", tracks-1, i);
        scanf("%d", &track);
        if(track <= 0){
            printf("Invalid track - too low. \n");
            release();
            return;
        }else if(track >= tracks){
            printf("Invalid track - too high. \n");
            release();
            return;
        }
        sequence[i] = track;
        for(j = 0; j < i; j++){
            if(sequence[j] == sequence[i]){
                printf("Invalid track - duplicate. \n");
                release();
                return;
            }
        }
    }
    
}//enter

void schedule(int alg){
    int i;
    int traversed = 0;
    int currentTrack = 0;
    //sstf variables
    int j;
    int *orderedSequence;
    int *orderedSequenceDelay;
    int averageDelayTotal;
    int averageDelaySize;
    int longestDelayAmount;
    int longestDelayTrack;
    
    if(tracks <= 1){
        printf("Invalid number of tracks. \n");
        return;
    }
    //construct additional variables for sstf
    if(alg == 1){
        //allocate arrayy
        orderedSequence = (int *)malloc(sequenceSize * sizeof(int));
        orderedSequenceDelay = (int*)malloc(sequenceSize * sizeof(int));
        //assign default values
        for(i = 0; i < sequenceSize; i++){
            orderedSequence[i] = sequence[i];
            orderedSequenceDelay[i] = 0;
        }
        for(i = 0; i < sequenceSize-1; i++){
            for(j = i+1; j < sequenceSize; j++){
                if(orderedSequence[i] > orderedSequence[j]){
                    int temp = orderedSequence[i];
                    orderedSequence[i] = orderedSequence[j];
                    orderedSequence[j] = temp;
                }
            }
        }
        
        for(i = 1; i < sequenceSize; i++){
            for(j = 0; j < i; j++){
                if(orderedSequence[i] == sequence[j]){
                    orderedSequenceDelay[i] = i - j;
                    break;
                }
            }
        }
        
        averageDelayTotal = 0;
        averageDelaySize = 0;
        longestDelayAmount = -1;
        longestDelayTrack = -1;
        
        for(i = 0; i < sequenceSize; i++){
            if(orderedSequenceDelay[i] > 0){
                averageDelayTotal += orderedSequenceDelay[i];
                averageDelaySize++;
            }
            if(longestDelayAmount < orderedSequenceDelay[i]){
                longestDelayAmount = orderedSequenceDelay[i];
                longestDelayTrack = orderedSequence[i];
            }
        }
        
    }
    
    //print original track sequence
    printf("Sequence of tracks to seek:");
    for(i = 0; i < sequenceSize; i++){
        printf(" %d", sequence[i]);
    }
    printf("\n");
    //print traversed track sequence
    printf("Traversed sequence:");
    for(i = 0; i < sequenceSize; i++){
        if(alg == 0){
            printf(" %d", sequence[i]);
            traversed += abs(currentTrack - sequence[i]);
            currentTrack = sequence[i];
        }else if(alg == 1){
             printf(" %d", orderedSequence[i]);
            traversed += abs(currentTrack - orderedSequence[i]);
            currentTrack = orderedSequence[i];
        }
    }
    
    //print algorithm results
    printf("\nThe number of tracks traveresed: %d\n", traversed);
    if(alg == 1){
        if(averageDelaySize > 0){
            double averageDelay = (double)averageDelayTotal / (double)averageDelaySize;
            printf("The average delay of all tracks processed later is: %.2f\n", averageDelay);
        }
        printf("The longest delay experienced by a track is: %d by track %d\n", longestDelayAmount, longestDelayTrack);
        free(orderedSequence);
        free(orderedSequenceDelay);
    }
    
}//schedule






int main()
{
    int option = 0;
    while(option != 4){
        option = 4;
        printf("Disk Schedulimg\n");
        printf("-------------------------------------------\n");
        printf("1) Enter Parameters\n");
        printf("2) Schedule disk tracks with FIFO algorithm\n");
        printf("3) Schedule disk tracks with SSTF algorithm\n");
        printf("4) Quit program and free memory\n");
        printf("\n");
        printf("Enter Selection: ");
        scanf("%d", &option);
        printf("\n");
        switch (option){
            case 1:
                enter();
                break;
            case 2:
                schedule(0);
                break;
            case 3:
                schedule(1);
                break;
            case 4:
                printf("Goodbye");
                release();
                break;
            default:
                printf("Invalid option, try again. \n");
        }
        printf("\n");
    }

    return 0;
    
}//main


