#version 330 core

out vec4 FragColor;

uniform float time;

void main() {
    // Normalize pixel coordinates (UV coordinates)
    vec2 uv = gl_FragCoord.xy / vec2(800.0, 600.0);  // Assuming screen resolution of 800x600
    uv.y = 1.0 - uv.y; // Flip Y axis to match common screen coordinate system (optional)

    // Apply a sine wave shift based on the x coordinate and time
    float sineShift = sin(uv.x * 10.0 + time * 2.0) * 0.1;  // Amplitude of 0.1 and frequency scaling on x
    uv.y += sineShift; // Apply the sine wave shift to the y-coordinate

    // Ensure that the uv.y value stays within bounds [0, 1]
    uv.y = mod(uv.y, 1.0);  // Wrap the y-coordinate to avoid going out of bounds

    // Define the number of horizontal beams (let's divide the screen into 10 beams)
    float numBeams = 10.0;
    
    // Calculate which beam the current pixel belongs to
    float beamIndex = floor(uv.y * numBeams);  // Divide the screen into 10 equal parts

    // Generate colors for each beam based on the beam index
    vec3 color;
    if (beamIndex == 0.0) {
        color = vec3(1.0, 0.0, 0.0);  // Red
    } else if (beamIndex == 1.0) {
        color = vec3(0.0, 1.0, 0.0);  // Green
    } else if (beamIndex == 2.0) {
        color = vec3(0.0, 0.0, 1.0);  // Blue
    } else if (beamIndex == 3.0) {
        color = vec3(1.0, 1.0, 0.0);  // Yellow
    } else if (beamIndex == 4.0) {
        color = vec3(1.0, 0.0, 1.0);  // Magenta
    } else if (beamIndex == 5.0) {
        color = vec3(0.0, 1.0, 1.0);  // Cyan
    } else if (beamIndex == 6.0) {
        color = vec3(0.5, 0.5, 0.5);  // Gray
    } else if (beamIndex == 7.0) {
        color = vec3(0.5, 0.25, 0.0); // Brown
    } else if (beamIndex == 8.0) {
        color = vec3(0.25, 0.0, 0.5); // Purple
    } else {
        color = vec3(0.0, 0.5, 0.25); // Teal
    }

    // Set the final color
    FragColor = vec4(color, 1.0);
}
