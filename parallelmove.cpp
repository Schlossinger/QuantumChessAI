#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <iomanip>

// Constants for the chessboard
constexpr int BOARD_SIZE = 8;
constexpr int NUM_FIELDS = BOARD_SIZE * BOARD_SIZE;
constexpr int MAX_PIECES = 32; // 16 per side

// Piece types
enum PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING, NONE };

// Colors
enum Color { WHITE, BLACK, NO_COLOR };

// Structure for a piece
struct Piece {
    PieceType type = NONE;
    Color color = NO_COLOR;
    int index = -1; // unique index (0..31)
    int pos = -1;   // field index 0..63
    double share = 0.0; // share in %
};

// For each field: up to 32 pieces
struct FieldShares {
    std::array<Piece, MAX_PIECES> shares{}; // pieces per field
    double sum_white = 0.0;
    double sum_black = 0.0;
    double sum_total = 0.0;
    double empty_share = 100.0;
};

// Helper functions
int toIndex(int row, int col) { return row * BOARD_SIZE + col; }
std::pair<int, int> toCoord(int idx) { return {idx / BOARD_SIZE, idx % BOARD_SIZE}; }

// Initialization of pieces (only pawns and knights as demo)
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

// Calculation of legal moves for pawns and knights (simplified demo)
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

// Distribution of pieces to target fields
void distributeShares(const std::vector<Piece>& pieces, std::array<FieldShares, NUM_FIELDS>& board) {
    // Clear fields
    for (auto& f : board) {
        for (auto& p : f.shares) p = Piece{};
        f.sum_white = f.sum_black = f.sum_total = 0.0;
        f.empty_share = 100.0;
    }
    // Distribution
    for (const auto& p : pieces) {
        auto moves = getMoves(p);
        double share_per_move = moves.empty() ? 0.0 : p.share / (moves.size() + 1); // +1 for origin field
        // Origin field
        board[p.pos].shares[p.index] = p;
        board[p.pos].shares[p.index].share = share_per_move;
        // Target fields
        for (int m : moves) {
            board[m].shares[p.index] = p;
            board[m].shares[p.index].share = share_per_move;
        }
    }
    // Calculate sums
    for (int f = 0; f < NUM_FIELDS; ++f) {
        double sum_white = 0.0, sum_black = 0.0, sum_total = 0.0;
        for (int i = 0; i < MAX_PIECES; ++i) {
            double s = board[f].shares[i].share;
            sum_total += s;
            if (board[f].shares[i].color == WHITE) sum_white += s;
            else if (board[f].shares[i].color == BLACK) sum_black += s;
        }
        board[f].sum_white = sum_white;
        board[f].sum_black = sum_black;
        board[f].sum_total = sum_total;
        board[f].empty_share = 100.0 - sum_total;
    }
}

// Output as heatmap (only sums white/black)
void printHeatmap(const std::array<FieldShares, NUM_FIELDS>& board) {
    std::cout << "\nHeatmap White (Sum of piece shares per field):\n";
    for (int r = 0; r < BOARD_SIZE; ++r) {
        for (int c = 0; c < BOARD_SIZE; ++c) {
            std::cout << std::setw(6) << std::fixed << std::setprecision(1)
                      << board[toIndex(r, c)].sum_white;
        }
        std::cout << '\n';
    }
    std::cout << "\nHeatmap Black (Sum of piece shares per field):\n";
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
    // For further iterations: write shares from board back to pieces and redistribute
    // (Here only one iteration as demo)
    return 0;
}
