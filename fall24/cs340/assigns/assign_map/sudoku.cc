/************************************************************************************
* NIU CSCI 340 Section 3
* Assignment # 5 
* Matt Warner - z2004200
* *
* I certify that everything I am submitting is either provided by the professor for use in *
* the assignment, or work done by me personally. I understand that if I am caught submitting *
* the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic *
* Misconduct and will be punished as such. *
* *
* Implementation of a sudoku board.
* 
************************************************************************************/
// Implementations of the sudoku functions go in this file
// Details can be found in README.md

// This will be compiled to sudoku.o by the Makefile and linked when needed


#include "settings.h"
#include "sudoku.h"

// Recursive functions for removing possibilities from neighboring cells.
auto r_remove_from_row(SUDOKUGRID &grid, int row, int col, int key, int) -> int;
auto r_remove_from_col(SUDOKUGRID &grid, int row, int col, int key, int) -> int;
auto r_remove_from_subgrid(SUDOKUGRID &grid, int row, int col, int key, auto endpoints) -> int;


void set_sudoku_cell_known(SUDOKUGRID &grid, int row, int col, int solution) {

    // Get the cell.
    std::set<int> * cell = &grid.atrc(row,col);

    // Clear everything from the cell and insert the solution.
    cell->clear();
    cell->insert(solution);

}

void set_sudoku_cell_unknown(SUDOKUGRID &grid, int row, int col) {
    // Get the cell in the grid.
    std::set<int> * cell = &grid.atrc(row,col);

    // Clear the cell before insertion.
    cell->clear();
    for (size_t i = 1; i < 10; ++i) {
        cell->insert(i);
    }
    
}

// remove a specific possibility from the sudoku cell given
void remove_sudoku_option(SUDOKUGRID &grid, int row, int col, int value) {
    grid.atrc(row,col).erase(value);
}

void print_sudoku_grid(std::ostream & ost, const SUDOKUGRID &grid, char unknown, char impossible) {
    // If col_count == 3 print | 
    // If row_count == 3 print a dashed hline
    auto row_iterator = grid.rowbegin(0);
    auto [row_count, col_count] = std::pair(0,0);

    auto print_cell = [&ost, col_count](const auto &value) {
        (col_count == 0) ? ost << ' ' << value << ' ' : ost << value << ' ';
    };

    while (row_count < 9) {


        if (row_iterator->size() == 1) {
            print_cell(*row_iterator->begin());
        }

        else { 
            print_cell(unknown);
        }

        if ((col_count + 1) % 3 == 0 && (col_count + 1) != 9) {
            ost << "|";
        }

        if (++col_count == 9) {
            ost << "\n";
            col_count = 0;
            row_iterator = grid.rowbegin(++row_count);
            
            if (row_count % 3 == 0 && row_count != 9) {
                    ost << "---------|---------|---------";
                ost << '\n';
            }
        }
        else {
            ++row_iterator;
        }
    }
    ost << '\n';
}
////////////////////////////////////////////////////////////////////////////////
// This one is provided. You do not need to change it.
////////////////////////////////////////////////////////////////////////////////
int handle_sudoku_cell(SUDOKUGRID &grid, int row, int col) {
  int count = 0;

  count += handle_row_for_cell(grid, row, col); 
  count += handle_col_for_cell(grid, row, col); 
  count += handle_subgrid_for_cell(grid, row, col); 

  return count; }

int handle_row_for_cell(SUDOKUGRID &grid, int row, int col) {

    // Get the cell.
    std::set<int> * cell = &grid.atrc(row, col);

    // If the cell is known, delete the value from all cells in this row.
    if (cell->size() == 1) {
        return r_remove_from_row(grid, row, 0, *cell->begin(), col);
    }

    return 0;
}
int handle_col_for_cell(SUDOKUGRID &grid, int row, int col) {

    // Get the cell.
    std::set<int> * cell = &grid.atrc(row,col);

    // If the cell is known, delete the value from all cells in this column.
    if (cell->size() == 1) {
        return  r_remove_from_col(grid, 0, col, *cell->begin(), row);
    }

    return 0; 
}

