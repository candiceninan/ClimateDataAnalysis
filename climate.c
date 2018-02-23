/**
 * climate.c
 *
 * Performs analysis on climate data provided by the
 * National Oceanic and Atmospheric Administration (NOAA).
 *
 * Input:    Tab-delimited file(s) to analyze.
 * Output:   Summary information about the data.
 *
 * Compile:  gcc -g -Wall -o climate climate.c
 *           (or run make)
 *
 * Run:      ./climate data_tn.tdv data_wa.tdv
 *
 *
 * Opening file: data_tn.tdv
 * Opening file: data_wa.tdv
 * States found: TN WA
 * -- State: TN --
 * Number of Records: 17097
 * Average Humidity: 49.4%
 * Average Temperature: 58.3F
 * Max Temperature: 110.4F on Mon Aug  3 11:00:00 2015
 * Min Temperature: -11.1F on Fri Feb 20 04:00:00 2015
 * Lightning Strikes: 781
 * Records with Snow Cover: 107
 * Average Cloud Cover: 53.0%
 * -- State: WA --
 * Number of Records: 48357
 * Average Humidity: 61.3%
 * Average Temperature: 52.9F
 * Max Temperature: 125.7F on Sun Jun 28 17:00:00 2015
 * Min Temperature: -18.7F on Wed Dec 30 04:00:00 2015
 * Lightning Strikes: 1190
 * Records with Snow Cover: 1383
 * Average Cloud Cover: 54.5%
 *
 * TDV format:
 *
 * CA 1428300000000 9prc 93.0 0.0 100.0 0.0 95644.0  277.58716
 * CA 1430308800000 9prc 4.0  0.0 100.0 0.0 99226.0  282.63037
 * CA 1428559200000 9prr 61.0 0.0 0.0   0.0 102112.0 285.07513
 * CA 1428192000000 9prk 57.0 0.0 100.0 0.0 101765.0 285.21332
 * CA 1428170400000 9prd 73.0 0.0 22.0  0.0 102074.0 285.10425
 * CA 1429768800000 9pr6 38.0 0.0 0.0   0.0 101679.0 283.9342
 * CA 1428127200000 9prj 98.0 0.0 100.0 0.0 102343.0 285.75
 * CA 1428408000000 9pr4 93.0 0.0 100.0 0.0 100645.0 285.82413
 *
 * Each field is separated by a tab character \t and ends with a newline \n.
 *
 * Fields:
 *      state code (e.g., CA, TX, etc),
 *      timestamp (time of observation as a UNIX timestamp),
 *      geolocation (geohash string),
 *      humidity (0 - 100%),
 *      snow (1 = snow present, 0 = no snow),
 *      cloud cover (0 - 100%),
 *      lightning strikes (1 = lightning strike, 0 = no lightning),
 *      pressure (Pa),
 *      surface temperature (Kelvin)
 */

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_STATES 50

struct climate_info {
    char code[3];
    unsigned long num_records;
    double sum_temperature, sum_humidity;
    double max_temp , min_temp;
    char time_max_temp[30], time_min_temp[30];
    unsigned long lightning_strikes, records_with_snow_cover;
    double sum_cloud_cover;
};

/* Function prototypes */
void analyze_file(FILE *file, struct climate_info *states[], int num_states, int *state_index);
void print_report(struct climate_info *states[], int num_states);
void initialize_state(struct climate_info *states[],int state_index);

int main(int argc, char *argv[]) {

    if (argc == 1) { // if no file given then show error else it will support multiple files
        printf("Usage: %s tdv_file1 tdv_file2 ... tdv_fileN \n", argv[0]);
        return EXIT_FAILURE;
    }
    /* Create an array to store our state data in. As we know, there are
     * 50 US states. */
    struct climate_info *states[NUM_STATES] = { NULL };

    FILE *file;
    int i;
    int flag = 0;
    int state_index = -1;
    //open files
    for (i = 1; i < argc; ++i) {
        file = fopen(argv[i] , "r");
        if(file == NULL)
        {
            perror("Error: "); // error handling using perror
            continue;
        }
        flag = 1;
        printf("Opening file: %s\n",argv[i]);
        analyze_file(file, states, NUM_STATES, &state_index);   
    }

    /* Now that we have recorded data for each file, we'll summarize them: */
    if(flag) // if flag = 0 , no information to print. 
        print_report(states, NUM_STATES);

    return 0;
}
/*-----------------------------------------------------------------
 * Function:   Analyze File
 * Purpose:    Declares the num_states entry and initialize it using dynamic memory allocation.
 *             uses string function (strtok ) to tokenize the string line form the input file
 *             then uses cases to update the fields
 * Input args: File name, array of struct climate_info , num_states (0-49, since 50 states)
 * Return val: Updates each value for the different states
 */

