# Grade Information

## Test 1: Compilation

No dead/leftover/unnecessary code should be highlighted here. [1 pts]

```
+ gcc -g -Wall climate.c -o climate
+ test_end
+ return=0
+ [Output Lines: 0]
```

## Test 2: No Args

Program should gracefully exit with no arguments [1 pts]

```
+ ./climate
Usage: ./climate tdv_file1 tdv_file2 ... tdv_fileN 
+ test_end
+ return=1
+ [Output Lines: 1]
```

## Test 3: Missing File

Program should gracefully exit and print an error message [1 pts]

```
+ ./climate this_file_should_not_exist.tdv
Error: : No such file or directory
+ test_end
+ return=0
+ [Output Lines: 1]
```

## Test 4: Use perror to report file errors

```
+ grep -A2 -B2 perror climate.c
        if(file == NULL)
        {
            perror("Error: "); // error handling using perror
            continue;
        }
+ test_end
+ return=0
+ [Output Lines: 5]
```

## Test 5: Use of memory allocation functions

```
+ grep -A2 -B2 .alloc climate.c
/*-----------------------------------------------------------------
 * Function:   Analyze File
 * Purpose:    Declares the num_states entry and initialize it using dynamic memory allocation.
 *             uses string function (strtok ) to tokenize the string line form the input file
 *             then uses cases to update the fields
--
--
    char *last_token;

    //loop through array structs to find state we wat-if doesnt exist, malloc
    //use ptr to struct to update stats
    while (fgets(line, line_sz, file) != NULL) {
--
--
}
void initialize_state(struct climate_info **states, int index){
    states[index] = malloc(sizeof(struct climate_info));
    states[index]->sum_humidity = 0;
    states[index]->sum_temperature = 0;
+ test_end
+ return=0
+ [Output Lines: 19]
```

## Test 6: Tennessee

```
+ ./climate ../../220/p1-files/data_tn.tdv
Opening file: ../../220/p1-files/data_tn.tdv
States found: TN 
-- State: TN -- 
Number of Records: 17097
Average Humidity: 49.4%
Average Temperature: 58.3F
Max Temperature: 110.4F on Mon Aug  3 11:00:00 2015
Min Temperature: -11.1F on Fri Feb 20 04:00:00 2015
Lightning Strikes: 781
Records with Snow Cover: 107
Average Cloud Cover: 53.0%

+ test_end
+ return=0
+ [Output Lines: 11]
```

## Test 7: Missing File + Valid File

Should still print data for TN [1 pts]

```
+ ./climate this_file_should_not_exist.tdv ../../220/p1-files/data_tn.tdv
Error: : No such file or directory
Opening file: ../../220/p1-files/data_tn.tdv
States found: TN 
-- State: TN -- 
Number of Records: 17097
Average Humidity: 49.4%
Average Temperature: 58.3F
Max Temperature: 110.4F on Mon Aug  3 11:00:00 2015
Min Temperature: -11.1F on Fri Feb 20 04:00:00 2015
Lightning Strikes: 781
Records with Snow Cover: 107
Average Cloud Cover: 53.0%

+ test_end
+ return=0
+ [Output Lines: 12]
```

## Test 8: Washington

```
+ ./climate ../../220/p1-files/data_wa.tdv
Opening file: ../../220/p1-files/data_wa.tdv
States found: WA 
-- State: WA -- 
Number of Records: 48357
Average Humidity: 61.3%
Average Temperature: 52.9F
Max Temperature: 125.7F on Sun Jun 28 17:00:00 2015
Min Temperature: -18.7F on Wed Dec 30 04:00:00 2015
Lightning Strikes: 1190
Records with Snow Cover: 1383
Average Cloud Cover: 54.5%

+ test_end
+ return=0
+ [Output Lines: 11]
```

## Test 9: Single state (WA) split across two files

This output should be the same as the previous test. [1 pts]

