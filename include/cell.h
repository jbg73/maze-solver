#ifndef MAZE_SOLVER_CELL_H
#define MAZE_SOLVER_CELL_H

#include <iostream>
#include <vector>
#include <globals.h>

/***********************************************************************
 * Cell object definition
 ***********************************************************************/ 
struct Cell{
    int x;
    int y;
    bool walls[4];
    std::vector<DIRECTION> visited_neighbours;

    Cell() : x{0}, y{0}, walls{true,true,true,true}{}
    Cell(int x_val, int y_val, bool walls_vals[4]) : x{x_val}, y{y_val}{
        for(int i = 0; i < 4; i++){
            walls[i] = walls_vals[i];
        }
    }

    // void ClearVisitedCells(){visited_cells.clear();}
    // bool IsCellVisited() const;
    // bool IsCellVisited(DIRECTION dir) const;
    // bool IsCellVisited(int pos_x, int pos_y) const;
    bool HasNonVisitedNeighbours() const;
    bool HasLegalNonVisitedNeighbours() const;
    bool IsNeighbourVisited(DIRECTION dir) const;
    void UpdateVisitedNeighbours(DIRECTION dir);
    // DIRECTION SelectRandomPossibleDirection() const;
    // Cell GetNextCell(DIRECTION dir) const;
    std::vector<std::pair<int,int>> GetCellEdges() const;
};

#endif