#include "fb.h"
#include "clib/string.h"

int *map;

#define MAX_PAGES 100 //Not sure about this value
#define PAGE_SIZE 4096

unsigned long starting; //The starting address
unsigned long ending; //The ending address
unsigned long length;


unsigned long malloc_page(unsigned long size){
  unsigned long address = 0;
  unsigned long i = 0;

  //Start out by finding how many segments we need
  int segments = size / PAGE_SIZE;
  //If we need 2.1 segments, we have to address 3
  float seg_remainder = size % PAGE_SIZE;
  if(seg_remainder != 0){
    segments++;
  }

  int found = 0;
  while(found == 0 && i < length){
    int possible = 1; //Weather this i will work
    if(segments > 1){
      //Check to make sure we don't assign to past our map
      if(i+segments > length){
        possible = 0;
      }
      //Check to see this free space has enough open segments
      int segment;
      for(segment = 0; segment < segments; segment++){
        if(possible == 1){
          possible = (map[segment+i] == 0);
        }
      }
    } else {
      possible = (map[i] == 0);
    }


    if(possible){
      //We found a match for all the segments
      //We need to loop through everone and set the value
      //For every segment we set bit 2 to 1
      //The last segment we set bit 2 to 0
      //For example: segment1(inital): 11, segment2: 11, segment3(last): 0,1
      //That way we can free every segment
      if(segments){
        int segment;
        for(segment = 0; segment < segments; segment++){
          map[segment+i] = 11;
          if((segment-1) == segments){
            //The last segment, set the last bit to 0
            map[segment+i] = 10;
          }
        }
      }else {
        map[i] = 10;
      }

      found = 1;
      address = starting+(i*PAGE_SIZE);
    }
    i += segments;
  }
  if(found == 0){
    fb_write("Out of Memory!! \n");
  }
  return address;
}



void free_page(unsigned long address){
  unsigned long i = (address-starting)/PAGE_SIZE;
  if(map[i] == 11){
    //This a multi segment allocation
    //Set every segment to 0 until we hit the last segment (10)
    unsigned long segment = 0;
    while(map[segment+i] != 10){
       map[segment+i] = 0;
       segment++;
    }
    //The loop above only sets up UNTIL it hits 10
    //We also need to set the final to 0
    map[segment+i] = 0;

  }else {
    map[i] = 0;
  }
}


/**
 * This function tests several aspects of malloc_page/free_page
 * It's run on kernel startup to make sure I haven't broken anything
 * It doesn't end up making any garabge and takes very little time to run
 * @return If the tests passed
 */
int test_alloc(){
    int passed = 1;

    //Small test
    char test = 'T';
    unsigned long a = malloc_page(PAGE_SIZE);

    memcpy(&test, (void *)a, 1);
    char check;
    memcpy(&check, (void *)a, 1);

    unsigned long b = malloc_page(PAGE_SIZE);


    free_page(a);
    free_page(b);

    if(passed == 1){
      passed = (a == starting && b == (starting+PAGE_SIZE) && check == test);
    }

    //Free test
    unsigned long c = malloc_page(PAGE_SIZE);
    free_page(c);
    if(passed == 1){
      passed = (c == starting);
    }

    //Large malloc_page test
    unsigned long d = malloc_page(PAGE_SIZE*2);
    unsigned long e = malloc_page(PAGE_SIZE);

    free_page(d);
    free_page(e);

    if(passed == 1){
      passed = (d == starting && e == (starting+(2*PAGE_SIZE)));
    }



    //Large free_page tests
    unsigned long f = malloc_page(PAGE_SIZE*2);
    free_page(f);
    if(passed == 1){
      passed = (f == starting);
    }

    //Overflow test
    //Not run since it takes a lot of CPU time
    //Only run when making LARGE change
    /*unsigned long g = malloc_page(length*PAGE_SIZE); //Fill all memory
    unsigned long h = malloc_page(PAGE_SIZE*2); //Try to get two more pages

      if(passed == 1){
       passed = (g == starting && h == 0); //Make sure it didn't address
      }
    free_page(g);

    //Edge case
    //Not run since it takes a lot of CPU time
    //Only run when making LARGE Change
    unsigned long i = malloc_page((length-1)*PAGE_SIZE);
    unsigned long j = malloc_page(PAGE_SIZE*2);

    if(passed == 1){
      passed = (i == starting && j == 0);
    } */

    return passed;
}

/**
 * Initalize the MM system
 * @param  starting_address The address where the memory starts
 * @return                  Weather the MM tests pass
 */
int MM_init(unsigned long starting_address){
  starting = starting_address;
  length = MAX_PAGES;

  //Start out by setting up the map setting every address to zero
  unsigned long i;
  for(i = 0; i < length; i++){
    map[i] = 0;
  }

  return test_alloc();

}
