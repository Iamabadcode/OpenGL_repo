#version 440 core

uniform float time;
uniform float pos;

out vec4 fragColor;

void main() {
    // Normalize screen coordinates
    vec2 p = gl_FragCoord.xy / vec2(800.0, 600.0); // assuming resolution 800x600
    p = p * 2.0 - 1.0; // center coordinates to [-1, 1]
    
    // Create wave ripple effect using time
    float wave = sin(time + p.x * 10.0) * cos(time + p.y * 10.0);
    
    // Generate color channels based on wave pattern
    float r = 0.5 + 0.5 * sin(time + wave * 3.14);
    float g = 0.5 + 0.5 * cos(time + wave * 3.14);
    float b = 0.5 + 0.5 * sin(time + wave * 6.28);
    
    // Final color output
    fragColor = vec4(r, g, b, 1.0);
}
