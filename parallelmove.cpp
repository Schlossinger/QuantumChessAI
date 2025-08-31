#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <iomanip>

// Constants for the chessboard
constexpr int BOARD_SIZE = 8;
constexpr int NUM_FIELDS = BOARD_SIZE * BOARD_SIZE;
constexpr int MAX_FIGURES = 32; // 16 per side

// Piece types
enum PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE };

// Colors
enum Color { WHITE, BLACK, NO_COLOR };

// Structure for a piece
struct Piece {
    PieceType type;
    Color color;
    int index; // unique index (0..31)
    int pos;   // field index 0..63
    double share; // occupancy share in %
};

// For each field: up to 32 piece shares
struct FieldShares {
    std::array<double, MAX_FIGURES> shares{}; // share per piece
    double sum_white = 0.0;
    double sum_black = 0.0;
    double sum_total = 0.0;
    double empty_share = 100.0;
};

// Helper functions
int toIndex(int row, int col) { return row * BOARD_SIZE + col; }
std::pair<int, int> toCoord(int idx) { return {idx / BOARD_SIZE, idx % BOARD_SIZE}; }

// Initialize pieces (only pawns and knights for demo)
std::vector<Piece> initPieces() {
    std::vector<Piece> pieces;
    int idx = 0;
    // White pawns
    for (int i = 0; i < 8; ++i)
        pieces.push_back({PAWN, WHITE, idx++, toIndex(1, i), 100.0});
    // White knights
    pieces.push_back({KNIGHT, WHITE, idx++, toIndex(0, 1), 100.0});
    pieces.push_back({KNIGHT, WHITE, idx++, toIndex(0, 6), 100.0});
    // Black pawns
    for (int i = 0; i < 8; ++i)
        pieces.push_back({PAWN, BLACK, idx++, toIndex(6, i), 100.0});
    // Black knights
    pieces.push_back({KNIGHT, BLACK, idx++, toIndex(7, 1), 100.0});
    pieces.push_back({KNIGHT, BLACK, idx++, toIndex(7, 6), 100.0});
    return pieces;
}

// Calculate legal moves for pawns and knights (simplified demo)
std::vector<int> getMoves(const Piece& p) {
    std::vector<int> moves;
    auto [row, col] = toCoord(p.pos);
    if (p.type == PAWN) {
        int dir = (p.color == WHITE) ? 1 : -1;
        int nextRow = row + dir;
        if (nextRow >= 0 && nextRow < BOARD_SIZE) {
            moves.push_back(toIndex(nextRow, col));
            // Double move at the beginning
            if ((p.color == WHITE && row == 1) || (p.color == BLACK && row == 6)) {
                int dblRow = row + 2 * dir;
                if (dblRow >= 0 && dblRow < BOARD_SIZE)
                    moves.push_back(toIndex(dblRow, col));
            }
        }
    } else if (p.type == KNIGHT) {
        const int d[8][2] = {{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2},{1,-2},{2,-1}};
        for (auto& off : d) {
            int r = row + off[0], c = col + off[1];
            if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE)
                moves.push_back(toIndex(r, c));
        }
    }
    return moves;
}

// Distribute piece shares to target squares
void distributeShares(const std::vector<Piece>& pieces, std::array<FieldShares, NUM_FIELDS>& board) {
    // Empty fields
    for (auto& f : board) {
        f.shares.fill(0.0);
        f.sum_white = f.sum_black = f.sum_total = 0.0;
        f.empty_share = 100.0;
    }
    // Distribute shares
    for (const auto& p : pieces) {
        auto moves = getMoves(p);
        double share_per_move = moves.empty() ? 0.0 : p.share / (moves.size() + 1); // +1 for origin square
        // Share on origin square
        board[p.pos].shares[p.index] += share_per_move;
        // To target squares
        for (int m : moves)
            board[m].shares[p.index] += share_per_move;
    }
    // Calculate sums
    for (int f = 0; f < NUM_FIELDS; ++f) {
        double sum_white = 0.0, sum_black = 0.0, sum_total = 0.0;
        for (int i = 0; i < MAX_FIGURES; ++i) {
            double s = board[f].shares[i];
            sum_total += s;
            if (i < 16) sum_white += s;
            else sum_black += s;
        }
        board[f].sum_white = sum_white;
        board[f].sum_black = sum_black;
        board[f].sum_total = sum_total;
        board[f].empty_share = 100.0 - sum_total;
    }
}

// Output as heatmap (only sums white/black)
void printHeatmap(const std::array<FieldShares, NUM_FIELDS>& board) {
    std::cout << "\nHeatmap White (sum of piece shares per square):\n";
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            std::cout << std::setw(6) << std::fixed << std::setprecision(1)
                      << board[toIndex(r, c)].sum_white;
        }
        std::cout << '\n';
    }
    std::cout << "\nHeatmap Black (sum of piece shares per square):\n";
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            std::cout << std::setw(6) << std::fixed << std::setprecision(1)
                      << board[toIndex(r, c)].sum_black;
        }
        std::cout << '\n';
    }
}

int main() {
    // Initialization
    auto pieces = initPieces();
    std::array<FieldShares, NUM_FIELDS> board;
    distributeShares(pieces, board);
    printHeatmap(board);
    // For further iterations: write shares from board back into pieces and distribute again
    // (Here only one iteration as demo)
    return 0;
}
