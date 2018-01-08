#extension GL_EXT_gpu_shader4 : enable

#ifdef GL_ES
precision highp float;
#endif

uniform vec3 iResolution;
varying vec2 v_texCoord;

float iGlobalTime = CC_Time[1];
const float focalLength = 4.0;
const float cameraDistance = 1.0;
const vec3 light_dir = vec3(-0.7, 0.7, -0.14);

vec3 getNormal(int i) {
	int block = i / 4;
    vec3 signs = sign(vec3(i & ivec3(4, 2, 1)) - 0.1);
    
    if (block > 5) {
        return 0.5774 * signs;
    }
    
    vec3 r = signs * (block < 3 ? vec3(0.0, 0.5257, 0.8507) : vec3(0.0, 0.9342, 0.3568));
    return vec3(r[block % 3], r[(block + 2) % 3], r[(block + 1) % 3]);    
}

mat2 rotationMatrix(float angle) {
	float s = sin(angle);
	float c = cos(angle);
	return mat2(c, -s, s, c);
}

float fragment(vec3 L, vec3 N, vec3 V) {
	float ambient = 0.1;
	float diffuse = 0.5 + 0.5 * dot(L, N);
	vec3 R = reflect(-L, N);
	float specular = pow(max(0.0, dot(R, V)), 2.0);
	return ambient + 0.8 * diffuse + 0.3 * specular;
}

float getColor(vec4 fragCoord) {
	vec2 uv = (2.0 * fragCoord.xy - iResolution.xy) / iResolution.y;
	vec3 viewDir = normalize(vec3(uv.xy, focalLength));
	mat2 rotation = rotationMatrix(iGlobalTime);
	
	float z_back = 1e8;
	float z_front = 0.0;
	vec3 result_normal;
    
	for (int i = 0; i < 32; i++) {
		vec3 normal = getNormal(i);
        normal.xz = rotation * normal.xz;
		float dist = i < 12 ? 1.0 : 0.975;
		
		float viewDirDotNormal = dot(viewDir, normal);
		float z = (dist + normal.z * cameraDistance) / viewDirDotNormal;
		bool front = viewDirDotNormal < 0.0;
		if (front && z > z_front) {
			result_normal = normal;
			z_front = z;
		}
		if (!front && z < z_back) {
			z_back = z;
		}
	}
    
	return z_front > z_back ? 0.0 : fragment(light_dir, result_normal, -viewDir);
}

void main()
{
	gl_FragColor = vec4(getColor(gl_FragCoord));
}