#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>


int main()
{
    printf("Content-type: text/html; charset=UTF-8\n\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<title>TP3 - Sistemas Operativos II</title>\n");
    printf("<link rel=\"stylesheet\" href=\"../styles.css\">");  
    printf("<link href=\"https://fonts.googleapis.com/css?family=Roboto&display=swap\" rel=\"stylesheet\">\n");
    printf("</head\n");
    printf("<body>\n");
    printf("<header class=\"other-header\">\n");
    printf("<h1>Modulos cargados en el sistema:</h1>\n");
    printf("</header>\n");

    /* system lsmod > lsmod.txt */
    char * command;
    command = calloc(256, sizeof(char));
	strcpy(command, "echo nein");
    snprintf(command, 250, "lsmod > lsmod.txt");
    //printf("<p>%s</p>", command);

    system(command);
	free(command);
    
    /* open file with lsmod output and save it in buffer variable */
	char buffer[50000];
	FILE *fp;
	fp = fopen("lsmod.txt", "r");
	fread(buffer, 50000, 1, fp);
	fclose(fp);
	//system("rm lsmod.txt");

	int init_size = strlen(buffer);
	char delim[] = "\n";

	char *ptr = strtok(buffer, delim);

	while(ptr != NULL)
	{
		printf("<p>%s<p>\n", ptr);
		ptr = strtok(NULL, delim);
	}

	/* This loop will show that there are zeroes in the str after tokenizing 
	for (int i = 0; i < init_size; i++)
	{
		printf("<p>%d</p> ", str[i]); /* Convert the character to integer, in this case
							            the character's ASCII equivalent 
	}
	printf("\n");*/



    printf("<table class = \"table-mods\" ><tr><th>Module</th><th>Size</th><th>Used by</th></tr>");
    printf("<p style = \"margin:0px; height: 0px; border-left: 2px solid;min-width: 1124px; border-right: 2px solid; border-bottom: 2px solid;\"> </p>");
    printf("</div>\n");

    

    // fscanf(cmdfile, "%s %ld %s %s %ld %s %s %ld %s", str1, &memTot, str2, str3, &memFree, str4, str5, &memAv, str6);
    // printf("<ul> <li> %s %ld %s</li> <li> %s %ld %s</li> <li> %s %ld %s</li></ul>", str1, &memTot, str2, str3, &memFree, str4, str5, &memAv, str6);
    // pclose(cmdfile);
    return 0; 











}