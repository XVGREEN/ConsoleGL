#ifndef RASTER
#define RASTER

namespace consoleGl{



void drawLine(int x0, int y0, int x1, int y1, frame_buffer& fb) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (x0 >= 0 && x0 < fb.width && y0 >= 0 && y0 < fb.height) {
            fb.set_pixel(x0, y0); // Draw the pixel
        }

        if (x0 == x1 && y0 == y1) break; // Exit when the end point is reached

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void drawTriangle(const vec2 vecs[3], frame_buffer& fb) {
    // Center of the framebuffer
    vec2 center = vec2(fb.width / 2.0f, fb.height / 2.0f);

    // Transform vertices to framebuffer coordinates
    vec2 v0 = vecs[0] + center;
    vec2 v1 = vecs[1] + center;
    vec2 v2 = vecs[2] + center;

    // Draw the three edges of the triangle
    drawLine(static_cast<int>(v0.x), static_cast<int>(v0.y), static_cast<int>(v1.x), static_cast<int>(v1.y), fb);
    drawLine(static_cast<int>(v1.x), static_cast<int>(v1.y), static_cast<int>(v2.x), static_cast<int>(v2.y), fb);
    drawLine(static_cast<int>(v2.x), static_cast<int>(v2.y), static_cast<int>(v0.x), static_cast<int>(v0.y), fb);
}


void raster(const vec2 vecs[3], frame_buffer& fb) {
    vec2 center = (vecs[0] + vecs[1] + vecs[2]) / 3.0f; 

    for (float t = 0.0f; t <= 1.0f; t += 0.01f) {
        vec2 scaled[3] = {
            center + (vecs[0] - center) * t,
            center + (vecs[1] - center) * t,
            center + (vecs[2] - center) * t
        };
        drawTriangle(scaled, fb);
    }
}
 
 void setColor(int r, int g, int b) {
     std::cout << "\033[38;2;" << r << ";" << g << ";" << b << "m";
 }
  void setColor(color col){
  	setColor(col.r,col.g,col.b);
  }
	
}
#endif
