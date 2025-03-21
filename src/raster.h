#ifndef RASTER
#define RASTER

namespace consoleGl{
void raster(const vec2 vecs[3], frame_buffer& fb) {
    vec2 center = vec2(fb.width, fb.height) * 0.5;
    vec2 v0 = vecs[0] + center, v1 = vecs[1] + center, v2 = vecs[2] + center;

    if (v0.y > v1.y) std::swap(v0, v1);
    if (v1.y > v2.y) std::swap(v1, v2);
    if (v0.y > v1.y) std::swap(v0, v1);

    auto interpolate = [](float y0, float y1, float x0, float x1, float y) {
        if (y1 == y0) return x0;
        return x0 + (x1 - x0) * ((y - y0) / (y1 - y0));
    };

    for (int y = static_cast<int>(v0.y); y <= static_cast<int>(v2.y); ++y) {
        bool second_half = y >= v1.y;

        vec2 A = v0, B = second_half ? v1 : v2, C = v2;

        float xA = interpolate(A.y, C.y, A.x, C.x, y);
        float xB = interpolate(B.y, C.y, B.x, C.x, y);

        if (xA > xB) std::swap(xA, xB);

        for (int x = static_cast<int>(xA); x <= static_cast<int>(xB); ++x) {
            if (x >= 0 && x < fb.width && y >= 0 && y < fb.height) {
                fb.set_pixel(x, y);
            }
        }
    }
}
}
#endif