```
+ ./climate ../../220/p1-files/data_wa_1.tdv ../../220/p1-files/data_wa_2.tdv
Opening file: ../../220/p1-files/data_wa_1.tdv
Opening file: ../../220/p1-files/data_wa_2.tdv
States found: WA 
-- State: WA -- 
Number of Records: 48357
Average Humidity: 61.3%
Average Temperature: 52.9F
Max Temperature: 125.7F on Sun Jun 28 17:00:00 2015
Min Temperature: -18.7F on Wed Dec 30 04:00:00 2015
Lightning Strikes: 1190
Records with Snow Cover: 1383
Average Cloud Cover: 54.5%

+ test_end
+ return=0
+ [Output Lines: 12]
```

## Test 10: Tennessee + Washington

```
+ ./climate ../../220/p1-files/data_tn.tdv ../../220/p1-files/data_wa.tdv
Opening file: ../../220/p1-files/data_tn.tdv
Opening file: ../../220/p1-files/data_wa.tdv
States found: TN WA 
-- State: TN -- 
Number of Records: 17097
Average Humidity: 49.4%
Average Temperature: 58.3F
Max Temperature: 110.4F on Mon Aug  3 11:00:00 2015
Min Temperature: -11.1F on Fri Feb 20 04:00:00 2015
Lightning Strikes: 781
Records with Snow Cover: 107
Average Cloud Cover: 53.0%
-- State: WA -- 
Number of Records: 48357
Average Humidity: 61.3%
Average Temperature: 52.9F
Max Temperature: 125.7F on Sun Jun 28 17:00:00 2015
Min Temperature: -18.7F on Wed Dec 30 04:00:00 2015
Lightning Strikes: 1190
Records with Snow Cover: 1383
Average Cloud Cover: 54.5%

+ test_end
+ return=0
+ [Output Lines: 21]
```

## Test 11: Multi State

```
+ ./climate ../../220/p1-files/data_multi.tdv
Opening file: ../../220/p1-files/data_multi.tdv
States found: CA CO PA FL LA 
-- State: CA -- 
Number of Records: 84601
Average Humidity: 38.1%
Average Temperature: 62.1F
Max Temperature: 126.5F on Sat Aug 15 11:00:00 2015
Min Temperature: -25.9F on Tue Dec 15 04:00:00 2015
Lightning Strikes: 1616
Records with Snow Cover: 599
Average Cloud Cover: 34.7%
-- State: CO -- 
Number of Records: 67040
Average Humidity: 60.8%
Average Temperature: 49.6F
Max Temperature: 116.1F on Mon Jul 13 11:00:00 2015
Min Temperature: -29.8F on Sun Dec 27 04:00:00 2015
Lightning Strikes: 4763
Records with Snow Cover: 3082
Average Cloud Cover: 40.1%
-- State: PA -- 
Number of Records: 19526
Average Humidity: 57.4%
Average Temperature: 48.8F
Max Temperature: 106.4F on Fri Jun 12 11:00:00 2015
Min Temperature: -30.4F on Fri Feb 20 04:00:00 2015
Lightning Strikes: 667
Records with Snow Cover: 575
Average Cloud Cover: 59.2%
-- State: FL -- 
Number of Records: 35632
Average Humidity: 38.2%
Average Temperature: 76.1F
Max Temperature: 122.1F on Sun Jun 21 11:00:00 2015
Min Temperature: 21.9F on Thu Jan  8 04:00:00 2015
Lightning Strikes: 1436
Records with Snow Cover: 0
Average Cloud Cover: 39.1%
-- State: LA -- 
Number of Records: 23350
Average Humidity: 42.1%
Average Temperature: 69.0F
Max Temperature: 126.1F on Thu Jul 30 11:00:00 2015
Min Temperature: 19.6F on Wed Jan  7 22:00:00 2015
Lightning Strikes: 814
Records with Snow Cover: 0
Average Cloud Cover: 44.5%

+ test_end
+ return=0
+ [Output Lines: 47]
```

## Test 12: Multi State + TN + WA

