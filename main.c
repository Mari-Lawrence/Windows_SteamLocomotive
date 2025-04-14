#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>

// ----------------------
// 动画帧定义
// ----------------------
typedef struct {
    const char* frame[10]; // 每帧10行
    int width;             // 该帧最大宽度
} AnimationFrame;

// 火车基础帧（4帧循环实现车轮转动）
static AnimationFrame train_frames[] = {
    { // Frame 0
        .frame = {
            "      ====        ________                ___________ ",
            "  _D _|  |_______/        \\__I_I_____===__|[]|_|__  ",
            "   |(_)---  |   H\\________/ |   |        =|oo o   | ",
            "   /     |  |   H  |  |     |   |         ||-\\-\\  | ",
            "  |      |  |   H  |__--------------------| [_] |  ",
            "  | ________|___H__/__|_____/[][]~\\_______|_o___o__ ",
            "  |/ |   |-----------I_____I [][] []  D   |=======| ",
            "__/ =| o |=-O~~\\  /~~\\  /~~\\  /~~\\ ____Y_\\_______/_",
            " |/-=|___|=    ||    ||    ||    |_____/~\\___/     ",
            "  \\_/      \\_O_/  \\_O_/  \\_O_/  \\_O_/      \\_/      "
        },
        .width = 70
    },
    { // Frame 1
        .frame = {
            "      ====        ________                ___________ ",
            "  _D _|  |_______/        \\__I_I_____===__|[]|_|__  ",
            "   |(_)---  |   H\\________/ |   |        =|oo o   | ",
            "   /     |  |   H  |  |     |   |         ||/-/-\\ | ",
            "  |      |  |   H  |__--------------------| [_] |  ",
            "  | ________|___H__/__|_____/[][]~\\_______|_o___o__ ",
            "  |/ |   |-----------I_____I [][] []  D   |=======| ",
            "__/ =| o |=-~~O/  /~~\\  /~~\\  /~~\\ ____Y_\\_______/_",
            " |/-=|___|=    ||    ||    ||    |_____/~\\___/     ",
            "  \\_/      \\_O_/  \\_O_/  \\_O_/  \\_O_/      \\_/      "
        },
        .width = 70
    },
    { // Frame 2
        .frame = {
            "      ====        ________                ___________ ",
            "  _D _|  |_______/        \\__I_I_____===__|[]|_|__  ",
            "   |(_)---  |   H\\________/ |   |        =|oo o   | ",
            "   /     |  |   H  |  |     |   |         ||\\-\\-\\ | ",
            "  |      |  |   H  |__--------------------| [_] |  ",
            "  | ________|___H__/__|_____/[][]~\\_______|_o___o__ ",
            "  |/ |   |-----------I_____I [][] []  D   |=======| ",
            "__/ =| o |=-~~\\  O/~~\\  /~~\\  /~~\\ ____Y_\\_______/_",
            " |/-=|___|=    ||    ||    ||    |_____/~\\___/     ",
            "  \\_/      \\_O_/  \\_O_/  \\_O_/  \\_O_/      \\_/      "
        },
        .width = 70
    },
    { // Frame 3
        .frame = {
            "      ====        ________                ___________ ",
            "  _D _|  |_______/        \\__I_I_____===__|[]|_|__  ",
            "   |(_)---  |   H\\________/ |   |        =|oo o   | ",
            "   /     |  |   H  |  |     |   |         ||/-/-\\ | ",
            "  |      |  |   H  |__--------------------| [_] |  ",
            "  | ________|___H__/__|_____/[][]~\\_______|_o___o__ ",
            "  |/ |   |-----------I_____I [][] []  D   |=======| ",
            "__/ =| o |=-~~\\  /~~O  /~~\\  /~~\\ ____Y_\\_______/_",
            " |/-=|___|=    ||    ||    ||    |_____/~\\___/     ",
            "  \\_/      \\_O_/  \\_O_/  \\_O_/  \\_O_/      \\_/      "
        },
        .width = 70
    }
};
#define FRAME_COUNT (sizeof(train_frames) / sizeof(train_frames[0]))

