# Goal Oriented Random Walk Swarm Robots
## Project Description
This project simulates a swarm of e-puck robots that move randomly in a 2D world created in Webots. The robots are programmed to explore the environment until they find their designated goal points, which are represented by LEDs placed on the ground. The world contains obstacles that the robots must navigate around to reach their goals.

![Simulation Screenshot](Screenshots/1robot_initial%20state.png)

_Above: A screenshot of the e-puck robots in the Webots simulation environment._

## Installation and Setup
### Prerequisites
- Install [Webots](https://cyberbotics.com/#download)

### Steps
1. Clone the repository:
```
git clone https://github.com/your-username/goal-oriented-random-walk-swarm-robots.git
```
2. Navigate to the project directory:
```
cd goal-oriented-random-walk-swarm-robots
```
3. Open the project in Webots:
```
File > Open World > [Navigate to the project folder and select the .wbt file]
```
## Usage
1. Running the Simulation:
- In Webots, press the 'Play' button to start the simulation.

2. Controlling the Simulation:
- Use the Webots interface to pause, restart, or step through the simulation as desired.

## How it Works
- The e-puck robots begin by moving randomly within the environment.
- When a robot senses the LED light (the goal), it changes its behavior to reach that point.
- Robots avoid obstacles using their proximity sensors.

## Customization
- To change the number of robots, modify the N_ROBOTS constant in the controller file.
- To move the goal points, adjust the LED light positions in the Webots world file.

## Contributing
If you would like to contribute to this project, please fork this repository, create a new branch, make your changes, and open a pull request.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.