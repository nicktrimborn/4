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
int max_line_latency[16];

void increment_statistics(char* origbuffer) {
    char buffer[60];
    strcpy (buffer, origbuffer);
    if(buffer != NULL) {
        int line, latency, timestamp;
        int field_count = 0;
        //extract csv fields
        char *field = strtok(buffer,",");
        line = atoi(field);
        field = strtok(NULL, ",");
        latency = atoi(field);

        //Increment interupt count for each line
        line_count[line]++;
        // Compute average CMA https://en.wikipedia.org/wiki/Moving_average
        if(avg_line_latency[line] == 0.0) {
            avg_line_latency[line] = latency;
        } else {
            avg_line_latency[line] = (latency + (avg_line_latency[line]*(line_count[line]-1)))
                                        / line_count[line];
        }
        // Store maximum latency
        if(max_line_latency[line] < latency) {
            max_line_latency[line] = latency;
        }
    }
}


int main(int argc, const char **argv) {

    printf("Statistics application Running, end with ctrl+c\n");
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

    int total_int = 0;
    int num_to_average = 0;
    float running_average = 0;
    int max_latency = 0;

    // Summary statistics loop
    for(int i = 0; i<16; i++)
    {
        // Print relevant line interrupts
        if(line_count[i] != 0) {
            printf("%d,%d,%.2f,%d\n", i, line_count[i], avg_line_latency[i], max_line_latency[i]);
        }
        // Print total stats    
        total_int += line_count[i];
        if(avg_line_latency[i] > 0.0) {
            num_to_average++;
            running_average += avg_line_latency[i];
        }
        // Max Latency Calc 
        if(max_line_latency[i] > max_latency) {
            max_latency = max_line_latency[i];
        }
    }
    // Print line independent statistics
    printf("%d,%d,%.2f,%d\n", -1, total_int, (float)(running_average/num_to_average), max_latency);
    return 0;    
}