// ----------------------
// 双缓冲系统
// ----------------------
typedef struct {
    CHAR_INFO* buffer;
    int width;
    int height;
} DoubleBuffer;

HANDLE hConsole;
CONSOLE_SCREEN_BUFFER_INFO csbi;

void init_console() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    SetConsoleOutputCP(65001);

    // 隐藏光标
    CONSOLE_CURSOR_INFO cursorInfo = { 100, FALSE };
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

DoubleBuffer create_buffer() {
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DoubleBuffer db = {
        .buffer = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * csbi.dwSize.X * csbi.dwSize.Y),
        .width = csbi.dwSize.X,
        .height = csbi.dwSize.Y
    };
    return db;
}

void clear_buffer(DoubleBuffer* db) {
    for (int i = 0; i < db->width * db->height; i++) {
        db->buffer[i].Char.AsciiChar = ' ';
        db->buffer[i].Attributes = csbi.wAttributes;
    }
}

// ----------------------
// 动画渲染
// ----------------------
void render_train(DoubleBuffer* db, int offset, int frame_index) {
    const WORD color = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    const AnimationFrame* frame = &train_frames[frame_index % FRAME_COUNT];

    const int vertical_pos = csbi.dwSize.Y / 4; // 垂直居中

    for (int y = 0; y < 10; y++) { // 每帧10行
        const int target_y = vertical_pos + y;
        if (target_y >= db->height) continue;

        const char* line = frame->frame[y];
        const int line_len = strlen(line);

        for (int x = 0; x < line_len; x++) {
            const int target_x = offset + x;
            if (target_x >= 0 && target_x < db->width) {
                const int idx = target_y * db->width + target_x;
                db->buffer[idx].Char.AsciiChar = line[x];
                db->buffer[idx].Attributes = color;
            }
        }
    }
}

void draw_buffer(DoubleBuffer* db) {
    COORD size = { db->width, db->height };
    COORD pos = { 0, 0 };
    SMALL_RECT area = { 0, 0, db->width - 1, db->height - 1 };
    WriteConsoleOutput(hConsole, db->buffer, size, pos, &area);
}

// ----------------------
// 动画主逻辑
// ----------------------
void show_train(int delay_ms) {
    DoubleBuffer db = create_buffer();
    int frame_counter = 0;
    const int max_offset = csbi.dwSize.X + 100;

    for (int offset = csbi.dwSize.X; offset > -max_offset; offset--) {
        clear_buffer(&db);
        render_train(&db, offset, frame_counter / 2); // 每移动2像素换一帧
        draw_buffer(&db);

        if (_kbhit() && _getch() == 27) { // ESC退出
            free(db.buffer);
            return;
        }

        frame_counter++;
        Sleep(delay_ms);
    }
    free(db.buffer);
}

void print_help() {
    printf("sl - Steam Locomotive (Windows Edition）\n\n");
    printf("用法:\n");
    printf("  sl                显示一次火车动画\n");
    printf("  sl -a             无限循环播放（按ESC退出）\n");
    printf("  sl -s <毫秒>      设置帧延迟时间（默认80）\n");
    printf("  sl --help         显示帮助信息\n\n");
    printf("示例:\n");
    printf("  sl -a -s 30      快速无限循环（30ms帧间隔）\n");
}

int main(int argc, char* argv[]) {
    init_console();

    bool loop = false;
    int delay_ms = 80;

    // 参数解析
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i], "-a") == 0) {
            loop = true;
        } else if (strcmp(argv[i], "-s") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "错误：-s参数需要指定延迟时间\n");
                return 1;
            }
            delay_ms = atoi(argv[i + 1]);
            if (delay_ms <= 0) delay_ms = 80;
            i++;
        } else {
            fprintf(stderr, "错误：未知参数 '%s'\n", argv[i]);
            print_help();
            return 1;
        }
    }

    if (loop) {
        printf("无限循环模式运行中（按ESC退出）...\n");
        while (1) {
            show_train(delay_ms);
        }
    } else {
        show_train(delay_ms);
    }
    return 0;
}