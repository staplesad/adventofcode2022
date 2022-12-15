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
          matrix[j][i]='#';
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


  //reverse sensor lookup -> skip larger chunks of searchspace?
  //
  int tmp_pos[2];
  int c =0;
  int end_max=4000000;
  //int end_max=20;
  int y_diff;
  int x_diff;
  int skip_y;
  int m_dist;

  //skip sensors once we're past range?
  //would have to sort sensors/beacons first
  int c_start=0;
  for (int j=0; j<end_max+1; j++){
    tmp_pos[1] = j;
    if(j%1000==0){
      printf("at j: %d\n", j);
    }
    for (int i=0; i<end_max+1; i++){
      tmp_pos[0] = i;
      for (c=c_start; c< count; c++){
        m_dist = manhatten_dist(sensors[c], tmp_pos);
        if(m_dist <= min_range[c]){
//          printf("i, j: %d, %d\n", i, j);
          y_diff  = abs(tmp_pos[1]-sensors[c][1]);
          x_diff = sensors[c][0]-tmp_pos[0];
          skip_y = m_dist + x_diff - y_diff;
          i += skip_y;
//          printf("min_range: %d\n", min_range[c]);
//          printf("diffs: %d, %d\tskip_x: %d\tnew_i: %d\n", x_diff, y_diff, skip_y, i+1);
          break;
        }
      }
      if (c==count){
        if (check_beacon(beacons, tmp_pos, count)){
          continue;
        };
        printf("%d, %d, s: %d\n", tmp_pos[0], tmp_pos[1], c);
        goto end;
      }
    }
  }
  end:
    printf("%d\n", tmp_pos[0]*4000000+tmp_pos[1]);
  //draw_sensors(sensors, min_range, count);
}
