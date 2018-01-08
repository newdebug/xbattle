attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;
attribute vec4 a_normal;

uniform vec4 u_color;

varying vec2 v_texCoord;
varying vec4 v_fragmentColor;

void main()
{
	// use CC_PMatrix not CC_MVPMatrix for 2D Sprites
    gl_Position = CC_MVPMatrix * a_position;
	v_texCoord = a_texCoord * a_normal;
	v_fragmentColor = a_color * u_color;
}

