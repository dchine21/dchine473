#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void usage(void) {
   printf("USAGE: \n ./print-matrix -i <input matrix file name>");
   exit(EXIT_SUCCESS);
}

int main (int argc, char * argv[]) {
   
   if(argc == 1)
      usage();

   int opt, rows = -1, cols = -1;
   char *file;
   FILE *fptr;
   double *a = NULL;

   while((opt = getopt(argc, argv, "i:")) != -1){
      switch(opt){  
 
         case 'i': 
               if(optarg != NULL){
                  
                  file = malloc(strlen(optarg));
                  
                  if(file != NULL)
                     strcpy(file,optarg);
                  else{
                      printf("Error: could not malloc space for filename.");
                      exit(EXIT_FAILURE);
                  }
                    
               } 
            break;
         case '?':
         default:
               usage();

      }  
   } 

    if (( fptr = fopen (file, "r")) == NULL){
        printf("Error: could not open matrix file \n");
        usage();
    }

    fread(&rows, sizeof(int), 1, fptr);
    fread(&cols, sizeof(int), 1, fptr);

   // printf("rows = %d, cols = %d \n", rows, cols);

    if (!(rows < 0 || cols < 0)){

       a = (double*) malloc(sizeof(double)*(rows*cols));

        fread(a, sizeof(double), (rows*cols), fptr);
        fclose(fptr);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++){
                printf("%.2f\t", *a++);
            }  
            printf ("\n");
        }
        
    }else{
        fclose(fptr);
        printf("Error: rows and columns could not be read from input file");
        usage();
    }

}

