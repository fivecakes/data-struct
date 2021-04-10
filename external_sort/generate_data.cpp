#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(){
	int MAX=80000;
    srand((unsigned int)time(0));
    FILE *fp = fopen("/tmp/test.txt", "w+");
    
    float random_float;
    for(int i=0;i<MAX;i++){
        // [-100,100]
        random_float = (2.0*(float)rand()/RAND_MAX-1.0)*100;
        fprintf(fp, "%f\n", random_float);
    }
    fclose(fp);
	
	return 0;
}
