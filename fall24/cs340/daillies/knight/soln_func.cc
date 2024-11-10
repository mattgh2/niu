#include <queue>
#include <array>
#include <algorithm>

typedef std::pair<std::pair<int,int>, int> node;
auto in_bounds(const std::pair<int,int> &move,  node &current_node) -> bool;

auto captured(int knight_r, int knight_c, int pawn_r, int pawn_c) -> int {

    if ((knight_r < 0 || knight_r > 7) || (pawn_r < 0 || pawn_r > 7)) return -1;
    if (knight_r == pawn_r && knight_c == pawn_c) return -1;

    auto captured_pawn = [&](const node &current_node) { return (current_node.first.first == pawn_r && current_node.first.second == pawn_c); };
    // Store move positions.
    static std::array<std::pair<int,int>, 8> knight_moves = {{{2,1},{2,-1},{-2,1},{-2, -1}, {1,2},{1,-2}, {-1,2},{-1,-2}}};

    std::queue<node> q;
    std::array<std::array<int, 8>, 8> visited = {0};

    q.push(node({knight_r, knight_c}, 0));
    visited[knight_r][knight_c] = 1;
    while (!q.empty()) {
        node current_node = q.front(); q.pop();
        
        if (captured_pawn(current_node)) return current_node.second;

        std::for_each(knight_moves.begin(), knight_moves.end(), [&current_node, &q, &visited](const auto &move) {
                    if (in_bounds(move, current_node)) {
                        node adjacent_node = {{current_node.first.first + move.first, current_node.first.second + move.second}, current_node.second + 1};
                        if (visited[adjacent_node.first.first][adjacent_node.first.second] == 0) {
                            q.push(adjacent_node);
                            visited[current_node.first.first][current_node.first.second] = 1;
                        }
                    }
                });
    }
    return -1;
}
()

auto in_bounds(const std::pair<int,int> &move,  node &current_node) -> bool {
    return ( current_node.first.first + move.first <= 7 && current_node.first.first + move.first >= 0)
        && (current_node.first.second + move.second <= 7 && current_node.first.second >= 0);
}
// int main() {
//     int kr = 3, kc = 3, pr = 3, pc = 4;
//
//     std::cout << captured(kr,kc,pr,pc) << '\n';
// }
