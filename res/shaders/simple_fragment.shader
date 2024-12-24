#version 330 core

out vec4 FragColor;

uniform vec2 pos; // The position of the circle (vec2f)

void main() {
    vec2 uv = gl_FragCoord.xy / vec2(800.0, 600.0);
    uv.y = 1.0 - uv.y; // Flip Y axis to match common screen coordinate system (optional)

    // Animate the position of the circle based on time
    vec2 animatedPosition = pos;

    // Define the radius of the circle
    float radius = 0.1; // 10% of the screen width

    // Calculate the distance from the current fragment (uv) to the animated circle center
    float dist = length(uv - animatedPosition);

    // Color the fragment based on whether it is inside the circle or not
    vec3 color;
    if (dist < radius) {
        color = vec3(1.0, 1.0, 0.0); // Inside the circle, color red
    } else {
        color = vec3(0.0, 0.0, 0.0); // Outside the circle, color black
    }

    // Set the final color
    FragColor = vec4(color, 1.0);
}
