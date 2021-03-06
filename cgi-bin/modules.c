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
	//strcpy(command, "echo nein");
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
	system("rm lsmod.txt");

    printf("<div class = \"table-container\"><table class = \"table-mods\" ><tr><th>Module</th><th>Size</th><th>Instances</th><th>Used by information</th></tr>");


    /* Parseo */
    char * end_str;
    char * token;
    
    token = strtok_r(buffer, "\n", &end_str);
    token = strtok_r(NULL, "\n", &end_str); // No uso la primer fila
    
    while(token != NULL) {

        char *end_token;
        char *token2;
        token2 = strtok_r(token, " ", &end_token);
        
        char line[5000] = {""};
        int index = 0;
        int counter = 0;
        while(token2 != NULL){
            strcat(line, "<td>");
            strcat(line, token2);
            strcat(line, "</td>");

            token2 = strtok_r(NULL, " ", &end_token);
            index = 2;
            counter++;
        }

        if (counter == 3){
            strcat(line, "<td></td>");
            counter = 0;
        } else {
            counter = 0;
        }
        // Evita que se imprima basura al final 
        if(index > 1){
            printf("%s", line);
        }

        printf("</tr>\n");
        token = strtok_r(NULL, "\n", &end_str);

    }

    printf("</table></div>");

    /* Back button */
    printf("<div style=\"display: flex; justify-content: center ;\">\n");
    printf("<form action=\"../main.html\">\n");
    printf("<button class = \"modules-btn\">Back to main</button>\n");
    printf("</form>\n");
    printf("<form action=\"../modules.html\">\n");
    printf("<button class = \"modules-btn\">Back to modules</button>\n");
    printf("</form>\n");
    printf("<form action=\"./removeModule.cgi\">\n");
    printf("<button class = \"modules-btn\">Remove hello_module</button>\n");
    printf("</form>\n");
    printf("</div>");
    
    printf("</body></html>");

    return 0; 

}