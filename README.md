# Rush Hour Game

Rush Hour is a captivating single-player game that puts you in the shoes of a taxi driver racing against time. Your mission: collect money by picking up passengers and dropping them off at their destinations while navigating a dynamic and challenging environment.

## Features

### Game Start Menu

- View the leaderboard displaying the top 10 scores along with player names.
  - High-scores and player names are stored in a file (`highscores.txt`) and updated dynamically.
  - If the game is being played for the first time, the leaderboard will be empty.
- Choose your taxi:
  - Select between a yellow taxi and a red taxi, or let the game assign one randomly.
- Enter your name to start the game.

### Game Board

- A 20x20 board featuring roads and buildings:
  - Roads (white) are navigable.
  - Buildings (black) are obstacles.
- Dynamic elements on the board:
  - Player’s taxi, other moving cars, obstacles, and passengers.
  - Passengers are placed randomly at positions not occupied by obstacles or other cars.

### Gameplay

- Use arrow keys to navigate the taxi in all four directions.
- Pick up passengers by stopping next to them and pressing the Spacebar.
- Deliver passengers to their randomly generated desired destinations (highlighted in green).

### Scoring System

- **Positive Points**:
  - +10 points for successfully delivering a passenger.
  - +1 point for each overtaking maneuver.
- **Negative Points**:
  - -5 points for hitting a person.
  - Penalties for hitting obstacles and other cars vary based on taxi type:
    - **Red Taxi**:
      - -2 points for hitting an obstacle (tree or box).
      - -3 points for hitting another car.
    - **Yellow Taxi**:
      - -4 points for hitting an obstacle (tree or box).
      - -2 points for hitting another car.

### Advanced Features

- Increasing difficulty:
  - Number of cars and their speed increases after every two successful passenger deliveries.
- Taxi speed:
  - Yellow taxi is faster than the red taxi.
- Dynamic obstacles and moving cars:
  - Non-player cars move continuously in all directions.

### Winning Criteria

- Total game time: **3 minutes**.
- Achieve a score of 100 or more within the time limit to win.

### Graphics

- Simple yet effective graphics with:
  - Stick figures for passengers.
  - Rectangles with circles for cars.

## How to Run

1. Extract the provided zip file containing the starter code.
2. Open a terminal and navigate to the extracted directory.
3. Compile the project with:
   ```bash
   make
   ```
4. Start the game by running:
   ```bash
   ./game
   ```

## Screenshots (Game Demo)

Below are some screenshots demonstrating the gameplay:  
![1](https://github.com/user-attachments/assets/ac423973-958d-4ec0-bd81-28736a5cc898)
![2](https://github.com/user-attachments/assets/7e58cbfa-48d3-463c-b668-e4ab1789506f)
![3](https://github.com/user-attachments/assets/bea67db0-2276-4238-9a08-f50fb43233b5)
![4](https://github.com/user-attachments/assets/0649f26f-6c2d-4d97-b4b5-6744143c5c4e)
![5](https://github.com/user-attachments/assets/f2d335ac-5a48-4afb-91f0-24d90d210a6b)
![6](https://github.com/user-attachments/assets/9520b20c-e470-403b-9aec-18da01d09053)
![7](https://github.com/user-attachments/assets/ee647caf-ec64-45de-a49e-405f9cee66cd)

---

Enjoy playing **Rush Hour** and experience the thrill of being a taxi driver under pressure!
