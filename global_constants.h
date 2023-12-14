#ifndef GLOBAL_CONST
#define GLOBAL_CONST
//image properties
constexpr float ASPECT_RATIO = 16.0f/9.0f;
constexpr int PX_HEIGHT = 1000;
constexpr float IDEAL_WIDTH = PX_HEIGHT * ASPECT_RATIO;
constexpr int PX_WIDTH = IDEAL_WIDTH < 1 ? 1 : static_cast<int>(IDEAL_WIDTH);

//virtual viewport properties
constexpr float VIEWPORT_HEIGHT = 2.0f;             //arbitrary choice
constexpr float VIEWPORT_WIDTH = VIEWPORT_HEIGHT * (static_cast<float>(PX_WIDTH)/PX_HEIGHT);

#endif