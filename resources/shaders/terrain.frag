#ifdef GL_ES
precision highp float;
#endif

uniform vec3 iResolution;
//uniform vec4 iMouse; 
uniform sampler2D iChannel0;

varying vec2 v_texCoord;

float iGlobalTime = CC_Time[1];

float length2(vec2 p)
{
	return dot(p, p);
}

float noise(vec2 p)
{
	return fract(sin(fract(sin(p.x) * (4313.13311)) + p.y) * 3131.0011);
}

float worley(vec2 p)
{
	float d = 1e30;
	for (int xo = -1; xo <= 1; ++xo)
	for (int yo = -1; yo <= 1; ++yo)
	{
		vec2 tp = floor(p) + vec2(xo, yo);
		d = min(d, length2(p - tp - vec2(noise(tp))));
	}
	return 3.*exp(-4.*abs(2.*d - 1.));
}

float fworley(vec2 p)
{
	return sqrt(sqrt(sqrt(
		pow(worley(p + iGlobalTime), 2.) *
		worley(p*2. + 1.3 + iGlobalTime*.5) *
		worley(p*4. + 2.3 + iGlobalTime*.25) *
		worley(p*8. + 3.3 + iGlobalTime*.125) *
		worley(p*32. + 4.3 + iGlobalTime*.125) *
		sqrt(worley(p * 64. + 5.3 + iGlobalTime * .0625)) *
		sqrt(sqrt(worley(p * 128. + 7.3))))));
}

void main()
{
	//gl_FragColor = texture2D(CC_Texture0, v_texCoord);
	vec2 uv = gl_FragCoord.xy / iResolution.xy;
	float t = fworley(uv * iResolution.xy / 600.);
	t *= exp(-length2(abs(2.*uv - 1.)));
	float r = length(abs(2.*uv - 1.) * iResolution.xy);
	gl_FragColor = vec4(t * vec3(1.8, 1.8*t, .1 + pow(t, 2.-t)), 1.);
}