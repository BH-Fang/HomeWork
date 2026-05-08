#include "dark_chess_client.h"
#include <stdio.h>
#include <windows.h>

#define BOARD_ROWS 4
#define BOARD_COLS 8
#define PIECE_TEXT_LEN 32
#define UPDATE_BUF_SIZE 4096
#define ACTION_BUF_SIZE 256

typedef struct {
    char board[BOARD_ROWS][BOARD_COLS][PIECE_TEXT_LEN];
    char role[16];
    char my_color[16];
    char enemy_color[16];
    char current_turn[16];
    char winner[16];
    int game_over;
} GameState;

static int extract_json_string_field(const char *json, const char *key, char *out, size_t out_len) {
    char pattern[64];
    const char *start;
    const char *end;
    size_t len;

    snprintf(pattern, sizeof(pattern), "\"%s\": \"", key);
    start = strstr(json, pattern);
    if (!start) {
        return 0;
    }

    start += strlen(pattern);
    end = strchr(start, '\"');
    if (!end) {
        return 0;
    }

    len = (size_t)(end - start);
    if (len >= out_len) {
        len = out_len - 1;
    }

    strncpy(out, start, len);
    out[len] = '\0';
    return 1;
}

static void init_game_state(GameState *state) {
    int r;
    int c;

    memset(state, 0, sizeof(*state));
    strcpy(state->winner, "None");

    for (r = 0; r < BOARD_ROWS; r++) {
        for (c = 0; c < BOARD_COLS; c++) {
            strcpy(state->board[r][c], "Covered");
        }
    }
}

static void parse_board(const char *json, GameState *state) {
    const char *board_start = strstr(json, "\"board\": [[");
    const char *p;
    int index;

    if (!board_start) {
        return;
    }

    p = board_start + strlen("\"board\": [[");
    for (index = 0; index < BOARD_ROWS * BOARD_COLS; index++) {
        const char *quote_start = strchr(p, '\"');
        const char *quote_end;
        int row;
        int col;
        size_t len;

        if (!quote_start) {
            break;
        }
        quote_start++;
        quote_end = strchr(quote_start, '\"');
        if (!quote_end) {
            break;
        }

        row = index / BOARD_COLS;
        col = index % BOARD_COLS;
        len = (size_t)(quote_end - quote_start);
        if (len >= PIECE_TEXT_LEN) {
            len = PIECE_TEXT_LEN - 1;
        }

        strncpy(state->board[row][col], quote_start, len);
        state->board[row][col][len] = '\0';
        p = quote_end + 1;
    }
}

static void parse_system_update(const char *json, GameState *state) {
    char role_a_color[16] = "";
    char role_b_color[16] = "";

    init_game_state(state);
    if (strcmp(_assigned_role, "first") == 0) {
        strcpy(state->role, "A");
    } else if (strcmp(_assigned_role, "second") == 0) {
        strcpy(state->role, "B");
    } else {
        strncpy(state->role, _assigned_role, sizeof(state->role) - 1);
    }

    parse_board(json, state);
    extract_json_string_field(json, "current_turn_role", state->current_turn, sizeof(state->current_turn));
    extract_json_string_field(json, "winner", state->winner, sizeof(state->winner));
    extract_json_string_field(json, "A", role_a_color, sizeof(role_a_color));
    extract_json_string_field(json, "B", role_b_color, sizeof(role_b_color));

    if (strcmp(state->role, "A") == 0) {
        strncpy(state->my_color, role_a_color, sizeof(state->my_color) - 1);
        strncpy(state->enemy_color, role_b_color, sizeof(state->enemy_color) - 1);
    } else {
        strncpy(state->my_color, role_b_color, sizeof(state->my_color) - 1);
        strncpy(state->enemy_color, role_a_color, sizeof(state->enemy_color) - 1);
    }

    if (strstr(json, "\"status\": \"game_over\"") || strcmp(state->winner, "None") != 0) {
        state->game_over = 1;
    }
}