```
+ ./climate ../../220/p1-files/data_multi.tdv ../../220/p1-files/data_tn.tdv ../../220/p1-files/data_wa.tdv
Opening file: ../../220/p1-files/data_multi.tdv
Opening file: ../../220/p1-files/data_tn.tdv
Opening file: ../../220/p1-files/data_wa.tdv
States found: CA CO PA FL LA TN WA 
-- State: CA -- 
Number of Records: 84601
Average Humidity: 38.1%
Average Temperature: 62.1F
Max Temperature: 126.5F on Sat Aug 15 11:00:00 2015
Min Temperature: -25.9F on Tue Dec 15 04:00:00 2015
Lightning Strikes: 1616
Records with Snow Cover: 599
Average Cloud Cover: 34.7%
-- State: CO -- 
Number of Records: 67040
Average Humidity: 60.8%
Average Temperature: 49.6F
Max Temperature: 116.1F on Mon Jul 13 11:00:00 2015
Min Temperature: -29.8F on Sun Dec 27 04:00:00 2015
Lightning Strikes: 4763
Records with Snow Cover: 3082
Average Cloud Cover: 40.1%
-- State: PA -- 
Number of Records: 19526
Average Humidity: 57.4%
Average Temperature: 48.8F
Max Temperature: 106.4F on Fri Jun 12 11:00:00 2015
Min Temperature: -30.4F on Fri Feb 20 04:00:00 2015
Lightning Strikes: 667
Records with Snow Cover: 575
Average Cloud Cover: 59.2%
-- State: FL -- 
Number of Records: 35632
Average Humidity: 38.2%
Average Temperature: 76.1F
Max Temperature: 122.1F on Sun Jun 21 11:00:00 2015
Min Temperature: 21.9F on Thu Jan  8 04:00:00 2015
Lightning Strikes: 1436
Records with Snow Cover: 0
Average Cloud Cover: 39.1%
-- State: LA -- 
Number of Records: 23350
Average Humidity: 42.1%
Average Temperature: 69.0F
Max Temperature: 126.1F on Thu Jul 30 11:00:00 2015
Min Temperature: 19.6F on Wed Jan  7 22:00:00 2015
Lightning Strikes: 814
Records with Snow Cover: 0
Average Cloud Cover: 44.5%
-- State: TN -- 
Number of Records: 17097
Average Humidity: 49.4%
Average Temperature: 58.3F
Max Temperature: 110.4F on Mon Aug  3 11:00:00 2015
Min Temperature: -11.1F on Fri Feb 20 04:00:00 2015
Lightning Strikes: 781
Records with Snow Cover: 107
Average Cloud Cover: 53.0%
-- State: WA -- 
Number of Records: 48357
Average Humidity: 61.3%
Average Temperature: 52.9F
Max Temperature: 125.7F on Sun Jun 28 17:00:00 2015
Min Temperature: -18.7F on Wed Dec 30 04:00:00 2015
Lightning Strikes: 1190
Records with Snow Cover: 1383
Average Cloud Cover: 54.5%

+ test_end
+ return=0
+ [Output Lines: 67]
```

## Test 13: File with all Zero Values

```
+ ./climate ../../220/p1-files/data_blank.tdv
Opening file: ../../220/p1-files/data_blank.tdv
States found: TX 
-- State: TX -- 
Number of Records: 14
Average Humidity: 0.0%
Average Temperature: -459.7F
Max Temperature: -1.0F on Min Temperature: -459.7F on Wed Dec 31 16:00:00 1969
Lightning Strikes: 0
Records with Snow Cover: 0
Average Cloud Cover: 0.0%

+ test_end
+ return=0
+ [Output Lines: 10]
```

## Test 14: 3x Tennessee

```
+ ./climate ../../220/p1-files/data_tn.tdv ../../220/p1-files/data_tn.tdv ../../220/p1-files/data_tn.tdv
Opening file: ../../220/p1-files/data_tn.tdv
Opening file: ../../220/p1-files/data_tn.tdv
Opening file: ../../220/p1-files/data_tn.tdv
States found: TN 
-- State: TN -- 
Number of Records: 51291
Average Humidity: 49.4%
Average Temperature: 58.3F
Max Temperature: 110.4F on Mon Aug  3 11:00:00 2015
Min Temperature: -11.1F on Fri Feb 20 04:00:00 2015
Lightning Strikes: 2343
Records with Snow Cover: 321
Average Cloud Cover: 53.0%

+ test_end
+ return=0
+ [Output Lines: 13]
```


## Deductions

* Awesome work!!
