#ifdef GL_ES
precision highp float;
#endif

//uniform vec3 iResolution;
float iTime = CC_Time[1];

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main()
{
	vec4 normalColor = texture2D(CC_Texture0, v_texCoord);
	gl_FragColor = v_fragmentColor * normalColor; // vec4(0.2, 0.1, 0.2, 1.0);
	//gl_FragColor = vec4(0.2, 0.1, 0.2, 1.0);
}