static void print_board_for_debug(const GameState *state) {
    int r;
    int c;

    printf("\n===== Current Board =====\n");
    for (r = 0; r < BOARD_ROWS; r++) {
        for (c = 0; c < BOARD_COLS; c++) {
            printf("%-8s ", state->board[r][c]);
        }
        printf("\n");
    }
    printf("=========================\n");
}

static int is_my_turn(const GameState *state) {
    return strcmp(state->current_turn, state->role) == 0;
}

static int choose_open_or_move(const GameState *state) {
    int r, c, d;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    if (strcmp(state->my_color, "") == 0) {
        return 0; // 翻棋
    }

    // 先找能不能吃或移動
    for (r = 0; r < BOARD_ROWS; r++) {
        for (c = 0; c < BOARD_COLS; c++) {
            if (strstr(state->board[r][c], state->my_color) == NULL) {
                continue;
            }

            for (d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr < 0 || nr >= BOARD_ROWS || nc < 0 || nc >= BOARD_COLS) {
                    continue;
                }

                if (strcmp(state->board[nr][nc], "Null") == 0) {
                    return 1; // 可以走
                }

                if (strstr(state->board[nr][nc], state->enemy_color) != NULL) {
                    return 2; // 可以嘗試吃
                }
            }
        }
    }

    return 0; // 沒得走就翻
}

static int select_target_position(const GameState *state) {
    int r, c;

    // 優先翻中間附近，比較容易展開
    int order[32] = {
        1, 2, 3, 4, 5, 6,
        9, 10, 11, 12, 13, 14,
        17, 18, 19, 20, 21, 22,
        25, 26, 27, 28, 29, 30,
        0, 7, 8, 15, 16, 23, 24, 31
    };

    int i;
    for (i = 0; i < 32; i++) {
        r = order[i] / BOARD_COLS;
        c = order[i] % BOARD_COLS;

        if (strcmp(state->board[r][c], "Covered") == 0) {
            return r * BOARD_COLS + c;
        }
    }

    return -1;
}