int handle_subgrid_for_cell(SUDOKUGRID &grid, int row, int col) {
    std::set<int> * cell = &grid.atrc(row,col);
    
    // If the cell is known, delete the value from all cells in the same 3x3 subgrid.
    if (cell->size() == 1) {
        
        // Taking the floor of (row / 3), then multiplying 
        // the result by 3 yields the starting row for the subgrib.
        int start_row = (row / 3) * 3;
        // Do the same for the column.
        int start_col = (col / 3) * 3;

        // Anyonymous struct to hold the subgrids ending position.
        struct { int stop_row; int stop_col; int init_row; int init_col;} endpoints = {start_row + 3, start_col + 3, row, col};

        // Recursivly delete all possibilities in the subgrid.
        return r_remove_from_subgrid(grid, start_row, start_col, *cell->begin(), endpoints);
    }
    return 0;

}

bool load_sudoku_grid(const std::string &filename, SUDOKUGRID &grid) {

    // Open the file.
    std::ifstream input_file(filename);

    // Check if file failed to open.
    if (input_file.fail()) {
        std::cerr << "Error opening file: " << filename;
        return false;
    }

    // Get the width and height.
    int width, height;
    input_file >> width >> height;

    // Check if width and height meet size requirements.
    if (width != 9 || height != 9) {
        return false;
    }

    // Resize grid to correct size.
    initialize_grid(grid);

    auto [row_count, row_insertion_count] = std::pair(0,0);
    auto first = grid.rowbegin(row_count);

    // Load input from file into grid. 
    while (input_file) {
        int value;
        
        // Get the current input value.
        input_file >> value;


        // If the value is not known, fill the set with all possibilities.
        if (value == 0) {
            for (size_t i = 1; i < 10; ++i) {
                (*first).insert(i);
            }
        }
        // Insert the value into the set.
        else{
            (*first).insert(value);
        } 

        ++first; ++row_insertion_count;

        // Hit the end of the current row, proceed to next.
        if (row_insertion_count == 9) {

            // Sucessfully filled the entire grid.
            if (++row_count == 9) {
                break;
            }
            else {
                // Move first to the start of the next row.
                first = grid.rowbegin(row_count);
                // Reset insertion count back to 0.
                row_insertion_count = 0;
            }
        }
    }

    return row_count == 9 ? true : false;
}

////////////////////////////////////////////////////////////////////////////////
// This is what the implementation looks like for grid_row_major,
//   if you're using another SUDOKUGRID type, you will likely have to change it.
////////////////////////////////////////////////////////////////////////////////
void initialize_grid(SUDOKUGRID &grid) {
  grid.resize(9,9);
}

auto r_remove_from_row(SUDOKUGRID &grid, int row, int col, int key, int init_col) -> int {

    int count = 0;
    // Base case: we are past the last column.
    if (col >= 9) {
        return count;
    }

    // Erase the key from the cell.
    if (col != init_col) {
        count += grid.atrc(row,col).erase(key);
    }

    // Recursive call to erase the key from all cells in the row.
    int counts_from_below = r_remove_from_row(grid, row, col + 1, key, init_col);

    // Get the total count.
    count += counts_from_below;

    return count;
}

auto r_remove_from_col(SUDOKUGRID &grid, int row, int col, int key, int init_row) -> int {
    int count = 0;
    if (row >= 9) {
        return count;
    }
    if (row != init_row) {
        count += grid.atrc(row,col).erase(key);
    }

    int counts_from_below = r_remove_from_col(grid, row + 1, col, key, init_row);

    count += counts_from_below;

    return count;

}

auto r_remove_from_subgrid(SUDOKUGRID &grid, int row, int col, int key, auto endpoints ) -> int {
    int count = 0;

    // Erase the the key from the set of possibilities.
    if ((row != endpoints.init_row) || (col != endpoints.init_col)) {
        count += grid.atrc(row,col).erase(key);
    }

    auto [counts_from_below_1, counts_from_below2] = std::pair(0,0);

    // Check if col is still in bounds.
    if (col < endpoints.stop_col - 1) {
        // Go the the next column
        // Retrieve all counts from recursive calls.
        counts_from_below_1 = r_remove_from_subgrid(grid,row, col + 1, key, endpoints);
    }
    // If there is still row left.
    if (row < endpoints.stop_row - 1) {
        // If thet column is at its limit.
        if (col == endpoints.stop_col - 1) {
            // Go to the next row, resetting column back to initial position.
            // Retrieve all counts from recursive calls.
            counts_from_below2 = r_remove_from_subgrid(grid, row + 1, endpoints.stop_col - 3, key, endpoints);
        }
    }

    // Get the total count of succesful erase operations.
    count += counts_from_below_1 + counts_from_below2;

    return count;
}


