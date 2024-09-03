#include "ofApp.h"

int Body::idCounter = 0;  // Static variable to assign unique IDs to each body
const float G = 0.001;    // Gravitational constant

// Body constructor initializes position, velocity, mass, radius, color, and assigns a unique ID
Body::Body(float x, float y, float dx, float dy, float m, Color c)
    : x(x), y(y), dx(dx), dy(dy), m(m), c(c) {
    r = sqrt(m) / 3;      // Radius of the body is proportional to the square root of its mass
    id = idCounter++;     // Assign a unique ID to this body
}

// Update the body's velocity based on gravitational forces from other bodies
void Body::update(float dt, std::vector<Body>& bodies) {
    float fx = 0, fy = 0;  // Force components

    for (auto& b : bodies) {
        if (b.id == id) continue;  // Skip self

        // Calculate distance squared between this body and another body
        float dsq = pow(b.x - x, 2) + pow(b.y - y, 2);
        float minD = r + b.r;  // Minimum distance for collision avoidance

        if (dsq < minD * minD) continue;  // Skip if too close (collision)

        // Gravitational force magnitude
        float f = G * m * b.m / dsq;

        // Normalize and calculate force components
        float d = sqrt(dsq);
        fx += f * (b.x - x) / d;
        fy += f * (b.y - y) / d;
    }

    // Calculate acceleration based on force and mass
    float ax = fx / m;
    float ay = fy / m;

    // Update velocity
    dx += ax * dt;
    dy += ay * dt;
}

// Move the body based on its velocity and the time step
void Body::move(float dt) {
    x += dx * dt;
    y += dy * dt;
}

// Draw the body as a circle with its specified color
void Body::draw() {
    ofSetColor(c.r, c.g, c.b);  // Set the drawing color
    ofDrawCircle(x, y, r);      // Draw the circle representing the body
}

// Setup the initial state of the application
void ofApp::setup() {
    ofSetFrameRate(60);           // Set the frame rate to 60 FPS
    ofBackground(0, 0, 0);        // Set the background color to black

    // Initialize the bodies with specific positions, velocities, and masses
    bodies = {
        Body(400, 400, 0.001, -0.006, 5000),
        Body(330, 400, -0.03, 0.27, 25),
        Body(260, 400, 0, 0.192, 40),
        Body(100, 400, 0, 0.135, 100),
        Body(85, 400, 0, 0.21, 0.1),
        Body(80, 400, 0, 0.21, 0.1),
        Body(740, 60, -0.0435, -0.025, 1)
    };
}

// Update the state of the application every frame
void ofApp::update() {
    int maxHistory = 15;  // Maximum number of points to track in mouse history

    // Maintain a fixed-length history of the mouse positions and time deltas
    if (mouseHistory.size() > maxHistory) {
        mouseHistory.erase(mouseHistory.begin());
    }
    mouseHistory.push_back(Point(ofGetMouseX(), ofGetMouseY(), ofGetLastFrameTime() * 1000));

    // Update and move each body
    for (int i = 0; i < bodies.size(); i++) {
        bodies[i].update(16, bodies);  // Update velocity based on forces
        bodies[i].move(16);            // Move based on updated velocity

        // Remove bodies that move too far off-screen
        if (abs(bodies[i].x) > 2000 || abs(bodies[i].y) > 2000) {
            bodies.erase(bodies.begin() + i);
            i--;  // Adjust index after removal
        }
    }

    // Update the report string with the number of bodies
    report = std::to_string(bodies.size()) + " bodies";
}

// Draw the scene every frame
void ofApp::draw() {
    ofBackground(0, 0, 0, 7);  // Clear the background with a slight transparency for trails

    // Draw the HUD (heads-up display) for the number of bodies
    ofSetColor(0, 0, 0);           // Set color to black for background
    ofDrawRectangle(0, 0, 155, 40); // Draw a rectangle as background for the text

    ofSetColor(0, 123, 255);       // Set color to blue for the text
    ofDrawBitmapString(report, 15, 32);  // Draw the number of bodies

    // Draw each body
    for (auto& b : bodies) {
        b.draw();
    }
}

// Handle mouse press events to create a new body at the mouse position
void ofApp::mousePressed(int x, int y, int button) {
    // Calculate the velocity based on the mouse history
    float dt = 0;
    for (auto& p : mouseHistory) {
        dt += p.dt;
    }
    dt /= 1000 * 100;  // Scale down the delta time for a reasonable speed

    // Calculate the velocity components based on mouse movement
    float dmx = (mouseHistory.back().x - mouseHistory.front().x) * dt;
    float dmy = (mouseHistory.back().y - mouseHistory.front().y) * dt;

    // Generate random RGB values for the new body's color
    int r = std::min(int(ofRandom(255)), 255);
    int g = std::min(int(ofRandom(255)), 255);
    int b = std::min(int(ofRandom(255)), 255);

    // Add the new body with calculated properties to the list of bodies
    bodies.push_back(Body(x, y, dmx, dmy, ofRandom(50, 500), Color(r, g, b)));
}

// Convert HSV to RGB colors for potential use in color generation
Color ofApp::HSVtoRGB(float h, float s, float v) {
    int i = floor(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);
    float r, g, b;

    // Assign RGB values based on the sector of the color wheel
    switch (i % 6) {
        default:
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
    }
    return Color(int(r * 255), int(g * 255), int(b * 255));
}
