#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>
#include "safe_input.c"

#define PI 3.14159265

// Polygon parameters
int n;                 // Number of sides (n < 15)
float side_length;     // Length of each side
float angle;           // Rotation angle in degrees

// Draw a regular polygon centered at (cx, cy)
void drawPolygon(float cx, float cy, int sides, float side_length, float rotation_angle) {
    if (sides < 3) return; // Minimum 3 sides

    // Calculate circumradius for the given side length
    float radius = side_length / (2 * sin(PI / sides));

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < sides; ++i) {
        float theta = 2.0f * PI * i / sides + rotation_angle - (PI / sides); // Adjusted starting angle
        float x = cx + radius * cos(theta);
        float y = cy + radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}

// Function to find the bottom-right vertex
void findBottomRightVertex(float cx, float cy, int sides, float side_length, float *bottom_right_x, float *bottom_right_y) {
    float radius = side_length / (2 * sin(PI / sides));
    float max_x = -INFINITY;
    float max_y = -INFINITY;

    // Loop through all vertices, find rightmost on the bottom horizontal side
    for (int i = 0; i < sides; ++i) {
        float theta = 2.0f * PI * i / sides - (PI / sides); // Adjust starting angle for orientation
        float x = cx + radius * cos(theta);
        float y = cy + radius * sin(theta);

        // Check for the rightmost bottom vertex
        if (y <= cy && (x > max_x || (x == max_x && y < max_y))) {
            max_x = x;
            max_y = y;
        }
    }

    *bottom_right_x = max_x;
    *bottom_right_y = max_y;
}

void display() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Center of the screen
    float cx = 0.0f;
    float cy = 0.0f;

    // Draw the polygon without rotation
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    drawPolygon(cx, cy, n, side_length, 0.0f);

    // Find the bottom-right vertex
    float corner_x, corner_y;
    findBottomRightVertex(cx, cy, n, side_length, &corner_x, &corner_y);

    // Draw the rotated polygon
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color
    glPushMatrix();
    glTranslatef(corner_x, corner_y, 0.0f);    // Move to the bottom-right vertex
    glRotatef(angle, 0.0f, 0.0f, 1.0f);       // Rotate around this vertex
    glTranslatef(-corner_x, -corner_y, 0.0f); // Move back to origin
    drawPolygon(cx, cy, n, side_length, 0.0f);
    glPopMatrix();

    // Swap buffers
    glutSwapBuffers();
}

void initialize() {
    // Set up 2D mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Automatically adjust orthographic projection based on side length
    float viewportSize = side_length * 3;
    glOrtho(-viewportSize, viewportSize, -viewportSize, viewportSize, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv) {
    // User input for parameters
    printf("Enter number of sides (n < 15): ");
    do {
        n = safe_uint_input();
        if (n < 3 || n >= 15) {
            printf("Number of sides must be between 3 and 14. Try again: ");
        }
    } while (n < 3 || n >= 15);

    printf("Enter side length: ");
    side_length = safe_real_input("");

    printf("Enter rotation angle (degrees): ");
    angle = safe_real_input("");

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Polygon with Rotation");

    initialize();

    // Set display function
    glutDisplayFunc(display);

    // Start the main loop
    glutMainLoop();

    return 0;
}
