#include <stdio.h>
#include <string.h>
#include <sys/statvfs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void main (int argc,char *argv[])
{
    FILE *fp,*hex;
    struct dirent **namelist;
    unsigned long c;
    int x = 0, n, i = 0;
    char path[1024]={0};
    char file_name[1024]={0};
    char name[1024]={0};

    n = scandir( argv[1], &namelist, 0, alphasort);
    if (n < 0){
        free(namelist);
    }else{
        printf("Total file [%d]...\n",n);
        while(i < n)
        {
            
            if(strlen(namelist[i]->d_name) < 3){i++;continue;}
            printf("Process [%s][%d]...\n",namelist[i]->d_name,i);
            strcpy(file_name,namelist[i]->d_name);
            sscanf(file_name,"%[^.]",name);
            sprintf(path,"%s%s", argv[1], file_name);
            fp = fopen(path,"rt");
            sscanf(file_name,"%[^.*]",name);
            sprintf(path,"%s%s.txt", argv[1], name);
            hex = fopen(path,"w");
            x = 0;
            do
            {
                if ((c = fgetc(fp)) == EOF)break;

                if(x == 0)
                    fprintf(hex,"\"");

                fprintf(hex,"\\x%02x",c);
                x++; 
                if(x == 23)
                {
                    fprintf(hex,"\"\n");
                    x = 0;
                }

            }while(c != EOF);
            fclose(fp);
            if(x != 0 || x != 23)
                fprintf(hex,"\"\n");
            fclose(hex);
            free(namelist[i]);
            i++;
        }
        free(namelist);
    }
}
