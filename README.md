# three-body-problem
This project is a particle simulation built using OpenFrameworks, a C++ toolkit for creative coding. The simulation models the gravitational interaction between particles (referred to as "bodies") in a 2D space. Users can also interact with the simulation by clicking to add new bodies with unique properties.

# Particle Simulation with OpenFrameworks
This project is a particle simulation built using [Link OpenFrameworks](https://openframeworks.cc/), a C++ toolkit for creative coding. The simulation models the gravitational interaction between particles (referred to as "bodies") in a 2D space. Users can also interact with the simulation by clicking to add new bodies with unique properties.

## Features
- **Gravitational Interaction**: Bodies are influenced by the gravitational pull of other bodies, leading to dynamic and realistic movement.
- **Interactive Particle Creation**: Click anywhere on the screen to spawn a new body at the mouse position. The initial velocity of the body is determined by the recent movement of the mouse.
- **HUD Display**: The simulation displays the number of active bodies on the screen.
- **Trail Effect**: The bodies leave a trail as they move, giving a visual representation of their paths.

## Getting Started

### Prerequisites
- **OpenFrameworks**: You need to have OpenFrameworks installed on your system. This project was developed with OpenFrameworks version 0.11.0, but it should work with other versions as well.
- **Development Environment**: You will need an IDE compatible with OpenFrameworks, such as Visual Studio (Windows), Xcode (macOS), or Code::Blocks (Linux).

### Installation

1. **Clone the repository**:
   ```
   git clone https://github.com/yourusername/particle-simulation.git
   ```
2. **Open the Project**:
   - Navigate to the project directory and open the **`particle-simulation`** folder using your IDE.
   - Ensure that OpenFrameworks is set up correctly in your IDE.
3. **Compile and Run**:
   - Build and run the project from your IDE. The simulation should start in a new window.

## Controls
- **Mouse Click**: Click anywhere on the screen to spawn a new body. The new body will have a random color and a velocity based on your recent mouse movement.
- **HUD**: The top left of the screen displays the number of bodies currently in the simulation.

## File Structure
- **`src/ofApp.h`**: Header file for the main application class.
- **`src/ofApp.cpp`**: Contains the main application logic, including setup, update, draw, and event handling methods.
- **`src/Body.h`**: Header file for the Body class, which represents each particle in the simulation.
- **`src/Body.cpp`**: Implementation of the Body class, including methods for updating position based on gravitational forces and drawing the body.
- **`src/main.cpp`**: Entry point for the application, which initializes the OpenFrameworks environment.

## Customization
- **Initial Bodies**: You can modify the initial bodies in the `setup()` function in `ofApp.cpp`. Add or remove bodies, or change their initial position, velocity, mass, and color.
- **Gravitational Constant (G)**: Adjust the gravitational constant `G` in `Body.cpp` to increase or decrease the strength of gravitational interaction between bodies.
- **Trail Effect**: The trail effect is achieved by drawing the background with slight transparency. You can modify this effect in the `draw()` function in `ofApp.cpp` by changing the alpha value in `ofBackground(0, 0, 0, 7);`.

## Known Issues
- **Performance**: The simulation's performance may degrade with a very high number of bodies due to the computational complexity of calculating gravitational interactions between all pairs of bodies.

## Future Enhancements
- **Collision Detection**: Implementing collision detection to handle bodies merging or bouncing off each other.
- **3D Simulation**: Expanding the simulation to 3D space for more complex interactions.
- **Optimized Physics**: Utilizing more advanced physics libraries or algorithms for better performance with large numbers of bodies.

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgements
This project was inspired by various gravitational simulations and particle systems often explored in creative coding. Thanks to the OpenFrameworks community for their extensive documentation and support.
