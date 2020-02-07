#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

int main()
{
printf("Content-type: text/html\n\n");
printf("<html>\n");
printf("<head>\n");
printf("<title>TP3 - Sistemas Operativos II</title>\n");
printf("<link rel=\"stylesheet\" href=\"../styles.css\">");  
printf("<link href=\"https://fonts.googleapis.com/css?family=Roboto&display=swap\" rel=\"stylesheet\">\n");
printf("</head\n");
printf("<body>\n");
printf("<header class=\"other-header\">\n");
printf("<h1>Recursos</h1>\n");
printf("</header>\n");

/* Get the uptime from /proc/uptime */
FILE *fp;
fp = fopen("/proc/uptime", "r");
char buff[3500];
fread(buff, 3500, 1, fp);
fclose(fp);

long uptime;
char *ptr;
uptime = strtol(buff, &ptr, 10);


/* Get actual date and time */
time_t t = time(NULL);
struct tm *tm = localtime(&t);
char today[64];
assert(strftime(today, sizeof(today), "%c", tm));


/* Print statics */
memset(buff, '\0', 3500);
printf("<div class = \"other-section\">\n");

//Uptime:
printf("<p><b>The system uptime is: </b> %d days, %02d:%02d:%02d</p>\n", (uptime / 60 / 60 / 24), (uptime / 60 / 60 % 24), (uptime / 60 % 60), (uptime % 60));
///////////////////////////////////////////////////////////////

//Actual time:
printf("<p><b>Actual date and time is: </b> %s</p>\n", today);
///////////////////////////////////////////////////////////////

//Memory stats:
printf("<p><b>Memory Stats: </b></p>\n");

char *cmd = "grep Mem /proc/meminfo";
FILE *cmdfile = popen(cmd, "r");
char str1[20], str2[20], str3[20], str4[20], str5[20], str6[20];
long memTot, memFree, memAv;

fscanf(cmdfile, "%s %ld %s %s %ld %s %s %ld %s", str1, &memTot, str2, str3, &memFree, str4, str5, &memAv, str6);
printf("<ul> <li> %s %ld %s</li> <li> %s %ld %s</li> <li> %s %ld %s</li></ul>", str1, &memTot, str2, str3, &memFree, str4, str5, &memAv, str6);
pclose(cmdfile);
///////////////////////////////////////////////////////////////

//CPU stats:
printf("<p><b>CPU Stats: </p></b>\n");
char *cmd2 = "cat /proc/cpuinfo | grep \"model name\"";
FILE *cmdfile2 = popen(cmd2, "r");

char *cmd3 = "cat /proc/top";
FILE *cmdfile3 = popen(cmd3, "r");

char str7[20], str8[20], str9[20], str10[20], str11[20], str12[20], str13[20], str14[20],str15[20];
fscanf(cmdfile2, "%s %s %s %s %s %s %s %s %s ", str7, str8, str9, str10, str11, str12, str13, str14, str15);

char oneMin[20];
fscanf(cmdfile3, "%s id,", oneMin); 
printf("<ul><li>Model Name: %s %s %s %s %s %s %s</li><li>Load Average: %d</li></ul>", str9, str10, str11, str12, str13, str14, str15, oneMin);


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