void analyze_file(FILE *file, struct climate_info **states, int num_states, int *state_index) {
    int i;
    const int line_sz = 100;
    char line[line_sz];
    char *last_token;

    //loop through array structs to find state we wat-if doesnt exist, malloc
    //use ptr to struct to update stats
    while (fgets(line, line_sz, file) != NULL) {
        //int len = strlen(line);
        last_token  = strtok(line,"\t");
        int token_id = 0;
        char temp_time[30];
        while(last_token != NULL)
        {
         //   printf("%s\n", last_token);
            switch(token_id)
            {
                case 0:
                    //state code
                    {
                        for(i = 0; i < num_states ; i++){
                            if(states[i] != NULL){
                                if(strcmp(states[i]->code, last_token) == 0){
                                    *(state_index) = i;
                                    break;
                                }
                            }
                        }
                        if(i == num_states){
                            *(state_index) = *(state_index)+1;
                            initialize_state(states,*(state_index));
                        }
                        states[*(state_index)]->num_records++;
                        strcpy(states[*(state_index)]->code,last_token);
                        break;
                    }
                case 1:
                    // timestamp
                    {
                        long long tempt = atoll(last_token);;
                        tempt /= 1000;
                        time_t _time = tempt;
                        strcpy(temp_time,ctime(&_time));
                        break;
                    }
                case 2:
                    break;
                case 3:
                    // Humidity
                    {
                        states[*(state_index)]->sum_humidity += atof(last_token);
                        break;
                    }
                case 4:
                    // snow
                    {
                        states[*(state_index)]->records_with_snow_cover += atoll(last_token);
                        break;
                    }
                case 5:
                    //cloud cover
                    {
                        states[*(state_index)]->sum_cloud_cover += atoll(last_token);
                        break;
                    }
                case 6:
                    //Lightning strikes
                    {
                        states[*(state_index)]->lightning_strikes += atoll(last_token);
                        break;
                    }
                case 7:
                    //pressure
                    {
                        // Not needed
                        break;
                    }
                case 8:
                    // temprature
                    {
                        double def_k = atof(last_token);
                        // conversion from Kelvin (K) to Fahrenheit (F).
                        double deg_f = def_k*1.8 - 459.67;
                        states[*(state_index)]->sum_temperature += deg_f;
                        if(deg_f < states[*(state_index)]->min_temp)
                        {
                            states[*(state_index)]->min_temp = deg_f;
                            strcpy(states[*(state_index)]->time_min_temp,temp_time);
                        }
                        if(deg_f > states[*(state_index)]->max_temp)
                        {
                            states[*(state_index)]->max_temp = deg_f;
                            strcpy(states[*(state_index)]->time_max_temp,temp_time);
                        }
                        break;
                    }
                default:
                    break;
            }
            last_token = strtok(NULL,"\t");
            token_id++;
        }
    }
}
/*-----------------------------------------------------------------
 * Function:   Print Report
 * Purpose:    Prints the information from the struct array of climate_info.
 *             Loop to find how many states have been filled and then printing its computed information.
 *
 *             Prints for the given state , the following information:
 *             Number of Records:
 *             Average Humidity:
 *             Average Temperature:
 *             Max Temperature:
 *             Min Temperature:
 *             Lightning Strikes:
 *             Records  with Snow Cover:
 *             Average Cloud Cover:
 * Input args: Array of struct climate_info , num_states (0-49, since 50 states)
 * Return val: Prints each of the values for the different states
 */
void print_report(struct climate_info *states[], int num_states) {
    printf("States found: ");
    int i;
    for (i = 0; i < num_states; ++i) {
        if(states[i] != NULL)
        {
          printf("%s ",states[i]->code);    
        }
        if(i == num_states-1)
            printf("\n");
    }
    for (i = 0; i < num_states; ++i) {
        if (states[i] != NULL) {
            struct climate_info *info = states[i];
            printf("-- State: %s -- \n", info->code);
            unsigned long n = states[i]->num_records;
            char ch = '%';
            printf("Number of Records: %lu\n",states[i]->num_records);
            printf("Average Humidity: %.1lf%c\n",(states[i]->sum_humidity / n),ch);
            printf("Average Temperature: %.1lfF\n",(states[i]->sum_temperature / n));
            printf("Max Temperature: %.1lfF on %s",states[i]->max_temp,states[i]->time_max_temp);
            printf("Min Temperature: %.1lfF on %s",states[i]->min_temp,states[i]->time_min_temp);
            printf("Lightning Strikes: %lu\n",states[i]->lightning_strikes);
            printf("Records with Snow Cover: %lu\n",states[i]->records_with_snow_cover);
            printf("Average Cloud Cover: %.1lf%c\n",(states[i]->sum_cloud_cover / n),ch);
        }
    }
    printf("\n");
}
void initialize_state(struct climate_info **states, int index){
    states[index] = malloc(sizeof(struct climate_info));
    states[index]->sum_humidity = 0;
    states[index]->sum_temperature = 0;
    states[index]->records_with_snow_cover = 0;
    states[index]->sum_cloud_cover = 0;
    states[index]->lightning_strikes = 0;
    states[index]->num_records = 0;
    states[index]->max_temp = -1;
    states[index]->min_temp = 4000;
}
