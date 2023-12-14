#ifndef GLOBAL_CONST
#define GLOBAL_CONST
constexpr float ASPECT_RATIO = 16.0f/9.0f;
constexpr int PX_WIDTH = PX_HEIGHT * ASPECT_RATIO < 1 ? 1 : static_cast<int>(PX_HEIGHT * ASPECT_RATIO);  //compile-time constants!
constexpr int PX_HEIGHT = 250;

constexpr float VIEWPORT_HEIGHT = 2.0f;             //arbitrary choice
constexpr float VIEWPORT_WIDTH = VIEWPORT_HEIGHT * (static_cast<float>(PX_WIDTH)/PX_HEIGHT);

#endif