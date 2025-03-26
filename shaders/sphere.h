consoleGl::FragShader sphereShader = [](int x, int y, std::vector<float> uniforms) {
    consoleGl::Vec2 coord(x, y);
    using namespace consoleGl::shader;
    using namespace consoleGl;

    Vec2 resolution(uniforms[0], uniforms[1]);
    float t = uniforms[2];

    // Normalize coordinates
    Vec2 uv = (coord * 2.0f - resolution) / resolution.y;

    // Ray origin (camera position)
    Vec3 ro = Vec3(0.0f, 0.0f, -3.0f);

    // Ray direction (perspective projection)
    Vec3 rd = normalize(Vec3(uv.x,uv.y, 1.0f));

    // Raymarching variables
    float tMarch = 0.0f;
    const int MAX_STEPS = 100;
    const float MAX_DIST = 10.0f;
    const float EPSILON = 0.001f;

    for (int i = 0; i < MAX_STEPS; i++) {
        Vec3 p = ro + rd * tMarch;
        float d = p.length() - 1.0f; // Sphere SDF

        if (d < EPSILON) {
            // Compute normal
            Vec3 normal = normalize(Vec3(
                length(p + Vec3(EPSILON, 0, 0)) - length(p - Vec3(EPSILON, 0, 0)),
                length(p + Vec3(0, EPSILON, 0)) - length(p - Vec3(0, EPSILON, 0)),
                length(p + Vec3(0, 0, EPSILON)) - length(p - Vec3(0, 0, EPSILON))
            ));
            
            // Light direction
            Vec3 lightDir =Mat3::rotate(t)* normalize(Vec3(1.0f, -1.0f, -1.0f));
   
            // Soft shadow calculation
            float shadow = 1.0f;
            float tShadow = 0.02f;
            const float MAX_SHADOW_DIST = 5.0f;
            for (int j = 0; j < 30; j++) {
                Vec3 pShadow = p + normal * EPSILON * 2.0f + lightDir * tShadow;
                float dShadow = length(pShadow) - 1.0f;

                if (dShadow < EPSILON) {
                    shadow = 0.0f;
                    break;
                }
                shadow = fmin(shadow, 16.0f * dShadow / tShadow);
                if (tShadow > MAX_SHADOW_DIST) break;

                tShadow += dShadow;
            }

            // Lambertian shading
            float diffuse = fmax(dot(normal, lightDir), 0.0f);

            return int(10 * diffuse * shadow);
        }

        if (tMarch > MAX_DIST) break;
        tMarch += d;
    }

    return 1;
};
