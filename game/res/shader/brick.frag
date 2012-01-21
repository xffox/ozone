varying float LightIntensity;
varying vec2 McPosition;

const vec4 MortarColor = vec4(0.0, 0.0, 0.0, 1.0);
const vec2 BrickSize = vec2(4.0, 1.0);
//const vec2 BrickPct = vec2(0.9, 0.9);
const float BrickPctX = 0.97;

void main()
{
    vec2 position;
    vec2 useBrick;
    
    position = McPosition / BrickSize;

    if(fract(position.y*0.5) > 0.5)
        position.x += 0.5;
    position = fract(position);

    vec2 BrickPct = vec2(BrickPctX, 1.0 - 4.0/1.0*(1.0-BrickPctX));
    useBrick = step(position, BrickPct);

    gl_FragColor = mix(MortarColor, gl_Color,
        useBrick.x*useBrick.y)*LightIntensity;
}
