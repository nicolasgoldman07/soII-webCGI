#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
    printf("<h1>Consultas GOES:</h1>\n");
    printf("</header>\n");


    /* Guardo las respuestas del formulario en variables */
    char * formResponse;
    int year, day;
    bool valid = true;

    formResponse = getenv("QUERY_STRING");

        if(formResponse == NULL){
            printf("<P>Error! Error in passing data from form to script.");
            valid = false;
        } else sscanf(formResponse,"doi=%d&anio=%d", &day, &year);


    /* Busco los archivos de la consulta */
    char * command;
    command = calloc(256, sizeof(char));
	strcpy(command, "echo nein");
    snprintf(command, 250, "aws s3 --no-sign-request ls --recursive noaa-goes16/ABI-L2-CMIPF/%d/%03d/ | grep M3C13 > list.txt", year, day);
    //printf("<p>%s</p>", command);
    
    
    system(command);
	free(command);
    
	char buffer[50000];
	FILE *fp;
	fp = fopen("list.txt", "r");
	fread(buffer, 50000, 1, fp);
	fclose(fp);
	system("rm list.txt");


    /* Print statics */
    printf("<div class = \"other-section\">\n");
    printf("<p>El <b>año</b> seleccionado: %d</p>", year);
    printf("<p>El <b>DOI</b> seleccionado: %d</p>", day);
    printf("</div>\n");

    /* Print table with scans */
    char * token;
    token = strtok(buffer, "\n");

    int odd = 1;
    printf("<div class = \"table-goes\">\n");
    printf("<p style=\"font-size:140%%; background-color:#e7f0c3; margin:0; padding:12; color:black; width: 1100px; text-align: center; border-left: 2px solid; border-right: 2px solid; border-top: 2px solid;\"><b>");
    printf("[%03d/%d] - Channel 13 Scans </b></p>", day, year);
    
    while(token != NULL){
        if(odd%2 == 0){
            printf("<p style=\"margin:0; padding:8; background-color:#ccedd2; min-width: 1108px; border-left: 2px solid; border-right: 2px solid;\">\n");
        }
        else{
            printf("<p style=\"margin:0; padding:8; background-color:#a7e9af; min-width: 1108px; border-left: 2px solid; border-right: 2px solid;\">\n");
        }
        printf("%s", token);
        printf("</p>\n");
        token = strtok(NULL, "\n");
        odd++;
    }
    printf("<p style = \"margin:0px; height: 0px; border-left: 2px solid;min-width: 1124px; border-right: 2px solid; border-bottom: 2px solid;\"> </p>");
    printf("</div>\n");

    

    /* Back button */
    printf("<div style=\"display: flex; justify-content: center ;\">\n");
    printf("<form action=\"../main.html\">\n");
    printf("<button class = \"other-btn\">Back to main</button>\n");
    printf("</form>\n");


    printf("</body>\n");
    printf("</html>\n");
    return 0;
}