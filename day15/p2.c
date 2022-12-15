#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
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

void draw_sensors(int sensors[S_LEN][2], int min_range[S_LEN], int count){
  char matrix[20][20]={0};
  int tmp[2];

  for(int j=0;j<20;j++){
    tmp[1] = j;
    for(int i=0;i<20;i++){
      tmp[0] = i;
      matrix[j][i]='0';
      for (int c=0;c<count;c++){
        if (manhatten_dist(sensors[c], tmp)<=min_range[c]){
          matrix[j][i]=c+48;
          break;
        }
      }
    }
  }
  for(int j=0;j<20;j++){
    for(int i=0;i<20;i++){
      printf("%c", matrix[j][i]);
    }
    printf("\n");
  }
  
}

bool outside_bounds(int point[2], int end_max){
  if (point[0] <0 || point[0]> end_max+1||point[1]<0||point[1]>end_max+1){
    return true;
  }
  return false;
}

bool invalid(int sensors[S_LEN][2], int min_range[S_LEN], int point[2], int count){
  for (int k=0; k<count; k++){
    if(manhatten_dist(sensors[k], point)<= min_range[k]){
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
  while(true){
    cap = scanf("Sensor at x=%d, y=%d: ", &sensors[count][0], &sensors[count][1]);
    if (cap!=2){
      break;
    }
    scanf("closest beacon is at x=%d, y=%d ", &beacons[count][0], &beacons[count][1]);
    min_range[count] = manhatten_dist(sensors[count], beacons[count]);
    count++;
  }
  for (int i=0;i<count; i++){
    printf("s: %d, %d\tb: %d, %d\n", sensors[i][0], sensors[i][1], beacons[i][0], beacons[i][1]);
    printf("md: %d\n", manhatten_dist(sensors[i], beacons[i]));
  }


  int tmp_pos[2];
  int end_max=4000000;
  //int end_max=20;


  //instead of skipping each line can I find only the edges of all sensor points and search those?
  for (int c=0; c< count; c++){
  //one point above
    //printf("%d, %d\n",  sensors[c][0], sensors[c][1]);
    //printf("----\n");
    tmp_pos[0] = sensors[c][0];
    tmp_pos[1] = sensors[c][1]-min_range[c]-1;
    //printf("%d, %d\n",  tmp_pos[0], tmp_pos[1]);
    if(!invalid(sensors, min_range, tmp_pos, count)){
      if (!outside_bounds(tmp_pos, end_max)){
        goto end;
      }
    }
  //diagonals down the sides until y
    tmp_pos[1]++;
    tmp_pos[0]--;
    int diag = 0;
    while(tmp_pos[1]!=sensors[c][1]+1){
      //printf("%d, %d\n",  tmp_pos[0], tmp_pos[1]);
      diag++;
      if(!invalid(sensors, min_range, tmp_pos, count)){
        if (!outside_bounds(tmp_pos, end_max)){
          goto end;
        }
      }
      tmp_pos[0]++;
      tmp_pos[0] += diag;
      //printf("%d, %d\n",  tmp_pos[0], tmp_pos[1]);
      if(!invalid(sensors, min_range,tmp_pos, count)){
        if (!outside_bounds(tmp_pos, end_max)){
          goto end;
        }
      }
      tmp_pos[0] -= (1+diag);
      tmp_pos[1]++;
    }
  //diagonals down the sides until y+range
   while(tmp_pos[1]!=sensors[c][1]+min_range[c]+1){
      diag--;
      //printf("%d, %d\n",  tmp_pos[0], tmp_pos[1]);
      if(!invalid(sensors, min_range, tmp_pos, count)){
        if (!outside_bounds(tmp_pos, end_max)){
          goto end;
        }
      }
      tmp_pos[0]++;
      tmp_pos[0] += diag;
      //printf("%d, %d\n",  tmp_pos[0], tmp_pos[1]);
      if(!invalid(sensors, min_range,tmp_pos, count)){
        if (!outside_bounds(tmp_pos, end_max)){
          goto end;
        }
      }
      tmp_pos[0] -= (1+diag);
      tmp_pos[1]++;
   }
  //one point below
    tmp_pos[0] = sensors[c][0];
    tmp_pos[1] = sensors[c][1]+min_range[c]+1;
    //printf("%d, %d\n",  tmp_pos[0], tmp_pos[1]);
    if(!invalid(sensors, min_range, tmp_pos, count)){
      if (!outside_bounds(tmp_pos, end_max)){
        goto end;
      }
    }
    //printf("----\n");
    //printf("----\n");
  }
end:
  printf("%d, %d\n", tmp_pos[0], tmp_pos[1]);
  printf("%"PRId64"\n", (uint64_t)tmp_pos[0]*4000000+(uint64_t)tmp_pos[1]);
  //draw_sensors(sensors, min_range, count);
}
