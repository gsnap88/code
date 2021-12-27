#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct {
    int hour;
    int minute;
    int second;
} t;
typedef struct {
    int year;
    int month;
    int day;
} d;
typedef struct {
    d date;
    t time;
    int precip;
    float temp;
    int snow_water;
    float snow_depth;
} data;



int main(){

    FILE* weatherdata = fopen("weatherdata.txt", "r"); //check if the file opens properly
    if(!weatherdata){
        printf("Error opening file.\n");
    }
    else{
        printf("File successfully opened.\n");
    }

    char line[1024]; //get to the right line in the file
    for(int i = 0; i < 10; i++){
    fgets(line, sizeof line, weatherdata);
    }
    
    data last_date; //acquire the last date (first on the list mind you i was confused too)
    fgets(line, sizeof line, weatherdata);
    for(int j = 0; j <= (sizeof line); j++){
                    if(isdigit(line[j]) == 0 && line[j] != '.' && line[j] != '-'){
                        line[j] = ' ';
                    }
            }
    sscanf(line, "%d %d %d %d %d %d %d %f %d %f", &last_date.date.year, &last_date.date.month, &last_date.date.day, &last_date.time.hour, &last_date.time.minute,
            &last_date.time.second, &last_date.precip, &last_date.temp, &last_date.snow_water, &last_date.snow_depth);

    data temp; //go thru all the values
    int i;
    data max_temp;
        max_temp.temp = -273;
    data min_temp;
        min_temp.temp = 100;
    for(i = 1; fgets(line, sizeof line, weatherdata) != NULL; i++){
            for(int j = 0; j <= (sizeof line); j++){
                    if(isdigit(line[j]) == 0 && line[j] != '.'&& line[j] != '-'){
                        line[j] = ' ';
                    }
            }
            sscanf(line, "%d %d %d %d %d %d %d %f %d %f", &temp.date.year, &temp.date.month, &temp.date.day, &temp.time.hour, &temp.time.minute,
            &temp.time.second, &temp.precip, &temp.temp, &temp.snow_water, &temp.snow_depth);
            if(temp.temp < min_temp.temp){
                min_temp = temp;
            }
            if(temp.temp > max_temp.temp){
                max_temp = temp;
            }

    }

    float change_snow = last_date.snow_depth - temp.snow_depth; //calculate some shit we wanna print
    d change_date;
    t change_time;
    change_date.year = last_date.date.year - temp.date.year;
    change_date.month = last_date.date.month - temp.date.month;
    change_date.day = last_date.date.day - temp.date.day;
    if(change_date.month < 0){
        change_date.month=+12;
    }
    if(change_date.day < 0){
        if(temp.date.month == 1 || 3 || 5 || 7 || 8 || 10 || 12){
        change_date.day=+31; 
        }
        if(temp.date.month == 4 || 6 || 9 || 11){
            change_date.day=+30;
        }
        if(change_date.month == 2){
        change_date.day=+28;
        }
    }
    change_time.hour = last_date.time.hour - temp.time.hour;
    change_time.minute = last_date.time.minute - temp.time.minute;
    change_time.second = last_date.time.second - temp.time.second;
    if(change_time.hour < 0){
        change_time.hour=+24;
    }
    if(change_time.minute < 0){
        change_time.minute=+60;
    }
    if(change_time.second < 0){
        change_time.second=+60;
    }

    printf("BC Hydro Weather Data for Powder King Ski Resort\n"); //print what we want
    printf("%d values were read\n", i);
    printf("Data collected spans %d years, %d months, %d days, %d hours, %d minutes and %d seconds\n",change_date.year, change_date.month, change_date.day, change_time.hour, change_time.minute,
            change_time.second);
    printf("Maximum temperature was %.1f measured at %.2d:%.2d:%.2d on %d/%d/%d\n",max_temp.temp, max_temp.time.hour, max_temp.time.minute, 
    max_temp.time.second, max_temp.date.year, max_temp.date.month, max_temp.date.day);
    printf("Minimum temperature was %.1f measured at %.2d:%.2d:%.2d on %d/%d/%d\n",min_temp.temp, min_temp.time.hour, min_temp.time.minute, 
    min_temp.time.second, min_temp.date.year, min_temp.date.month, min_temp.date.day);
    printf("The snow pack has changed by %.2f cm\n", change_snow);

    fclose(weatherdata); //concierge
    return 0;
}


