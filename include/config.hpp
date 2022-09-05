#pragma once

namespace config
{
    // 540p     qHD
	static int const WINDOW_WIDTH = 960;
	static int const WINDOW_HEIGHT = 540;
    // 720p     HD
	//static int const WINDOW_WIDTH = 1280;
	//static int const WINDOW_HEIGHT = 720;
    // 1080p    Full HD / FHD
	//static int const WINDOW_WIDTH = 1920;
	//static int const WINDOW_HEIGHT = 1080;
    // 2K
	//static int const WINDOW_WIDTH = 2048;
	//static int const WINDOW_HEIGHT = 1080;
    // 1440p    QHD / QuadHD / WQHD
	//static int const WINDOW_WIDTH = 2560;
	//static int const WINDOW_HEIGHT = 1440;
    // 2160p    UHD
	//static int const WINDOW_WIDTH = 2840;
	//static int const WINDOW_HEIGHT = 2160;
    // 4K
	//static int const WINDOW_WIDTH = 4096;
	//static int const WINDOW_HEIGHT = 2160;
    // 5K
	//static int const WINDOW_WIDTH = 5120;
	//static int const WINDOW_HEIGHT = 2880;
    // 8K       8K UHD
	//static int const WINDOW_WIDTH = 7680;
	//static int const WINDOW_HEIGHT = 4320;

	static int const TILE_SIZE = 64;
    static int const TILEMAP_WIDTH = 22;
    static int const TILEMAP_HEIGHT = 25;

	static int const FPS = 60;
	static int const FRAME_DELAY = 1000 / FPS;
}