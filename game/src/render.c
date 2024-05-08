#include "render.h" // Include rendering functions header.
#include "raymath.h" // Include ray math functions header.

Vector2 ncScreenSize = { 1280, 720 }; // Screen size (width, height).
float ncScreenZoom = 1.0f; // Screen zoom factor.
float ncViewSize = 25.0f; // View size in world units.

// Convert screen coordinates to world coordinates.
Vector2 ConvertScreenToWorld(Vector2 screen)
{
    float ratio = ncScreenSize.x / ncScreenSize.y; // Calculate screen aspect ratio.
    Vector2 extents = (Vector2){ ncViewSize * ratio, ncViewSize }; // Calculate world extents.
    extents = Vector2Scale(extents, ncScreenZoom); // Scale by zoom factor.

    Vector2 lower = Vector2Negate(extents); // Calculate lower world bound.
    Vector2 upper = extents; // Calculate upper world bound.

    float nx = screen.x / ncScreenSize.x; // Normalize screen x-coordinate.
    float ny = (ncScreenSize.y - screen.y) / ncScreenSize.y; // Normalize screen y-coordinate.

    Vector2 world;
    world.x = ((1 - nx) * lower.x) + (nx * upper.x); // Convert normalized x-coordinate to world.
    world.y = ((1 - ny) * lower.y) + (ny * upper.y); // Convert normalized y-coordinate to world.

    return world; // Return world coordinates.
}

// Convert world coordinates to screen coordinates.
Vector2 ConvertWorldToScreen(Vector2 world)
{
    float ratio = ncScreenSize.x / ncScreenSize.y; // Calculate screen aspect ratio.
    Vector2 extents = (Vector2){ ncViewSize * ratio, ncViewSize }; // Calculate world extents.
    extents = Vector2Scale(extents, ncScreenZoom); // Scale by zoom factor.

    Vector2 lower = Vector2Negate(extents); // Calculate lower world bound.
    Vector2 upper = extents; // Calculate upper world bound.

    float nx = (world.x - lower.x) / (upper.x - lower.x); // Normalize world x-coordinate.
    float ny = (world.y - lower.y) / (upper.y - lower.y); // Normalize world y-coordinate.

    Vector2 screen;
    screen.x = nx * ncScreenSize.x; // Convert normalized x-coordinate to screen.
    screen.y = (1.0f - ny) * ncScreenSize.y; // Convert normalized y-coordinate to screen.

    return screen; // Return screen coordinates.
}

// Convert world coordinates to pixel coordinates.
float ConvertWorldToPixel(float world)
{
    float ratio = ncScreenSize.x / ncScreenSize.y; // Calculate screen aspect ratio.
    Vector2 extents = (Vector2){ ncViewSize * ratio, ncViewSize }; // Calculate world extents.
    extents = Vector2Scale(extents, ncScreenZoom); // Scale by zoom factor.

    float nx = world / extents.x; // Normalize world coordinate.
    float pixel = nx * ncScreenSize.x; // Convert normalized coordinate to pixels.

    return pixel; // Return pixel coordinate.
}
