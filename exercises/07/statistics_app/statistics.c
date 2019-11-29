#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>


#define BUFFER_SIZE BUFSIZ /* or some other number */
static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}


int line_count[16];
float avg_line_latency[16];
float max_line_latency[16];

void increment_statistics(char* origbuffer) {
    char buffer[BUFFER_SIZE];
    strcpy (buffer, origbuffer);
    if(buffer != NULL) {
        int line, latency, timestamp;
        int field_count = 0;

        char *field = strtok(buffer,",");
        line = atoi(field);
        field = strtok(NULL, ",");
        latency = atoi(field);

        // printf("line: %d latecy:%d\n",line,latency); 
        // printf(buffer);
        line_count[line]++;
        if(avg_line_latency[line] == 0) {
            avg_line_latency[line] = latency;
        } else {
            avg_line_latency[line] = (avg_line_latency[line] + latency)/2;
        }
        if(max_line_latency[line] < latency) {
            max_line_latency[line] = latency;
        }
    }
}


int main(int argc, const char **argv) {

    signal(SIGINT, intHandler);
    char stdin_buf[BUFFER_SIZE];
    char stdout_buf[BUFFER_SIZE];
    char *cur_string;
    cur_string = fgets(stdin_buf, BUFSIZ, stdin);
    while (keepRunning) {
        if(cur_string != NULL)// printf(stdin_buf);
            increment_statistics(stdin_buf);
        cur_string = fgets(stdin_buf, BUFSIZ, stdin);
    }
    for(int i = 0; i<16; i++)
    {
        if(line_count[i] != 0) {
            printf("%d,%d,%.3f,%.3f\n", i, line_count[i], avg_line_latency[i],max_line_latency[i]);
        }
    }
    return 0;    
}
