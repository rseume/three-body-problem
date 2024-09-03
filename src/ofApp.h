#pragma once

#include "ofMain.h"

class Point {
public:
    float x, y;
    float dt;
    Point(float x, float y, float dt) : x(x), y(y), dt(dt) {}
};

class Color {
public:
    int r, g, b;
    Color(int r = 255, int g = 255, int b = 255) : r(r), g(g), b(b) {}
};

class Body {
public:
    float x, y;
    float dx, dy;
    float m;
    float r;
    Color c;
    int id;
    static int idCounter;

    Body(float x, float y, float dx, float dy, float m, Color c = Color());
    void update(float dt, std::vector<Body>& bodies);
    void move(float dt);
    void draw();
};

class ofApp : public ofBaseApp {
public:
    std::vector<Body> bodies;
    std::vector<Point> mouseHistory;
    std::string report;

    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    Color HSVtoRGB(float h, float s, float v);
};
