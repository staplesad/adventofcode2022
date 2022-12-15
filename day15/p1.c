#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define S_LEN 40

int manhatten_dist(int x[2], int y[2]){
  return abs(y[0]-x[0])+ abs(y[1]-x[1]);
}

bool check_beacon(int beacons[S_LEN][2], int z[2], int count){
  for (int i =0; i< count; i++){
    if (beacons[i][0]==z[0] && beacons[i][1]==z[1]){
      return true;
    }
  }
  return false;
}

int main(void){
  int sensors[S_LEN][2];
  int beacons[S_LEN][2];
  int min_range[S_LEN];
  int count = 0;
  int cap;
  int min_x = 0;
  int max_x = 0;
  int max_range = 0;
  while(true){
    cap = scanf("Sensor at x=%d, y=%d: ", &sensors[count][0], &sensors[count][1]);
    if (sensors[count][0] < min_x){
      min_x = sensors[count][0];
    }
    else if(sensors[count][0] > max_x){
      max_x = sensors[count][0];
    }
    if (cap!=2){
      break;
    }
    scanf("closest beacon is at x=%d, y=%d ", &beacons[count][0], &beacons[count][1]);
    if (beacons[count][0] < min_x){
      min_x = beacons[count][0];
    }
    else if(beacons[count][0] > max_x){
      max_x = beacons[count][0];
    }
    min_range[count] = manhatten_dist(sensors[count], beacons[count]);
    if (min_range[count] > max_range){
      max_range=min_range[count];
    }
    count++;
  }
  for (int i=0;i<count; i++){
    printf("s: %d, %d\tb: %d, %d\n", sensors[i][0], sensors[i][1], beacons[i][0], beacons[i][1]);
    printf("md: %d\n", manhatten_dist(sensors[i], beacons[i]));
  }


  int confirm_row = 2000000;
  int invalid_pos = 0;
  int tmp_pos[2];
  tmp_pos[1] = confirm_row;
  for (int i=min_x-max_range; i< max_x+max_range+1; i++){
    tmp_pos[0] = i;
    if (check_beacon(beacons, tmp_pos, count)){
      continue;
    };
    for (int c=0; c< count; c++){
      if(manhatten_dist(sensors[c], tmp_pos)<=min_range[c]){
        //printf("%d, %d, s: %d\n", tmp_pos[0], tmp_pos[1], c);
        invalid_pos++;
        break;
      }
    }
  }
  printf("%d\n", invalid_pos);
}
