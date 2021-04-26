#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void usage(void) {
   printf("USAGE: \n ./make-2d  -r <rows> -c <cols>  -o <output_file>");
   exit(EXIT_SUCCESS);
}

int main (int argc, char * argv[]) {
   
   if(argc == 1)
      usage();

   int opt, rows = -1, cols = -1;
   char *file;
   FILE *foutptr;
   double *a;
   double *ptr;

   while((opt = getopt(argc, argv, "r:c:o:")) != -1){
      switch(opt){  
 
         case 'r':
               if(optarg != NULL)
                  rows = atoi(optarg);
               //printf("rows set \n");
            break;  
         case 'c':
               if(optarg != NULL)
                  cols = atoi(optarg);
               //printf("columns set \n");
            break;  
         case 'o': 
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

   a = (double *) malloc ((rows * cols + 1)* sizeof(double));
   
   if (a != NULL){
      ptr = a;
   
      for (int i = 0; i < rows; i++) {
         for (int j = 0; j < cols; j++)

             if(j == 0 || j == (cols - 1))
                 *(ptr++) = 1;  
             else
                *(ptr++) = 0; 
                    
      }
      
      foutptr = fopen (file, "w");
      fwrite (&rows, sizeof(int), 1, foutptr);
      fwrite (&cols, sizeof(int), 1, foutptr);
      fwrite (a, sizeof(double), rows*cols, foutptr);
      fclose (foutptr);
   }else{
      printf("Error: could not malloc space for matrix.");
      exit(EXIT_FAILURE);
   }

}