static void build_action_command(const GameState *state, char *out_cmd, size_t out_len) {

    int r, c, d;
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

#define PIECE_RANK(piece) \
    (strstr(piece, "King") ? 7 : \
    strstr(piece, "Guard") ? 6 : \
    strstr(piece, "Elephant") ? 5 : \
    strstr(piece, "Car") ? 4 : \
    strstr(piece, "Horse") ? 3 : \
    strstr(piece, "Cannon") ? 2 : \
    strstr(piece, "Soldier") ? 1 : 0)

#define IS_MY(piece) \
    (strcmp(state->my_color, "") != 0 && strstr(piece, state->my_color) != NULL)

#define IS_ENEMY(piece) \
    (strcmp(piece, "Covered") != 0 && \
     strcmp(piece, "Null") != 0 && \
     strcmp(state->my_color, "") != 0 && \
     strstr(piece, state->my_color) == NULL)

#define IN_BOARD(rr, cc) \
    ((rr) >= 0 && (rr) < BOARD_ROWS && (cc) >= 0 && (cc) < BOARD_COLS)

#define DIST(r1, c1, r2, c2) \
    (abs((r1) - (r2)) + abs((c1) - (c2)))

#define CAN_EAT(my_piece, target_piece) \
    ((strstr(my_piece, "Soldier") && strstr(target_piece, "King")) ? 1 : \
    ((strstr(my_piece, "King") && strstr(target_piece, "Soldier")) ? 0 : \
    (PIECE_RANK(my_piece) >= PIECE_RANK(target_piece))))

#define IS_DANGEROUS(enemy, my_piece) \
    (IS_ENEMY(enemy) && CAN_EAT(enemy, my_piece))

    // 1. 能吃就吃：一般棋
    {
        int best_r = -1, best_c = -1;
        int best_nr = -1, best_nc = -1;
        int best_score = -9999;

        for (r = 0; r < BOARD_ROWS; r++) {
            for (c = 0; c < BOARD_COLS; c++) {
                char *my_piece = (char *)state->board[r][c];

                if (!IS_MY(my_piece)) continue;
                if (strstr(my_piece, "Cannon")) continue;

                for (d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (!IN_BOARD(nr, nc)) continue;

                    char *target = (char *)state->board[nr][nc];

                    if (!IS_ENEMY(target)) continue;
                    if (!CAN_EAT(my_piece, target)) continue;

                    int score = PIECE_RANK(target) * 10 - PIECE_RANK(my_piece);

                    if (score > best_score) {
                        best_score = score;
                        best_r = r;
                        best_c = c;
                        best_nr = nr;
                        best_nc = nc;
                    }
                }
            }
        }

        if (best_r != -1) {
            snprintf(out_cmd, out_len, "%d %d %d %d\n", best_r, best_c, best_nr, best_nc);
            printf("AI eat: %s", out_cmd);
            return;
        }
    }

    //2. 炮吃：中間必須隔一顆棋子
    
    {
        int best_r = -1, best_c = -1;
        int best_nr = -1, best_nc = -1;
        int best_score = -9999;

        for (r = 0; r < BOARD_ROWS; r++) {
            for (c = 0; c < BOARD_COLS; c++) {
                char *my_piece = (char *)state->board[r][c];

                if (!IS_MY(my_piece)) continue;
                if (!strstr(my_piece, "Cannon")) continue;

                for (d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    int middle = 0;

                    while (IN_BOARD(nr, nc)) {
                        char *target = (char *)state->board[nr][nc];

                        if (strcmp(target, "Null") != 0) {
                            if (middle == 0) {
                                middle = 1;
                            } else {
                                if (IS_ENEMY(target)) {
                                    int score = PIECE_RANK(target) * 10;

                                    if (score > best_score) {
                                        best_score = score;
                                        best_r = r;
                                        best_c = c;
                                        best_nr = nr;
                                        best_nc = nc;
                                    }
                                }
                                break;
                            }
                        }

                        nr += dr[d];
                        nc += dc[d];
                    }
                }
            }
        }

        if (best_r != -1) {
            snprintf(out_cmd, out_len, "%d %d %d %d\n", best_r, best_c, best_nr, best_nc);
            printf("AI cannon eat: %s", out_cmd);
            return;
        }
    }

    //3. 被威脅就逃
    {
        int escape_r = -1, escape_c = -1;
        int escape_nr = -1, escape_nc = -1;
        int best_safety = -9999;

        for (r = 0; r < BOARD_ROWS; r++) {
            for (c = 0; c < BOARD_COLS; c++) {
                char *my_piece = (char *)state->board[r][c];
                int threatened = 0;

                if (!IS_MY(my_piece)) continue;

                for (d = 0; d < 4; d++) {
                    int er = r + dr[d];
                    int ec = c + dc[d];

                    if (!IN_BOARD(er, ec)) continue;

                    char *enemy = (char *)state->board[er][ec];

                    if (IS_DANGEROUS(enemy, my_piece)) {
                        threatened = 1;
                    }
                }

                if (!threatened) continue;

                for (d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (!IN_BOARD(nr, nc)) continue;
                    if (strcmp(state->board[nr][nc], "Null") != 0) continue;

                    int safe = 1;
                    int nearest_enemy = 999;

                    for (int er = 0; er < BOARD_ROWS; er++) {
                        for (int ec = 0; ec < BOARD_COLS; ec++) {
                            char *enemy = (char *)state->board[er][ec];

                            if (!IS_ENEMY(enemy)) continue;

                            int dist = DIST(nr, nc, er, ec);

                            if (dist == 1 && IS_DANGEROUS(enemy, my_piece)) {
                                safe = 0;
                            }

                            if (dist < nearest_enemy) {
                                nearest_enemy = dist;
                            }
                        }
                    }

                    if (safe && nearest_enemy > best_safety) {
                        best_safety = nearest_enemy;
                        escape_r = r;
                        escape_c = c;
                        escape_nr = nr;
                        escape_nc = nc;
                    }
                }
            }
        }

        if (escape_r != -1) {
            snprintf(out_cmd, out_len, "%d %d %d %d\n", escape_r, escape_c, escape_nr, escape_nc);
            printf("AI escape: %s", out_cmd);
            return;
        }
    }

    //4. 沒有可以吃、也沒有要逃：先翻棋

    {
        int pos = select_target_position(state);

        if (pos != -1) {
            r = pos / BOARD_COLS;
            c = pos % BOARD_COLS;

            snprintf(out_cmd, out_len, "%d %d\n", r, c);
            printf("AI flip: %s", out_cmd);
            return;
        }
    }

    //5. 沒棋可翻才走：安全走一步

    {
        int best_r = -1, best_c = -1;
        int best_nr = -1, best_nc = -1;
        int best_score = -9999;

        for (r = 0; r < BOARD_ROWS; r++) {
            for (c = 0; c < BOARD_COLS; c++) {
                char *my_piece = (char *)state->board[r][c];

                if (!IS_MY(my_piece)) continue;

                for (d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (!IN_BOARD(nr, nc)) continue;
                    if (strcmp(state->board[nr][nc], "Null") != 0) continue;

                    int safe = 1;
                    int nearest_enemy = 999;

                    for (int er = 0; er < BOARD_ROWS; er++) {
                        for (int ec = 0; ec < BOARD_COLS; ec++) {
                            char *enemy = (char *)state->board[er][ec];

                            if (!IS_ENEMY(enemy)) continue;

                            int dist = DIST(nr, nc, er, ec);

                            if (dist == 1 && IS_DANGEROUS(enemy, my_piece)) {
                                safe = 0;
                            }

                            if (dist < nearest_enemy) {
                                nearest_enemy = dist;
                            }
                        }
                    }

                    if (!safe) continue;

                    int score = nearest_enemy;

                    if (score > best_score) {
                        best_score = score;
                        best_r = r;
                        best_c = c;
                        best_nr = nr;
                        best_nc = nc;
                    }
                }
            }
        }

        if (best_r != -1) {
            snprintf(out_cmd, out_len, "%d %d %d %d\n", best_r, best_c, best_nr, best_nc);
            printf("AI safe move: %s", out_cmd);
            return;
        }
    }

    //6. 真的沒辦法：隨便找一個合法移動，避免送空指令
    {
        for (r = 0; r < BOARD_ROWS; r++) {
            for (c = 0; c < BOARD_COLS; c++) {
                char *my_piece = (char *)state->board[r][c];

                if (!IS_MY(my_piece)) continue;

                for (d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (!IN_BOARD(nr, nc)) continue;
                    if (strcmp(state->board[nr][nc], "Null") != 0) continue;

                    snprintf(out_cmd, out_len, "%d %d %d %d\n", r, c, nr, nc);
                    printf("AI fallback move: %s", out_cmd);
                    return;
                }
            }
        }
    }

    //7. 完全沒有合法步：送空

    snprintf(out_cmd, out_len, "");

#undef PIECE_RANK
#undef IS_MY
#undef IS_ENEMY
#undef IN_BOARD
#undef DIST
#undef CAN_EAT
#undef IS_DANGEROUS
}
static void game_loop(void) {
    char update_buf[UPDATE_BUF_SIZE];
    char action_cmd[ACTION_BUF_SIZE];
    GameState state;

    while (1) {
        receive_update(update_buf, sizeof(update_buf));
        if (strlen(update_buf) == 0) {
            continue;
        }

        parse_system_update(update_buf, &state);
        print_board_for_debug(&state);

        if (state.game_over) {
            printf("Game Over. Winner: %s\n", state.winner);
            break;
        }

        if (!is_my_turn(&state)) {
            printf("Waiting opponent move...\n");
            continue;
        }

        Sleep(2000);
        build_action_command(&state, action_cmd, sizeof(action_cmd));
        send_action(action_cmd);
    }
}

int main(void) {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    if (init_connection() != 0) {
        printf("Connection failed.\n");
        return 1;
    }

    auto_join_room();
    game_loop();
    close_connection();
    return 0;
}