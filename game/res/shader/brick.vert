const float SpecularContribution = 0.0;
const float DiffuseContribution = 1.0 - SpecularContribution;

varying float LightIntensity;
varying vec2 McPosition;

void main()
{
    vec3 lightPosition = gl_LightSource[0].position.xyz;
    vec3 ecPosition = vec3(gl_ModelViewMatrix*gl_Vertex);
    vec3 tnorm = normalize(gl_NormalMatrix*gl_Normal);
    vec3 lightVec = normalize(lightPosition - ecPosition);
    vec3 reflectVec = reflect(-lightVec, tnorm);
    vec3 viewVec = normalize(vec3(-gl_ProjectionMatrix*vec4(ecPosition, 1.0)));

    float diffuse = max(dot(lightVec, tnorm), 0.0);
    float spec = 0.0;
    if(diffuse > 0.0)
    {
        spec = max(dot(reflectVec, viewVec), 0.0);
        spec = pow(spec, 16.0);
    }
    LightIntensity = DiffuseContribution*diffuse + SpecularContribution*spec;

    McPosition = gl_Vertex.xy;
    gl_Position = ftransform();
    gl_FrontColor = gl_Color;
//    gl_BackColor = gl_Color;
}
