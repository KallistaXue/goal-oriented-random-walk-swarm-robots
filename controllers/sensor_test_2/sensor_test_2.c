/*
 * File:          sensor_test_2.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/motor.h>, etc.
 */
 // include headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <webots/device.h>
#include <webots/distance_sensor.h>
#include <webots/light_sensor.h>
#include <webots/led.h>
#include <webots/motor.h>
#include <webots/nodes.h>
#include <webots/robot.h>

/*
 * You may want to add macros here.
 */
#define TIME_STEP 64

#define DISTANCE_SENSORS_NUMBER 8
static WbDeviceTag distance_sensors[DISTANCE_SENSORS_NUMBER];
static double distance_sensors_values[DISTANCE_SENSORS_NUMBER];
static const char *distance_sensors_names[DISTANCE_SENSORS_NUMBER] = {"ps0", "ps1", "ps2", "ps3", "ps4", "ps5", "ps6", "ps7"};

#define LIGHT_SENSORS_NUMBER 8
static WbDeviceTag light_sensors[LIGHT_SENSORS_NUMBER];
static double light_sensors_values_pure[LIGHT_SENSORS_NUMBER];
static const char *light_sensors_names[LIGHT_SENSORS_NUMBER] = {"ls0", "ls1", "ls2", "ls3", "ls4", "ls5", "ls6", "ls7"};


// motor
static WbDeviceTag left_motor, right_motor;

#define LEFT 0
#define RIGHT 1
#define MAX_SPEED 6.28
static double speeds[2];


static int get_time_step() {
  static int time_step = -1;
  if (time_step == -1)
    time_step = (int)wb_robot_get_basic_time_step();
  return time_step;
}

static void step() {
  if (wb_robot_step(get_time_step()) == -1) {
    wb_robot_cleanup();
    exit(EXIT_SUCCESS);
  }
}

static void passive_wait(double sec) {
  double start_time = wb_robot_get_time();
  do {
    step();
  } while (start_time + sec > wb_robot_get_time());
}

static void turn_left() {
  wb_motor_set_velocity(left_motor, -MAX_SPEED);
  wb_motor_set_velocity(right_motor, MAX_SPEED);
  printf("Turning\n");
  passive_wait(1.5);
  //wb_motor_set_velocity(left_motor, 0);
  //wb_motor_set_velocity(right_motor, 0);
}


static void init_devices() {
  int i;
  for (i = 0; i < DISTANCE_SENSORS_NUMBER; i++) {
    distance_sensors[i] = wb_robot_get_device(distance_sensors_names[i]);
    wb_distance_sensor_enable(distance_sensors[i], get_time_step());
    
    
  }
  
  for (i = 0; i < LIGHT_SENSORS_NUMBER; i++) {
    light_sensors[i] = wb_robot_get_device(light_sensors_names[i]);
    wb_light_sensor_enable(light_sensors[i], get_time_step());
  }
  
  // get a handler to the motors and set target position to infinity (speed control).
  left_motor = wb_robot_get_device("left wheel motor");
  right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  wb_motor_set_velocity(left_motor, 0.0);
  wb_motor_set_velocity(right_motor, 0.0);

  step();
}

static void get_sensor_input() {
  int i;
  for (i = 0; i < DISTANCE_SENSORS_NUMBER; i++) {
    distance_sensors_values[i] = wb_distance_sensor_get_value(distance_sensors[i]);
  }
   for (i = 0; i < LIGHT_SENSORS_NUMBER; i++) {
    light_sensors_values_pure[i] = wb_light_sensor_get_value(light_sensors[i]);
  }
}



/*
 * This is the main program.
 * The arguments of the main function can be specified by the
 * "controllerArgs" field of the Robot node
 */
int main(int argc, char **argv) {
  double maxval = 0;
  double minval = 10000;
  int i = 0;
  /* necessary to initialize webots stuff */
  wb_robot_init();

  /*
   * You should declare here WbDeviceTag variables for storing
   * robot devices like this:
   *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
   *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
   */
  printf("Default controller of the e-puck robot started...\n");
  //printf(wb_distance_sensor_get_lookup_table);
  init_devices();
  /* main loop
   * Perform simulation steps of TIME_STEP milliseconds
   * and leave the loop when the simulation is over
   */
  //turn_left();
  //while (wb_robot_step(TIME_STEP) != -1) {
  for(i = 0;i<=100;i++) {
    /*
     * Read the sensors :
     * Enter here functions to read sensor data, like:
     *  double val = wb_distance_sensor_get_value(my_sensor);
     */
     wb_robot_step(TIME_STEP);
    get_sensor_input();
    if(light_sensors_values_pure[0]>maxval)
      maxval = light_sensors_values_pure[0];
    if(light_sensors_values_pure[0]<minval)
      minval = light_sensors_values_pure[0];
    printf("%d   ",i);
    /*
    printf("front: %f %f\n", distance_sensors_values[0], distance_sensors_values[7]);
    printf("left:  %f\n", distance_sensors_values[5]);
    printf("right: %f\n", distance_sensors_values[2]);
    */
    /* Process sensor data here */
    //printf("1\n");
    /*
     * Enter here functions to send actuator commands, like:
     * wb_motor_set_position(my_actuator, 10.0);
     */
     //printf("%f, %f, %f\n", light_sensors_values_pure[0], light_sensors_values_pure[1], light_sensors_values_pure[2]);
  }
  printf("\nmax: %f\nmin: %f\ndiff: %f\n",maxval,minval,maxval-minval);
  /* Enter your cleanup code here */

  /* This is necessary to cleanup webots resources */
  wb_robot_cleanup();

  return 0;
}
