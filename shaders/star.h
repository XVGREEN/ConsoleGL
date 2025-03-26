
consoleGl::FragShader starShader = [](int x, int y, std::vector<float> uniforms) {
    consoleGl::Vec2 coord(x, y);
    using namespace consoleGl::shader;
    using namespace consoleGl;

    consoleGl::Vec2 resolution(uniforms[0], uniforms[1]);
    float t = uniforms[2];
     
    auto uv = (coord * 2.0f - resolution) / resolution.x;
    uv=uv*1.5;
    auto uvRot = Mat2::rotate(t * PI * 0.5f) * uv;

    float d = sdStar(uvRot, 5, 0.3f, 0.1f); // Uma estrela de 5 pontas

    return abs(d) <= 0.03 ? 10 : 0;
};
