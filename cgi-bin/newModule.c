#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
      FILE *fp;
      char *request_method;
      char *content_length;
      char *content_type;
      char *boundary, *pchar;
      char *pschar, *pechar;
      char *delim = "\r\n";
      char *datastart = "\r\n\r\n";

      int data_len, data_read, i,found;
      char *buffer;

      printf("Content-type: text/html\n\n");
      printf("<html>\n");
      printf("<head>\n");
      printf("<title>TP3 - Sistemas Operativos II</title>\n");
      printf("<meta charset=\"UTF-8\">");
      printf("<link rel=\"stylesheet\" href=\"../styles.css\">");  
      printf("<link href=\"https://fonts.googleapis.com/css?family=Roboto&display=swap\" rel=\"stylesheet\">\n");
      printf("</head\n");
      printf("<body>\n");
      printf("<header class=\"other-header\">\n");
      printf("<h1>Agregando módulo de kernel</h1>\n");
      printf("</header>\n");

      /* Guardo los valores de enviroment variables en los strings */
      request_method = getenv("REQUEST_METHOD");
      content_length = getenv("CONTENT_LENGTH");
      content_type = getenv("CONTENT_TYPE");


      /* Handles para los diferentes errores que puedo tener en los env variables */
      if(request_method == NULL){
            printf("<center>Error: Unknown cgi-bin request</center>\n");
            printf("</html>\n");
            return 0;
      }


      /* Handles error of using other method than post */
      if(strcmp(request_method, "POST") != 0){
            printf("<center>Error: %s request method not supported</center>\n", request_method);
            printf("</html>\n");
            return 0;
      } //end if strcmp


      /* The total length of what the client sent upstream (atoi converts string to integer) */
      data_len = atoi(content_length);


      /* Make a space to hold all of the data.  If large uploads are expected
         and memory is limited, this should be done in blocks rather than all
         at once */
      buffer = (char *)malloc(data_len);
      
      data_read = fread((void *)buffer, 1, data_len, stdin); 

      /* Get the boundary marker for start/end of the data */
      pchar = strtok(buffer, delim);
      boundary = strdup(buffer);

      /* Find the data start */
      pschar = strstr(buffer+strlen(boundary)+1, datastart);
      if(pschar == NULL){
            printf("<p>ERROR - BAD DATA START</p>\n");
            for(i=0; i<10; i++){
                  printf("%c ", *(buffer+strlen(boundary)+i));
            } //end for i
            return 0;
      } //end if pschar

      /* Move the pointer past the end of headers marker */
      pschar+=strlen(datastart);

      /* Find the data end */
      /* Can't use strstr here as the data may be binary */
      found = 0;
      for(pchar=pschar; pchar < buffer+data_len-strlen(boundary); pchar++){
            if(memcmp(pchar, boundary, strlen(boundary)) == 0){
                  found = 1;
                  break;
            } //end if memcmp
      } //end for pchar

      if(found == 1){
            pechar = pchar;
      } else{
            printf("<p>ERROR - BAD DATA END</p>\n");
            free(boundary);
            free(buffer);
            return 0;
      } //end if found

      /* Write the data to a file */
      fp = fopen("hello_module.ko", "w");
      if(fp == NULL){
            printf("<p>Error opening output file for write</p>\n");
      } else{
            fwrite(pschar, 1, pechar-pschar, fp);
            fclose(fp);
      } //end if fp

      free(boundary);
      free(buffer);

      char * command;
      command = calloc(256, sizeof(char));
      snprintf(command, 250, "sudo insmod ./hello_module.ko");
      system(command);
	free(command);

      printf("<p><center>Modulo cargado exitosamente</center></p>");
      printf("<div style=\"display: flex; justify-content: center; margin-top: 20px\">\n");
      printf("<form action=\"../main.html\">\n");
      printf("<button class = \"modules-btn\">Back to main</button>\n");
      printf("</form>\n");
      printf("<form action=\"./modules.cgi\">\n");
      printf("<button class = \"modules-btn\">Go to insmoded modules</button>\n");
      printf("</form>\n");
      printf("</div>");
      
      printf("</body>");
      printf("</html>\n");
}//end main