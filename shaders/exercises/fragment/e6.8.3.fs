#version 330 core
out vec4 FragColor;
in vec3 myColor;

void main() {
    FragColor = vec4(myColor, 1.0f);
    /*
    yellow at the first quadrant:
    x+, y+ = red + green = yellow

    green at the second quadrant:
    x-, y+ = _ + green = green

    black at the third quadrant:
    x-, y- = _ + _ = black
    
    red at the fourth quadrant:
    x+, y- = red + _ = red
    */
}