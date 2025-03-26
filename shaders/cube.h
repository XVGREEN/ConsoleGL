consoleGl::FragShader cubeShader = [](int x, int y, std::vector<float> uniforms) {
    consoleGl::Vec2 coord(x, y);
    using namespace consoleGl::shader;
    using namespace consoleGl;

    Vec2 resolution(uniforms[0], uniforms[1]);
    float t = uniforms[2];

    // Normaliza coordenadas
    Vec2 uv = (coord * 2.0f - resolution) / resolution.y;

    // Origem do raio (posição da câmera)
    Vec3 ro =Mat3::rotate(t*3.14)* Vec3(0.0f, 0.0f, -3.0f);

    // Direção do raio (projeção perspectiva)
    Vec3 rd = normalize(Vec3(uv.x, uv.y, 1.0f));

    // Variáveis do raymarching
    float tMarch = 0.0f;
    const int MAX_STEPS = 100;
    const float MAX_DIST = 10.0f;
    const float EPSILON = 0.001f;

    // Posição e tamanho do cubo
    Vec3 cubePos =Mat3::rotate(t)* Vec3(0.1f, 2.0f, 1.0f);
    Vec3 cubeSize = Vec3(0.9f); // Meio tamanho do cubo

    // Loop de raymarching
    for (int i = 0; i < MAX_STEPS; i++) {
        Vec3 p = ro + rd * tMarch;
        
        // Distância ao cubo
        float d = sdCube(p - cubePos, cubeSize);

        if (d < EPSILON) {
            // Normal do cubo usando aproximação de derivadas
            Vec3 normal = normalize(Vec3(
                sdCube(p + Vec3(EPSILON, 0, 0) - cubePos, cubeSize) - d,
                sdCube(p + Vec3(0, EPSILON, 0) - cubePos, cubeSize) - d,
                sdCube(p + Vec3(0, 0, EPSILON) - cubePos, cubeSize) - d
            ));

            // Luz móvel girando com o tempo
            Vec4 light = Vec4(1, -1.8, -1, -1);
            Vec3 lightDir = normalize(light.xyz());

            // Sombra suave
            float shadow = 1.0f;
            float tShadow = 0.02f;
            const float MAX_SHADOW_DIST = 5.0f;
            Vec3 pShadow = p + normal * EPSILON * 2.0f; // Evita autossombra
            for (int j = 0; j < 30; j++) {
                Vec3 pLight = pShadow + lightDir * tShadow;
                float dShadow = sdCube(pLight - cubePos, cubeSize);

                if (dShadow < EPSILON) {
                    shadow = 0.0f; // Sombra total
                    break;
                }
                shadow = fmin(shadow, 16.0f * dShadow / tShadow);
                if (tShadow > MAX_SHADOW_DIST) break;

                tShadow += dShadow;
            }

            // Iluminação difusa (Lambertiana)
            float diffuse = fmax(dot(normal, lightDir), 0.0f);

            return int(12 * diffuse * shadow);
        }

        if (tMarch > MAX_DIST) break;
        tMarch += d;
    }

    return 1;
};
