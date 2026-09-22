#version 400

layout( location = 0 ) out vec4 fragcolor;

uniform float randColourX;
uniform float randColourY;
uniform float randColourZ;
 
void main()
{
//Setting each vector component to uniform varaible then setting final colour
	vec4 color;
	color = vec4(randColourX,randColourY,randColourZ,1.0);
    fragcolor = color;
}